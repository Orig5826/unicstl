/**
 * @file test_ustring.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

void test_ustring_new(void)
{
    ustring_t str = ustring_new(uv("hello"));
    TEST_ASSERT_EQUAL_INT(5, str->len(str));
    TEST_ASSERT_EQUAL_INT(6, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "hello");
    ustring_free(&str);
}

void test_ustring_new_lazy(void)
{
    ustring_t str = ustring_new(uv(""));
    TEST_ASSERT_EQUAL_INT(0, str->len(str));
    TEST_ASSERT_EQUAL_INT(1, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "");
    ustring_free(&str);
}

void test_ustring_new_int(void)
{
    const int num = 1234567890;
    ustring_t str = ustring_new(uvi(num));
    TEST_ASSERT_EQUAL_INT(10, str->len(str));
    TEST_ASSERT_EQUAL_INT(11, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "1234567890");
    ustring_free(&str);
}

void test_ustring_new_float(void)
{
    const double num = 123.456789;
    ustring_t str = ustring_new(uvf(num));
    TEST_ASSERT_EQUAL_INT(10, str->len(str));
    TEST_ASSERT_EQUAL_INT(11, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "123.456789");
    ustring_free(&str);
}

void test_ustring_tolower(void)
{
    ustring_t str = ustring_new(uv("HELLO wolrD"));
    str->tolower(str);
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "hello wolrd");
    ustring_free(&str);
}

void test_ustring_toupper(void)
{
    ustring_t str = ustring_new(uv("hello"));
    str->toupper(str);
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "HELLO");
    ustring_free(&str);
}

void test_ustring_isalpha(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_TRUE(str->isalpha(str));
    ustring_free(&str);

    str = ustring_new(uv("unicstl123"));
    TEST_ASSERT_FALSE(str->isalpha(str));
    ustring_free(&str);
}

void test_ustring_isalnum(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_TRUE(str->isalnum(str));
    ustring_free(&str);

    str = ustring_new(uv("unicstl123"));
    TEST_ASSERT_TRUE(str->isalnum(str));
    ustring_free(&str);
}

void test_ustring_isdigit(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_FALSE(str->isdigit(str));
    ustring_free(&str);

    str = ustring_new(uv("1234567890"));
    TEST_ASSERT_TRUE(str->isdigit(str));
    ustring_free(&str);
}

void test_ustring_isprint(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_TRUE(str->isprint(str));
    ustring_free(&str);

    str = ustring_new(uv("unicstl\r\n\t"));
    TEST_ASSERT_FALSE(str->isprint(str));
    ustring_free(&str);
}

void test_ustring_isspace(void)
{
    ustring_t str = ustring_new(uv("unicstl\r\n\t"));
    TEST_ASSERT_FALSE(str->isspace(str));
    ustring_free(&str);

    str = ustring_new(uv("\r\n\t"));
    TEST_ASSERT_TRUE(str->isspace(str));
    ustring_free(&str);
}

void test_ustring_islower(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_TRUE(str->islower(str));
    ustring_free(&str);

    str = ustring_new(uv("unicstl123"));
    TEST_ASSERT_FALSE(str->islower(str));
    ustring_free(&str);
}

void test_ustring_isupper(void)
{
    ustring_t str = ustring_new(uv("UNICSTL"));
    TEST_ASSERT_TRUE(str->isupper(str));
    ustring_free(&str);

    str = ustring_new(uv("UNIcSTL"));
    TEST_ASSERT_FALSE(str->isupper(str));
    ustring_free(&str);
}

void test_ustring_strip_right(void)
{
    ustring_t str = ustring_new(uv("  unicstl\r\n\t"));
    TEST_ASSERT_EQUAL_INT(12, str->len(str));
    str->strip_right(str);
    TEST_ASSERT_EQUAL_STRING("  unicstl", str->cstr(str));
    TEST_ASSERT_EQUAL_INT(9, str->len(str));
    ustring_free(&str);
}

void test_ustring_strip_left(void)
{
    ustring_t str = ustring_new(uv("  unicstl\r\n\t"));
    TEST_ASSERT_EQUAL_INT(12, str->len(str));
    str->strip_left(str);
    TEST_ASSERT_EQUAL_STRING("unicstl\r\n\t", str->cstr(str));
    TEST_ASSERT_EQUAL_INT(10, str->len(str));
    ustring_free(&str);
}

void test_ustring_strip(void)
{
    ustring_t str = ustring_new(uv("  unicstl\r\n\t"));
    TEST_ASSERT_EQUAL_INT(12, str->len(str));
    str->strip(str);
    TEST_ASSERT_EQUAL_STRING("unicstl", str->cstr(str));
    TEST_ASSERT_EQUAL_INT(7, str->len(str));
    ustring_free(&str);
}

void test_ustring_append(void)
{
    ustring_t str = ustring_new_fromcstr("unicstl ");
    ustring_t str2 = ustring_new_fromcstr("ustring");
    size_t len = str->len(str);
    size_t len2 = str2->len(str2);
    TEST_ASSERT_TRUE(str->append(str, uvs(str2)));
    TEST_ASSERT_EQUAL_INT(len + len2, str->len(str));
    ustring_free(&str);
    ustring_free(&str2);
}


void test_ustring(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_ustring_new);
    RUN_TEST(test_ustring_new_lazy);
    RUN_TEST(test_ustring_new_int);
    RUN_TEST(test_ustring_new_float);

    RUN_TEST(test_ustring_tolower);
    RUN_TEST(test_ustring_toupper);

    RUN_TEST(test_ustring_isalpha);
    RUN_TEST(test_ustring_isalnum);
    RUN_TEST(test_ustring_isdigit);
    RUN_TEST(test_ustring_isprint);
    RUN_TEST(test_ustring_isspace);
    RUN_TEST(test_ustring_islower);
    RUN_TEST(test_ustring_isupper);

    RUN_TEST(test_ustring_strip_right);
    RUN_TEST(test_ustring_strip_left);
    RUN_TEST(test_ustring_strip);

    RUN_TEST(test_ustring_append);
}
