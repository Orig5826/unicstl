
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


// optional
#define RBTREE		1
#define AVLTREE		0
#define RAVLTREE	0	// avl tree by recursion
#define QUEUE		1
#define STACK		1
#define LIST		1


// --------------------------------------------------
#if RBTREE == 1 && AVLTREE == 1
#error "Rbtree and avltree cannot coexist"
#endif

#if RAVLTREE == 1 && AVLTREE == 1
#error "Recursive avltree and avltree cannot coexist"
#endif

#endif // _CONFIG_H_

