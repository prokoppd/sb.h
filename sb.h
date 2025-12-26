#ifndef STRINNG_BUILDER_H
#define STRINNG_BUILDER_H

#include <stdbool.h>
#include <stddef.h>

#ifndef SB_INITIAL_CAPACITY
#define SB_INITIAL_CAPACITY (32)
#endif // SB_INITIAL_CAPACITY

#ifndef SB_GROWTH_FACTOR
#define SB_GROWTH_FACTOR (2)
#endif // SB_GROWTH_FACTOR

#ifndef SB_MALLOC
#include <stdlib.h>
#define SB_MALLOC(size) malloc((size))
#endif // SB_MALLOC

#ifndef SB_REALLOC
#include <stdlib.h>
#define SB_REALLOC(ptr, size) realloc((ptr), (size))
#endif // SB_REALLOC

#ifndef SB_FREE
#include <stdlib.h>
#define SB_FREE(ptr) free((ptr))
#endif // SB_FREE

#ifndef SB_MEMCPY
#include <string.h>
#define SB_MEMCPY(dest, src, n) memcpy((dest), (src), (n))
#endif // SB_MEMCPY

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct StringBuilder
    {
        char  *buffer;
        size_t length;
        size_t capacity;
    } StringBuilder;
    // clang-format off
    StringBuilder *sb_create(size_t initial_capacity);

    StringBuilder *sb_from_cstr(const char *str);

    void sb_destroy(StringBuilder *sb);
    
    bool sb_append(StringBuilder *sb, const char *str);
    
    // void sb_append_fmt(StringBuilder *sb, const char *format, ...);
    
    void sb_clear(StringBuilder *sb);
    
    bool sb_resize(StringBuilder *sb, size_t new_capacity);
    
    const char *sb_cstr(const StringBuilder *sb);
    
    size_t sb_length(const StringBuilder *sb);
    // clang-format on

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // STRINNG_BUILDER_H

#ifdef SB_IMPLEMENTATION

static bool sb__ensure_capacity(StringBuilder *sb, size_t needed)
{
    if (!sb || !sb->buffer || (sb->capacity < (needed + 1))) return false;
    return true;
}

static bool sb__realloc(StringBuilder *sb, size_t needed)
{
    if (!sb) return false;
    size_t new_capacity = sb->capacity == 0 ? SB_INITIAL_CAPACITY : sb->capacity;
    while (new_capacity < (needed + 1))
    {
        new_capacity *= SB_GROWTH_FACTOR;
    }

    char *new_buffer = (char *)SB_REALLOC(sb->buffer, new_capacity);
    if (!new_buffer) return false;

    sb->buffer   = new_buffer;
    sb->capacity = new_capacity;
    return true;
}

StringBuilder *sb_create(size_t initial_capacity)
{
    StringBuilder *sb = (StringBuilder *)SB_MALLOC(sizeof(StringBuilder));
    if (!sb) return NULL;

    if (initial_capacity == 0) initial_capacity = SB_INITIAL_CAPACITY;

    sb->buffer = (char *)SB_MALLOC(initial_capacity);
    if (!sb->buffer)
    {
        SB_FREE(sb);
        return NULL;
    }

    sb->length    = 0;
    sb->capacity  = initial_capacity;
    sb->buffer[0] = '\0';
    return sb;
}

StringBuilder *sb_from_cstr(const char *str)
{
    if (!str) return sb_create(0);

    StringBuilder *sb = sb_create(SB_INITIAL_CAPACITY);
    if (!sb) return NULL;

    sb_append(sb, str);
    return sb;
}

void sb_destroy(StringBuilder *sb)
{
    if (sb)
    {
        if (sb->buffer) SB_FREE(sb->buffer);
        SB_FREE(sb);
        // sb = NULL;
    }
}

bool sb_append(StringBuilder *sb, const char *str)
{
    if (!sb || !str) return false;

    size_t str_len = strlen(str);
    if (str_len == 0) return true;

    if (!sb__ensure_capacity(sb, sb->length + str_len))
    {
        if (!sb__realloc(sb, sb->length + str_len)) return false;
    }

    SB_MEMCPY(sb->buffer + sb->length, str, str_len);
    sb->length += str_len;
    return true;
}

size_t sb_length(const StringBuilder *sb)
{
    if (sb) return sb->length;
    return 0;
}

const char *sb_cstr(const StringBuilder *sb)
{
    if (!sb || !sb->buffer) return "";
    sb->buffer[sb->length] = '\0';
    return sb->buffer;
}

void sb_clear(StringBuilder *sb)
{
    if (sb)
    {
        sb->length = 0;
        if (sb->buffer) sb->buffer[0] = '\0';
    }
}

bool sb_resize(StringBuilder *sb, size_t new_capacity)
{
    if (!sb || (new_capacity <= sb->capacity)) return false;
    return sb__realloc(sb, new_capacity);
}

#endif // SB_IMPLEMENTATION
