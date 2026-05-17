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
    ustring_t str = ustring_new("hello");
    TEST_ASSERT_EQUAL_INT(5, str->len(str));
    TEST_ASSERT_EQUAL_INT(6, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "hello");
    ustring_free(&str);
}

void test_ustring_new_lazy(void)
{
    ustring_t str = ustring_new("");
    TEST_ASSERT_EQUAL_INT(0, str->len(str));
    TEST_ASSERT_EQUAL_INT(1, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "");
    ustring_free(&str);
}

void test_ustring_tolower(void)
{
    ustring_t str = ustring_new("HELLO wolrD");
    str->tolower(str);
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "hello wolrd");
    ustring_free(&str);
}

void test_ustring_toupper(void)
{
    ustring_t str = ustring_new("hello");
    str->toupper(str);
    TEST_ASSERT_EQUAL_STRING(str->cstr(str), "HELLO");
    ustring_free(&str);
}

void test_ustring_isalpha(void)
{
    ustring_t str = ustring_new("unicstl");
    TEST_ASSERT_TRUE(str->isalpha(str));
    ustring_free(&str);

    str = ustring_new("unicstl123");
    TEST_ASSERT_FALSE(str->isalpha(str));
    ustring_free(&str);
}

void test_ustring_isalnum(void)
{
    ustring_t str = ustring_new("unicstl");
    TEST_ASSERT_TRUE(str->isalnum(str));
    ustring_free(&str);

    str = ustring_new("unicstl123");
    TEST_ASSERT_TRUE(str->isalnum(str));
    ustring_free(&str);
}

void test_ustring_isdigit(void)
{
    ustring_t str = ustring_new("unicstl");
    TEST_ASSERT_FALSE(str->isdigit(str));
    ustring_free(&str);

    str = ustring_new("1234567890");
    TEST_ASSERT_TRUE(str->isdigit(str));
    ustring_free(&str);
}

void test_ustring_isprint(void)
{
    ustring_t str = ustring_new("unicstl");
    TEST_ASSERT_TRUE(str->isprint(str));
    ustring_free(&str);

    str = ustring_new("unicstl\r\n\t");
    TEST_ASSERT_FALSE(str->isprint(str));
    ustring_free(&str);
}

void test_ustring_isspace(void)
{
    ustring_t str = ustring_new("unicstl\r\n\t");
    TEST_ASSERT_FALSE(str->isspace(str));
    ustring_free(&str);

    str = ustring_new("\r\n\t");
    TEST_ASSERT_TRUE(str->isspace(str));
    ustring_free(&str);
}

void test_ustring_islower(void)
{
    ustring_t str = ustring_new("unicstl");
    TEST_ASSERT_TRUE(str->islower(str));
    ustring_free(&str);

    str = ustring_new("unicstl123");
    TEST_ASSERT_FALSE(str->islower(str));
    ustring_free(&str);
}

void test_ustring_isupper(void)
{
    ustring_t str = ustring_new("UNICSTL");
    TEST_ASSERT_TRUE(str->isupper(str));
    ustring_free(&str);

    str = ustring_new("UNIcSTL");
    TEST_ASSERT_FALSE(str->isupper(str));
    ustring_free(&str);
}

void test_ustring_strip(void)
{
    ustring_t str = ustring_new("  unicstl\r\n\t");
    str->strip(str);
    TEST_ASSERT_EQUAL_STRING("unicstl", str->cstr(str));
    ustring_free(&str);
}

void test_ustring(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_ustring_new);
    RUN_TEST(test_ustring_new_lazy);

    RUN_TEST(test_ustring_tolower);
    RUN_TEST(test_ustring_toupper);

    RUN_TEST(test_ustring_isalpha);
    RUN_TEST(test_ustring_isalnum);
    RUN_TEST(test_ustring_isdigit);
    RUN_TEST(test_ustring_isprint);
    RUN_TEST(test_ustring_isspace);
    RUN_TEST(test_ustring_islower);
    RUN_TEST(test_ustring_isupper);

    RUN_TEST(test_ustring_strip);
}
