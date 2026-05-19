/**
 * @file string.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-17
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _USTRING_H_
#define _USTRING_H_

#include "unicstl_internal.h"
#include "iterator.h"
#include "darray.h"
#include "arraylist.h"

// clang-format off
#define UVIEW_BUF_SIZE              64
// clang-format on

typedef enum{
    UV_NONE = 0,
    UV_CSTR,
    UV_CHAR,
    UV_USTRING,
    UV_INT,
    UV_LONG,
    UV_DOBULE
}uv_type;

typedef struct _uview
{
    const char *str;
    size_t len;
    uv_type type;
} uview_t;

struct _ustring
{
    // -------------------- private --------------------
    arraylist_t _alist;
    bool is_view;
    bool _sorted;

    struct _iterator _iter;
    void (*_destory)(struct _ustring *self);

    // -------------------- public --------------------
    // char operations
    bool (*set)(struct _ustring *self, ssize_t index, const char* ch);   // O(1)
    bool (*get)(struct _ustring *self, ssize_t index, char *ch);         // O(1)
    const char* (*at)(struct _ustring *self, ssize_t index);             // O(1)

    // base
    bool (*reserve)(struct _ustring *self, size_t capacity);
    bool (*resize)(struct _ustring *self, size_t size);
    size_t (*len)(struct _ustring *self);
    size_t (*capacity)(struct _ustring *self);
    bool (*empty)(struct _ustring *self);
    bool (*full)(struct _ustring *self);
    bool (*clear)(struct _ustring *self);

    // -------------------- uview --------------------
    // erase
    bool (*erase)(struct _ustring *self, ssize_t index, size_t count);
    
    // append 
    bool (*append)(struct _ustring *self, uview_t newstr);
    bool (*insert)(struct _ustring *self, ssize_t index, uview_t newstr);
    
    // find and ...
    uview_t (*find)(struct _ustring *self, uview_t v);
    bool (*replace)(struct _ustring *self, uview_t oldstr, uview_t newstr);
    bool (*remove)(struct _ustring *self, uview_t oldstr);

    size_t (*index)(struct _ustring *self, uview_t uvstr);
    bool (*contains)(struct _ustring *self, uview_t uvstr);
    size_t (*count)(struct _ustring *self, uview_t uvstr);

    // split
    struct _ustring *(*substr)(struct _ustring *self, ssize_t start, ssize_t end);
    // bool (*split)(struct _ustring *self, uview_t delim);
    // bool (*splitlines)(struct _ustring *self);
    // bool (*join)(struct _ustring *self, uview_t delim);

    // judge
    bool (*isdigit)(struct _ustring *self);
    bool (*isxdigit)(struct _ustring *self);
    bool (*isalnum)(struct _ustring *self);
    bool (*isalpha)(struct _ustring *self);
    bool (*isspace)(struct _ustring *self);
    bool (*islower)(struct _ustring *self);
    bool (*isupper)(struct _ustring *self);
    bool (*isprint)(struct _ustring *self);
    bool (*iscntrl)(struct _ustring *self);
    bool (*ispunct)(struct _ustring *self);
    bool (*isgraph)(struct _ustring *self);

    // transform
    const char *(*cstr)(struct _ustring *self);
    bool (*tolower)(struct _ustring *self);
    bool (*toupper)(struct _ustring *self);
    bool (*trim)(struct _ustring *self);
    bool (*reverse)(struct _ustring *self);

    // format
    bool (*strip)(struct _ustring *self);
    bool (*strip_left)(struct _ustring *self);
    bool (*strip_right)(struct _ustring *self);
    bool (*ljust)(struct _ustring *self, size_t width);
    bool (*rjust)(struct _ustring *self, size_t width);
    bool (*center)(struct _ustring *self, size_t width);

    // compare
    int (*eq)(struct _ustring *self, uview_t v);
    int (*ne)(struct _ustring *self, uview_t v);
    int (*lt)(struct _ustring *self, uview_t v);
    int (*le)(struct _ustring *self, uview_t v);
    int (*gt)(struct _ustring *self, uview_t v);
    int (*ge)(struct _ustring *self, uview_t v);
    int (*cmp)(struct _ustring *self, uview_t v);

    // iter
    iterator_t (*iter)(struct _ustring *self, linear_order_t order);

    // config
    compare_fun_t compare; // !!! you have to implement this function

    // -------------------- debug --------------------
    void (*print)(struct _ustring *self);
    void (*print_obj)(const void *obj);
};
typedef struct _ustring *ustring_t;

/**
 * @brief create a uview from cstr
 */
static inline uview_t uv(const char *cstr)
{
    return (uview_t){cstr, cstr ? strlen(cstr) : 0, UV_CSTR};
}

/**
 * @brief create a uview from ustring
 */
static inline uview_t uvs(struct _ustring *string)
{
    if (string == NULL || string->_alist == NULL || string->len(string) == 0)
    {
        return (uview_t){NULL, 0};
    }
    arraylist_t alist = string->_alist;
    return (uview_t){alist->_darray->obj, string->len(string), UV_USTRING};
}

/**
 * @brief create a uview from char
 */
static inline uview_t uvch(const char c)
{
    return (uview_t){&c, 1, UV_CHAR};
}

/**
 * @brief create a uview from int
 */
static inline uview_t uvi(int i)
{
    static char buf[UVIEW_BUF_SIZE + 1] = {0};
    snprintf(buf, sizeof(buf), "%d", i);
    return (uview_t){buf, strlen(buf), UV_INT};
}

/**
 * @brief create a uview from long
 */
static inline uview_t uvl(long l)
{
    static char buf[UVIEW_BUF_SIZE + 1] = {0};
    snprintf(buf, sizeof(buf), "%ld", l);
    return (uview_t){buf, strlen(buf), UV_LONG};
}

/**
 * @brief create a uview from double
 */
static inline uview_t uvf(double f)
{
    static char buf[UVIEW_BUF_SIZE + 1] = {0};
    snprintf(buf, sizeof(buf), "%f", f);
    return (uview_t){buf, strlen(buf), UV_DOBULE};
}

ustring_t ustring_new(uview_t view);
void ustring_free(ustring_t *ustring);

ustring_t ustring_view(uview_t view);

#define ustring_new_fromcstr(cstr) ustring_new(uv(cstr))

#endif
