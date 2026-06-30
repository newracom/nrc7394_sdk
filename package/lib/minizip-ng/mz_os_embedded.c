/* mz_os_embedded.c -- OS utilities for embedded (NRC FreeRTOS) port
   part of the minizip-ng project

   Only the minimal surface needed by mz_zip.c and mz_compat.c is
   provided.  Everything related to real filesystem paths / directory
   operations returns MZ_SUPPORT_ERROR because the embedded target uses
   LittleFS exclusively and those operations are not needed for the
   in-memory decompression use-case.

   SPDX-License-Identifier: Zlib
*/

#include "mz.h"
#include "mz_os.h"

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/***************************************************************************/
/* Path utilities used by mz_zip.c                                          */
/***************************************************************************/

int32_t mz_path_combine(char *path, const char *join, int32_t max_path) {
    int32_t path_len;
    if (!path || !join || max_path <= 0) return MZ_PARAM_ERROR;
    path_len = (int32_t)strlen(path);
    if (path_len > 0 && path[path_len - 1] != '/' && path[path_len - 1] != '\\') {
        if (path_len + 1 >= max_path) return MZ_BUF_ERROR;
        path[path_len]     = '/';
        path[path_len + 1] = '\0';
        path_len++;
    }
    if (path_len + (int32_t)strlen(join) + 1 > max_path) return MZ_BUF_ERROR;
    strcat(path, join);
    return MZ_OK;
}

int32_t mz_path_resolve(const char *path, char *target, int32_t max_target) {
    if (!path || !target || max_target <= 0) return MZ_PARAM_ERROR;
    strncpy(target, path, (size_t)(max_target - 1));
    target[max_target - 1] = '\0';
    return MZ_OK;
}

int32_t mz_path_has_slash(const char *path) {
    int32_t len;
    if (!path) return MZ_PARAM_ERROR;
    len = (int32_t)strlen(path);
    if (len == 0) return MZ_EXIST_ERROR;
    return (path[len - 1] == '/' || path[len - 1] == '\\') ? MZ_OK : MZ_EXIST_ERROR;
}

int32_t mz_path_get_filename(const char *path, const char **filename) {
    const char *p;
    if (!path || !filename) return MZ_PARAM_ERROR;
    p = strrchr(path, '/');
    if (!p) p = strrchr(path, '\\');
    *filename = p ? (p + 1) : path;
    return MZ_OK;
}

int32_t mz_path_remove_slash(char *path) {
    int32_t len;
    if (!path) return MZ_PARAM_ERROR;
    len = (int32_t)strlen(path);
    if (len > 0 && (path[len - 1] == '/' || path[len - 1] == '\\'))
        path[len - 1] = '\0';
    return MZ_OK;
}

int32_t mz_path_remove_filename(char *path) {
    char *p;
    if (!path) return MZ_PARAM_ERROR;
    p = strrchr(path, '/');
    if (!p) p = strrchr(path, '\\');
    if (p) *(p + 1) = '\0';
    return MZ_OK;
}

/***************************************************************************/
/* Time (not needed for read-only ZIP, but must link)                        */
/***************************************************************************/

