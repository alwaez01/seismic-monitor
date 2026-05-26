#ifndef MON_QUEUE_H
#define MON_QUEUE_H

#define QUEUE_OK         0
#define QUEUE_ERR_MEM   -1
#define QUEUE_ERR_EMPTY -2

typedef struct MEASUREMENT
{
     int                 sensor_id;
     int                 intensity;
     long long           timestamp_ms;
     struct MEASUREMENT *next;
} MEASUREMENT;

typedef struct
{
     MEASUREMENT *head;
     MEASUREMENT *tail;
     int          size;
} QUEUE;

MEASUREMENT *measurement_create(int sensor_id, int intensity, long long timestamp_ms);
void         measurement_destroy(MEASUREMENT *m);

QUEUE *queue_create(void);
void   queue_destroy(QUEUE *q);
int    queue_push(QUEUE *q, MEASUREMENT *m);
int    queue_pop_head(QUEUE *q);

#endif