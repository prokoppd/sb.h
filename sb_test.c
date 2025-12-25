#include "greatest.h"

#define SB_IMPLEMENTATION
#include "sb.h"

TEST test_sb_destroy(void)
{
    StringBuilder *sb = NULL;
    sb_destroy(sb);
    PASS();
}

TEST test_sb_destroy_null_buffer(void)
{
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->buffer        = NULL;
    sb->length        = 0;
    sb->capacity      = 0;

    sb_destroy(sb);
    PASS();
}

TEST test_sb_create_and_destroy(void)
{
    StringBuilder *sb = sb_create(16);
    ASSERT(sb != NULL);
    ASSERT(sb_length(sb) == 0);
    ASSERT(sb_cstr(sb)[0] == '\0');

    sb_destroy(sb);
    PASS();
}

TEST test_sb_create_and_destroy_zero_capacity(void)
{
    StringBuilder *sb = sb_create(0);
    ASSERT(sb != NULL);
    ASSERT(sb_length(sb) == 0);
    ASSERT(sb_cstr(sb)[0] == '\0');

    sb_destroy(sb);
    PASS();
}

TEST test_sb_create_and_destroy_capacity_bigger_than_initial(void)
{
    StringBuilder *sb = sb_create(64);
    ASSERT(sb != NULL);
    ASSERT(sb_length(sb) == 0);
    ASSERT(sb_cstr(sb)[0] == '\0');

    sb_destroy(sb);
    PASS();
}

TEST test_sb_append_and_cstr(void)
{
    StringBuilder *sb = sb_create(8);
    ASSERT(sb != NULL);

    ASSERT(sb_append(sb, "Hello"));
    ASSERT(sb_length(sb) == 5);
    ASSERT(strcmp(sb_cstr(sb), "Hello") == 0);

    ASSERT(sb_append(sb, ", World!"));
    ASSERT(sb_length(sb) == 13);
    ASSERT(strcmp(sb_cstr(sb), "Hello, World!") == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_append_null_string(void)
{
    StringBuilder *sb = sb_create(8);
    ASSERT(sb != NULL);

    ASSERT(sb_append(sb, NULL) == false);
    ASSERT(sb_length(sb) == 0);
    ASSERT(strcmp(sb_cstr(sb), "") == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_append_null_string_builder(void)
{
    StringBuilder *sb = NULL;
    ASSERT(sb_append(sb, "Test") == false);
    PASS();
}

TEST test_sb_append_empty_string(void)
{
    StringBuilder *sb = sb_create(8);
    ASSERT(sb != NULL);

    ASSERT(sb_append(sb, "") == true);
    ASSERT(sb_length(sb) == 0);
    ASSERT(strcmp(sb_cstr(sb), "") == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_length(void)
{
    StringBuilder *sb = NULL;

    sb = sb_create(8);
    ASSERT(sb != NULL);

    ASSERT(sb_length(sb) == 0);

    ASSERT(sb_append(sb, "Test"));
    ASSERT(sb_length(sb) == 4);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_length_null_string_builder(void)
{
    const StringBuilder *sb = NULL;
    ASSERT(sb_length(sb) == 0);
    PASS();
}

TEST test_sb_cstr_null_string_builder(void)
{
    StringBuilder *sb = NULL;
    ASSERT(strcmp(sb_cstr(sb), "") == 0);
    PASS();
}

TEST test_sb_cstr_null_buffer(void)
{
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->buffer        = NULL;
    sb->length        = 0;
    sb->capacity      = 0;

    ASSERT(strcmp(sb_cstr(sb), "") == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_cstr(void)
{
    StringBuilder *sb = sb_create(8);
    ASSERT(sb != NULL);

    ASSERT(sb_append(sb, "Hello"));
    ASSERT(strcmp(sb_cstr(sb), "Hello") == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_from_cstr_null(void)
{
    const char *test_str = NULL;

    StringBuilder *sb = sb_from_cstr(test_str);
    ASSERT(sb != NULL);
    ASSERT(sb_length(sb) == 0);
    ASSERT(strcmp(sb_cstr(sb), "") == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_from_cstr_valid(void)
{
    const char *test_str = "Hello, World!";

    StringBuilder *sb = sb_from_cstr(test_str);
    ASSERT(sb != NULL);
    ASSERT(sb_length(sb) == strlen(test_str));
    ASSERT(strcmp(sb_cstr(sb), test_str) == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_from_cstr_empty(void)
{
    const char *test_str = "";

    StringBuilder *sb = sb_from_cstr(test_str);
    ASSERT(sb != NULL);
    ASSERT(sb_length(sb) == 0);
    ASSERT(strcmp(sb_cstr(sb), test_str) == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_clear(void)
{
    StringBuilder *sb = sb_create(16);
    ASSERT(sb != NULL);

    ASSERT(sb_append(sb, "Hello, World!"));
    ASSERT(sb_length(sb) == 13);
    ASSERT(strcmp(sb_cstr(sb), "Hello, World!") == 0);

    sb_clear(sb);
    ASSERT(sb_length(sb) == 0);
    ASSERT(strcmp(sb_cstr(sb), "") == 0);

    sb_destroy(sb);
    PASS();
}

TEST test_sb_clear_null_string_builder(void)
{
    StringBuilder *sb = NULL;
    sb_clear(sb);
    // ASSERT(sb == NULL);
    ASSERT(sb_length(sb) == 0);
    PASS();
}

TEST test_sb_clear_null_buffer(void)
{
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->buffer        = NULL;
    sb->length        = 10;
    sb->capacity      = 20;

    sb_clear(sb);
    ASSERT(sb->length == 0);

    sb_destroy(sb);
    PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();
    RUN_TEST(test_sb_destroy);
    RUN_TEST(test_sb_destroy_null_buffer);
    RUN_TEST(test_sb_create_and_destroy);
    RUN_TEST(test_sb_create_and_destroy_zero_capacity);
    RUN_TEST(test_sb_create_and_destroy_capacity_bigger_than_initial);
    RUN_TEST(test_sb_append_and_cstr);
    RUN_TEST(test_sb_append_null_string);
    RUN_TEST(test_sb_append_null_string_builder);
    RUN_TEST(test_sb_append_empty_string);
    RUN_TEST(test_sb_length);
    RUN_TEST(test_sb_length_null_string_builder);
    RUN_TEST(test_sb_cstr_null_string_builder);
    RUN_TEST(test_sb_cstr_null_buffer);
    RUN_TEST(test_sb_cstr);
    RUN_TEST(test_sb_from_cstr_null);
    RUN_TEST(test_sb_from_cstr_valid);
    RUN_TEST(test_sb_from_cstr_empty);
    RUN_TEST(test_sb_clear);
    RUN_TEST(test_sb_clear_null_string_builder);
    RUN_TEST(test_sb_clear_null_buffer);
    GREATEST_MAIN_END();
    return 0;
}
