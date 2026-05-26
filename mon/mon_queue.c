#include <stdlib.h>

#include "mon_queue.h"

MEASUREMENT *measurement_create(int sensor_id, int intensity, long long timestamp_ms)
{
     MEASUREMENT *m;

     m = (MEASUREMENT*)malloc(sizeof(MEASUREMENT));
     if (m == NULL)
     {
          return NULL;
     }

     m->sensor_id    = sensor_id;
     m->intensity    = intensity;
     m->timestamp_ms = timestamp_ms;
     m->next         = NULL;

     return m;
}

void measurement_destroy(MEASUREMENT *m)
{
     free(m);
}

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