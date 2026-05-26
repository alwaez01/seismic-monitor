#ifndef MON_QUEUE_H
#define MON_QUEUE_H

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

#endif