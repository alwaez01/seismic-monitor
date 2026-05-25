#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main(int argc, char **argv)
{
     SIM_CONFIG cfg;
     int        result;

     result = parse_args(&cfg, argc, argv);

     if (result != PARSER_OK)
     {
          printf("error parsing arguments: %d\n", result);
          return -1;
     }

     printf("sensor_count: %d\n",   cfg.sensor_count);
     printf("frequency: %lf\n", cfg.frequency);
     printf("burst_prob: %lf\n", cfg.burst_prob);
     printf("burst_size: %d\n",   cfg.burst_size);
     printf("random_seed: %d\n",   cfg.random_seed);

     return 0;
}