#include <stdio.h>
#include <time.h>

#include "mon_display.h"

void display_render(STATS *s, MON_CONFIG *cfg)
{
     time_t     now;
     struct tm *t;
     char       time_buf[16];
     double     mean;
     double     stddev;
     int        i;

     now = time(NULL);
     t   = localtime(&now);
     strftime(time_buf, sizeof(time_buf), "%H:%M:%S", t);

     printf("=== Seismic Monitor | window: %ds | lag: %dms | %s ===\n\n",
          cfg->window_sec, cfg->lag_ms, time_buf);
     printf(" %4s | %5s | %10s | %10s\n", "ID", "COUNT", "MEAN", "STD DEV");
     printf(" %4s | %5s | %10s | %10s\n", "----", "-----", "----------", "----------");

     for (i = 0; i < cfg->sensor_count; i++)
     {
          if (s->sensors[i].count == 0)
          {
               if (cfg->show_empty)
               {
                    printf(" %4d | %5s | %10s | %10s\n", i, "-", "-", "-");
               }
               continue;
          }

          stats_mean(s, i, &mean);
          stats_stddev(s, i, &stddev);
          printf(" %4d | %5d | %*.*f | %*.*f\n",
               i, s->sensors[i].count,
               cfg->precision + 5, cfg->precision, mean,
               cfg->precision + 5, cfg->precision, stddev);
     }
}