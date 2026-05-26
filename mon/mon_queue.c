#include <stdlib.h>

#include "mon_queue.h"

QUEUE *queue_create(void)
{
     QUEUE *q;

     q = (QUEUE*)malloc(sizeof(QUEUE));
     if (q == NULL)
     {
          return NULL;
     }
     
     q->head = NULL;
     q->tail = NULL;
     q->size = 0;

     return q;
}

void queue_destroy(QUEUE *q)
{
     MEASUREMENT *current;
     MEASUREMENT *next;

     current = q->head;
     while (current != NULL)
     {
          next = current->next;
          free(current);
          current = next;
     }

     free(q);
}