#include <stdlib.h>
#include <unistd.h>

#include "parser.h"

int parse_args(SIM_CONFIG *cfg, int argc, char **argv)
{
     cfg->sensor_count = DEFAULT_SENSOR_COUNT;
     cfg->frequency    = DEFAULT_FREQUENCY;
     cfg->burst_prob   = DEFAULT_BURST_PROB;
     cfg->burst_size   = DEFAULT_BURST_SIZE;
     cfg->random_seed  = DEFAULT_RANDOM_SEED;

     int opt;
     while ((opt = getopt(argc, argv, "n:f:b:B:s:")) != -1)
     {
          switch (opt)
          {
               case 'n':
                    cfg->sensor_count = atoi(optarg);
                    break;
               case 'f':
                    cfg->frequency = atof(optarg);
                    break;
               case 'b':
                    cfg->burst_prob = atof(optarg);
                    break;
               case 'B':
                    cfg->burst_size = atoi(optarg);
                    break;
               case 's':
                    cfg->random_seed = atoi(optarg);
                    break;
               default:
                    return -1;
                    break;
          }
     }

     return 0;
}