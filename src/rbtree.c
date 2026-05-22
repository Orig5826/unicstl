/**
 * @file rbtree_ree.c
 * @author wenjf (orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-22
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "rbtree.h"

#define RBTREE_NULL ((size_t)-1)

static rbt_node_t *rbt_at(darray_t da, size_t idx)
{
    return (rbt_node_t *)da->at(da, idx);
}

static size_t rbtree_find(struct _rbtree *self, void *obj)
{
    size_t idx = self->_root;
    rbt_node_t node = {0};
    while (idx != RBTREE_NULL)
    {
        if(!self->_nodes->get(self->_nodes, idx, &node))
        {
            return RBTREE_NULL;
        }

        int cmp = self->compare(rbt_at(self->_keys, idx), obj);
        if (cmp < 0)
        {
            if(rbt_at(self->_nodes, idx)->left == RBTREE_NULL)
            {
                break;
            }
            idx = rbt_at(self->_nodes, idx)->left;
        }
        else if(cmp > 0)
        {
            if(rbt_at(self->_nodes, idx)->right != RBTREE_NULL)
            {
                break;
            }
            idx = rbt_at(self->_nodes, idx)->right;
        }
        else
        {
            break;
        }
    }
    return idx;
}

static bool rbtree_insert(struct _rbtree *self, void *obj)
{
    unicstl_assert(self != NULL);
    rbt_node_t node = {0};
    if (self->_root == RBTREE_NULL &&
        self->_nodes->empty(self->_nodes) && self->_keys->empty(self->_keys))
    {
        self->_root = 0;
        node.idx = 0;
        node.parent = RBTREE_NULL;
        node.left = RBTREE_NULL;
        node.right = RBTREE_NULL;
        node.color = RBT_BLACK;

        if (!self->_nodes->append(self->_nodes, &node))
        {
            log_error("append node failed");
            return false;
        }
        if (!self->_keys->append(self->_keys, obj))
        {
            log_error("append key failed");
            return false;
        }
    }
    else
    {
        if (!self->_free->empty(self->_free))
        {
            if (!self->_free->pop(self->_free, &node))
            {
                log_error("pop free node failed");
                return false;
            }
            // keys set
            if (!self->_keys->set(self->_keys, node.idx, obj))
            {
                log_error("set key failed");
                return false;
            }
            // nodes set
        }
        else
        {
            size_t idx = self->size(self);
            if (!self->_keys->append(self->_keys, obj))
            {
                log_error("append key failed");
                return false;
            }
            node.idx = idx;
            node.parent = RBTREE_NULL;
            node.left = RBTREE_NULL;
            node.right = RBTREE_NULL;
            node.color = RBT_BLACK;
            if(!self->_nodes->append(self->_nodes, &node))
            {
                log_error("append node failed");
                return false;
            }

            // find a free node
            size_t root = rbtree_find(self, obj);
            if(root == RBTREE_NULL)
            {
                log_debug("find root failed");
                return false;
            }

            if (self->compare(obj, rbt_at(self->_keys, root)) < 0)
            {
                rbt_at(self->_nodes, root)->left = idx;
                rbt_at(self->_nodes, idx)->parent = root;
            }
            else if (self->compare(obj, rbt_at(self->_keys, root)) > 0)
            {
                rbt_at(self->_nodes, root)->right = idx;
                rbt_at(self->_nodes, idx)->parent = root;
            }

            // rebalance
            // self->_rebalance(self, idx);
        }
    }

    self->_size++;
    return true;
}

static bool rbtree_remove(struct _rbtree *self, void *obj)
{
}

static size_t rbtree_height(struct _rbtree *self)
{
}

static size_t rbtree_size(struct _rbtree *self)
{
    unicstl_assert(self != NULL);
    return self->_size;
}

static size_t rbtree_capacity(struct _rbtree *self)
{
    unicstl_assert(self != NULL);
    self->_capacity = self->_keys->capacity(self->_keys);
    return self->_capacity;
}

static bool rbtree_empty(struct _rbtree *self)
{
    unicstl_assert(self != NULL);
    return self->size(self) == 0;
}

static bool rbtree_full(struct _rbtree *self)
{
    unicstl_assert(self != NULL);
    return self->size(self) == self->capacity(self);
}

static bool rbtree_clear(struct _rbtree *self)
{
    unicstl_assert(self != NULL);
    self->_keys->clear(self->_keys);
    self->_nodes->clear(self->_nodes);
    self->_free->clear(self->_free);
    self->_root = RBTREE_NULL;
    return true;
}

static void rbtree_destory(struct _rbtree *self)
{
    unicstl_assert(self != NULL);
    self->clear(self);
    if (self->_destory)
    {
        darray_free(&self->_keys);
        darray_free(&self->_nodes);
        stack_free(&self->_free);

        stack_free(&self->_stack);
        queue_free(&self->_queue);
    }
}

static bool rbtree_rebalance(struct _rbtree *self, struct _rbt_node *root)
{
    unicstl_assert(self != NULL);
    log_warn("rebalance not implemented yet");
    return true;
}

static iterator_t rbtree_iter(struct _rbtree *self, tree_order_t order)
{
}

static bool rbtree_min(struct _rbtree *self, void *obj)
{
}

static bool rbtree_max(struct _rbtree *self, void *obj)
{
}

static void rbtree_print(struct _rbtree* self)
{
    unicstl_assert(self != NULL);
    self->_keys->print_obj = self->print_obj;
    self->_keys->print(self->_keys);
}

static bool rbtree_init(struct _rbtree *self, size_t obj_size, size_t capacity, compare_fun_t compare)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);
    unicstl_assert(compare != NULL);

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;
    self->_root = RBTREE_NULL;

    self->_rebalance = rbtree_rebalance;
    self->_destory = rbtree_destory;

    // -------------------- public --------------------
    // kernel
    self->insert = rbtree_insert;
    self->remove = rbtree_remove;
    self->height = rbtree_height;

    // base
    self->reserve = NULL;
    self->resize = NULL;
    self->size = rbtree_size;
    self->empty = rbtree_empty;
    self->full = rbtree_full;
    self->clear = rbtree_clear;

    // iter
    self->iter = rbtree_iter;

    // others
    self->max = rbtree_max;
    self->min = rbtree_min;

    // -------------------- default --------------------
    self->compare = default_compare;
    self->print_obj = default_print_obj;
    self->print = rbtree_print;
    if (compare != NULL)
    {
        self->compare = compare;
    }

    // -------------------- init --------------------
    self->_keys = darray_new(obj_size, capacity);
    if (self->_keys == NULL)
    {
        goto done;
    }
    self->_nodes = darray_new(sizeof(rbt_node_t), capacity);
    if (self->_nodes == NULL)
    {
        goto done1;
    }
    self->_free = stack_new(sizeof(rbt_node_t), 8);
    if (self->_free == NULL)
    {
        goto done2;
    }
    self->_stack = stack_new(sizeof(rbt_node_t), 8);
    if (self->_stack == NULL)
    {
        goto done3;
    }
    self->_queue = queue_new(sizeof(rbt_node_t), 8);
    if (self->_queue == NULL)
    {
        goto done4;
    }

    return true;
done5:
    queue_free(&self->_queue);
done4:
    stack_free(&self->_stack);
done3:
    stack_free(&self->_free);
done2:
    darray_free(&self->_nodes);
done1:
    darray_free(&self->_keys);
done:
    return false;
}

rbtree_t rbtree_new(size_t obj_size, size_t capacity, compare_fun_t compare)
{
    rbtree_t tree = NULL;
    tree = (struct _rbtree *)unicstl_malloc(sizeof(struct _rbtree));
    if (tree == NULL)
    {
        log_warn("rbtree malloc failed\n");
        return NULL;
    }

    if (rbtree_init(tree, obj_size, capacity, compare) != true)
    {
        log_warn("rbtree init failed\n");
        unicstl_free(tree);
        return NULL;
    }
    return tree;
}

void rbtree_free(rbtree_t *tree)
{
    if (*tree != NULL)
    {
        (*tree)->_destory(*tree);
        unicstl_free(*tree);
    }
    *tree = NULL;
}
