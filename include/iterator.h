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
    // ---------- private ---------- 
    void* _container;   // pointer to stack/queue/tree ...

    void* _node;        // current node 
    uint32_t _index;    // current index
    uint32_t _order;

    // ---------- public ---------- 
    bool (*hasnext)(struct _iterator* self);
    const void* (*next)(struct _iterator* self);
};
typedef struct _iterator* iterator_t;

#endif // !_ITER_H_
