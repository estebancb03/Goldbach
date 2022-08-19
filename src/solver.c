/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "solver.h"
#include <stdio.h>

typedef struct solver {
  array_goldbach_t array;
} solver_t;

solver_t* solver_create() {
  // Crear e inicializar campos de la estructura
  solver_t* solver = (solver_t*) calloc(1, sizeof(solver_t));
  array_goldbach_init(&solver -> array);
  return solver;
}

void solver_read(solver_t* solver) {
  assert(solver);
  char data[100];
  // Craer goldbach y agregarlo al arreglo para cada valor introducido
  while (fscanf(stdin, "%s", (char*) data) == 1) {
    goldbach_t* goldbach = goldbach_create((char*)data);
    array_goldbach_add(&solver -> array, goldbach);
  }
}

void solver_run(solver_t* solver) {
  assert(solver);
  uint32_t element_count = array_goldbach_get_count(&solver -> array);
  goldbach_t** elements = array_goldbach_get_elements(&solver -> array);
  // Calcular las Sumas de Goldbach para cada valor del arreglo
  for (uint32_t index = 0; index < element_count; ++index) {
    goldbach_t* goldbach = elements[index];
    goldbach_run(goldbach);
  }
}

void solver_print(solver_t* solver) {
  assert(solver);
  uint32_t element_count = array_goldbach_get_count(&solver -> array);
  goldbach_t** elements = array_goldbach_get_elements(&solver -> array);
  // Imprimir las Sumas de Goldbach para cada valor del arreglo
  for (uint32_t index = 0; index < element_count; ++index) {
    goldbach_t* goldbach = elements[index];
    goldbach_print(goldbach);
  }
}

void solver_destroy(solver_t* solver) {
  assert(solver);
  // Liberar memoria empleada por la estructura
  array_goldbach_destroy(&solver -> array);
  free(solver);
}
