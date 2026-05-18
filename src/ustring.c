/**
 * @file ustring.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-17
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "ustring.h"
#include "algo.h"
#include <ctype.h>

static const char null_char = '\0';

static size_t ustring_len(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->size(self->_darray) - 1;
}

static size_t ustring_capacity(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->capacity(self->_darray);
}

static bool ustring_empty(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->empty(self->_darray);
}

static bool ustring_full(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->full(self->_darray);
}

static bool ustring_clear(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->clear(self->_darray);
}

static void ustring_destory(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    if (self->_darray != NULL)
    {
        darray_free(&self->_darray);
    }
}

static void ustring_print(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    self->_darray->print_obj = self->print_obj;
    self->_darray->print(self->_darray);
}

static bool ustring_reserve(struct _ustring *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->reserve(self->_darray, capacity);
}

static bool ustring_insert(struct _ustring *self, size_t index, uview_t v)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return true;
}

static bool ustring_remove(struct _ustring *self, uview_t oldstr)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return true;
}

static bool ustring_pop(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->pop(self->_darray, NULL);
}

static bool ustring_append(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);

    // ustring_pop(self);
    for (size_t i = 0; i < v.len; i++)
    {
        if (!self->_darray->append(self->_darray, &v.str[i]))
        {
            log_error("ustring_append error");
            return false;
        }
    }
    if(!self->_darray->append(self->_darray, '\0'))
    {
        log_error("append '\0' error");
        return false;
    }
    return true;
}

static bool ustring_set(struct _ustring *self, size_t index, const char c)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->set(self->_darray, index, &c);
}

static bool ustring_get(struct _ustring *self, size_t index, char *c)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->get(self->_darray, index, &c);
}

static char ustring_at(struct _ustring *self, size_t index)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return *(char *)self->_darray->at(self->_darray, index);
}

bool ustring_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    ustring_t self = (ustring_t)iter->_container;

    if (iter->_order == LINEAR_FORWARD)
    {
        if (iter->_index >= self->len(self))
        {
            return false;
        }
    }
    else
    {
        if (iter->_index == 0)
        {
            return false;
        }
    }
    return true;
}

const void *ustring_iter_next(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    ustring_t self = (ustring_t)iter->_container;

    size_t index = iter->_index;
    if (iter->_order == LINEAR_FORWARD)
    {
        iter->_index++;
    }
    else
    {
        iter->_index = iter->_index - 1;
    }
    return self->_darray->at(self->_darray, index);
}

iterator_t ustring_iter(struct _ustring *self, linear_order_t order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;
    if (iter->_order == LINEAR_FORWARD)
    {
        iter->_index = 0;
    }
    else
    {
        iter->_index = self->len(self) - 1;
    }

    iter->hasnext = ustring_iter_hasnext;
    iter->next = ustring_iter_next;
    return iter;
}

static size_t ustring_index(struct _ustring *self, const void *obj)
{
    unicstl_assert(self != NULL);
    return self->search(self, obj);
}

static bool ustring_contains(struct _ustring *self, const void *obj)
{
    unicstl_assert(self != NULL);
    return self->search(self, obj) != (size_t)-1;
}

static bool darry_sort(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->sort(self->_darray);
}

static size_t darry_search(struct _ustring *self, const void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->search(self->_darray, obj);
}

static size_t darry_count(struct _ustring *self, const void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->count(self->_darray, obj);
}

bool ustring_isdigit(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isdigit(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}
bool ustring_isalpha(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isalpha(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isalnum(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isalnum(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isspace(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isspace(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_islower(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!islower(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isupper(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isupper(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_iscntrl(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!iscntrl(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isprint(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isprint(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_ispunct(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!ispunct(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isgraph(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isgraph(*(char *)self->_darray->at(self->_darray, i)))
        {
            return false;
        }
    }
    return true;
}

const char *ustring_cstr(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return (const char *)self->_darray->obj;
}

bool ustring_tolower(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        *(char *)self->_darray->at(self->_darray, i) = tolower(*(char *)self->_darray->at(self->_darray, i));
    }
    return true;
}

bool ustring_toupper(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        *(char *)self->_darray->at(self->_darray, i) = toupper(*(char *)self->_darray->at(self->_darray, i));
    }
    return true;
}

bool ustring_reverse(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    darray_t da = self->_darray;
    char temp = 0;
    for (size_t i = 0; i < self->len(self)/2; i++)
    {
        size_t j = self->len(self) - i - 1;
        da->get(da, i, &temp);
        da->set(da, i, da->at(da, j));
        da->set(da, j, da->at(da, i));
    }
}

static bool ustring_strip(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    return self->strip_left(self) && self->strip_right(self);
}

static bool ustring_strip_left(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    darray_t da = self->_darray;
    for (size_t i = 0; i < da->size(da); i++)
    {
        if (isspace(*(char *)da->at(da, 0)))
        {
            if(!da->remove(da, 0, NULL))
            {
                log_error("da->remove failed!");
                return false;
            }
        }
        else
        {
            break;
        }
    }
    log_warn("TODO: optimize later");
    return true;
}

static bool ustring_strip_right(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    darray_t da = self->_darray;
    for (size_t i = self->len(self) - 1; i >= 0; i--)
    {
        if (isspace(*(char *)da->at(da, i)))
        {
            if(!da->remove(da, i, NULL))
            {
                log_error("da->remove failed!");
                return false;
            }
        }
        else
        {
            break;
        }
    }
    log_warn("TODO: optimize later");
    return true;
}

static bool ustring_init(struct _ustring *self, uview_t view)
{
    unicstl_assert(self != NULL);

    // -------------------- private --------------------
    self->_sorted = false;

    self->_darray = NULL;
    self->_destory = ustring_destory;

    // -------------------- public --------------------
    // kernel
    self->insert = ustring_insert;
    self->remove = ustring_remove;
    self->append = ustring_append;

    self->set = ustring_set;
    self->get = ustring_get;
    self->at = ustring_at;

    // base
    self->reserve = ustring_reserve;
    self->len = ustring_len;
    self->capacity = ustring_capacity;
    self->empty = ustring_empty;
    self->full = ustring_full;
    self->clear = ustring_clear;

    // iter
    self->iter = ustring_iter;

    // sort and search
    self->index = ustring_index;
    self->contains = ustring_contains;
    self->sort = darry_sort;
    self->search = darry_search;

    // string
    self->isdigit = ustring_isdigit;
    self->isalpha = ustring_isalpha;
    self->isalnum = ustring_isalnum;
    self->isspace = ustring_isspace;
    self->islower = ustring_islower;
    self->isupper = ustring_isupper;
    self->iscntrl = ustring_iscntrl;
    self->isprint = ustring_isprint;
    self->ispunct = ustring_ispunct;
    self->isgraph = ustring_isgraph;
    self->cstr = ustring_cstr;
    self->tolower = ustring_tolower;
    self->toupper = ustring_toupper;
    self->reverse = ustring_reverse;

    // strip
    self->strip = ustring_strip;
    self->strip_left = ustring_strip_left;
    self->strip_right = ustring_strip_right;

    // -------------------- default --------------------
    self->print_obj = uprint_char;

    // -------------------- debug --------------------
    self->print = ustring_print;

    // -------------------- malloc --------------------
    self->_darray = darray_new(sizeof(char), view.len + 1);
    if (self->_darray == NULL)
    {
        log_warn("malloc darray failed!");
        return false;
    }
    for (size_t i = 0; i < view.len; i++)
    {
        if(!self->_darray->append(self->_darray, &view.str[i]))
        {
            log_error("append failed!");
            return false;
        }
    }
    if(!self->_darray->append(self->_darray, &null_char))
    {
        log_error("append '\0' failed!");
        return false;
    }
    return true;
}

ustring_t ustring_new(uview_t view)
{
    struct _ustring *ustring = NULL;
    ustring = (struct _ustring *)unicstl_malloc(sizeof(struct _ustring));
    if (ustring == NULL)
    {
        log_warn("ustring malloc failed!");
        return NULL;
    }

    if (ustring_init(ustring, view) != true)
    {
        log_warn("ustring init failed!");
        unicstl_free(ustring);
        return NULL;
    }
    return ustring;
}

void ustring_free(ustring_t *ustring)
{
    if (ustring != NULL && *ustring != NULL)
    {
        if ((*ustring)->_destory != NULL)
        {
            (*ustring)->_destory((*ustring));
        }
        unicstl_free(*ustring);
        *ustring = NULL;
    }
}
