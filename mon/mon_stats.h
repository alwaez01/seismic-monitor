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

#endif