#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
	node* next;
	unsigned value;
};

typedef struct
{
	node* end;
	node* start;
	int size;
} queue;

// Complexity O(1)
queue* queue_create()
{
	queue* newQueue = (queue*)malloc(sizeof(queue));
	newQueue->size = 0;
	newQueue->start = NULL;
	newQueue->end = NULL;

	return newQueue;
}

// Complexity O(1)
int queue_size(queue* q)
{
	if (q == NULL)
		exit(1);

	return q->size;
}

// Complexity O(1)
void queue_enqueue(queue* q, int d)
{
	if (q == NULL)
		exit(1);

	if (queue_size(q) == 0)
	{
		node* temp = (node*)malloc(sizeof(node));
		temp->next = NULL;
		temp->value = d;

		q->start = temp;
		q->end = temp;
	}
	else
	{
		node* temp = (node*)malloc(sizeof(node));
		temp->next = NULL;
		temp->value = d;

		q->end->next = temp;
		q->end = q->end->next;
	}

	q->size += 1;
}
	
// Complexity O(1)
unsigned queue_dequeue(queue* q)
{
	if (q == NULL)
		exit(1);
	if (q->size == 0)
		exit(1);

	int result = q->start->value;
	q->start = q->start->next;
	q->size -= 1;

	return result;
}

#endif
