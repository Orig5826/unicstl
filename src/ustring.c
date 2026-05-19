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
static const char space_char = ' ';

static size_t ustring_len(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    return self->_alist->size(self->_alist) - 1;
}

static size_t ustring_capacity(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    return self->_alist->capacity(self->_alist) - 1;
}

static bool ustring_empty(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    return self->_alist->empty(self->_alist);
}

static bool ustring_full(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    return self->_alist->full(self->_alist);
}

static bool ustring_clear(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    return self->_alist->clear(self->_alist);
}

static void ustring_destory(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    if (self->_alist != NULL)
    {
        arraylist_free(&self->_alist);
    }
}

static void ustring_print(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    // self->_alist->print_obj = self->print_obj;
    log_debug("ustring_print: len = %d", self->len(self));
    for (size_t i = 0; i < self->len(self); i++)
    {
        self->print_obj(self->at(self, i));
    }
}

static bool ustring_reserve(struct _ustring *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    return self->_alist->reserve(self->_alist, capacity);
}

static bool ustring_resize(struct _ustring *self, size_t size)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    arraylist_t alist = self->_alist;
    if (!alist->resize(alist, size + 1))
    {
        false;
    }
    alist->set(alist, size, &null_char);
    return true;
}

static bool ustring_erase(struct _ustring *self, ssize_t index, size_t count)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    log_debug("erase start");
    if(index >= (ssize_t)self->len(self))
    {
        log_error("index or count error");
        return false;
    }
    if(index + count > (ssize_t)self->len(self))
    {
        count = self->len(self) - index;
    }
    log_debug("index = %d, count = %d", index, count);
    return self->_alist->erase(self->_alist, index, count);
}

static bool ustring_insert(struct _ustring *self, ssize_t index, uview_t v)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);

    size_t len_cur = self->len(self);
    size_t len_sum = len_cur + v.len;

    if (!self->resize(self, len_sum))
    {
        log_error("resize error");
        return false;
    }

    log_debug("insert str: %s", v.str);

    size_t left = len_cur - index;
    ssize_t idx = 0;
    char temp = 0;
    for (size_t i = 0; i < left; i++)
    {
        idx = (ssize_t)len_cur - 1 - i;
        // log_debug("idx = %d", idx);
        if (!self->get(self, idx, &temp))
        {
            log_error("get ustring[i] error");
            return false;
        }

        idx = (ssize_t)len_sum - 1 - i;
        // log_debug("idx = %d", idx);
        if (!self->set(self, idx, &temp))
        {
            log_error("get ustring[i-1] error");
            return false;
        }
    }
    // log_debug("move after index");

    for (ssize_t i = 0; i < v.len; i++)
    {
        if (!self->set(self, index + i, &v.str[i]))
        {
            log_error("ustring_insert error");
            return false;
        }
    }
    // log_debug("set before index");

    if (!self->set(self, len_sum, &null_char))
    {
        log_error("set '\0' error");
        return false;
    }
    return true;
}

uview_t ustring_find(struct _ustring *self, uview_t uvstr)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    uview_t v = {0, 0, UV_NONE};

    v.str = strstr(self->cstr(self), uvstr.str);
    if(v.str != NULL)
    {
        v.len = uvstr.len;
    }
    return v;
}

bool ustring_replace(struct _ustring *self, uview_t oldstr, uview_t newstr)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    uview_t v = self->find(self, oldstr);
    if(v.len == 0)
    {
        log_error("not found");
        return false;
    }
    size_t index = v.str - self->at(self, 0);
    if(!self->erase(self, index, oldstr.len))
    {
        log_error("erase error");
        return false;
    }
    if(!self->insert(self, index, newstr))
    {
        log_error("insert error");
        return false;
    }
    return true;
}

static bool ustring_remove(struct _ustring *self, uview_t oldstr)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);

    uview_t v = self->find(self, oldstr);
    if(v.len == 0)
    {
        log_error("not found");
        return false;
    }
    size_t index = v.str - self->at(self, 0);
    log_debug("remove_idx: %ld", index);
    if(!self->erase(self, index, oldstr.len))
    {
        log_error("erase error");
        return false;
    }
    log_debug("remove ok!");
    return true;
}

