/*
 * LittleFS CLI-style utilities (no dependency on command framework)
 */

#ifndef LFS_CLI_UTILS_H
#define LFS_CLI_UTILS_H

#include "lfs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief List directory contents (similar to UNIX 'ls')
 *
 * Traverses the specified path in LittleFS and prints directory entries
 * (files and subdirectories) using the configured logging/print routine.
 *
 * This utility is intended for debugging, inspection, or CLI interaction.
 *
 * @param lfs  Pointer to initialized LittleFS instance
 * @param path Directory path to list (must be valid, e.g., "/", "/dir")
 *
 * @return 0 on success
 * @return Negative error code on failure (e.g., path not found, IO error)
 *
 * @note Behavior depends on how underlying print/log API formats output.
 * @note Returned data is printed, not returned to caller.
 */
int lfs_util_ls(lfs_t *lfs, const char *path);


/**
 * @brief Dump file contents in hex/text format
 *
 * Opens the specified file and prints its contents using either hex dump
 * or human-readable text formatting, starting from a specified offset.
 *
 * Useful for inspecting small configuration files, debugging binary
 * structures, or examining corrupted data.
 *
 * @param lfs     Pointer to initialized LittleFS instance
 * @param filename File name to read (absolute or relative path)
 * @param offset   Starting byte offset (0-based)
 * @param size     Maximum number of bytes to read (0 = until EOF)
 *
 * @return 0 on success
 * @return Negative error code on failure (file not found, IO error, etc.)
 *
 * @note Large files may generate substantial output; use responsibly.
 * @note If size == 0, reads until end-of-file.
 * @note Output format depends on implementation of print routine.
 */
int lfs_util_cat(lfs_t *lfs, const char *filename,
                 uint32_t offset, uint32_t size);


/**
 * @brief Remove a file or directory (optional recursive mode)
 *
 * Deletes the specified file or directory. If recursive mode is enabled
 * and the target is a directory, all nested files and subdirectories are
 * deleted recursively.
 *
 * @param lfs       Pointer to initialized LittleFS instance
 * @param name      File or directory name to remove
 * @param recursive If true, perform recursive deletion for directories
 *
 * @return 0 on success
 * @return Negative error code on failure (e.g., not found, access denied)
 *
 * @warning Recursive deletion is potentially destructive—ensure the path
 *          is valid and intentional before use.
 *
 * @note For non-recursive mode, attempting to delete a directory may fail.
 * @note Recursive behavior depends on properly implemented directory walk.
 */
int lfs_util_rm(lfs_t *lfs, const char *name, bool recursive);


/**
 * @brief Delete all files and directories from LittleFS (format-like)
 *
 * Erases all user-accessible objects stored in the filesystem by walking
 * the root directory and deleting all files and subdirectories.
 *
 * Unlike a full format operation, this function typically does NOT erase
 * filesystem metadata, block structures, or configuration headers.
 *
 * Proper implementation depends on lfs_util_rm() to handle recursive
 * directory removal.
 *
 * @param lfs Pointer to initialized LittleFS instance
 *
 * @return 0 on success
 * @return Negative error code on partial/complete failure
 *
 * @warning This operation is destructive; all data is permanently lost.
 *
 * @note May be slower than a raw block erase, depending on filesystem size.
 * @note Useful for "factory reset" operations without remounting FS.
 */
int lfs_util_format(lfs_t *lfs);

#ifdef __cplusplus
}
#endif

#endif /* LFS_CLI_UTILS_H */