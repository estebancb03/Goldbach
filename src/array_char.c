/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "array_char.h"

/**
 * @brief Incrementa la capacidad de almacenamiento en el arreglo
 * @details Utilizando realloc se aumenta la capacidad de almacenar 
 *          elementos cuando se agota su capacidad inicial
 * @code
 *   more_capacity(array);
 * @endcode
 * @param array arreglo  
 */
void more_capacity(array_char_t* array);

void array_char_init(array_char_t* array) {
  assert(array);
  // Inicializar campos de la estructura
  array -> count = 0;
  array -> capacity = 0;
  array -> elements = NULL;
}

void array_char_destroy(array_char_t* array) {
  assert(array);
  // Liberar la memoria utilizada por la estructura
  array -> capacity = 0;
  array -> count = 0;
  free(array -> elements);
}

void array_char_add(array_char_t* array, char element) {
  assert(array);
  /* Guardar el elemento en el arreglo, aumentar capacidad en caso de ser 
     insuficiente */
  if (array -> count == array -> capacity)
    more_capacity(array);
  array -> elements[array -> count++] = element;
}

void more_capacity(array_char_t* array) {
  assert(array);
  // Aumentar capacidad de la estructura
  uint32_t new_capacity = 10 * (array -> capacity ? array -> capacity : 1);
  // Copiar los elementos del antiguo arreglo en el nuevo
  char* new_elements = (char*) realloc(array -> elements,
                                               new_capacity * sizeof(char));
  if (new_elements) {
    array -> capacity = new_capacity;
    array -> elements = new_elements;
  }
}

char* array_char_get_elements(array_char_t* array) {
  assert(array);
  return array -> elements;  // Retornar campo elements de array
}

uint32_t array_char_get_count(array_char_t* array) {
  assert(array);
  return array -> count;  // Retornar campo count de array
}
