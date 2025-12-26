#include "external/utest.h"

#define SB_IMPLEMENTATION
#include "sb.h"

UTEST(StringBuilder, sb_destroy)
{
    StringBuilder *sb = NULL;
    sb_destroy(sb);
}

UTEST(StringBuilder, sb_destroy_null_buffer)
{
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->buffer        = NULL;
    sb->length        = 0;
    sb->capacity      = 0;

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_create_and_destroy)
{
    StringBuilder *sb = sb_create(16);
    ASSERT_TRUE(sb != NULL);
    ASSERT_EQ(sb_length(sb), (size_t)0);
    ASSERT_EQ(sb_cstr(sb)[0], '\0');

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_create_and_destroy_zero_capacity)
{
    StringBuilder *sb = sb_create(0);
    ASSERT_NE(sb, NULL);
    ASSERT_EQ(sb_length(sb), (size_t)0);
    ASSERT_EQ(sb->capacity, (size_t)SB_INITIAL_CAPACITY);
    ASSERT_EQ(sb_cstr(sb)[0], '\0');

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_create_and_destroy_capacity_bigger_than_initial)
{
    StringBuilder *sb = sb_create(64);
    ASSERT_NE(sb, NULL);
    ASSERT_EQ(sb_length(sb), (size_t)0);
    ASSERT_EQ(sb->capacity, (size_t)64);
    ASSERT_EQ(sb_cstr(sb)[0], '\0');

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_append_and_cstr)
{
    StringBuilder *sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb_append(sb, "Hello"));
    ASSERT_EQ(sb_length(sb), (size_t)5);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello"), 0);

    ASSERT_TRUE(sb_append(sb, ", World!"));
    ASSERT_EQ(sb_length(sb), (size_t)13);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello, World!"), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_append_null_string)
{
    StringBuilder *sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_FALSE(sb_append(sb, NULL));
    ASSERT_EQ(sb_length(sb), (size_t)0);
    ASSERT_EQ(strcmp(sb_cstr(sb), ""), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_append_null_string_builder)
{
    StringBuilder *sb = NULL;
    ASSERT_FALSE(sb_append(sb, "Test"));
}

UTEST(StringBuilder, sb_append_empty_string)
{
    StringBuilder *sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb_append(sb, ""));
    ASSERT_EQ(sb_length(sb), (size_t)0);
    ASSERT_EQ(strcmp(sb_cstr(sb), ""), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_append_upto_reallocation)
{
    StringBuilder *sb = sb_create(4);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb_append(sb, "Hello, "));
    ASSERT_EQ(sb_length(sb), (size_t)7);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello, "), 0);

    ASSERT_TRUE(sb_append(sb, "World!"));
    ASSERT_EQ(sb_length(sb), (size_t)13);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello, World!"), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_length)
{
    StringBuilder *sb = NULL;

    sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_EQ(sb_length(sb), (size_t)0);

    ASSERT_TRUE(sb_append(sb, "Test"));
    ASSERT_EQ(sb_length(sb), (size_t)4);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_length_null_string_builder)
{
    const StringBuilder *sb = NULL;
    ASSERT_EQ(sb_length(sb), (size_t)0);
}

UTEST(StringBuilder, sb_cstr_null_string_builder)
{
    StringBuilder *sb = NULL;
    ASSERT_EQ(strcmp(sb_cstr(sb), ""), 0);
    ASSERT_EQ(strcmp(sb_cstr(NULL), ""), 0);
}

UTEST(StringBuilder, sb_cstr_null_buffer)
{
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->buffer        = NULL;
    sb->length        = 0;
    sb->capacity      = 0;

    ASSERT_EQ(strcmp(sb_cstr(sb), ""), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_cstr)
{
    StringBuilder *sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb_append(sb, "Hello"));
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello"), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_from_cstr_null)
{
    const char *test_str = NULL;

    StringBuilder *sb = sb_from_cstr(test_str);
    ASSERT_NE(sb, NULL);
    ASSERT_EQ(sb_length(sb), (size_t)0);
    ASSERT_EQ(strcmp(sb_cstr(sb), ""), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_from_cstr_valid)
{
    const char *test_str = "Hello, World!";

    StringBuilder *sb = sb_from_cstr(test_str);
    ASSERT_NE(sb, NULL);
    ASSERT_EQ(sb_length(sb), strlen(test_str));
    ASSERT_EQ(strcmp(sb_cstr(sb), test_str), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_clear)
{
    StringBuilder *sb = sb_create(16);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb_append(sb, "Hello, World!"));
    ASSERT_EQ(sb_length(sb), (size_t)13);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello, World!"), 0);

    sb_clear(sb);
    ASSERT_EQ(sb_length(sb), (size_t)0);
    ASSERT_EQ(strcmp(sb_cstr(sb), ""), 0);
    ASSERT_EQ('\0', sb->buffer[0]);
    sb_destroy(sb);
}

UTEST(StringBuilder, sb_clear_null_string_builder)
{
    StringBuilder *sb = NULL;
    sb_clear(sb);
    ASSERT_EQ(sb, NULL);
    ASSERT_EQ(sb_length(sb), (size_t)0);
}
//
UTEST(StringBuilder, sb_clear_null_buffer)
{
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->buffer        = NULL;
    sb->length        = 10;
    sb->capacity      = 20;

    sb_clear(sb);
    ASSERT_EQ(sb->length, (size_t)0);
    ASSERT_EQ(sb->buffer, NULL);
    sb_destroy(sb);
}

UTEST(StringBuilder, sb_clear_null)
{
    StringBuilder *sb = NULL;
    sb_clear(sb);
    ASSERT_EQ(sb, NULL);
}

UTEST(StringBuilder, sb_resize)
{
    StringBuilder *sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb_append(sb, "Hello"));
    ASSERT_EQ(sb_length(sb), (size_t)5);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello"), 0);

    ASSERT_TRUE(sb_resize(sb, 32));
    ASSERT_EQ(sb->capacity, (size_t)64);
    ASSERT_EQ(sb_length(sb), (size_t)5);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello"), 0);

    ASSERT_TRUE(sb_append(sb, ", World!"));
    ASSERT_EQ(sb_length(sb), (size_t)13);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello, World!"), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_resize_smaller)
{
    StringBuilder *sb = sb_create(32);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb_append(sb, "Hello, World!"));
    ASSERT_EQ(sb_length(sb), (size_t)13);
    ASSERT_EQ(sb->capacity, (size_t)32);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello, World!"), 0);

    ASSERT_FALSE(sb_resize(sb, 8));
    ASSERT_EQ(sb->capacity, (size_t)32);
    ASSERT_EQ(sb_length(sb), (size_t)13);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello, World!"), 0);

    sb_destroy(sb);
}

UTEST(StringBuilder, sb_resize_null_string_builder)
{
    StringBuilder *sb = NULL;
    ASSERT_FALSE(sb_resize(sb, 16));
}

UTEST(StringBuilder, sb_resize_zero_capacity)
{
    StringBuilder *sb = sb_create(16);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb_append(sb, "Hello"));
    ASSERT_EQ(sb_length(sb), (size_t)5);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello"), 0);

    ASSERT_FALSE(sb_resize(sb, 0));
    ASSERT_EQ(sb->capacity, (size_t)16);
    ASSERT_EQ(sb_length(sb), (size_t)5);
    ASSERT_EQ(strcmp(sb_cstr(sb), "Hello"), 0);

    sb_destroy(sb);
}

UTEST(PRIVATE, sb__ensure_capacity)
{
    StringBuilder *sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_FALSE(sb__ensure_capacity(sb, 16));
    ASSERT_EQ(sb->capacity, (size_t)8);

    ASSERT_FALSE(sb__ensure_capacity(sb, 32));
    ASSERT_EQ(sb->capacity, (size_t)8);

    sb_destroy(sb);
}

UTEST(PRIVATE, sb__ensure_capacity_no_realloc_needed)
{
    StringBuilder *sb = sb_create(64);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb__ensure_capacity(sb, 32));
    ASSERT_EQ(sb->capacity, (size_t)64);

    sb_destroy(sb);
}