// static bool ustring_pop(struct _ustring *self)
// {
//     unicstl_assert(self != NULL);
//     unicstl_assert(self->_alist != NULL);
//     return self->_alist->pop(self->_alist, NULL);
// }

static bool ustring_append(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    arraylist_t alist = self->_alist;
    alist->pop(alist, NULL); // pop '\0' first
    for (size_t i = 0; i < v.len; i++)
    {
        if (!alist->append(alist, &v.str[i]))
        {
            log_error("ustring_append error");
            return false;
        }
    }
    if (!alist->append(alist, &null_char))
    {
        log_error("append '\0' error");
        return false;
    }
    return true;
}

static bool ustring_set(struct _ustring *self, ssize_t index, const char *ch)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    if (index > (ssize_t)self->len(self) + 1)
    {
        log_error("size out of range");
        return false;
    }
    if(index == self->len(self) + 1 && *ch != null_char)
    {
        log_error("!notice: the last char is not null_char");
    }

    if(index < 0)
    {
        index -= 1;
    }
    return self->_alist->set(self->_alist, index, ch);
}

static bool ustring_get(struct _ustring *self, ssize_t index, char *ch)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    if (index > (ssize_t)self->len(self))
    {
        log_error("size out of range");
        return false;
    }
    if(index < 0)
    {
        index -= 1;
    }
    return self->_alist->get(self->_alist, index, ch);
}

static const char *ustring_at(struct _ustring *self, ssize_t index)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    if (index > (ssize_t)self->len(self))
    {
        log_error("size out of range");
        return false;
    }
    if(index < 0)
    {
        index -= 1;
    }
    return self->_alist->at(self->_alist, index);
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
    return self->_alist->at(self->_alist, index);
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

static size_t ustring_index(struct _ustring *self, uview_t uvstr)
{
    unicstl_assert(self != NULL);
    char *p = strstr(self->cstr(self), uvstr.str);
    if(p == NULL)
    {
        return (size_t)-1;
    }
    return p - self->at(self, 0);
}

static bool ustring_contains(struct _ustring *self, uview_t uvstr)
{
    unicstl_assert(self != NULL);
    return self->index(self, uvstr) != (size_t)-1;
}

static size_t ustring_count(struct _ustring *self, uview_t uvstr)
{
    unicstl_assert(self != NULL);
    size_t count = 0;
    char *p = self->cstr(self);
    while(p != '\0')
    {
        p = strstr(p, uvstr.str);
        if(p == NULL)
        {
            break;
        }
        count++;
        p += uvstr.len;
    }
    return count;
}

