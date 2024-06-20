
#include "stack.h"

static uint32_t stack_capacity(struct _stack* s)
{
	assert(s != NULL);
	return s->_capacity;
}

static uint32_t stack_size(struct _stack* s)
{
	assert(s != NULL);
	return s->_size;
}

static bool stack_empty(struct _stack* s)
{
	assert(s != NULL);
	// assert(s->_head != NULL);
	// return s->_head->next == NULL ? true : false;
	return !stack_size(s);
}

static bool stack_peek(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	assert(obj != NULL);

	if (s->empty(s))
	{
		return false;
	}

	struct _stack_node * node = s->_head->next;
	memmove(obj, node->obj, s->_obj_size);
	return true;
}

static bool stack_push(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	assert(obj != NULL);

	void* new_obj = (void*)calloc(1, s->_obj_size);
	if (new_obj == NULL)
	{
		return false;
	}
	memmove(new_obj, obj, s->_obj_size);

	struct _stack_node* new_node = (struct _stack_node*)malloc(sizeof(struct _stack_node));
	if (new_node == NULL)
	{
		return false;
	}
	new_node->obj = new_obj;
	new_node->next = s->_head->next;
	s->_head->next = new_node;

	s->_size += 1;
	return true;
}

static bool stack_pop(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	// assert(obj != NULL);
	
	if (s->empty(s))
	{
		return false;
	}

	struct _stack_node* node = s->_head->next;

	if (obj != NULL)
	{
		// 将弹出的数据输出
		memmove(obj, node->obj, s->_obj_size);
	}

	// 更新指针
	s->_head->next = node->next;

	// 释放数据和节点
	free(node->obj);
	free(node);

	s->_size -= 1;
	return true;
}

static bool stack_clear(struct _stack* s)
{
	assert(s != NULL);

	if (s->empty(s))
	{
		return false;
	}

	struct _stack_node* node = s->_head->next;
	while (node != NULL)
	{
		// 更新指针
		s->_head->next = node->next;

		// 释放数据和节点
		free(node->obj);
		free(node);

		node = s->_head->next;
	}
	s->_size = 0;
	return true;
}

static void stack_destory(struct _stack* s)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	
	s->clear(s);
	free(s->_head);
	s->_head = NULL;
}

static void stack_print(struct _stack* s)
{
	uint32_t i = 0;
	struct _stack_node* node = s->_head->next;
	while (node != NULL)
	{
		s->print_obj(node->obj);
		node = node->next;
	}
}

bool stack_init(struct _stack* s, uint32_t obj_size)
{
	assert(s != NULL);

	// 1. set attr
	s->_obj_size = obj_size;
	s->_size = 0;
	// s->_capacity = 64;
	
	// 2. set function
	s->clear = stack_clear;
	s->empty = stack_empty;
	s->peek = stack_peek;
	s->pop = stack_pop;
	s->push = stack_push;
	s->size = stack_size;
	s->destory = stack_destory;
	s->print = stack_print;

	// 3. set node
	s->_head = (struct _stack_node *)malloc(sizeof(struct _stack_node));
	if (s->_head == NULL)
	{
		return false;
	}
	s->_head->obj = NULL;
	s->_head->next = NULL;

	return true;
}


static bool stack2_peek(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	assert(obj != NULL);

	if (s->empty(s))
	{
		return false;
	}

	uint32_t top = s->size(s) - 1;
	uint32_t offset = top * s->_obj_size;
	memmove(obj, (char *)s->_head->obj + offset, s->_obj_size);
	return true;
}

static bool stack2_push(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	assert(obj != NULL);

	void* new_obj = (void*)calloc(1, s->_obj_size);
	if (new_obj == NULL)
	{
		return false;
	}
	memmove(new_obj, obj, s->_obj_size);

	struct _stack_node* new_node = (struct _stack_node*)malloc(sizeof(struct _stack_node));
	if (new_node == NULL)
	{
		return false;
	}
	new_node->obj = new_obj;
	new_node->next = s->_head->next;
	s->_head->next = new_node;

	s->_size += 1;
	return true;
}

static bool stack2_pop(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	// assert(obj != NULL);

	if (s->_head->next == NULL)
	{
		return false;
	}

	struct _stack_node* node = s->_head->next;

	if (obj != NULL)
	{
		// 将弹出的数据输出
		memmove(obj, node->obj, s->_obj_size);
	}

	// 更新指针
	s->_head->next = node->next;

	// 释放数据和节点
	free(node->obj);
	free(node);

	s->_size -= 1;
	return true;
}

static void stack2_print(struct _stack* s)
{
	uint32_t i = 0;
	struct _stack_node* node = s->_head->next;
	while (node != NULL)
	{
		s->print_obj(node->obj);
		node = node->next;
	}
}

