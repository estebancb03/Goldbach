/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef ARRAY_CHAR_H
#define ARRAY_CHAR_H
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/**
 * @brief Estructura de datos que se encarga de almacenar elementos de tipo
 *        char, de forma efectiva y evita buffers overflows y erores de
 *        memoria
 */
typedef struct array_char {
  uint32_t count;
  uint32_t capacity;
  char* elements;
} array_char_t;

/**
 * @brief Inicializador, inicializa los campos de la estructura de datos
 * @code 
 *   array_char_init(&array);
 * @endcode
 * @param array arreglo sin inicializar
 */
void array_char_init(array_char_t* array);

/**
 * @brief Destructor, destruye la estructura y libera la memoria empleada
 * @code 
 *   array_char_destroy(&array);
 * @endcode
 * @param array arreglo inicializado
 */
void array_char_destroy(array_char_t* array);

/**
 * @brief Agrega un nuevo elemento al final del arreglo
 * @code
 *   array_char_add(&array, 11);
 * @endcode
 * @param array arreglo en el cual se va a agregar el elemento 
 * @param element elemento a agregar al arreglo 
 */
void array_char_add(array_char_t* array, char element);

/**
 * @brief Retorna el campo elements de la estructura
 *   char* array_elements = array_char_get_elements(&array);
 * @param array arreglo 
 * @return char* elementos almacenados en el arreglo 
 */
char* array_char_get_elements(array_char_t* array);

/**
 * @brief Retorna el campo count de la estructura
 * @code
 *   uint32_t array_count = array_char_get_count(&array); 
 * @endcode
 * @param array arreglo
 * @return uint32_t cantidad de elementos almacenaddos 
 */
uint32_t array_char_get_count(array_char_t* array);

#endif  // !ARRAY_CHAR_H
