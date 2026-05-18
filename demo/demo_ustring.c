/**
 * @file demo_ustring.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "demo.h"

void demo_ustring(void)
{
    ustring_t str = ustring_new_fromcstr("unicstle string demo. ");
    printf("\n@len=%d\n", str->len(str));
    str->print(str);

    str->append(str, uv("hello world. "));
    printf("\n@len=%d\n", str->len(str));
    str->print(str);

    str->append(str, uvc('#'));
    printf("\n@len=%d\n", str->len(str));
    str->print(str);

    ustring_t str2 = ustring_new_fromcstr("show time! \n");
    str->append(str, uvs(str2));
    printf("\n@len=%d\n", str->len(str));
    str->print(str);


    printf("isalpha: %d\n", str->isalpha(str));
    printf("isdigit: %d\n", str->isdigit(str));
    printf("isalnum: %d\n", str->isalnum(str));
    printf("isspace: %d\n", str->isspace(str));
    printf("islower: %d\n", str->islower(str));
    printf("isupper: %d\n", str->isupper(str));
    printf("iscntrl: %d\n", str->iscntrl(str));
    printf("isprint: %d\n", str->isprint(str));
    printf("ispunct: %d\n", str->ispunct(str));
    printf("isgraph: %d\n", str->isgraph(str));

    str->tolower(str);
    str->print(str);
    printf("islower: %d\n", str->islower(str));

    str->toupper(str);
    str->print(str);
    printf("isupper: %d\n", str->isupper(str));

    printf("str->tocstr: %s\n", str->cstr(str));
    printf("str2->tocstr: %s\n", str2->cstr(str2));

    ustring_free(&str);
}