bool ustring_isdigit(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isdigit(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isxdigit(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isxdigit(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isalpha(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isalpha(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isalnum(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isalnum(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isspace(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isspace(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_islower(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!islower(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isupper(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isupper(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_iscntrl(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!iscntrl(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isprint(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isprint(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_ispunct(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!ispunct(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

bool ustring_isgraph(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        if (!isgraph(*(char *)self->_alist->at(self->_alist, i)))
        {
            return false;
        }
    }
    return true;
}

const char *ustring_cstr(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    return (const char *)self->at(self, 0);
}

bool ustring_tolower(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        *(char *)self->_alist->at(self->_alist, i) = tolower(*(char *)self->_alist->at(self->_alist, i));
    }
    return true;
}

bool ustring_toupper(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    for (size_t i = 0; i < self->len(self); i++)
    {
        *(char *)self->_alist->at(self->_alist, i) = toupper(*(char *)self->_alist->at(self->_alist, i));
    }
    return true;
}

bool ustring_reverse(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    arraylist_t da = self->_alist;
    char temp = 0;
    for (size_t i = 0; i < self->len(self) / 2; i++)
    {
        size_t j = self->len(self) - i - 1;
        da->get(da, i, &temp);
        da->set(da, i, da->at(da, j));
        da->set(da, j, &temp);
    }
}

static bool ustring_strip(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    return self->strip_right(self) && self->strip_left(self);
}

static bool ustring_strip_left(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    arraylist_t da = self->_alist;
    log_debug("strip_left: %ld", da->size(da));
    size_t i = 0;
    for (i = 0; i < da->size(da); i++)
    {
        if (!isspace(*(char *)da->at(da, i)))
        {
            break;
        }
    }
    da->erase(da, 0, i);
    return true;
}

static bool ustring_strip_right(struct _ustring *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    arraylist_t da = self->_alist;
    size_t i = 0;
    for (i = self->len(self) - 1; i >= 0; i--)
    {
        if (!isspace(*(char *)da->at(da, i)))
        {
            break;
        }
    }
    self->resize(self, i + 1);
    return true;
}

bool ustring_ljust(struct _ustring *self, size_t width)
{
    unicstl_assert(self != NULL);
    if (width <= self->len(self))
    {
        return true;
    }
    size_t len = width - self->len(self);
    for (size_t i = 0; i < len; i++)
    {
        self->append(self, uv(" "));
    }
    return true;
}

static bool ustring_rshift(struct _ustring *self, size_t shift, size_t count)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_alist != NULL);
    if(shift + count > self->len(self))
    {
        if(!self->resize(self, shift + count))
        {
            return false;
        }
    }
    char* src = (char*)self->at(self, 0);
    char* dst = src + shift;
    memmove(dst, src, count);
    return true;
}

bool ustring_rjust(struct _ustring *self, size_t width)
{
    unicstl_assert(self != NULL);
    size_t count = self->len(self);
    if(width < count)
    {
        return false;
    }
    if(!self->resize(self, width))
    {
        return false;
    }
    size_t shift = width - count;
    if(!ustring_rshift(self, shift, count))
    {
        log_error("rshift failed");
        return false;
    }
    for(size_t i = 0; i < shift; i++)
    {
        if(!self->set(self, i, &space_char))
        {
            log_error("set failed");
            return false;
        }
    }
    return true;
}

bool ustring_center(struct _ustring *self, size_t width)
{
    unicstl_assert(self != NULL);
    size_t count = self->len(self);
    if(width < count)
    {
        return false;
    }
    if(!self->resize(self, width))
    {
        return false;
    }

    size_t shift = (width - count)/2;
    log_debug("space_cnt: %ld", shift);
    if(!ustring_rshift(self, shift, count))
    {
        log_error("rshift failed");
        return false;
    }

    for(size_t i = 0; i < shift; i++)
    {
        if(!self->set(self, i, &space_char))
        {
            log_error("insert failed");
            return false;
        }
    }

    size_t idx = shift + count;
    if((width - count) % 2 == 1)
    {
        shift += 1;
    }
    for(size_t i = 0; i < shift; i++)
    {
        if(!self->set(self, idx + i, &space_char))
        {
            log_error("insert failed");
            return false;
        }
    }
    return true;
}

int ustring_cmp(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    size_t max = self->len(self) > v.len ? self->len(self) : v.len;
    return strncmp(self->at(self, 0), v.str, max);
}

int ustring_eq(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    return self->cmp(self, v) == 0;
}

int ustring_ne(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    return self->cmp(self, v) != 0;
}

int ustring_lt(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    return self->cmp(self, v) < 0;
}

int ustring_le(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    return self->cmp(self, v) <= 0;
}

int ustring_gt(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    return self->cmp(self, v) > 0;
}

int ustring_ge(struct _ustring *self, uview_t v)
{
    unicstl_assert(self != NULL);
    return self->cmp(self, v) >= 0;
}

struct _ustring* ustring_substr(struct _ustring *self, ssize_t start, ssize_t end)
{
    unicstl_assert(self != NULL);
    log_debug("substr");
    ustring_t substr = ustring_new(uv(""));
    if(substr == NULL)
    {
        return NULL;
    }
    log_debug("ustring_new");
    char ch = 0;
    for(ssize_t i = start; i <= end; i++)
    {
        if(!self->get(self, i, &ch))
        {
            log_error("get failed");
            return NULL;
        }
        log_debug("ch: %c", ch);
        if(!substr->append(substr, uvch(ch)))
        {
            log_error("append failed");
            return NULL;
        }
    }
    return substr;
}

static bool ustring_init(struct _ustring *self, uview_t view, bool is_view)
{
    unicstl_assert(self != NULL);

    // -------------------- private --------------------
    self->_sorted = false;

    self->_alist = NULL;
    self->_destory = ustring_destory;

    self->is_view = is_view;

    // -------------------- public --------------------
    self->set = ustring_set;
    self->get = ustring_get;
    self->at = ustring_at;

    // base
    self->reserve = ustring_reserve;
    self->resize = ustring_resize;
    self->len = ustring_len;
    self->capacity = ustring_capacity;
    self->empty = ustring_empty;
    self->full = ustring_full;
    self->clear = ustring_clear;

    // iter
    self->iter = ustring_iter;

    // 
    self->erase = ustring_erase;

    // append
    self->append = ustring_append;
    self->insert = ustring_insert;

    // 
    self->find = ustring_find;
    self->replace = ustring_replace;
    self->remove = ustring_remove;

    // sort and search
    self->index = ustring_index;
    self->contains = ustring_contains;
    self->count = ustring_count;

    // string
    self->isdigit = ustring_isdigit;
    self->isxdigit = ustring_isxdigit;
    self->isalpha = ustring_isalpha;
    self->isalnum = ustring_isalnum;
    self->isspace = ustring_isspace;
    self->islower = ustring_islower;
    self->isupper = ustring_isupper;
    self->iscntrl = ustring_iscntrl;
    self->isprint = ustring_isprint;
    self->ispunct = ustring_ispunct;
    self->isgraph = ustring_isgraph;

    // format
    self->cstr = ustring_cstr;
    self->tolower = ustring_tolower;
    self->toupper = ustring_toupper;
    self->reverse = ustring_reverse;

    // strip
    self->strip = ustring_strip;
    self->strip_left = ustring_strip_left;
    self->strip_right = ustring_strip_right;
    self->ljust = ustring_ljust;
    self->rjust = ustring_rjust;
    self->center = ustring_center;

    self->eq = ustring_eq;
    self->ne = ustring_ne;
    self->lt = ustring_lt;
    self->le = ustring_le;
    self->gt = ustring_gt;
    self->ge = ustring_ge;
    self->cmp = ustring_cmp;

    // split
    self->substr = ustring_substr;
    // self->split = ustring_split;
    // self->join = ustring_join;

    // -------------------- default --------------------
    self->print_obj = uprint_char;

    // -------------------- debug --------------------
    self->print = ustring_print;

    // -------------------- malloc --------------------
    self->_alist = arraylist_new(sizeof(char), view.len + 1);
    if (self->_alist == NULL)
    {
        log_warn("malloc darray failed!");
        return false;
    }
    for (size_t i = 0; i < view.len; i++)
    {
        if (!self->_alist->append(self->_alist, &view.str[i]))
        {
            log_error("append failed!");
            return false;
        }
    }
    if (!self->_alist->append(self->_alist, &null_char))
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

    if (ustring_init(ustring, view, false) != true)
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

ustring_t ustring_view(uview_t view)
{
    log_error("TODO: implement ustring_view()");
    return NULL;

    struct _ustring *ustring = NULL;
    ustring = (struct _ustring *)unicstl_malloc(sizeof(struct _ustring));
    if (ustring == NULL)
    {
        log_warn("ustring malloc failed!");
        return NULL;
    }

    if (ustring_init(ustring, view, true) != true)
    {
        log_warn("ustring init failed!");
        unicstl_free(ustring);
        return NULL;
    }
    return ustring;
}
