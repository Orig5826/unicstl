#ifndef _TREE_H_
#define _TREE_H_

#include "common.h"

#if AVLTREE == 1 || RAVLTREE == 1
// typedef int tree_data_t;

typedef struct _tree_node_t
{
	tree_data_t data;
	struct _tree_node_t * left;
	struct _tree_node_t * right;
	struct _tree_node_t * parent;
	int32_t balance;		// balance of avl tree
}tree_node_t, *ptree_node_t;


typedef struct _tree_t
{
	struct _tree_node_t * tree;
	uint32_t size;
}tree_t, *ptree_t;

typedef void (*tree_data_disp_t)(tree_data_t data);

#endif


#if RAVLTREE == 1
	bool tree_init(ptree_node_t *head);
	void tree_destroy(ptree_node_t *head);
	bool tree_empty(ptree_node_t head);
	void tree_clear(ptree_node_t head);
	uint32_t tree_get_size(ptree_node_t head);

	bool tree_insert(ptree_node_t head, tree_data_t data);
	bool tree_delete(ptree_node_t head, tree_data_t data);
	bool tree_get_min(ptree_node_t head, tree_data_t *data);
	bool tree_get_max(ptree_node_t head, tree_data_t *data);

	void tree_traversal_depth_preorder(ptree_node_t head, tree_data_disp_t tree_data_disp);
	void tree_traversal_depth_inorder(ptree_node_t head, tree_data_disp_t tree_data_disp);
	//void tree_traversal_depth_postorder(ptree_node_t head, tree_data_disp_t tree_data_disp);
	//void tree_traversal_breadth(ptree_node_t head, tree_data_disp_t tree_data_disp);

#endif

#if AVLTREE == 1
	bool tree_init(ptree_t *head);
	void tree_destroy(ptree_t *head);
	bool tree_empty(ptree_t head);
	void tree_clear(ptree_t head);
	uint32_t tree_get_size(ptree_t head);

	bool tree_insert(ptree_t head, tree_data_t data);
	bool tree_delete(ptree_t head, tree_data_t data);
	bool tree_get_min(ptree_t head, tree_data_t *data);
	bool tree_get_max(ptree_t head, tree_data_t *data);

	void tree_traversal_depth_preorder(ptree_t head, tree_data_disp_t tree_data_disp);
	void tree_traversal_depth_inorder(ptree_t head, tree_data_disp_t tree_data_disp);
	void tree_traversal_depth_postorder(ptree_t head, tree_data_disp_t tree_data_disp);
	void tree_traversal_breadth(ptree_t head, tree_data_disp_t tree_data_disp);
#endif


#endif // _TREE_H_

