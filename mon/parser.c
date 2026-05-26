#include <stdlib.h>
#include <unistd.h>

#include "parser.h"

int parse_args(MON_CONFIG *cfg, int argc, char **argv)
{
     int opt;

     cfg->window_sec   = DEFAULT_WINDOW_SEC;
     cfg->lag_ms       = DEFAULT_LAG_MS;
     cfg->sensor_count = DEFAULT_SENSOR_COUNT;
     cfg->precision    = DEFAULT_PRECISION;
     cfg->show_empty   = DEFAULT_SHOW_EMPTY;

     while ((opt = getopt(argc, argv, "a:l:n:p:z")) != -1)
     {
          switch (opt)
          {
               case 'a':
                    cfg->window_sec = atoi(optarg);
                    if (cfg->window_sec <= 0)
                         return PARSER_ERR_OUT_OF_RANGE;
                    break;
               case 'l':
                    cfg->lag_ms = atoi(optarg);
                    if (cfg->lag_ms <= 0)
                         return PARSER_ERR_OUT_OF_RANGE;
                    break;
               case 'n':
                    cfg->sensor_count = atoi(optarg);
                    if (cfg->sensor_count <= 0)
                         return PARSER_ERR_OUT_OF_RANGE;
                    break;
               case 'p':
                    cfg->precision = atoi(optarg);
                    if (cfg->precision < 0)
                         return PARSER_ERR_OUT_OF_RANGE;
                    break;
               case 'z':
                    cfg->show_empty = 1;
                    break;
               default:
                    return PARSER_ERR_UNKNOWN_FLAG;
                    break;
          }
     }

     return PARSER_OK;
}