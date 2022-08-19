/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "solver.h"

int main(int argc, char* argv[]) {
  solver_t* solver = solver_create();
  struct timespec start_time, finish_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  solver_run(solver, argc, argv);
  clock_gettime(CLOCK_MONOTONIC, &finish_time);
  double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
        (finish_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
  printf("\nElapsed time: %.9lfs\n", elapsed_time);
  solver_destroy(solver);
  return EXIT_SUCCESS;
}
