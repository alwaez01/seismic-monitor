#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sim_generator.h"

static void generator_emit(GENERATOR *gen)
{
     int             sensor_id;
     int             intensity;
     long long       timestamp_ms;
     struct timespec ts;
 
     sensor_id = rand() % gen->sensor_count;
     intensity = MIN_INTENSITY + rand() % (MAX_INTENSITY - MIN_INTENSITY + 1);
 
     clock_gettime(CLOCK_REALTIME, &ts);
     timestamp_ms = ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
 
     printf("%d %d %lld\n", sensor_id, intensity, timestamp_ms);
     fflush(stdout);
}

GENERATOR *generator_create(SIM_CONFIG *cfg)
{
     GENERATOR *gen;

     gen = (GENERATOR*)malloc(sizeof(GENERATOR));
     if (gen == NULL)
     {
          return NULL;
     }

     gen->sensor_count = cfg->sensor_count;
     gen->frequency    = cfg->frequency;
     gen->burst_prob   = cfg->burst_prob;
     gen->burst_size   = cfg->burst_size;

     if (cfg->random_seed == 0)
     {
          srand(time(NULL));
     }
     else
     {
          srand(cfg->random_seed);
     }

     return gen;
}

void generator_destroy(GENERATOR *gen)
{
     free(gen);
}

void generator_tick(GENERATOR *gen)
{
     double          roll;
     int             i;
     struct timespec ts;
 
     roll = (double)rand() / RAND_MAX;
 
     if (roll < gen->burst_prob)
     {
          for (i = 0; i < gen->burst_size; i++)
          {
               generator_emit(gen);
          }
     }
     else
     {
          generator_emit(gen);
          ts.tv_sec  = 0;
          ts.tv_nsec = (long long)(1000000000.0 / gen->frequency);
          nanosleep(&ts, NULL);
     }
}