#include <stdio.h>
#include <stdlib.h>

#include "mon_parser.h"
#include "mon_queue.h"
#include "mon_stats.h"

int main(int argc, char **argv)
{
     MON_CONFIG   cfg;
     QUEUE       *q;
     STATS       *s;
     MEASUREMENT *m;
     double       mean;
     double       stddev;
     int          result;
     int          i;

     result = parse_args(&cfg, argc, argv);
     if (result != PARSER_OK)
     {
          printf("error parsing arguments: %d\n", result);
          return 1;
     }

     q = queue_create();
     if (q == NULL)
     {
          printf("failed to create queue\n");
          return 1;
     }

     s = stats_create(cfg.sensor_count);
     if (s == NULL)
     {
          printf("failed to create stats\n");
          queue_destroy(q);
          return 1;
     }

     while ((m = input_read()) != NULL)
     {
          stats_add(s, m->sensor_id, m->intensity);
          queue_push(q, m);

          printf("queue size: %d\n", q->size);
          for (i = 0; i < cfg.sensor_count; i++)
          {
               stats_mean(s, i, &mean);
               stats_stddev(s, i, &stddev);
               printf("sensor %d | count: %d | mean: %.2f | stddev: %.2f\n",
                    i, s->sensors[i].count, mean, stddev);
          }
     }

     stats_destroy(s);
     queue_destroy(q);

     return 0;
}