int32_t mz_os_get_file_date(const char *path, time_t *modified_date,
                              time_t *accessed_date, time_t *creation_date) {
    MZ_UNUSED(path); MZ_UNUSED(modified_date);
    MZ_UNUSED(accessed_date); MZ_UNUSED(creation_date);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_os_set_file_date(const char *path, time_t modified_date,
                              time_t accessed_date, time_t creation_date) {
    MZ_UNUSED(path); MZ_UNUSED(modified_date);
    MZ_UNUSED(accessed_date); MZ_UNUSED(creation_date);
    return MZ_SUPPORT_ERROR;
}

/***************************************************************************/
/* File attribute stubs                                                      */
/***************************************************************************/

int32_t mz_os_get_file_attribs(const char *path, uint32_t *attributes) {
    MZ_UNUSED(path); MZ_UNUSED(attributes);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_os_set_file_attribs(const char *path, uint32_t attributes) {
    MZ_UNUSED(path); MZ_UNUSED(attributes);
    return MZ_SUPPORT_ERROR;
}

/***************************************************************************/
/* Directory / file existence stubs                                          */
/***************************************************************************/

int32_t mz_os_make_dir(const char *path) {
    MZ_UNUSED(path);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_os_file_exists(const char *path) {
    MZ_UNUSED(path);
    return MZ_EXIST_ERROR;
}

int32_t mz_os_is_dir(const char *path) {
    MZ_UNUSED(path);
    return MZ_EXIST_ERROR;
}

int32_t mz_os_is_symlink(const char *path) {
    MZ_UNUSED(path);
    return MZ_EXIST_ERROR;
}

int32_t mz_os_make_symlink(const char *path, const char *target_path) {
    MZ_UNUSED(path); MZ_UNUSED(target_path);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_os_read_symlink(const char *path, char *target_path, int32_t max_target_path) {
    MZ_UNUSED(path); MZ_UNUSED(target_path); MZ_UNUSED(max_target_path);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_os_rename(const char *source_path, const char *target_path) {
    MZ_UNUSED(source_path); MZ_UNUSED(target_path);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_os_unlink(const char *path) {
    MZ_UNUSED(path);
    return MZ_SUPPORT_ERROR;
}

/***************************************************************************/
/* Additional path utilities                                                  */
/***************************************************************************/

int32_t mz_path_append_slash(char *path, int32_t max_path, char slash) {
    int32_t len;
    if (!path || max_path <= 0) return MZ_PARAM_ERROR;
    len = (int32_t)strlen(path);
    if (len > 0 && path[len - 1] != '/' && path[len - 1] != '\\') {
        if (len + 2 > max_path) return MZ_BUF_ERROR;
        path[len]     = slash;
        path[len + 1] = '\0';
    }
    return MZ_OK;
}

int32_t mz_path_remove_extension(char *path) {
    char *p;
    if (!path) return MZ_PARAM_ERROR;
    p = strrchr(path, '.');
    if (p) *p = '\0';
    return MZ_OK;
}

int32_t mz_path_convert_slashes(char *path, char slash) {
    char *p;
    if (!path) return MZ_PARAM_ERROR;
    for (p = path; *p; p++)
        if (*p == '/' || *p == '\\') *p = slash;
    return MZ_OK;
}

int32_t mz_path_compare_wc(const char *path, const char *wildcard, uint8_t ignore_case) {
    /* Simple wildcard match: supports * and ? */
    if (!path || !wildcard) return MZ_PARAM_ERROR;
    while (*path && *wildcard && *wildcard != '*') {
        char a = *path, b = *wildcard;
        if (ignore_case) {
            if (a >= 'A' && a <= 'Z') a += 32;
            if (b >= 'A' && b <= 'Z') b += 32;
        }
        if (b != '?' && a != b) return MZ_EXIST_ERROR;
        path++; wildcard++;
    }
    if (*wildcard == '*') {
        while (*wildcard == '*') wildcard++;
        if (!*wildcard) return MZ_OK;
        while (*path) {
            if (mz_path_compare_wc(path, wildcard, ignore_case) == MZ_OK)
                return MZ_OK;
            path++;
        }
        return MZ_EXIST_ERROR;
    }
    return (*path == '\0' && *wildcard == '\0') ? MZ_OK : MZ_EXIST_ERROR;
}

/***************************************************************************/
/* Directory helpers (stubs)                                                 */
/***************************************************************************/

int32_t mz_dir_make(const char *path) {
    MZ_UNUSED(path);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_file_get_crc(const char *path, uint32_t *result_crc) {
    MZ_UNUSED(path); MZ_UNUSED(result_crc);
    return MZ_SUPPORT_ERROR;
}

int64_t mz_os_get_file_size(const char *path) {
    MZ_UNUSED(path);
    return -1;
}

DIR *mz_os_open_dir(const char *path) {
    MZ_UNUSED(path);
    return NULL;
}

struct dirent *mz_os_read_dir(DIR *dir) {
    MZ_UNUSED(dir);
    return NULL;
}

int32_t mz_os_close_dir(DIR *dir) {
    MZ_UNUSED(dir);
    return MZ_SUPPORT_ERROR;
}

uint64_t mz_os_ms_time(void) {
    /* Return 0 — time-based functions not needed for embedded decompress */
    return 0;
}

/***************************************************************************/
/* Unicode / UTF-8 stubs (no wchar support on embedded target)               */
/***************************************************************************/

wchar_t *mz_os_unicode_string_create(const char *string, int32_t encoding) {
    MZ_UNUSED(string); MZ_UNUSED(encoding);
    return NULL;
}

void mz_os_unicode_string_delete(wchar_t **string) {
    if (string) *string = NULL;
}

char *mz_os_utf8_string_create(const char *string, int32_t encoding) {
    char *copy;
    size_t len;
    MZ_UNUSED(encoding);
    if (!string) return NULL;
    len  = strlen(string) + 1;
    copy = (char *)mz_malloc(len);
    if (copy) memcpy(copy, string, len);
    return copy;
}

void mz_os_utf8_string_delete(char **string) {
    if (string && *string) { mz_free(*string); *string = NULL; }
}

/***************************************************************************/
/* Random — delegates to mz_crypt_rand                                       */
/***************************************************************************/

int32_t mz_os_rand(uint8_t *buf, int32_t size) {
    /* mz_crypt_rand is implemented in mz_crypt_mbedtls.c */
    extern int32_t mz_crypt_rand(uint8_t *buf, int32_t size);
    return mz_crypt_rand(buf, size);
}