UTEST(PRIVATE, sb__ensure_capacity_null_string_builder)
{
    StringBuilder *sb = NULL;
    ASSERT_FALSE(sb__ensure_capacity(sb, 16));
}

UTEST(PRIVATE, sb__ensure_capacity_null_buffer)
{
    StringBuilder *sb = (StringBuilder*)SB_MALLOC(sizeof(StringBuilder));
    sb->buffer        = NULL;
    sb->length        = 0;
    sb->capacity      = 0;
    
    ASSERT_FALSE(sb__ensure_capacity(sb, 16));
    
    sb_destroy(sb);
}
UTEST(PRIVATE, sb__ensure_capacity_less_than_needed)
{
    StringBuilder *sb = sb_create(16);
    ASSERT_NE(sb, NULL);

    ASSERT_FALSE(sb__ensure_capacity(sb, 20));
    ASSERT_EQ(sb->capacity, (size_t)16);

    sb_destroy(sb);
}

UTEST(PRIVATE, sb__realloc)
{
    StringBuilder *sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb__realloc(sb, 32));
    ASSERT_GE(sb->capacity, (size_t)33);

    sb_destroy(sb);
}

UTEST(PRIVATE, sb__realloc_null_string_builder)
{
    StringBuilder *sb = NULL;
    ASSERT_FALSE(sb__realloc(sb, 16));
}

UTEST(PRIVATE, sb__realloc_multiple_growth)
{
    StringBuilder *sb = sb_create(8);
    ASSERT_NE(sb, NULL);

    ASSERT_TRUE(sb__realloc(sb, 100));
    ASSERT_GE(sb->capacity, (size_t)101);

    sb_destroy(sb);
}

UTEST_MAIN();
