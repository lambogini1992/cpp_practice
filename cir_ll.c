#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


typedef struct _node_ll_
{
	uint8_t node_id;
	char *data_card;
	bool has_car;

	struct _node_ll_ *next;
	struct _node_ll_ *prev;
}NODE_LL;
uint8_t no_car_park;


NODE_LL *create_node(uint8_t node_id)
{
	NODE_LL *new_node;

	new_node = (NODE_LL *)malloc(sizeof(NODE_LL));

	new_node->node_id 	= node_id;

	new_node->next 		= NULL;
	new_node->prev		= NULL;

	return new_node;
}

void link_node(NODE_LL *start_node, NODE_LL *next, NODE_LL *prev)
{
	start_node->next = next;
	start_node->prev = prev;
}

/*dir is true, that mean direction is clockwise
**dir is false, that mean  direction is anti-clockwise	*/
NODE_LL *scan_empty_node(NODE_LL *start_node, uint8_t *count, bool *dir)
{
	NODE_LL *tmp_node_c;
	NODE_LL *tmp_node_ac;
	uint8_t count_clockwise;
	uint8_t count_aclockwise;

	tmp_node_c = start_node;
	tmp_node_ac = start_node;

	count_aclockwise 	= 0;
	count_clockwise 	= 0;

	/*check with clockwise */
	while(true == tmp_node_c->has_car)
	{
		tmp_node_c = tmp_node_c->next;
		count_clockwise++;
	}

	while(true == tmp_node_ac->has_car)
	{
		tmp_node_ac = tmp_node_ac->prev;
		count_aclockwise++;
	}

	if(count_clockwise <= count_aclockwise)
	{
		*dir = true;
		*count = count_clockwise;
		return tmp_node_c;
	}
	else
	{
		*dir = false;
		*count = count_aclockwise;
		return tmp_node_ac;
	}
}

NODE_LL *check_car(const char *card_id, NODE_LL *start_node, uint8_t *count, bool *dir)
{
	NODE_LL *tmp_node;
	uint8_t count_clockwise;
	uint8_t count_aclockwise;

	count_aclockwise 	= 0;
	count_clockwise 	= 0;

	tmp_node 		= start_node;
	while(1)
	{
		if(strcmp(tmp_node->data_card, card_id) == 0)
		{
			break;
		}
		tmp_node = tmp_node->next;
		count_clockwise++;
	}

	tmp_node 		= start_node;
	while(1)
	{
		if(strcmp(tmp_node->data_card, card_id) == 0)
		{
			break;
		}
		tmp_node = tmp_node->prev;
		count_aclockwise++;
	}

	if(count_clockwise <= count_aclockwise)
	{
		*dir = true;
		*count = count_clockwise;
	}
	else
	{
		*dir = false;
		*count = count_aclockwise;
	}

	return tmp_node;
}

void put_car(NODE_LL *node, const char *card_id)
{
	uint8_t data_len;
	node->has_car = true;

	data_len = strlen(card_id);
	node->data_card = malloc(data_len);
	memcpy(node->data_card, card_id, data_len);
}

void get_car(NODE_LL *node)
{
	node->has_car = false;
	free(node->data_card);
}

void print_ll(NODE_LL *start_node)
{
	NODE_LL *tmp_node;
	int i;

	tmp_node = start_node;

	printf(">>>>PRINT NODE with CLOCKWISE DIRECTION<<<<\n");
	for (i = 0; i < 5; i++)
	{
		printf("NODE ID: %i; NODE NEXT: %i; NODE PREV: %i\n", tmp_node->node_id, tmp_node->next->node_id, tmp_node->prev->node_id);
		tmp_node = tmp_node->next;
	}

	printf(">>>>PRINT NODE with ANTI-CLOCKWISE DIRECTION<<<<\n");
	for (i = 0; i < 5; i++)
	{
		printf("NODE ID: %i; NODE NEXT: %i; NODE PREV: %i\n", tmp_node->node_id, tmp_node->next->node_id, tmp_node->prev->node_id);
		tmp_node = tmp_node->prev;
	}
}

