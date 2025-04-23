/**
 * @file iter.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2025-04-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _ITER_H_
#define _ITER_H_

#include "common.h"

struct _iterator
{
    void* obj;
    void* self;
    void* parent;

    void* (*begin)(struct _iterator* self);
    void* (*next)(struct _iterator* self);
    void* (*end)(struct _iterator* self);

    bool (*hasnext)(struct _iterator* self);

    void* (*data)(struct _iterator* self);
};
typedef struct _iterator* iterator_t;

#endif // !_ITER_H_
