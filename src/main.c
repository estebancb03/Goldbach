/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "solver.h"

int main() {
  struct timespec start_time, finish_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  solver_t* solver = solver_create();
  solver_read(solver);
  solver_run(solver);
  solver_print(solver);
  solver_destroy(solver);
  clock_gettime(CLOCK_MONOTONIC, &finish_time);
  double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
        (finish_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
  printf("\nElapsed time: %.9lfs\n", elapsed_time);
  return EXIT_SUCCESS;
}
