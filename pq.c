/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include "pq.h"
#include "dynarray.h"
#include <assert.h>


struct priority_value_node
{
	int priority;
	void *value;
};
/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq;
{
	struct dynarray* da_pq;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* queue = malloc(sizeof(struct pq));
	assert(queue);

	queue->da_pq = dynarray_create();

	return queue;
}


/*
code to swap, compare, adjust node and last one

*/
static void priority_queue_swap(struct pq* pq,
		int pos1, int pos2)
{
	struct priority_value_node* temp1 = NULL;
	struct priority_value_node* temp2 = NULL;
	temp1 = dynarray_get(pq->da_pq, pos1);
	temp2 = dynarray_get(pq->da_pq, pos2);
	dynarray_set(pq->da_pq, pos1, temp2);
	dynarray_set(pq->da_pq, pos2, temp1);
}

static int priority_queue_compare(struct pq* pq, int pos1, int pos2)
{
	int value;
	struct priority_value_node* node1 = NULL;
	struct priority_value_node* node2 = NULL;
	if(dynarray_size(pq->da_pq))
	{
		node1 = dynarray_get(pq->da_pq, pos1);
		node2 = dynarray_get(pq->da_pq, pos2);
		value = node1->priority - node2->priority;

		return value;
	}

	return -1;



}

static void priority_queue_adjust_head(struct pq* pq)
{
	assert(pq);
	int i, j, parent, left, right;
	int size;

	i = j = parent = left = right = 0;

	size = dynarray_size(pq->da_pq);

	while(i < (size - 1) / 2)
	{
		parent = i;
		left = 2 * i + 1;
		right = left + 1;
		j = left;
		if(priority_queue_compare(pq, left, right) > 0)
		{
			j++;
		}
		if(priority_queue_compare(pq, parent, j) > 0)
		{
			priority_queue_swap(pq, i, j);
			i = j;
		}
		else
		{
			break;
		}

	}

}


static void priority_queue_adjust_tail(struct pq* pq)
{
	assert(pq);
	int i, parent, child;

	i = dynarray_size(pq->da_pq) - 2;

	while(i > 0)
	{
		child = i;
		parent = (child - 1) / 2;

		if(priority_queue_compare(pq, parent, child) > 0)
		{
			priority_queue_swap(pq, child, parent);
			i = parent;
		}
		else
		{
			break;
		}
	}
}



/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  assert(pq);
	int i;
	struct priority_value_node* node;


	for(i = 0; i < dynarray_size(pq->da_pq); i++)
	{
		node = dynarray_get(pq->da_pq, i);
		free(node);
	}
	dynarray_free(pq->da_pq);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
	if(dynarray_size(pq->da_pq) == 0)
		return 1;
	else
		return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  assert(pq);
	int size;
	struct priority_value_node* node = malloc(sizeof(struct priority_value_node));
	assert(node);
	node->priority = priority;
	node->value = value;

	dynarray_insert(pq->da_pq, -1, node);
	priority_queue_adjust_tail(pq);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  assert(pq);
	struct priority_value_node* node = NULL;

	if(dynarray_size(pq->da_pq))
	{
		node = dynarray_get(pq->da_pq, 0);
		return node->value;
	}
	return NULL;

}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  assert(pq);
	struct priority_value_node* node = NULL;

	if(dynarray_size(pq->da_pq))
	{
		node = dynarray_get(pq->da_pq, 0);
		return node->priority;
	}

	return -1;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  assert(pq);
	struct priority_value_node* node = NULL;
	int* value;
	int size;

	size = dynarray_size(pq->da_pq);

	if(size)
	{
		node = dynarray_get(pq->da_pq, 0);
		priority_queue_swap(pq, 0, size - 1);
		dynarray_remove(pq->da_pq,-1);
		value = node->value;
		free(node);
		priority_queue_adjust_head(pq);
		return value;
	}

	return NULL;
}
