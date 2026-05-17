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

typedef struct _uview
{
    const char *str;
    size_t len;
}uview_t;

struct _ustring
{
    // -------------------- private --------------------
    darray_t _darray;

    bool _sorted;

    struct _iterator _iter;
    void (*_destory)(struct _ustring *self);

    // -------------------- public --------------------
    bool (*set)(struct _ustring *self, size_t index, const char c);       // O(1)
    bool (*get)(struct _ustring *self, size_t index, char *c);            // O(1)
    char (*at)(struct _ustring *self, size_t index);                      // O(1)

    // base
    bool (*resize)(struct _ustring *self, size_t capacity);
    size_t (*len)(struct _ustring *self);
    size_t (*capacity)(struct _ustring *self);
    bool (*empty)(struct _ustring *self);
    bool (*full)(struct _ustring *self);
    bool (*clear)(struct _ustring *self);

    // sort and search
    size_t (*index)(struct _ustring *self, const void *obj);            // O(n) return (size_t)-1 if not found
    bool (*contains)(struct _ustring *self, const void *obj);           // O(n)

    bool (*sort)(struct _ustring *self);                                // O(nlogn)
    size_t (*search)(struct _ustring *self, const void *obj);           // O(n) if not sorted; O(logn) if sorted
                                                                        // return leftmost matched index; return (size_t)-1 if not found
    size_t (*count)(struct _ustring *self, const void *obj);            // O(nlogn) if sorted; O(n) if not sorted


    // -------------------- uview --------------------
    // append and remove
    bool (*append)(struct _ustring *self, uview_t v);
    // bool (*pop)(struct _ustring *self);
    bool (*remove)(struct _ustring *self, uview_t oldstr);
    bool (*insert)(struct _ustring *self, size_t index, uview_t v);

    // split
    bool (*split)(struct _ustring *self, uview_t delim);
    bool (*splitlines)(struct _ustring *self);
    bool (*join)(struct _ustring *self, uview_t delim);

    // substring
    ssize_t (*find)(struct _ustring* str, uview_t v);
    struct _ustring* (*substr)(struct _ustring *self, size_t start, size_t end);
    bool (*replace)(struct _ustring *self, uview_t oldstr, uview_t newstr);

    // judge
    bool (*isdigit)(struct _ustring *self);
    bool (*isalpha)(struct _ustring *self);
    bool (*isalnum)(struct _ustring *self);
    bool (*isspace)(struct _ustring *self);
    bool (*islower)(struct _ustring *self);
    bool (*isupper)(struct _ustring *self);
    bool (*iscntrl)(struct _ustring *self);
    bool (*isprint)(struct _ustring *self);
    bool (*ispunct)(struct _ustring *self);
    bool (*isgraph)(struct _ustring *self);

    // transform
    const char* (*cstr)(struct _ustring* self);
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
    bool (*format)(struct _ustring *self, const char* format); 

    // compare
    int (*eq)(struct _ustring *self, struct _ustring *other);
    int (*ne)(struct _ustring *self, struct _ustring *other);
    int (*lt)(struct _ustring *self, struct _ustring *other);
    int (*le)(struct _ustring *self, struct _ustring *other);
    int (*gt)(struct _ustring *self, struct _ustring *other);
    int (*ge)(struct _ustring *self, struct _ustring *other);
    int (*cmp)(struct _ustring *self, struct _ustring *other);

    // iter
    iterator_t (*iter)(struct _ustring *self, linear_order_t order);

    // config
    compare_fun_t compare;      // !!! you have to implement this function

    // -------------------- debug --------------------
    void (*print)(struct _ustring *self);
    void (*print_obj)(const void *obj);
};
typedef struct _ustring *ustring_t;

ustring_t ustring_new(const char *cstr);
void ustring_free(ustring_t *ustring);


/**
 * @brief create a uview from cstr
 * 
 * @param cstr 
 * @return uview_t 
 */
static inline uview_t uv(const char *cstr)
{
    return (uview_t){cstr, cstr ? strlen(cstr) : 0};
}

/**
 * @brief create a uview from ustring
 * 
 * @param string 
 * @return uview_t 
 */
static inline uview_t uvs(struct _ustring *string)
{
    if(string == NULL || string->_darray == NULL || string->len(string) == 0)
    {
        return (uview_t){NULL, 0};
    }
    return (uview_t){string->_darray->obj, string->len(string)};
}

/**
 * @brief create a uview from char
 * 
 * @param c 
 * @return uview_t 
 */
static inline uview_t uvc(const char c)
{
    return (uview_t){&c, 1};
}

#endif
