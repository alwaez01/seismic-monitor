#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>

#include "mon_parser.h"
#include "mon_queue.h"
#include "mon_stats.h"
#include "mon_display.h"

static long long get_time_ms(void)
{
     struct timespec ts;

     clock_gettime(CLOCK_REALTIME, &ts);
     return ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

int main(int argc, char **argv)
{
     MON_CONFIG      cfg;
     QUEUE          *q;
     STATS          *s;
     MEASUREMENT    *m;
     fd_set          read_fds;
     struct timeval  timeout;
     long long       last_render_ms;
     long long       now_ms;
     long long       elapsed_ms;
     long long       window_ms;
     int             result;

     result = parse_args(&cfg, argc, argv);
     if (result != PARSER_OK)
     {
          fprintf(stderr, "error parsing arguments: %d\n", result);
          return EXIT_FAILURE;
     }

     q = queue_create();
     if (q == NULL)
     {
          fprintf(stderr, "failed to create queue\n");
          return EXIT_FAILURE;
     }

     s = stats_create(cfg.sensor_count);
     if (s == NULL)
     {
          fprintf(stderr, "failed to create stats\n");
          queue_destroy(q);
          return EXIT_FAILURE;
     }

     window_ms      = (long long)cfg.window_sec * 1000LL;
     last_render_ms = get_time_ms();

     while (1)
     {
          now_ms     = get_time_ms();
          elapsed_ms = now_ms - last_render_ms;

          while (q->head != NULL && now_ms - q->head->timestamp_ms > window_ms)
          {
               stats_remove(s, q->head->sensor_id, q->head->intensity);
               queue_pop_head(q);
          }

          if (elapsed_ms >= cfg.lag_ms)
          {
               display_render(s, &cfg);
               last_render_ms = now_ms;
               elapsed_ms     = 0;
          }

          FD_ZERO(&read_fds);
          FD_SET(0, &read_fds);

          timeout.tv_sec  = 0;
          timeout.tv_usec = (cfg.lag_ms - elapsed_ms) * 1000;

          result = select(1, &read_fds, NULL, NULL, &timeout);

          if (result < 0)
          {
               break;
          }

          if (result > 0 && FD_ISSET(0, &read_fds))
          {
               m = input_read();
               if (m == NULL)
               {
                    break;
               }

               if (m->sensor_id < 0 || m->sensor_id >= cfg.sensor_count)
               {
                    measurement_destroy(m);
                    continue;
               }

               stats_add(s, m->sensor_id, m->intensity);
               queue_push(q, m);
          }
     }

     display_render(s, &cfg);

     stats_destroy(s);
     queue_destroy(q);

     return EXIT_SUCCESS;
}