/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef GOLDBACH_H
#define GOLDBACH_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include "array_char.h"
#include "array_uint32.h"

/**
 * @brief Estructura de datos que se encarga del cálculo e impresión de
 *        las Sumas de Goldbach para un valor dado.
 * @details Almacena una cadena de cracteres como valor de entrada la cual
 *          se le aplican métodos de validación para asignar un valor de 
 *          verdad a los campos is_valid, is_negative y is_even_number.
 *          También se guarda el número entero resultante de transformar 
 *          la cadena de caracteres entry, se almacenan los número primos
 *          correspondientes en un arreglo y se almacenan los valores de
 *          las soluciones de Sumas de Goldbach en otro arreglo.
 */
typedef struct goldbach goldbach_t;

/**
 * @brief Constructor, inicializa los campos de la estructura y aplica
 *        algunas validaciones
 * @code
 *  goldbach_sums_t* goldbach_sums = goldbach_sums_create("31");
 * @endcode
 * @param entry cadena de caracteres a evaluar 
 * @return goldbach_sums_t* estructura de datos 
 */
goldbach_t* goldbach_create(char* entry);

/**
 * @brief Se invocan los métodos de cálculo de números primos y sumas
 * @code
 *  goldbach_run(goldbach);
 * @endcode
 * @param goldbach estructura de datos
 */
void goldbach_run(goldbach_t* goldbach);

/**
 * @brief Imprime con formato las sumas de goldbach
 * @details Imprime las Sumas de Goldbach correspondientes con un formato
 *          adecuado dependiendo de el valor de ciertos campos de la 
 *          estructura como is_valid, is_negative, is_even_number se 
 *          imprimirá en consola con un formato u otro
 * @code
 *  goldbach_print(goldbach);
 * @endcode
 * @param goldbach estructura de datos
 */
void goldbach_print(goldbach_t* goldbach);

/**
 * @brief Destructor, libera la memoria de las estructuras de datos empleadas
 * @code
 *  goldbach_destroy(goldbach_sums);
 * @endcode
 * @param goldbach estructura de datos
 */
void goldbach_destroy(goldbach_t* goldbach);

#endif  // !GOLDBACH_H
