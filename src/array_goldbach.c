/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "array_goldbach.h"

/**
 * @brief Incrementa la capacidad de almacenamiento en el arreglo
 * @details Utilizando realloc se aumenta la capacidad de almacenar 
 *          elementos cuando se agota su capacidad inicial
 * @code
 *   add_capacity(array);
 * @endcode
 * @param array arreglo  
 */
void add_capacity(array_goldbach_t* array);

void array_goldbach_init(array_goldbach_t* array) {
  assert(array);
  // Inicializar campos de la estructura
  array -> count = 0;
  array -> capacity = 0;
  array -> elements = NULL;
}

void array_goldbach_destroy(array_goldbach_t* array) {
  assert(array);
  // Liberar la memoria utilizada por la estructura
  for (uint32_t index = 0; index < array -> count; ++index)
    goldbach_destroy(array -> elements[index]);
  array -> capacity = 0;
  array -> count = 0;
  free(array -> elements);
}

void array_goldbach_add(array_goldbach_t* array, goldbach_t* element) {
  assert(array);
  /* Guardar el elemento en el arreglo, aumentar capacidad en caso de ser 
     insuficiente */
  if (array -> count == array -> capacity)
    add_capacity(array);
  array -> elements[array -> count++] = element;
}

void add_capacity(array_goldbach_t* array) {
  assert(array);
  // Aumentar capacidad de la estructura
  uint32_t new_capacity = 10 * (array -> capacity ? array -> capacity : 1);
  // Copiar los elementos del antiguo arreglo en el nuevo
  goldbach_t** new_elements = (goldbach_t**) realloc(array -> elements,
                              new_capacity * sizeof(goldbach_t*));
  if (new_elements) {
    array -> capacity = new_capacity;
    array -> elements = new_elements;
  }
}

goldbach_t** array_goldbach_get_elements(array_goldbach_t* array) {
  assert(array);
  return array -> elements;  // Retornar campo elements de array
}

uint32_t array_goldbach_get_count(array_goldbach_t* array) {
  assert(array);
  return array -> count;  // Retornar campo count de array
}
