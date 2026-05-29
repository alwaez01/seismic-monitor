#ifndef MON_PARSER_H
#define MON_PARSER_H

#define DEFAULT_WINDOW_SEC    30
#define DEFAULT_LAG_MS        200
#define DEFAULT_SENSOR_COUNT  5
#define DEFAULT_PRECISION     2
#define DEFAULT_SHOW_EMPTY    0

#define PARSER_OK                0
#define PARSER_ERR_UNKNOWN_FLAG -1
#define PARSER_ERR_OUT_OF_RANGE -2

typedef struct
{
     int window_sec;
     int lag_ms;
     int sensor_count;
     int precision;
     int show_empty;
} MON_CONFIG;

int parse_args(MON_CONFIG *cfg, int argc, char **argv);

#endif