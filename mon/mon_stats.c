#include <stdlib.h>

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