bool stack2_init(struct _stack* s, uint32_t obj_size)
{
	assert(s != NULL);

	// 1. set attr
	s->_obj_size = obj_size;
	s->_size = 0;
	s->_capacity = 64;

	// 2. set function
	s->clear = stack_clear;
	s->empty = stack_empty;
	s->peek = stack2_peek;
	s->pop = stack2_pop;
	s->push = stack2_push;
	s->size = stack_size;
	s->destory = stack_destory;
	s->print = stack2_print;

	// 3. set node
	s->_head = (struct _stack_node*)malloc(sizeof(struct _stack_node));
	if (s->_head == NULL)
	{
		return false;
	}
	// s->_head->obj = NULL;
	s->_head->next = NULL;		// 无效参数

	// 4. set array
	s->_head->obj = (void *)calloc(s->_capacity, s->_obj_size);
	if (s->_head->obj == NULL)
	{
		return false;
	}
	return true;
}


void print_num(void *obj)
{
	printf("(%2d )", *(int*)obj);
}

void stack_test_num(void)
{
	uint32_t i = 0;
	int data[] = {1,2,3,4,5,6,7,8,9,10};
	int temp = 0;
	uint32_t len = sizeof(data)/sizeof(data[0]);

	struct _stack s;
	stack_init(&s, sizeof(int));
	s.print_obj = print_num;

	printf("\n\n----- stack_test_num -----\n");
	// get top if stack is empty
	s.peek(&s, &temp);

	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		s.push(&s, &data[i]);

		s.peek(&s, &temp);

		printf("top = ");
		s.print_obj(&temp);
		printf("\tsize after push = %2d\n", s.size(&s));
	}
	printf("----- print -----\n");
	s.print(&s);
	printf("\n");

	printf("----- pop -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == s.pop(&s, &temp))
		{
			printf("top = ");
			s.print_obj(&temp);
			printf("\tsize after push = %2d\n", s.size(&s));
		}
		else
		{
			printf("pop failed! because stack is empty\n");
		}

		if (s.empty(&s))
		{
			printf("----- empty -----\n");
		}
	}

	s.destory(&s);
}

void print_char(void* obj)
{
	printf("(%2c )", *(char*)obj);
}

void stack_test_char(void)
{
	uint32_t i = 0;
	char data[] = "abcdefghijk";
	char temp = 0;
	uint32_t len = sizeof(data) / sizeof(data[0]) - 1;

	struct _stack s;
	stack_init(&s, sizeof(char));
	s.print_obj = print_char;

	printf("\n\n----- stack_test_char -----\n");
	// get top if stack is empty
	s.peek(&s, &temp);

	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		s.push(&s, &data[i]);

		s.peek(&s, &temp);
		printf("top = ");
		s.print_obj(&temp);
		printf("\tsize after push = %2d\n", s.size(&s));
	}
	printf("----- print -----\n");
	s.print(&s);
	printf("\n");

	printf("----- pop -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == s.pop(&s, &temp))
		{
			printf("top = ");
			s.print_obj(&temp);
			printf("\tsize after push = %2d\n", s.size(&s));
		}
		else
		{
			printf("pop failed! because stack is empty\n");
		}

		if (s.empty(&s))
		{
			printf("----- empty -----\n");
		}
	}

	s.destory(&s);
}


struct _student
{
	char name[16];
	int id;
};

void print_struct(void* obj)
{
	struct _student * student = (struct _student*)obj;
	printf("(%2d:%-5s ) ", student->id, student->name);
}

void stack_test_struct(void)
{
	uint32_t i = 0;
	struct _student data[] = {
		{"zhao", 1001},{"qian", 1002}, {"sun", 1003}, {"li", 1004},
		"zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008, 
	};
	struct _student temp = {0};
	uint32_t len = sizeof(data) / sizeof(data[0]);

	struct _stack s;
	stack_init(&s, sizeof(struct _student));
	s.print_obj = print_struct;

	printf("\n\n----- stack_test_struct -----\n");
	// get top if stack is empty
	s.peek(&s, &temp);

	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		s.push(&s, &data[i]);

		s.peek(&s, &temp);
		printf("top = ");
		s.print_obj(&temp);
		printf("\tsize after push = %2d\n", s.size(&s));
	}
	printf("----- print -----\n");
	s.print(&s);
	printf("\n");

	printf("----- clear -----\n");
	s.clear(&s);
	printf("----- print -----\n");
	s.print(&s);
	printf("\n");
	
	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		s.push(&s, &data[i]);
	}

	printf("----- pop -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == s.pop(&s, &temp))
		{
			printf("top = ");
			s.print_obj(&temp);
			printf("\tsize after push = %2d\n", s.size(&s));
		}
		else
		{
			printf("pop failed! because stack is empty\n");
		}

		if (s.empty(&s))
		{
			printf("----- empty -----\n");
		}
	}

	s.destory(&s);
}

void stack_test(void)
{
	stack_test_num();
	stack_test_char();
	stack_test_struct();
}
