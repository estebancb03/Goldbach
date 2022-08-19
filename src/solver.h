/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef SOLVER_H
#define SOLVER_H
#include <assert.h>
#include "goldbach.h"
#include "array_goldbach.h"

/**
 * @brief Estructura de datos, contiene campo array (array_goldbach_t*)
 * @details Lee los datos introducidos y para la cadena de caracteres de 
 *          cada línea de la entrada estandar se crea un objeto goldbach_t* 
 *          y de ser un valor válido se calculan sus respectivas Sumas de
 *          Goldbach y se imprime su resultado en consola. Para este fin,
 *          se crea un objeto goldbach_t* para cada valor y se guarda en 
 *          un arreglo dinámico
 */
typedef struct solver solver_t;

/**
 * @brief Constructor, inicializa los campos de la estructura
 * @code
 *  solver_t* solver = solver_create();
 * @endcode 
 * @return solver_t* la estructura de datos 
 */
solver_t* solver_create();

/**
 * @brief Lee los valores introducidos en la entrada estandar
 * @code 
 *  solver_read(solver);
 * @endcode
 * @param solver estructura
 */
void solver_read(solver_t* solver);

/**
 * @brief Encuentra las soluciones para cada goldbach del arreglo de goldbach
 * @code 
 *  solver_run(solver);
 * @endcode
 * @param solver estructura de datos
 */
void solver_run(solver_t* solver);

/**
 * @brief Imprime las soluciones para cada valor del archivo
 * @code 
 *  solver_print(solver);
 * @endcode
 * @param solver estructura
 */
void solver_print(solver_t* solver);

/**
 * @brief Destructor, libera la memoria de las estructuras de datos empleadas
 * @code 
 *  solver_destroy(solver);
 * @endcode
 * @param solver estructura de datos
 */
void solver_destroy(solver_t* solver);

#endif  // !SOLVER_H
