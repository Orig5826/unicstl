
#include "rbtree.h"
#include "stack.h"
#include "queue.h"

#if RBTREE == 1

// ----------------------------------------
// rbtree ���Ը���
#define RBT_COLOR(x)			((x)->color)
#define RBT_COLOR_INIT(x)		(RBT_COLOR(x) = 0)

// color <- bit[0]
#define RBT_COLOR_MASK	(0x01)
#define RBT_BALCK		(0x01)
#define BRT_RED			(0x00)

#define RBT_SET_RED(x)			(RBT_COLOR(x) &= ~RBT_BALCK)
#define RBT_SET_BLACK(x)		(RBT_COLOR(x) |= RBT_BALCK)
#define RBT_IS_BLACK(x)			(((RBT_COLOR(x) & RBT_BALCK) == RBT_BALCK)?true:false)
#define RBT_IS_RED(x)			(!RBT_IS_BLACK(x))
#define RBT_COLOR_ASSIGN(a,b)	(RBT_COLOR(a) = RBT_COLOR(b))

// ----------------------------------------
// visited node <- bit[1:2]
#define RBT_VISIT_FLAG_MASK			(0x06)
#define RBT_VISIT_FLAG_LEFT			(0x04)
#define RBT_VISIT_FLAG_RIGHT		(0x02)

#define RBT_VISIT_CLR(x)			(RBT_COLOR(x) &= ~RBT_VISIT_FLAG_MASK)
#define RBT_VISIT_LEFT(x)			(RBT_COLOR(x) |= RBT_VISIT_FLAG_LEFT)
#define RBT_VISIT_RIGHT(x)			(RBT_COLOR(x) |= RBT_VISIT_FLAG_RIGHT)
#define RBT_IS_VISITED_LEFT(x)		(((RBT_COLOR(x) & RBT_VISIT_FLAG_LEFT) == RBT_VISIT_FLAG_LEFT)?\
	true:false)
#define RBT_IS_VISITED_RIGHT(x)		(((RBT_COLOR(x) & RBT_VISIT_FLAG_RIGHT) == RBT_VISIT_FLAG_RIGHT)?\
	true:false)



/**
 * ��������
 */
static bool rbtree_insert_fixup(prbtree_t head, prbtree_node_t tree);
static bool rbtree_delete_fixup(prbtree_t head, prbtree_node_t tree);


bool rbtree_init(prbtree_t *head)
{
	*head = (prbtree_t)malloc(sizeof(rbtree_t));
	if (*head == NULL)
	{
		return false;
	}
	(*head)->tree = NULL;
	(*head)->size = 0;
	return true;
}

void rbtree_destroy(prbtree_t * head)
{
	if (*head != NULL)
	{
		rbtree_clear(*head);
		free(*head);
		*head = NULL;
	}
}

bool rbtree_empty(prbtree_t head)
{
	return ((head == NULL) || (head->tree == NULL)) ? true : false;
}

void rbtree_clear(prbtree_t head)
{
	pqueue_t queue;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	if ((head == NULL) || head->tree == NULL)
	{
		return;
	}
	root = head->tree;

	queue_init(&queue);
	queue_in(queue, root);

	while (!queue_empty(queue))
	{
		queue_out(queue, &tree_node);
		if (tree_node->left != NULL)
		{
			queue_in(queue, tree_node->left);
		}
		if (tree_node->right != NULL)
		{
			queue_in(queue, tree_node->right);
		}

		free(tree_node);
		tree_node = NULL;
	}

	queue_destroy(&queue);

	head->tree = NULL;
	head->size = 0;
}

uint32_t rbtree_get_size(prbtree_t head)
{
	return head->size;
}

static prbtree_node_t rbtree_find(prbtree_t head, rbtree_data_t data)
{
	prbtree_node_t root;

	if ((head == NULL) || head->tree == NULL)
	{
		return NULL;
	}
	root = head->tree;

	while (root != NULL)
	{
		if (data < root->data)
		{
			if (root->left != NULL)
			{
				root = root->left;
			}
			else
			{
				return root;
			}
		}
		else if (data > root->data)
		{
			if (root->right != NULL)
			{
				root = root->right;
			}
			else
			{
				return root;
			}
		}
		else
		{
			// ==
			return root;
		}
	}

	return root;
}

