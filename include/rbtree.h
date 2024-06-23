
#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "common.h"

#if RBTREE == 1
typedef int rbtree_data_t;

typedef struct _rbtree_node_t
{
	rbtree_data_t data;
	struct _rbtree_node_t * left;
	struct _rbtree_node_t * right;
	struct _rbtree_node_t * parent;
	uint32_t color;
}rbtree_node_t, *prbtree_node_t;

typedef struct _rbtree_t
{
	struct _rbtree_node_t * tree;
	uint32_t size;
}rbtree_t, *prbtree_t;


typedef void (*tree_data_disp_t)(rbtree_data_t data);


bool rbtree_init(prbtree_t *head);
void rbtree_destroy(prbtree_t * head);
bool rbtree_empty(prbtree_t head);
void rbtree_clear(prbtree_t head);
uint32_t rbtree_get_size(prbtree_t head);
bool rbtree_insert(prbtree_t head, rbtree_data_t data);
bool rbtree_delete(prbtree_t head, rbtree_data_t data);


bool rbtree_get_min(prbtree_t head, rbtree_data_t *data);
bool rbtree_get_max(prbtree_t head, rbtree_data_t *data);
void rbtree_traversal_depth_preorder(prbtree_t head, tree_data_disp_t tree_data_disp);
void rbtree_traversal_depth_inorder(prbtree_t head, tree_data_disp_t tree_data_disp);
void rbtree_traversal_depth_postorder(prbtree_t head, tree_data_disp_t tree_data_disp);
void rbtree_traversal_breadth(prbtree_t head, tree_data_disp_t tree_data_disp);

// check
bool rbtree_check(prbtree_t head);
#endif

#endif // _RBTREE_H_
