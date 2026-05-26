#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "generator.h"

int main(int argc, char **argv)
{
     SIM_CONFIG cfg;
     int        result;
     GENERATOR *gen;

     result = parse_args(&cfg, argc, argv);

     if (result != PARSER_OK)
     {
          printf("error parsing arguments: %d\n", result);
          return -1;
     }

     gen = generator_create(&cfg);
     while (1)
     {
          generator_tick(gen);
     }

     generator_destroy(gen);

     return 0;
}