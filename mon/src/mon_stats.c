#include <stdlib.h>
#include <math.h>

#include "mon_stats.h"

STATS *stats_create(int sensor_count)
{
     STATS *s;
     int    i;

     s = (STATS*)malloc(sizeof(STATS));
     if (s == NULL)
     {
          return NULL;
     }

     s->sensors = (SENSOR_STATS*)malloc(sizeof(SENSOR_STATS) * sensor_count);
     if (s->sensors == NULL)
     {
          free(s);
          return NULL;
     }

     s->sensor_count = sensor_count;

     for (i = 0; i < sensor_count; i++)
     {
          s->sensors[i].count  = 0;
          s->sensors[i].sum    = 0.0;
          s->sensors[i].sum_sq = 0.0;
     }

     return s;
}

void stats_destroy(STATS *s)
{
     free(s->sensors);
     free(s);
}

void stats_add(STATS *s, int sensor_id, int value)
{
     s->sensors[sensor_id].count  += 1;
     s->sensors[sensor_id].sum    += value;
     s->sensors[sensor_id].sum_sq += (double)value * value;
}

void stats_remove(STATS *s, int sensor_id, int value)
{
     s->sensors[sensor_id].count  -= 1;
     s->sensors[sensor_id].sum    -= value;
     s->sensors[sensor_id].sum_sq -= (double)value * value;
}

int stats_mean(STATS *s, int sensor_id, double *result)
{
     if (s->sensors[sensor_id].count == 0)
     {
          return STATS_ERR_NO_DATA;
     }

     *result = s->sensors[sensor_id].sum / s->sensors[sensor_id].count;

     return STATS_OK;
}

int stats_stddev(STATS *s, int sensor_id, double *result)
{
     double mean;

     if (s->sensors[sensor_id].count == 0)
     {
          return STATS_ERR_NO_DATA;
     }

     mean    = s->sensors[sensor_id].sum / s->sensors[sensor_id].count;
     *result = sqrt(s->sensors[sensor_id].sum_sq / s->sensors[sensor_id].count - mean * mean);

     return STATS_OK;
}