static prbtree_node_t get_parent_node(prbtree_node_t tree)
{
	if (tree == NULL)
	{
		return NULL;
	}
	return tree->parent;
}

bool rbtree_insert(prbtree_t head, rbtree_data_t data)
{
	prbtree_node_t tree_node;
	prbtree_node_t new_node;

	if (head == NULL)
	{
		return false;
	}

	// no root of tree
	if (head->tree == NULL)
	{
		new_node = (prbtree_node_t)malloc(sizeof(rbtree_node_t));
		if (new_node == NULL)
		{
			return false;
		}
		new_node->data = data;
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->parent = NULL;	// the parent of root is NULL
		RBT_COLOR_INIT(new_node);

		head->tree = new_node;
	}
	else
	{
		tree_node = rbtree_find(head, data);
		if (data < tree_node->data)
		{
			new_node = (prbtree_node_t)malloc(sizeof(rbtree_node_t));
			if (new_node == NULL)
			{
				return false;
			}
			new_node->data = data;
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->parent = tree_node;
			RBT_COLOR_INIT(new_node);

			tree_node->left = new_node;
		}
		else if(data > tree_node->data)
		{
			new_node = (prbtree_node_t)malloc(sizeof(rbtree_node_t));
			if (new_node == NULL)
			{
				return false;
			}
			new_node->data = data;
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->parent = tree_node;
			RBT_COLOR_INIT(new_node);

			tree_node->right = new_node;
		}
		else
		{
			// ��key��ȣ�������˵Ӧ���滻valueֵ��
			// ����Ĵ�������Ǹ����̼򵥹���ʾ����
			// data����һ�����ݣ���˴˴�ֱ�Ӻ��ԡ�
			return true;
		}
	}

	rbtree_insert_fixup(head, new_node);

	if (head->size < _UI32_MAX)
	{
		head->size++;
	}
	return true;
}


static prbtree_node_t rbtree_turn_left(prbtree_node_t tree)
{
	// �Ե�ǰ�ڵ�Ϊ������ת
	// ע�⸸�ڵ㲢������ֻ��Ϊ�������µ��ӽڵ�
	// 
	prbtree_node_t node_n;		// ��ǰ�ڵ�
	prbtree_node_t node_nr;		// ��ǰ�ڵ�����ӽڵ�
	prbtree_node_t node_p;		// ��ǰ�ڵ�ĸ��ڵ�

	if (tree == NULL)
	{
		return NULL;
	}
	node_n = tree;
	node_nr = node_n->right;
	node_p = node_n->parent;

	// 1. ����node_p�ӽڵ�
	if (node_p != NULL)
	{
		// not root of tree
		if (node_p->left == node_n)
		{
			node_p->left = node_nr;
		}
		else
		{
			node_p->right = node_nr;
		}
	}
	node_nr->parent = node_p;

	// 2. ��ת
	node_n->parent = node_nr;	// ����ֱ��node_p=node_nr��ԭ���㶮��
	node_n->right = node_nr->left;
	node_nr->left = node_n;
	if (node_n->right != NULL)
	{
		node_n->right->parent = node_n;
	}

	// 3. �����µĽڵ�
	return node_nr;
}


static prbtree_node_t rbtree_turn_right(prbtree_node_t tree)
{
	// �Ե�ǰ�ڵ�Ϊ������ת
	// ע�⸸�ڵ㲢������ֻ��Ϊ�������µ��ӽڵ�
	// 
	prbtree_node_t node_n;		// ��ǰ�ڵ�
	prbtree_node_t node_nl;		// ��ǰ�ڵ�����ӽڵ�
	prbtree_node_t node_p;		// ��ǰ�ڵ�ĸ��ڵ�

	if (tree == NULL)
	{
		return NULL;
	}
	node_n = tree;
	node_nl = node_n->left;
	node_p = node_n->parent;

	// 1. ����node_p�ӽڵ�
	if (node_p != NULL)
	{
		// not node_n
		if (node_p->left == node_n)
		{
			node_p->left = node_nl;
		}
		else
		{
			node_p->right = node_nl;
		}
	}
	node_nl->parent = node_p;

	// 2. ��ת
	node_n->parent = node_nl;	// ����ֱ��node_p=node_nl��ԭ���㶮��
	node_n->left = node_nl->right;
	node_nl->right = node_n;
	if (node_n->left != NULL)
	{
		node_n->left->parent = node_n;
	}

	// 3. �����µĽڵ�
	return node_nl;
}

