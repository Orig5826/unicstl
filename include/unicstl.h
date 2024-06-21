
#ifndef _DEMO_H_
#define _DEMO_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#if RBTREE == 1
#include "rbtree.h"
	typedef prbtree_node_t stack_data_t;
	typedef prbtree_node_t queue_data_t;

	typedef int list_data_t;
#elif AVLTREE == 1
#include "tree.h"
	typedef ptree_node_t stack_data_t;
	typedef ptree_node_t queue_data_t;
#else
	typedef int stack_data_t;
	typedef int queue_data_t;
	typedef int list_data_t;
#endif

#endif // _DEMO_H_

