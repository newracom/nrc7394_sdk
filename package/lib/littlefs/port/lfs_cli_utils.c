#include <stdio.h>
#include <string.h>
#include "lfs.h"
#include "lfs_cli_utils.h"
#include "lfs_file_utils.h"

/* internal helper: recursive dir removal */
static int lfs_util_remove_dir_recursive(lfs_t *lfs, const char *path);

int lfs_util_ls(lfs_t *lfs, const char *path)
{
    lfs_dir_t dir;
    struct lfs_info info;
    int ret;
    uint32_t total_size = 0;
    uint32_t file_count = 0;

    if (!path) {
        path = "/";
    }

    ret = lfs_dir_open(lfs, &dir, path);
    if (ret < 0) {
        printf("Failed to open directory '%s': %d\n", path, ret);
        return ret;
    }

    printf("%-20s %10s\n", "Name", "Size");
    printf("----------------------------------------\n");

    while (1) {
        ret = lfs_dir_read(lfs, &dir, &info);
        if (ret < 0) {
            printf("Failed to read directory: %d\n", ret);
            lfs_dir_close(lfs, &dir);
            return ret;
        }
        if (ret == 0)
            break;

        if (strcmp(info.name, ".") == 0 || strcmp(info.name, "..") == 0)
            continue;

        if (info.type == LFS_TYPE_REG) {
            printf("%-20s %10lu bytes\n",
                   info.name, (unsigned long)info.size);
            total_size += info.size;
            file_count++;
        } else if (info.type == LFS_TYPE_DIR) {
            printf("%-20s %10s\n", info.name, "<DIR>");
        }
    }

    lfs_dir_close(lfs, &dir);

    printf("----------------------------------------\n");
    printf("Total: %lu files, %lu bytes\n",
           (unsigned long)file_count, (unsigned long)total_size);

    return 0;
}

int lfs_util_cat(lfs_t *lfs, const char *filename,
         uint32_t offset, uint32_t size)
{
    struct lfs_info info;
    int ret;

    ret = lfs_stat(lfs, filename, &info);
    if (ret < 0) {
        printf("File not found: %s\n", filename);
        return ret;
    }

    if (offset >= info.size) {
        printf("Offset exceeds file size (%lu >= %lu)\n",
               (unsigned long)offset, (unsigned long)info.size);
        return -1;
    }

    if (size == 0 || offset + size > info.size) {
        size = info.size - offset;
    }

    printf("File: %s (offset: %lu, size: %lu/%lu bytes)\n",
           filename,
           (unsigned long)offset,
           (unsigned long)size,
           (unsigned long)info.size);
    printf("----------------------------------------\n");

    /* 이미 lfs_file_print_data가 있으니 그걸 활용하는 게 깔끔 */
    ret = lfs_file_print_data(lfs,
                  filename,
                  LFS_PRINT_HEX | LFS_PRINT_STRING,
                  offset,
                  size);
    if (ret < 0) {
        printf("Failed to print file data: %d\n", ret);
    }

    return ret;
}

static int lfs_util_remove_dir_recursive(lfs_t *lfs, const char *path)
{
    lfs_dir_t dir;
    struct lfs_info info;
    int ret;

    ret = lfs_dir_open(lfs, &dir, path);
    if (ret < 0) {
        printf("Failed to open dir '%s': %d\n", path, ret);
        return ret;
    }

    while (1) {
        ret = lfs_dir_read(lfs, &dir, &info);
        if (ret < 0) {
            printf("Failed to read dir '%s': %d\n", path, ret);
            lfs_dir_close(lfs, &dir);
            return ret;
        }
        if (ret == 0)
            break;

        if (strcmp(info.name, ".") == 0 || strcmp(info.name, "..") == 0)
            continue;

        char child_path[512];
        snprintf(child_path, sizeof(child_path),
             "%s/%s", path, info.name);

        if (info.type == LFS_TYPE_DIR) {
            ret = lfs_util_remove_dir_recursive(lfs, child_path);
            if (ret < 0)
                return ret;
        } else {
            ret = lfs_remove(lfs, child_path);
            if (ret < 0) {
                printf("Failed to remove file '%s': %d\n",
                       child_path, ret);
                return ret;
            }
        }
    }

    lfs_dir_close(lfs, &dir);

    ret = lfs_remove(lfs, path);
    if (ret < 0) {
        printf("Failed to remove dir '%s': %d\n", path, ret);
    }
    return ret;
}

int lfs_util_rm(lfs_t *lfs, const char *name, bool recursive)
{
    struct lfs_info info;
    int ret;

    ret = lfs_stat(lfs, name, &info);
    if (ret < 0) {
        printf("'%s' not found: %d\n", name, ret);
        return ret;
    }

    if (info.type == LFS_TYPE_DIR) {
        if (!recursive) {
            printf("'%s' is a directory (use recursive option)\n", name);
            return -1;
        }
        return lfs_util_remove_dir_recursive(lfs, name);
    } else {
        ret = lfs_remove(lfs, name);
        if (ret < 0) {
            printf("Failed to remove file '%s': %d\n", name, ret);
        }
        return ret;
    }
}

int lfs_util_format(lfs_t *lfs)
{
    lfs_dir_t dir;
    struct lfs_info info;
    int ret;
    uint32_t deleted_count = 0;

    ret = lfs_dir_open(lfs, &dir, "/");
    if (ret < 0) {
        printf("Failed to open root dir: %d\n", ret);
        return ret;
    }

    printf("Formatting filesystem...\n");

    while (1) {
        ret = lfs_dir_read(lfs, &dir, &info);
        if (ret < 0) {
            printf("Failed to read directory: %d\n", ret);
            lfs_dir_close(lfs, &dir);
            return ret;
        }
        if (ret == 0)
            break;

        if (strcmp(info.name, ".") == 0 || strcmp(info.name, "..") == 0)
            continue;

        if (info.type == LFS_TYPE_DIR) {
            ret = lfs_util_remove_dir_recursive(lfs, info.name);
        } else {
            ret = lfs_remove(lfs, info.name);
        }

        if (ret < 0) {
            printf("Failed to remove '%s': %d\n", info.name, ret);
        } else {
            deleted_count++;
        }
    }

    lfs_dir_close(lfs, &dir);

    printf("Format complete. %lu items deleted.\n",
           (unsigned long)deleted_count);

    return 0;
}
