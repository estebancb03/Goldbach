/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef ARRAY_UINT32_H
#define ARRAY_UINT32_H
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/**
 * @brief Estructura de datos que se encarga de almacenar elementos de tipo
 *        uint32_t, de forma efectiva y evita buffers overflows y erores de
 *        memoria
 */
typedef struct array_uint32 {
  uint32_t count;
  uint32_t capacity;
  uint32_t* elements;
} array_uint32_t;

/**
 * @brief Inicializador, inicializa los campos de la estructura de datos
 * @code 
 *   array_uint32_init(&array);
 * @endcode
 * @param array arreglo sin inicializar
 */
void array_uint32_init(array_uint32_t* array);

/**
 * @brief Destructor, destruye la estructura y libera la memoria empleada
 * @code 
 *   array_uint32_destroy(&array);
 * @endcode
 * @param array arreglo inicializado
 */
void array_uint32_destroy(array_uint32_t* array);

/**
 * @brief Agrega un nuevo elemento al final del arrglio
 * @code
 *   array_uint32_add(&array, 11);
 * @endcode
 * @param array arreglo en el cual se va a agregar el elemento 
 * @param element elemento a agregar al arreglo 
 */
void array_uint32_add(array_uint32_t* array, uint32_t element);

/**
 * @brief Retorna el campo elements de la estructura
 *   uint32_t array_elements = array_uint32_get_elements(&array);
 * @param array arreglo 
 * @return uint32_t* elementos almacenados en el arreglo 
 */
uint32_t* array_uint32_get_elements(array_uint32_t* array);

/**
 * @brief Retorna el campo count de la estructura
 * @code
 *   uint32_t array_count = array_uint32_get_count(&array); 
 * @endcode
 * @param array arreglo
 * @return uint32_t cantidad de elementos almacenaddos 
 */
uint32_t array_uint32_get_count(array_uint32_t* array);

#endif  // !ARRAY_UINT32_H
