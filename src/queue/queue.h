#ifndef TSQ_H
#define TSQ_H

#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE(typename, type) \
	typedef struct typename##TSQ_NODE{ \
		struct typename##TSQ_NODE* next; \
		struct typename##TSQ_NODE* prev; \
		type data; \
	}typename##TSQ_NODE; \
 \
	typename##TSQ_NODE* typename##TSQ_NODE_INIT(type data); \
 \
	void typename##TSQ_NODE_FREE(typename##TSQ_NODE* n); \
 \
	typedef struct typename{ \
		typename##TSQ_NODE* head; \
		typename##TSQ_NODE* end;	 \
		uint32_t size; \
	}typename; \
 \
	typename typename##Init(); \
 \
	void typename##Free(typename* q); \
 \
	void typename##Push(typename* q, type data); \
 \
	type typename##Pop(typename* q); \
 \


#define QUEUE_SOURCE(typename, type) \
	typename##TSQ_NODE* typename##TSQ_NODE_INIT(type data){ \
		typename##TSQ_NODE* n = malloc(sizeof(typename##TSQ_NODE)); \
		n->data = data; \
		n->next = NULL; \
		n->prev = NULL; \
		return n; \
	} \
 \
	void typename##TSQ_NODE_FREE(typename##TSQ_NODE* n){ \
		while (n){ \
			typename##TSQ_NODE* temp = n; \
			n = n->next; \
			temp->prev = NULL; \
			temp->next = NULL; \
			free(temp); \
			temp= NULL; \
		} \
		n = NULL; \
	} \
	typename typename##Init(){ \
		typename q; \
		q.head = NULL; \
		q.end = NULL; \
		q.size = 0; \
		return q; \
	} \
 \
	void typename##Free(typename* q){ \
		typename##TSQ_NODE_FREE(q->head); \
		q->head = NULL; \
		q->size = 0; \
	} \
 \
	void typename##Push(typename* q, type data){ \
		q->size++; \
		typename##TSQ_NODE* n = typename##TSQ_NODE_INIT(data); \
		if (q->head == NULL){ \
			q->head = n; \
			q->end = q->head; \
			return; \
		} \
		q->end->next = n; \
		n->prev = q->end; \
		q->end = n; \
	} \
 \
	type typename##Pop(typename* q){ \
		type dat; \
		if (q->head != NULL){ \
			q->size--; \
			dat = q->head->data; \
			typename##TSQ_NODE* n = q->head; \
			q->head = q->head->next; \
			n->next = NULL; \
			typename##TSQ_NODE_FREE(n); \
			n = NULL; \
		} \
		return dat; \
	} \
	\


#endif
