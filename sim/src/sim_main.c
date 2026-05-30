#include <stdio.h>
#include <stdlib.h>

#include "sim_parser.h"
#include "sim_generator.h"

int main(int argc, char **argv)
{
     SIM_CONFIG cfg;
     int        result;
     GENERATOR *gen;

     result = parse_args(&cfg, argc, argv);

     if (result != PARSER_OK)
     {
          fprintf(stderr, "error parsing arguments: %d\n", result);
          return EXIT_FAILURE;
     }

     gen = generator_create(&cfg);

     if (gen == NULL)
     {
          fprintf(stderr, "failed to create generator\n");
          return EXIT_FAILURE;
     }

     while (1)
     {
          generator_tick(gen);
     }

     generator_destroy(gen);

     return EXIT_SUCCESS;
}