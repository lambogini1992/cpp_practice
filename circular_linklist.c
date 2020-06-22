#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct node
{
  int data;
  struct node *node_next;
}NODE;

typedef struct _cir_ll_
{
  NODE *head;
  NODE *tail;
  int count;
  int max_count;
}CIR_LL;

CIR_LL *creat_circular_ll(int max_count)
{
	CIR_LL *ll;

	ll = (CIR_LL *)malloc(sizeof(CIR_LL));
	ll->head = NULL;
	ll->tail = NULL;
	ll->max_count = max_count;
	ll->count = 0;
}

bool check_ll_empty(CIR_LL *ll)
{
	if((ll->count == 0))
	{
		printf("linklist empty\n");
		return true;
	}
	return false;
}

bool check_ll_full(CIR_LL *ll)
{
	if(ll->count == ll->max_count)
	{
		printf("linklist full\n");
		return true;
	}
	return false;
}

bool add_node_at_head(CIR_LL *ll, int data)
{
	NODE *new_node;

	if(check_ll_full(ll))
	{
		return false;
	}

	new_node = (NODE *)malloc(sizeof(NODE));
	if(new_node == NULL)
	{
		return false;
	}
	new_node->data = data;
	new_node->node_next = NULL;
	// printf("DEBUG\n");
	if(check_ll_empty(ll))
	{
		ll->head = new_node;
		ll->tail = new_node;
	}
	else
	{
		// printf("DEBUG\n");
		// printf("ll->tail->data: %d\n", ll->tail->data);
		// printf("ll->head->data: %d\n", ll->head->data);
		new_node->node_next = ll->head->node_next;
		ll->tail->node_next = new_node;
		ll->head = new_node;
	}
	ll->count++;
	return true;
}

bool add_node_at_tail(CIR_LL *ll, int data)
{
	NODE *new_node;

	if(check_ll_full(ll))
	{
		return false;
	}

	new_node = (NODE *)malloc(sizeof(NODE));
	if(new_node == NULL)
	{
		return false;
	}
	new_node->data = data;
	new_node->node_next = NULL;
	// printf("DEBUG\n");
	if(check_ll_empty(ll))
	{
		ll->head = new_node;
		ll->tail = new_node;
	}
	else
	{
		// printf("DEBUG\n");
		// printf("ll->tail->data: %d\n", ll->tail->data);
		// printf("ll->head->data: %d\n", ll->head->data);
		ll->tail->node_next = new_node;
		new_node->node_next = ll->head;
		ll->tail = new_node;

	}
	ll->count++;
	return true;
}

void del_all_node(CIR_LL *ll)
{
	NODE *node;
	NODE *rm_node;

	node = ll->head;
	while(1)
	{
		rm_node = node;
		node    = node->node_next;
		free(rm_node);
		if(node == ll->tail)
		{
			free(node);
			break;
		}
	}
	ll->count = 0;
}

int del_node_from_head(CIR_LL *ll, int no_node)
{
	NODE *node;
	NODE *rm_node;
	int idx;

	if(no_node > ll->count)
	{
		return (ll->max_count - ll->count);
	}
	else if((ll->count - no_node) == 0)
	{
		del_all_node(ll);
		return ll->max_count;
	}
	else if((ll->count - no_node) > 0)
	{
		idx = 0;
		node = ll->head;
		while(idx != no_node)
		{
			rm_node = node;
			node = node->node_next;
			idx++;
			free(rm_node);
		}
		ll->head = node;
		ll->tail->node_next = node;
		ll->count = ll->count - no_node;
	}
	return (ll->max_count - ll->count);
}

int del_node_from_tail(CIR_LL *ll, int no_node)
{
	NODE *node;
	NODE *tmp_tail;
	NODE *rm_node;
	int idx;

	if(no_node > ll->count)
	{
		return (ll->max_count - ll->count);
	}
	else if((ll->count - no_node) == 0)
	{
		del_all_node(ll);
		return ll->max_count;
	}
	else if((ll->count - no_node) > 0)
	{
		node = ll->head;
		idx = 0;
		while(idx != (ll->count - no_node - 1))
		{
			node = node->node_next;
			idx++;
		}
		tmp_tail = node;
		node = node->node_next;
		idx = no_node;
		while(idx != 0)
		{
			rm_node = node;
			node = node->node_next;
			idx--;
			free(rm_node);
			if(node == ll->head)
			{
				break;
			}
		}
		tmp_tail->node_next = ll->head;
		ll->tail = tmp_tail;
		ll->count = ll->count - no_node;
	}

	return (ll->max_count - ll->count);
}

int check_node(CIR_LL *ll, int data_check)
{
	NODE *check_node;
	NODE *prev_node;
	int count;

	if(check_ll_empty(ll))
	{
		printf("ll empty\n");
		return -1;
	}

	check_node = ll->head;
	prev_node = ll->tail;

	count = 0;
	if(data_check == ll->tail->data)
	{
		return (ll->count - 1);
	}

	while(check_node != ll->tail)
	{
		if(check_node->data == data_check)
		{
			return count;
		}
		if(count == 0)
		{
			if(prev_node->data == data_check)
			{
				return ll->count;
			}
		}
		count++;
		prev_node = check_node;
		check_node = check_node->node_next;
	}
	return -1;
}

bool ll_print(CIR_LL *ll)
{
	NODE *temp_node = NULL;

	if(check_ll_empty(ll))
	{
		return false;
	}
	printf("linklist: ");
	temp_node = ll->head;

	while(1)
	{
		printf("%d ", temp_node->data);
		temp_node = temp_node->node_next;

		if(temp_node == ll->head)
			break;

		printf(" -> ");
	}
	printf("\n");
	return true;
}

bool rotation_ll(CIR_LL *ll, int time)
{
	// NODE *temp_node;
	int temp_time;
	if(check_ll_empty(ll))
	{
		return true;
	}

	temp_time = time;
	if(ll->count <= 1)
	{
		return true;
	}

	while(temp_time != 0)
	{
		ll->head = ll->head->node_next;
		ll->tail = ll->tail->node_next;
		temp_time--;
	}
}

int main(int argc, char const *argv[])
{
	CIR_LL *linklist = NULL;
	int i;

	linklist = creat_circular_ll(16);
	if(linklist == NULL)
	{
		return -1;
	}
	for(i = 1; i <= 16; i++)
	{
		if(add_node_at_tail(linklist, i) == false)
			return -1;
	}

	printf("node at idx: %d\n", check_node(linklist, 4));
	(void)ll_print(linklist);


	

	// (void)ll_print(linklist);
	printf("remain node for write: %d\n", del_node_from_tail(linklist, 4));
	
	rotation_ll(linklist, 4);

	(void)ll_print(linklist);

	printf("remain node for write: %d\n", del_node_from_head(linklist, 2));
	(void)ll_print(linklist);

	return 0;
}