static bool rbtree_insert_fixup(prbtree_t head, prbtree_node_t tree)
{
	prbtree_node_t father, grandfather, uncle;
	if ((head == NULL) || head->tree == NULL)
	{
		return false;
	}

	if (tree == NULL)
	{
		return false;
	}

	// ---------------------------------------
	// case1.���ڵ㲻���ڣ���ֱ�Ӳ����ɫ�ڵ�
	// case2.���ڵ�Ϊ�ڣ������ɫ�ڵ�Կ�
	// ���������������Ҫ���insert������⣩
	// case3.��Ҫ��Ϊ����������ǣ�����
	// �����ҶԳƣ������������������Ҳ�Ͳ����ˣ�
	// ----------------------------------------
	while (tree->parent != NULL && RBT_IS_RED(tree->parent))
	{
		father = get_parent_node(tree);
		grandfather = get_parent_node(father);
		
		if (father == grandfather->left)
		{
			uncle = grandfather->right;
			if (uncle != NULL && RBT_IS_RED(uncle))
			{
				RBT_SET_BLACK(father);
				RBT_SET_BLACK(uncle);
				RBT_SET_RED(grandfather);
				tree = grandfather;
			}
			else
			{
				if (tree == father->right)
				{
					tree = rbtree_turn_left(father);
					RBT_SET_BLACK(tree);
				}
				else
				{
					RBT_SET_BLACK(father);
				}
				RBT_SET_RED(grandfather);
				tree = rbtree_turn_right(grandfather);
				break;
			}
		}
		else
		{
			uncle = grandfather->left;
			if (uncle != NULL && RBT_IS_RED(uncle))
			{
				RBT_SET_BLACK(father);
				RBT_SET_BLACK(uncle);
				RBT_SET_RED(grandfather);
				tree = grandfather;
			}
			else
			{
				if (tree == father->left)
				{
					tree = rbtree_turn_right(father);
					RBT_SET_BLACK(tree);
				}
				else
				{
					RBT_SET_BLACK(father);
				}
				RBT_SET_RED(grandfather);
				tree = rbtree_turn_left(grandfather);
				break;
			}
		}
	}

	if (tree->parent == NULL)
	{
		head->tree = tree;
		RBT_SET_BLACK(head->tree);
	}

	return true;
}

static prbtree_node_t tree_get_node_min(prbtree_node_t tree)
{
	while (tree != NULL)
	{
		if (tree->left != NULL)
		{
			tree = tree->left;
		}
		else
		{
			return tree;
		}
	}
	return tree;
}

bool rbtree_delete(prbtree_t head, rbtree_data_t data)
{
	prbtree_node_t tree_node;		//��ǰ����ɾ���Ľڵ�
	prbtree_node_t tree_node_del;	//ʵ���ϱ�ɾ���Ľڵ�

	if ((head == NULL) || head->tree == NULL)
	{
		return false;
	}
	
	tree_node = rbtree_find(head, data);
	if (tree_node == NULL)
	{
		return false;
	}

	if (tree_node->data != data)
	{
		// û���ҵ��ò���
		return false;
	}

	if (tree_node->left == NULL && tree_node->right == NULL)
	{
		tree_node_del = tree_node;
	}
	else if (tree_node->left != NULL && tree_node->right == NULL)
	{
		tree_node_del = tree_node->left;
		tree_node->data = tree_node_del->data;
	}
	else if (tree_node->left == NULL && tree_node->right != NULL)
	{
		tree_node_del = tree_node->right;
		tree_node->data = tree_node_del->data;
	}
	else
	{
		// ˫�Ӷ��ڣ�����Һ�̽ڵ�
		tree_node_del = tree_get_node_min(tree_node->right);

		tree_node->data = tree_node_del->data;
		if (tree_node_del->right != NULL)
		{
			// �غ�
			tree_node_del->data = tree_node_del->right->data;
			tree_node_del = tree_node_del->right;
		}
	}

	if (RBT_IS_BLACK(tree_node_del))
	{
		rbtree_delete_fixup(head, tree_node_del);
	}

	// ��tree��ɾ��
	if (tree_node_del->parent != NULL)
	{
		if (tree_node_del == tree_node_del->parent->left)
		{
			tree_node_del->parent->left = NULL;
		}
		else
		{
			tree_node_del->parent->right = NULL;
		}
	}
	else
	{
		// ��Ϊ���ڵ�
		head->tree = NULL;
	}
	// �ͷ��ڴ�
	free(tree_node_del);

	if (head->size > 0)
	{
		head->size--;
	}
	return true;
}

