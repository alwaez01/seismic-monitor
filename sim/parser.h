#ifndef SIM_PARSER_H
#define SIM_PARSER_H

#define DEFAULT_SENSOR_COUNT  5
#define DEFAULT_FREQUENCY     10.0
#define DEFAULT_BURST_PROB    0.2
#define DEFAULT_BURST_SIZE    500
#define DEFAULT_RANDOM_SEED   0

#define PARSER_OK                0
#define PARSER_ERR_UNKNOWN_FLAG -1
#define PARSER_ERR_OUT_OF_RANGE -2

typedef struct
{
     int    sensor_count;
     double frequency;
     double burst_prob;
     int    burst_size;
     int    random_seed;
} SIM_CONFIG;

int parse_args(SIM_CONFIG *cfg, int argc, char **argv);

#endif