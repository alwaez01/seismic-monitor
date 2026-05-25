#include <stdlib.h>
#include <unistd.h>

#include "parser.h"

int parse_args(SIM_CONFIG *cfg, int argc, char **argv)
{
     int opt;
     
     cfg->sensor_count = DEFAULT_SENSOR_COUNT;
     cfg->frequency    = DEFAULT_FREQUENCY;
     cfg->burst_prob   = DEFAULT_BURST_PROB;
     cfg->burst_size   = DEFAULT_BURST_SIZE;
     cfg->random_seed  = DEFAULT_RANDOM_SEED;

     while ((opt = getopt(argc, argv, "n:f:b:B:s:")) != -1)
     {
          switch (opt)
          {
               case 'n':
                    cfg->sensor_count = atoi(optarg);
                    if (cfg->sensor_count <= 0)
                         return PARSER_ERR_OUT_OF_RANGE;
                    break;
               case 'f':
                    cfg->frequency = atof(optarg);
                    if (cfg->frequency <= 0.0)
                         return PARSER_ERR_OUT_OF_RANGE;
                    break;
               case 'b':
                    cfg->burst_prob = atof(optarg);
                    if (cfg->burst_prob < 0.0 || cfg->burst_prob > 1.0)
                         return PARSER_ERR_OUT_OF_RANGE;
                    break;
               case 'B':
                    cfg->burst_size = atoi(optarg);
                    if (cfg->burst_size <= 0)
                         return PARSER_ERR_OUT_OF_RANGE;
                    break;
               case 's':
                    cfg->random_seed = atoi(optarg);
                    break;
               default:
                    return PARSER_ERR_UNKNOWN_FLAG;
                    break;
          }
     }

     return PARSER_OK;
}