static bool rbtree_delete_fixup(prbtree_t head, prbtree_node_t tree)
{
	prbtree_node_t node_temp = NULL;
	prbtree_node_t father, brother;
	if ((head == NULL) || head->tree == NULL)
	{
		return false;
	}

	while ((tree->parent != NULL) && RBT_IS_BLACK(tree))
	{
		father = get_parent_node(tree);
		if (tree == father->left)
		{
			brother = father->right;
			if (RBT_IS_RED(brother))
			{
				// ����rbtree���ʣ����ڵ�ض�Ϊ�ڣ�
				// ��brother���ӽڵ�˫�ڻ���˫��
				// case 5
				RBT_SET_BLACK(brother);
				RBT_SET_RED(father);
				node_temp = rbtree_turn_left(father);
				// �ڵ�δɾ��ʱƽ�⣬����ɾ��֮���ֲ�ƽ����
				// �����Ҫ�����ж�
			}
			else if(brother->right != NULL && RBT_IS_RED(brother->right))
			{
				// ��bother����right�ڵ㣬����Ϊ��ɫ�����
				// ���ڵ���ɫδ֪
				// case 1 �������Ӻ죩�� case 3��˫�Ӻ죩 ������һ��
				RBT_COLOR_ASSIGN(brother,father);	//color(f) -> color(b)
				RBT_SET_BLACK(father);
				RBT_SET_BLACK(brother->right);
				tree = rbtree_turn_left(father);
				// ɾ���ڵ�֮�󣬿϶�ƽ���ˣ�����˳�
				// ���⣬��ת֮�����պ��Ǹ��ڵ㡣��ֵ��tree
				// ����ѭ�������ж�
				break;
			}
			else if(brother->left != NULL && RBT_IS_RED(brother->left))
			{
				// ��bother����left�ڵ㣬��leftΪ��ɫ,����rigth����������
				// ���ڵ���ɫδ֪
				// case 2
				// ע�⣺����д����Ļ����������case2ǰ���ж�case1/case3
				RBT_SET_RED(brother);
				RBT_SET_BLACK(brother->left);
				node_temp = rbtree_turn_right(brother);
				// ���ת��Ϊ��case 1
			}
			else
			{
				// ��brother���ӽڵ�Ϊ˫�ջ�˫��
				// case 4
				if(RBT_IS_BLACK(father))
				{
					// �����ڵ�Ϊ�ڣ���brotherȾΪ��ɫ��
					// ��������������һ�ڣ�����Ը��ڵ�Ϊtree���ϵݹ�
					RBT_SET_RED(brother);
					tree = father;
				}
				else
				{
					// brother˫�ӿգ����ʾbrother�ͱ�ɾ���Ľڵ�ƽ��
					// ���ֱ��ת����ɫ����
					RBT_SET_RED(brother);
					RBT_SET_BLACK(father);
					// ɾ���ڵ�֮�󣬿϶�ƽ���ˣ�����˳�
					break;
				}
			}
		}
		else
		{
			brother = father->left;
			if (RBT_IS_RED(brother))
			{
				// ����rbtree���ʣ����ڵ�ض�Ϊ�ڣ�
				// ��brother���ӽڵ�˫�ڻ���˫��
				// case 5
				RBT_SET_BLACK(brother);
				RBT_SET_RED(father);
				node_temp = rbtree_turn_right(father);
				// �ڵ�δɾ��ʱƽ�⣬����ɾ��֮���ֲ�ƽ����
				// �����Ҫ�����ж�
			}
			else if (brother->left != NULL && RBT_IS_RED(brother->left))
			{
				// ��bother����left�ڵ㣬����Ϊ��ɫ�����
				// ���ڵ���ɫδ֪
				// case 1 �������Ӻ죩�� case 3��˫�Ӻ죩 ������һ��
				RBT_COLOR_ASSIGN(brother,father);
				RBT_SET_BLACK(father);
				RBT_SET_BLACK(brother->left);
				tree = rbtree_turn_right(father);
				// ɾ���ڵ�֮�󣬿϶�ƽ���ˣ�����˳�
				// ���⣬��ת֮�����պ��Ǹ��ڵ㡣��ֵ��tree
				// ����ѭ�������ж�
				break;
			}
			else if (brother->right != NULL && RBT_IS_RED(brother->right))
			{
				// ��bother����right�ڵ㣬��rightΪ��ɫ������left����������
				// ���ڵ���ɫδ֪
				// case 2
				// ע�⣺����д����Ļ����������case2ǰ���ж�case1/case3
				RBT_SET_RED(brother);
				RBT_SET_BLACK(brother->right);
				node_temp = rbtree_turn_left(brother);
				// ���ת��Ϊ�� case 1
			}
			else
			{
				// ��brother���ӽڵ�Ϊ˫�ջ�˫��
				// case 4
				if(RBT_IS_BLACK(father))
				{
					// �����ڵ�Ϊ�ڣ���brotherȾΪ��ɫ��
					// ��������������һ�ڣ�����Ը��ڵ�Ϊtree���ϵݹ�
					RBT_SET_RED(brother);
					tree = father;
				}
				else
				{
					// brother˫�ӿգ����ʾbrother�ͱ�ɾ���Ľڵ�ƽ��
					// ���ֱ��ת����ɫ����
					RBT_SET_RED(brother);
					RBT_SET_BLACK(father);
					// ɾ���ڵ�֮�󣬿϶�ƽ���ˣ�����˳�
					break;
				}
			}
		}

		// �ڴ�������У���ֹ���ڵ㶪ʧ
		if (node_temp != NULL && node_temp->parent == NULL)
		{
			head->tree = node_temp;
		}
	}

	if (tree->parent == NULL)
	{
		head->tree = tree;
	}

	RBT_SET_BLACK(head->tree);
	return true;
}



