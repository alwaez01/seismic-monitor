#ifndef GENERATOR_H
#define GENERATOR_H

#include "parser.h"

#define MIN_INTENSITY -1000
#define MAX_INTENSITY  1000

typedef struct
{
     int    sensor_count;
     double frequency;
     double burst_prob;
     int    burst_size;
} GENERATOR;

GENERATOR *generator_create(SIM_CONFIG *cfg);
void       generator_destroy(GENERATOR *gen);
void       generator_tick(GENERATOR *gen);

#endif