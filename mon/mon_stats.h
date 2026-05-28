#ifndef MON_STATS_H
#define MON_STATS_H

typedef struct
{
     int    count;
     double sum;
     double sum_sq;
} SENSOR_STATS;

typedef struct
{
     SENSOR_STATS *sensors;
     int           sensor_count;
} STATS;

STATS *stats_create(int sensor_count);
void   stats_destroy(STATS *s);

void   stats_add(STATS *s, int sensor_id, int value);
void   stats_remove(STATS *s, int sensor_id, int value);
void   stats_mean(STATS *s, int sensor_id, double *result);
void   stats_stddev(STATS *s, int sensor_id, double *result);

#endif