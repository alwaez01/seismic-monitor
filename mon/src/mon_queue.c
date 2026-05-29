#include <stdio.h>
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

int queue_push(QUEUE *q, MEASUREMENT *m)
{
     if (m == NULL)
     {
          return QUEUE_ERR_MEM;
     }

     m->next = NULL;

     if (q->tail == NULL)
     {
          q->head = m;
          q->tail = m;
     }
     else
     {
          q->tail->next = m;
          q->tail       = m;
     }

     q->size++;

     return QUEUE_OK;
}

int queue_pop_head(QUEUE *q)
{
     MEASUREMENT *expired;

     if (q->head == NULL)
     {
          return QUEUE_ERR_EMPTY;
     }

     expired = q->head;
     q->head = q->head->next;

     if (q->head == NULL)
     {
          q->tail = NULL;
     }

     measurement_destroy(expired);
     q->size--;

     return QUEUE_OK;
}

MEASUREMENT *input_read(void)
{
     char      buf[INPUT_BUFFER_SIZE];
     int       sensor_id;
     int       value;
     long long timestamp_ms;
     int       parsed;

     if (fgets(buf, INPUT_BUFFER_SIZE, stdin) == NULL)
     {
          return NULL;
     }

     parsed = sscanf(buf, "%d %d %lld", &sensor_id, &value, &timestamp_ms);
     if (parsed != 3)
     {
          return NULL;
     }

     return measurement_create(sensor_id, value, timestamp_ms);
}