NODE_LL *park_car_proc(NODE_LL *start_node, const char *card_id)
{
	NODE_LL *tmp_node;
	uint8_t count;
	bool dir;

	printf(">>>>>>START PARKING CAR PROCESS<<<<<<<\n");
	tmp_node = start_node;

	start_node = scan_empty_node(tmp_node, &count , &dir);
	printf("start_node id: %i\n", start_node->node_id);

	if(dir == true)
	{
		printf("node %i is emtyp, must turn clockwise direction %i time\n",start_node->node_id, count);
	}
	else
	{
		printf("node %i is emtyp, must turn anti-clockwise direction %i time\n",start_node->node_id, count);
	}

	put_car(start_node, card_id);

	printf("node %i has car with card id is %s\n", start_node->node_id, start_node->data_card);
	printf(">>>>>>>>>>>END PARKING CAR PROCESS<<<<<<<<<<<<\n");
	return start_node;
}

NODE_LL *take_car_proc(NODE_LL *start_node, const char *card_id)
{
	NODE_LL *tmp_node;
	uint8_t count;
	bool dir;

	printf(">>>>>>>>>BEGINNING OF TAKING A CAR PROCESS<<<<<<<<<<<<\n");

	tmp_node = start_node;
	start_node = check_car(card_id, tmp_node, &count, &dir);
	printf("start_node id: %i\n", start_node->node_id);

	if(dir == true)
	{
		printf("node %i has a car with %s card, must turn clockwise direction %i time\n",start_node->node_id, card_id, count);
	}
	else
	{
		printf("node %i has a car with %s card, must turn anti-clockwise direction %i time\n",start_node->node_id, card_id, count);
	}

	get_car(start_node);
	printf("get a car from node %i\n",start_node->node_id);
	printf(">>>>>>>>>END OF TAKING A CAR PROCESS<<<<<<<<<<<<\n");
	return start_node;
}

int main(int argc, char const *argv[])
{
	char card_id[20];
	char cmd[4];

	NODE_LL *node_1 = NULL;
	NODE_LL *node_2 = NULL;
	NODE_LL *node_3 = NULL;
	NODE_LL *node_4 = NULL;
	NODE_LL *node_5 = NULL;

	NODE_LL *start_node = NULL;

	no_car_park = 0;
	node_1 = create_node(1);
	node_2 = create_node(2);
	node_3 = create_node(3);
	node_4 = create_node(4);
	node_5 = create_node(5);

	link_node(node_1, node_2, node_5);
	link_node(node_2, node_3, node_1);
	link_node(node_3, node_4, node_2);
	link_node(node_4, node_5, node_3);
	link_node(node_5, node_1, node_4);
	print_ll(node_1);
	start_node = node_1;

	while(1)
	{
		printf("\nPlease choose mode\n");
		scanf("%s", cmd);
		printf("%s\n", cmd);
		if(strcmp(cmd, "park") == 0)
		{
			if(no_car_park < 5)
			{
				printf("Please enter card id\n");
				scanf("%s", card_id);
				printf("%s\n", card_id);
				start_node = park_car_proc(start_node, (const char *)card_id);
				no_car_park++;
			}
			else
			{
				printf(">>>>>>>>>PARKING CAR IS FULL<<<<<<<<<\n");
			}

		}
		else if(strcmp(cmd, "take") == 0)
		{
			if(no_car_park > 0)
			{
				printf("Please enter card id\n");
				scanf("%s", card_id);
				printf("%s\n", card_id);
				start_node = take_car_proc(start_node, (const char *)card_id);
			}
			else
			{
				printf(">>>>>>>>>PARKING CAR IS EMPTY<<<<<<<<<\n");
			}
		}
	}

	return 0;
}