bool rbtree_get_min(prbtree_t head, rbtree_data_t *data)
{
	prbtree_node_t root;

	if ((head == NULL) || head->tree == NULL)
	{
		return false;
	}
	root = head->tree;

	while (root != NULL)
	{
		if (root->left != NULL)
		{
			root = root->left;
		}
		else
		{
			*data = root->data;
			return true;
		}
	}
	return false;
}

bool rbtree_get_max(prbtree_t head, rbtree_data_t *data)
{
	prbtree_node_t root;
	if ((head == NULL) || head->tree == NULL)
	{
		return false;
	}
	root = head->tree;

	while (root != NULL)
	{
		if (root->right != NULL)
		{
			root = root->right;
		}
		else
		{
			*data = root->data;
			return true;
		}
	}
	return false;
}

#if  1
void rbtree_traversal_depth_preorder(prbtree_t head, tree_data_disp_t tree_data_disp)
{
	pstack_t stack;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	if ((head == NULL) || head->tree == NULL)
	{
		return;
	}
	root = head->tree;

	stack_init(&stack);
	tree_node = root;
	while (!stack_empty(stack) || tree_node != NULL)
	{
		if (tree_node != NULL)
		{
			tree_data_disp(tree_node->data);

			stack_push(stack, tree_node);
			tree_node = tree_node->left;
		}
		else
		{
			stack_pop(stack, &tree_node);
			tree_node = tree_node->right;
		}
	}

	stack_destroy(&stack);
}

void rbtree_traversal_depth_inorder(prbtree_t head, tree_data_disp_t tree_data_disp)
{
	pstack_t stack;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	if ((head == NULL) || head->tree == NULL)
	{
		return;
	}
	root = head->tree;

	stack_init(&stack);
	tree_node = root;
	while (!stack_empty(stack) || tree_node != NULL)
	{
		if (tree_node != NULL)
		{
			stack_push(stack, tree_node);
			tree_node = tree_node->left;
		}
		else
		{
			stack_pop(stack, &tree_node);
			tree_data_disp(tree_node->data);
			tree_node = tree_node->right;
		}
	}

	stack_destroy(&stack);
}

