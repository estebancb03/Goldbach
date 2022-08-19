/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef ARRAY_GOLDBACH_H
#define ARRAY_GOLDBACH_H
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "goldbach.h"

/**
 * @brief Estructura de datos que se encarga de almacenar elementos de tipo
 *        goldbach, de forma efectiva y evita buffers overflows y erores de
 *        memoria
 */
typedef struct array_goldbach {
  uint32_t count;
  uint32_t capacity;
  goldbach_t** elements;
} array_goldbach_t;

/**
 * @brief Inicializador, inicializa los campos de la estructura de datos
 * @code 
 *   array_goldbach_init(&array);
 * @endcode
 * @param array arreglo sin inicializar
 */
void array_goldbach_init(array_goldbach_t* array);

/**
 * @brief Destructor, destruye la estructura y libera la memoria empleada
 * @code 
 *   array_goldbach_destroy(&array);
 * @endcode
 * @param array arreglo inicializado
 */
void array_goldbach_destroy(array_goldbach_t* array);

/**
 * @brief Agrega un nuevo elemento al final del arreglo
 * @code
 *   array_goldbach_add(&array, goldbach);
 * @endcode
 * @param array arreglo en el cual se va a agregar el elemento 
 * @param element elemento a agregar al arreglo 
 */
void array_goldbach_add(array_goldbach_t* array, goldbach_t* element);

/**
 * @brief Retorna el campo elements de la estructura
 *   goldbach_t** array_elements = array_goldbach_get_elements(&array);
 * @param array arreglo 
 * @return goldbach_t** elementos almacenados en el arreglo 
 */
goldbach_t** array_goldbach_get_elements(array_goldbach_t* array);

/**
 * @brief Retorna el campo count de la estructura
 * @code
 *   uint64_t array_count = array_goldbach_get_count(&array); 
 * @endcode
 * @param array arreglo
 * @return uint64_t cantidad de elementos almacenaddos 
 */
uint32_t array_goldbach_get_count(array_goldbach_t* array);

#endif  // !ARRAY_GOLDBACH_H
