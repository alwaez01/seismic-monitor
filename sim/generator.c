#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generator.h"

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
