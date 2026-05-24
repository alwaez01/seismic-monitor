#ifndef SIM_PARSER_H
#define SIM_PARSER_H

#define DEFAULT_SENSOR_COUNT  5
#define DEFAULT_FREQUENCY     10.0
#define DEFAULT_BURST_PROB    0.2
#define DEFAULT_BURST_SIZE    500
#define DEFAULT_RANDOM_SEED   0

typedef struct
{
     int    sensor_count;
     double frequency;
     double burst_prob;
     int    burst_size;
     int    random_seed;
} SIM_CONFIG;

#endif