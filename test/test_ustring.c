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
    TEST_ASSERT_EQUAL_INT(5, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING("hello", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_new_lazy(void)
{
    ustring_t str = ustring_new(uv(""));
    TEST_ASSERT_EQUAL_INT(0, str->len(str));
    TEST_ASSERT_EQUAL_INT(0, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING("", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_new_int(void)
{
    const int num = 1234567890;
    ustring_t str = ustring_new(uvi(num));
    TEST_ASSERT_EQUAL_INT(10, str->len(str));
    TEST_ASSERT_EQUAL_INT(10, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING("1234567890", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_new_float(void)
{
    const double num = 123.456789;
    ustring_t str = ustring_new(uvf(num));
    TEST_ASSERT_EQUAL_INT(10, str->len(str));
    TEST_ASSERT_EQUAL_INT(10, str->capacity(str));
    TEST_ASSERT_EQUAL_STRING("123.456789", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_get(void)
{
    ustring_t str = ustring_new(uv("hello"));
    TEST_ASSERT_EQUAL_INT(5, str->len(str));

    char ch = 0;
    TEST_ASSERT_TRUE(str->get(str, 0, &ch));
    TEST_ASSERT_EQUAL_CHAR('h', ch);

    TEST_ASSERT_TRUE(str->get(str, 5, &ch));
    TEST_ASSERT_EQUAL_CHAR('\0', ch);

    TEST_ASSERT_TRUE(str->get(str, -1, &ch));
    TEST_ASSERT_EQUAL_CHAR('o', ch);

    ustring_free(&str);
}

void test_ustring_at(void)
{
    ustring_t str = ustring_new(uv("hello"));
    TEST_ASSERT_EQUAL_INT(5, str->len(str));

    TEST_ASSERT_EQUAL_CHAR('h', *(char *)str->at(str, 0));
    TEST_ASSERT_EQUAL_CHAR('\0', *(char *)str->at(str, 5));
    TEST_ASSERT_EQUAL_CHAR('o', *(char *)str->at(str, -1));

    ustring_free(&str);
}

void test_ustring_set(void)
{
    ustring_t str = ustring_new(uv("hello"));
    TEST_ASSERT_EQUAL_INT(5, str->len(str));

    char ch = '1';
    TEST_ASSERT_TRUE(str->set(str, 0, &ch));
    TEST_ASSERT_EQUAL_CHAR('1', *(char *)str->at(str, 0));

    ch = '5';
    TEST_ASSERT_TRUE(str->set(str, 5, &ch));
    TEST_ASSERT_EQUAL_CHAR('5', *(char *)str->at(str, 5));

    TEST_ASSERT_TRUE(str->set(str, -1, &ch));
    TEST_ASSERT_EQUAL_CHAR('5', *(char *)str->at(str, -1));

    ustring_free(&str);
}


void test_ustring_tolower(void)
{
    ustring_t str = ustring_new(uv("HELLO worlD"));
    str->tolower(str);
    TEST_ASSERT_EQUAL_STRING("hello world", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_toupper(void)
{
    ustring_t str = ustring_new(uv("hello"));
    str->toupper(str);
    TEST_ASSERT_EQUAL_STRING("HELLO",str->cstr(str));
    ustring_free(&str);
}

void test_ustring_reverse(void)
{
    ustring_t str = ustring_new(uv("hello"));
    str->reverse(str);
    TEST_ASSERT_EQUAL_STRING("olleh", str->cstr(str));
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

void test_ustring_isxdigit(void)
{
    ustring_t str = ustring_new(uv("GHgh"));
    TEST_ASSERT_FALSE(str->isxdigit(str));
    ustring_free(&str);

    str = ustring_new(uv("ABCDEF1234567890abcdef"));
    TEST_ASSERT_TRUE(str->isxdigit(str));
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

void test_ustring_iscntrl(void)
{
    ustring_t str = ustring_new(uv("\x01\x02\x03\t\b\n"));
    TEST_ASSERT_TRUE(str->iscntrl(str));
    ustring_free(&str);

    str = ustring_new(uv("@#$#*"));
    TEST_ASSERT_FALSE(str->iscntrl(str));
    ustring_free(&str);
}

void test_ustring_ispunct(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_FALSE(str->ispunct(str));
    ustring_free(&str);

    str = ustring_new(uv(",.;:?!"));
    TEST_ASSERT_TRUE(str->ispunct(str));
    ustring_free(&str);
}

void test_ustring_isgrach(void)
{
    ustring_t str = ustring_new(uv("\1\2\0"));
    TEST_ASSERT_FALSE(str->isgraph(str));
    ustring_free(&str);

    str = ustring_new(uv("unicstl123*&#@"));
    TEST_ASSERT_TRUE(str->isgraph(str));
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

void test_ustring_ljust(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_EQUAL_INT(7, str->len(str));
    TEST_ASSERT_TRUE(str->ljust(str, 16));
    TEST_ASSERT_EQUAL_INT(16, str->len(str));
    TEST_ASSERT_EQUAL_STRING("unicstl         ", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_rjust(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_EQUAL_INT(7, str->len(str));
    TEST_ASSERT_TRUE(str->rjust(str, 16));
    TEST_ASSERT_EQUAL_INT(16, str->len(str));
    TEST_ASSERT_EQUAL_STRING("         unicstl", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_center(void)
{
    ustring_t str = ustring_new(uv("unicstl"));
    TEST_ASSERT_EQUAL_INT(7, str->len(str));
    TEST_ASSERT_TRUE(str->center(str, 16));
    TEST_ASSERT_EQUAL_INT(16, str->len(str));
    TEST_ASSERT_EQUAL_STRING("    unicstl     ", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_erase(void)
{
    log_info("start");
    ustring_t str = ustring_new_fromcstr("hello world");
    TEST_ASSERT_EQUAL_INT(11, str->len(str));
    TEST_ASSERT_TRUE(str->erase(str, 2, 7));
    TEST_ASSERT_EQUAL_INT(4, str->len(str));
    TEST_ASSERT_EQUAL_STRING("held", str->cstr(str));
    ustring_free(&str);
    log_info("end");
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

void test_ustring_insert(void)
{
    ustring_t str = ustring_new_fromcstr("hello world");
    ustring_t str2 = ustring_new_fromcstr(" unicstl");
    size_t len = str->len(str);
    size_t len2 = str2->len(str2);

    TEST_ASSERT_TRUE(str->insert(str, 5, uvs(str2)));
    TEST_ASSERT_EQUAL_INT(len + len2, str->len(str));
    TEST_ASSERT_EQUAL_STRING("hello unicstl world", str->cstr(str));
    ustring_free(&str);
    ustring_free(&str2);

    str = ustring_new_fromcstr("hello world");
    TEST_ASSERT_TRUE(str->insert(str, 0, uv("unicstl ")));
    TEST_ASSERT_EQUAL_INT(len + 8, str->len(str));
    TEST_ASSERT_EQUAL_STRING("unicstl hello world", str->cstr(str));
    ustring_free(&str);
    log_info("end");
}

void test_ustring_find(void)
{
    ustring_t str = ustring_new_fromcstr("hello world");
    ustring_t str2 = ustring_new_fromcstr("world");
    uview_t v = str->find(str, uvs(str2));
    TEST_ASSERT_EQUAL_INT(5, v.len);
    TEST_ASSERT_EQUAL_STRING("world", v.str);

    v = str->find(str, uv("llo"));
    TEST_ASSERT_EQUAL_INT(3, v.len);
    // TEST_ASSERT_EQUAL_STRING("llo", v.str);  // change test case
    TEST_ASSERT_EQUAL_MEMORY("llo", v.str, 3);  // is ok!

    ustring_free(&str);
    ustring_free(&str2);
}

void test_ustring_remove(void)
{
    ustring_t str = ustring_new_fromcstr("hello world");
    TEST_ASSERT_TRUE(str->remove(str, uv("llo wor")));
    TEST_ASSERT_EQUAL_INT(4, str->len(str));
    TEST_ASSERT_EQUAL_STRING("held", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_replace(void)
{
    ustring_t str = ustring_new_fromcstr("hello world!");
    TEST_ASSERT_TRUE(str->replace(str, uv("world"), uv("unicstl")));
    TEST_ASSERT_EQUAL_STRING("hello unicstl!", str->cstr(str));
    ustring_free(&str);
}

void test_ustring_cmp(void)
{
    ustring_t str = ustring_new_fromcstr("unicstl");
    TEST_ASSERT_TRUE(str->eq(str, uv("unicstl")));
    TEST_ASSERT_TRUE(str->ne(str, uv("unicstl1")));

    TEST_ASSERT_FALSE(str->eq(str, uv("")));
    TEST_ASSERT_TRUE(str->ne(str, uv("")));

    TEST_ASSERT_FALSE(str->eq(str, uv("unicstz")));
    TEST_ASSERT_FALSE(str->ne(str, uv("unicstl")));

    TEST_ASSERT_TRUE(str->le(str, uv("unicstz")));
    TEST_ASSERT_TRUE(str->ge(str, uv("unicsta")));
    TEST_ASSERT_TRUE(str->lt(str, uv("unicstz")));
    TEST_ASSERT_TRUE(str->gt(str, uv("unicsta")));
    ustring_free(&str);
}

void test_ustring_substr(void)
{
    ustring_t str = ustring_new_fromcstr("hello world");
    ustring_t substr = str->substr(str, 6, 10);
    TEST_ASSERT_EQUAL_STRING("world", substr->cstr(substr));
    ustring_free(&substr);
    ustring_free(&str);
}

void test_ustring_index(void)
{
    ustring_t str = ustring_new_fromcstr("hello world");
    TEST_ASSERT_EQUAL_INT(2, str->index(str, uv("l")));
    TEST_ASSERT_EQUAL_INT(6, str->index(str, uv("wor")));

    TEST_ASSERT_TRUE(str->contains(str, uv("l")));
    TEST_ASSERT_TRUE(str->contains(str, uv("wor")));
    ustring_free(&str);
}

void test_ustring_count(void)
{
    ustring_t str = ustring_new_fromcstr("hello world");
    TEST_ASSERT_EQUAL_INT(3, str->count(str, uv("l")));
    TEST_ASSERT_EQUAL_INT(1, str->count(str, uv("ll")));
    ustring_free(&str);
}

void test_ustring(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_ustring_new);
    RUN_TEST(test_ustring_new_lazy);
    RUN_TEST(test_ustring_new_int);
    RUN_TEST(test_ustring_new_float);

    RUN_TEST(test_ustring_get);
    RUN_TEST(test_ustring_at);
    RUN_TEST(test_ustring_set);

    RUN_TEST(test_ustring_isdigit);
    RUN_TEST(test_ustring_isxdigit);
    RUN_TEST(test_ustring_isalnum);
    RUN_TEST(test_ustring_isalpha);
    RUN_TEST(test_ustring_isprint);
    RUN_TEST(test_ustring_isspace);
    RUN_TEST(test_ustring_islower);
    RUN_TEST(test_ustring_isupper);
    RUN_TEST(test_ustring_iscntrl);
    RUN_TEST(test_ustring_ispunct);
    RUN_TEST(test_ustring_isgrach);

    RUN_TEST(test_ustring_tolower);
    RUN_TEST(test_ustring_toupper);
    RUN_TEST(test_ustring_reverse);

    RUN_TEST(test_ustring_strip_right);
    RUN_TEST(test_ustring_strip_left);
    RUN_TEST(test_ustring_strip);
    RUN_TEST(test_ustring_ljust);
    RUN_TEST(test_ustring_rjust);
    RUN_TEST(test_ustring_center);

    RUN_TEST(test_ustring_erase);
    RUN_TEST(test_ustring_append);
    RUN_TEST(test_ustring_insert);

    RUN_TEST(test_ustring_find);
    RUN_TEST(test_ustring_remove);
    RUN_TEST(test_ustring_replace);

    RUN_TEST(test_ustring_cmp);

    RUN_TEST(test_ustring_substr);
    RUN_TEST(test_ustring_index);
    RUN_TEST(test_ustring_count);
}