void rbtree_traversal_depth_postorder(prbtree_t head, tree_data_disp_t tree_data_disp)
{
	pstack_t stack;
	pstack_t stack_disp;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	if ((head == NULL) || head->tree == NULL)
	{
		return;
	}
	root = head->tree;

	stack_init(&stack);
	stack_init(&stack_disp);
	tree_node = root;
	while (!stack_empty(stack) || tree_node != NULL)
	{
		if (tree_node != NULL)
		{
			stack_push(stack_disp, tree_node);

			stack_push(stack, tree_node);
			tree_node = tree_node->right;
		}
		else
		{
			stack_pop(stack, &tree_node);
			tree_node = tree_node->left;
		}
	}

	while (!stack_empty(stack_disp))
	{
		stack_pop(stack_disp, &tree_node);
		tree_data_disp(tree_node->data);
	}

	stack_destroy(&stack);
	stack_destroy(&stack_disp);
}
#else 
// -------------------------------------------------
// ��ʽ2 �����˷��ʱ�־�������и����ƣ��������߶�
// -------------------------------------------------
void rbtree_traversal_depth_preorder(prbtree_t head, tree_data_disp_t tree_data_disp)
{
	pstack_t stack;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	if ((head == NULL) || head->tree == NULL)
	{
		return;
	}
	root = head->tree;

	stack_init(&stack);
	stack_push(stack, root);
	tree_data_disp(root->data);
	while (!stack_empty(stack))
	{
		stack_get_top(stack, &tree_node);

		if (tree_node->left != NULL && !RBT_IS_VISITED_LEFT(tree_node))
		{
			RBT_VISIT_LEFT(tree_node);

			stack_push(stack, tree_node->left);
			tree_node = tree_node->left;

			tree_data_disp(tree_node->data);
		}
		else if (tree_node->right != NULL && !RBT_IS_VISITED_RIGHT(tree_node))
		{
			RBT_VISIT_RIGHT(tree_node);

			stack_push(stack, tree_node->right);
			tree_node = tree_node->right;

			tree_data_disp(tree_node->data);
		}
		else
		{
			RBT_VISIT_CLR(tree_node);
			stack_pop(stack, &tree_node);
		}
	}

	stack_destroy(&stack);
}

void rbtree_traversal_depth_inorder(prbtree_t head, tree_data_disp_t tree_data_disp)
{
	pstack_t stack;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	if ((head == NULL) || head->tree == NULL)
	{
		return;
	}
	root = head->tree;

	stack_init(&stack);
	stack_push(stack, root);
	while (!stack_empty(stack))
	{
		stack_get_top(stack, &tree_node);

		if (tree_node->left != NULL && !RBT_IS_VISITED_LEFT(tree_node))
		{
			RBT_VISIT_LEFT(tree_node);
			
			stack_push(stack, tree_node->left);
			tree_node = tree_node->left;
		}
		else if (tree_node->right != NULL && !RBT_IS_VISITED_RIGHT(tree_node))
		{
			RBT_VISIT_RIGHT(tree_node);
			
			tree_data_disp(tree_node->data);
			
			stack_push(stack, tree_node->right);
			tree_node = tree_node->right;
		}
		else
		{
			if (!RBT_IS_VISITED_RIGHT(tree_node))
			{
				tree_data_disp(tree_node->data);
			}

			RBT_VISIT_CLR(tree_node);
			stack_pop(stack, &tree_node);
		}
	}

	stack_destroy(&stack);
}

void rbtree_traversal_depth_postorder(prbtree_t head, tree_data_disp_t tree_data_disp)
{
	pstack_t stack;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	if ((head == NULL) || head->tree == NULL)
	{
		return;
	}
	root = head->tree;

	stack_init(&stack);
	stack_push(stack, root);
	while (!stack_empty(stack))
	{
		stack_get_top(stack, &tree_node);

		if (tree_node->left != NULL && !RBT_IS_VISITED_LEFT(tree_node))
		{
			RBT_VISIT_LEFT(tree_node);

			stack_push(stack, tree_node->left);
			tree_node = tree_node->left;
		}
		else if (tree_node->right != NULL && !RBT_IS_VISITED_RIGHT(tree_node))
		{
			RBT_VISIT_RIGHT(tree_node);

			stack_push(stack, tree_node->right);
			tree_node = tree_node->right;
		}
		else
		{
			RBT_VISIT_CLR(tree_node);
			stack_pop(stack, &tree_node);

			tree_data_disp(tree_node->data);
		}
	}

	stack_destroy(&stack);
}
#endif


