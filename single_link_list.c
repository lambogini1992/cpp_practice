#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct node
{
	int data;
	struct node *next;
}NODE;

typedef struct single_ll
{
	int node_count;
	int node_max;
	NODE *head;
	NODE *tail;
}SINGLE_LL;

SINGLE_LL *LL_create(int node_max)
{
	SINGLE_LL *linklist = NULL;

	linklist = (SINGLE_LL *)malloc(sizeof(SINGLE_LL));

	linklist->head = NULL;
	linklist->tail = NULL;
	linklist->node_count = 0;
	linklist->node_max = node_max;

	return linklist;
}

bool LL_empty(SINGLE_LL *ll)
{
	if(ll->node_count == 0)
	{
		return true;
	}
	return false;
}

bool LL_full(SINGLE_LL *ll)
{
	if(ll->node_count == ll->node_max)
	{
		return true;
	}
	return false;
}

int LL_scan_node(SINGLE_LL *ll, int data_check)
{
	NODE *check_node;
	int idx;
	if(LL_empty(ll))
	{
		printf("linklist empty\n");
		return -1;
	}

	check_node = ll->head;
	idx = 0;

	while(check_node != NULL)
	{
		if(check_node->data == data_check)
		{
			break;
		}
		idx++;
		check_node = check_node->next;
	}
}

NODE LL_scan_node_v2(SINGLE_LL ll, int data_check)
{
	NODE *check_node;
	int idx;
	if(LL_empty(ll))
	{
		printf("linklist empty\n");
		return -1;
	}

	check_node = ll->head;
	idx = 0;

	while(check_node != NULL)
	{
		if(check_node->data == data_check)
		{
			break;
		}
		idx++;
		check_node = check_node->next;
	}
	return check_node;
}

bool LL_add_node_head(SINGLE_LL *ll, int data)
{
	NODE *new_node;

	if(LL_full(ll))
	{
		printf("linklist is full\n");
		return false;
	}

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->data = data;
	new_node->next = NULL;

	if(LL_empty(ll))
	{
		ll->head = new_node;
		ll->tail = new_node;
	}
	else
	{
		new_node->next = ll->head;
		ll->head = new_node;
	}
	ll->node_count++;
	return true;
}

bool LL_add_node_tail(SINGLE_LL *ll, int data)
{
	NODE *new_node;
	if (LL_full(ll))
	{
		printf("linklist is full\n");
		return false;
	}

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->data = data;
	new_node->next = NULL;

	if(LL_empty(ll))
	{
		ll->head = new_node;
		ll->tail = new_node;
	}
	else
	{
		ll->tail->next = new_node;
		ll->tail = new_node;
	}
	ll->node_count++;
	return true;
}

bool LL_insert_node(SINGLE_LL *ll, int data_new, int data_prev)
{
	NODE *new_node;
	NODE *prev_node;
	if (LL_full(ll))
	{
		printf("linklist is full\n");
		return false;
	}

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->data = data_new;
	new_node->next = NULL;

	prev_node = LL_scan_node_v2(ll, data_prev);

	new_node->next = prev_node->next;
	prev_node->next = new_node;

	return true;
}

int LL_delete_node(SINGLE_LL *ll, int data_check)
{
	NODE *check_node;
	NODE *prev_node = NULL;

	if(LL_empty(ll))
	{
		printf("linklist empty\n");
		return -1;
	}

	check_node = ll->head;
	if(check_node->data == data_check)
	{
		ll->head = check_node->next;
		return 0;
	}

	while(check_node != NULL)
	{
		if(check_node->data == data_check)
		{
			prev_node->next = check_node->next;
			if(check_node == ll->tail)
			{
			ll->tail = prev_node;
			}
			free(check_node);
			ll->node_count--;
		}
		prev_node = check_node;
		check_node = check_node->next;
	}
	return 0;
}



void LL_print(SINGLE_LL *ll)
{
	NODE *node;
	if(LL_empty(ll))
	{
		return;
	}

	node = ll->head;

	while(1)
	{
		printf("%d", node->data);
		node = node->next;
		if(node == NULL)
		{
			printf("\n");
			break;
		}
		printf(" -> ");
	}
}

int main(void)
{
	SINGLE_LL *ll;

	ll = LL_create(10);

	LL_add_node_head(ll, 10);
	LL_add_node_head(ll, 2);
	LL_add_node_tail(ll, 134);
	LL_add_node_tail(ll, 26);
	LL_add_node_tail(ll, 13);
	LL_add_node_tail(ll, 14);

	LL_print(ll);

	LL_delete_node(ll, 134);
	LL_add_node_head(ll, 21);
	LL_add_node_tail(ll, 33);

	LL_print(ll);

	LL_insert_node(ll, 15, 26);

	LL_print(ll);

	return 0;
}