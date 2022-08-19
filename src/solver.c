/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "solver.h"

/**
 * @brief Lee los valores introducidos en la entrada estandar y opcionalmente
 *        la cantidad de hilos que el usario desea utilizar
 * @code 
 *  solver_read(solver, argc, argv);
 * @endcode
 * @param solver estructura
 * @param argc
 * @param argv
 */
void solver_read(solver_t* solver, int argc, char* argv[]);

/**
 * @brief Imprime las soluciones para cada valor del archivo
 * @code 
 *  solver_print(solver);
 * @endcode
 * @param solver estructura
 */
void solver_print(solver_t* solver);

typedef struct solver {
  uint32_t thread_count;
  array_goldbach_t buffer;
} solver_t;

solver_t* solver_create() {
  // Crear e inicializar campos de la estructura
  solver_t* solver = (solver_t*) calloc(1, sizeof(solver_t));
  solver -> thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  array_goldbach_init(&solver -> buffer);
  return solver;
}

void solver_read(solver_t* solver, int argc, char* argv[]) {
  assert(solver);
  char data[100];
  if (argc == 2) {
    // Leer cantidad de hilos que el usuario quiere emplear
    if (sscanf(argv[1], "%" SCNu32, &solver -> thread_count) == 1) {
    } else {
      fprintf(stderr, "Error: invalid thread count\n");
    }
  }
  // Craer goldbach y agregarlo al arreglo para cada valor introducido
  while (fscanf(stdin, "%s", (char*) data) == 1) {
    goldbach_t* goldbach = goldbach_create((char*)data);
    array_goldbach_add(&solver -> buffer, goldbach);
  }
}

void solver_run(solver_t* solver, int argc, char* argv[]) {
  assert(solver);
  solver_read(solver, argc, argv);
  goldbach_t** buffer_elements = array_goldbach_get_elements(&solver -> buffer);
  uint32_t buffer_size = array_goldbach_get_count(&solver -> buffer);
  // Cálculo de sumas de Goldbach
  #pragma omp parallel for schedule(dynamic) \
    num_threads(solver -> thread_count) default(none) \
    shared(buffer_elements, buffer_size)
    for (uint32_t index = 0; index < buffer_size; ++index)
      goldbach_run(buffer_elements[index]);
  solver_print(solver);  // Imprimir sumas de Goldbach
}

void solver_print(solver_t* solver) {
  assert(solver);
  uint32_t element_count = array_goldbach_get_count(&solver -> buffer);
  goldbach_t** elements = array_goldbach_get_elements(&solver -> buffer);
  // Imprimir las Sumas de Goldbach para cada valor del arreglo
  for (uint32_t index = 0; index < element_count; ++index)
    goldbach_print(elements[index]);
}

void solver_destroy(solver_t* solver) {
  assert(solver);
  // Liberar memoria empleada por la estructura
  array_goldbach_destroy(&solver -> buffer);
  free(solver);
}