void rbtree_traversal_breadth(prbtree_t head, tree_data_disp_t tree_data_disp)
{
	pqueue_t queue;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	if ((head == NULL) || head->tree == NULL)
	{
		return;
	}
	root = head->tree;

	queue_init(&queue);
	queue_in(queue, root);
	if (root != NULL)
	{
		while (!queue_empty(queue))
		{
			queue_out(queue, &tree_node);
			if (tree_node->left != NULL)
			{
				queue_in(queue, tree_node->left);
			}
			if (tree_node->right != NULL)
			{
				queue_in(queue, tree_node->right);
			}

			tree_data_disp(tree_node->data);
		}
	}

	queue_destroy(&queue);
}


static bool rbtree_node_check(prbtree_node_t tree_node)
{
	// check
	if (tree_node->parent == NULL)
	{
		if (RBT_IS_RED(tree_node))
		{
			return false;
		}
	}
	else
	{
		if (RBT_IS_RED(tree_node))
		{
			if (tree_node->left != NULL && tree_node->right != NULL)
			{
				if (RBT_IS_RED(tree_node->left) || RBT_IS_RED(tree_node->right))
				{
					// error
					return false;
				}
			}
			else if (tree_node->left != NULL && tree_node->right == NULL)
			{
				// error 
				return false;
			}
			else if (tree_node->left == NULL && tree_node->right != NULL)
			{
				// error 
				return false;
			}
			else
			{
				// pass
			}
		}
		else
		{
			if (tree_node->left != NULL && tree_node->right == NULL)
			{
				if (RBT_IS_BLACK(tree_node->left))
				{
					// error 
					return false;
				}
			}
			else if (tree_node->left == NULL && tree_node->right != NULL)
			{
				if (RBT_IS_BLACK(tree_node->right))
				{
					// error 
					return false;
				}
			}
			else
			{
				// pass
			}
		}
	}

	return true;
}


bool rbtree_check(prbtree_t head)
{
	pstack_t stack;
	prbtree_node_t root;
	prbtree_node_t tree_node;

	bool ret = true;
	uint32_t black_cnt = 0, black_cnt_max = 0;

	if ((head == NULL) || head->tree == NULL)
	{
		// ok
		return ret;
	}
	root = head->tree;

	if (RBT_IS_RED(root))
	{
		ret = false;
		return ret;
	}
	else
	{
		black_cnt++;
		if (black_cnt > black_cnt_max)
		{
			black_cnt_max = black_cnt;
		}
	}

	stack_init(&stack);
	stack_push(stack, root);
	while (!stack_empty(stack))
	{
		stack_get_top(stack,&tree_node);

		if (tree_node->left != NULL && !RBT_IS_VISITED_LEFT(tree_node))
		{
			RBT_VISIT_LEFT(tree_node);

			stack_push(stack, tree_node->left);
			tree_node = tree_node->left;

			if (RBT_IS_BLACK(tree_node))
			{
				black_cnt++;
				if (black_cnt > black_cnt_max)
				{
					black_cnt_max = black_cnt;
				}
			}
		}
		else if (tree_node->right != NULL && !RBT_IS_VISITED_RIGHT(tree_node))
		{
			RBT_VISIT_RIGHT(tree_node);

			stack_push(stack, tree_node->right);
			tree_node = tree_node->right;

			if (RBT_IS_BLACK(tree_node))
			{
				black_cnt++;
				if (black_cnt > black_cnt_max)
				{
					black_cnt_max = black_cnt;
				}
			}
		}
		else
		{
			if (tree_node->left == NULL && tree_node->right == NULL)
			{
				if (black_cnt != black_cnt_max)
				{
					ret = false;
					goto black_check_exit;
				}
			}

			RBT_VISIT_CLR(tree_node);
			stack_pop(stack, &tree_node);

			if (RBT_IS_BLACK(tree_node))
			{
				if (black_cnt > 0)
				{
					black_cnt--;
				}
			}

			// check node
			if (true != rbtree_node_check(tree_node))
			{
				ret = false;
				goto black_check_exit;
			}
		}
	}

black_check_exit:
	stack_destroy(&stack);
	return ret;
}

#endif // RBTREE == 1

