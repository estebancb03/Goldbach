/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "solver.h"

/**
 * @brief Estructura que almacena la información privada de cada hilo
 * @details Guarda la posición de inicio y final del arreglo de objetos
 *          goldbach_t en la que un determinado hilo debe trabajar. También
 *          almaecena un puntero a los datos compartidos entre hilos
 */
typedef struct private_data {
  uint32_t start;
  uint32_t finish;
  solver_t* solver;
} private_data_t;

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

/**
 * @brief Crea los hilos y distribulle el trabajo entre ellos
 * @code 
 *   create_threads(solver);
 * @endcode
 * @param solver Estructura de datos compartidos entre hilos
 */
void create_threads(solver_t* solver);

/**
 * @brief Invoca los métodos de calculo de Sumas de Goldbach para que varios
 *        hilos puedan hacer sus calculos de forma concurrente.
 * @code 
 *   pthread_create(&threads[index], NULL, calculate, &private_data[index]);
 * @endcode
 * @param data Datos privados de cada hilo
 * @return void* NULL
 */
void* calculate(void* data);

/**
 * @brief Hace el join de cada hilo del arreglo de hilos
 *   join_threads(threads, 10);
 * @param threads Arreglo de hilos
 * @param thread_count Cantidad de hilos del arreglo
 */
void join_threads(pthread_t* threads, uint32_t thread_count);

typedef struct solver {
  uint32_t thread_count;
  array_goldbach_t array;
} solver_t;

solver_t* solver_create() {
  // Crear e inicializar campos de la estructura
  solver_t* solver = (solver_t*) calloc(1, sizeof(solver_t));
  solver -> thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  array_goldbach_init(&solver -> array);
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
    array_goldbach_add(&solver -> array, goldbach);
  }
}

void solver_run(solver_t* solver, int argc, char* argv[]) {
  assert(solver);
  solver_read(solver, argc, argv);
  create_threads(solver);
}

void solver_print(solver_t* solver) {
  assert(solver);
  uint32_t element_count = array_goldbach_get_count(&solver -> array);
  goldbach_t** elements = array_goldbach_get_elements(&solver -> array);
  // Imprimir las Sumas de Goldbach para cada valor del arreglo
  for (uint32_t index = 0; index < element_count; ++index)
    goldbach_print(elements[index]);
}

void solver_destroy(solver_t* solver) {
  assert(solver);
  // Liberar memoria empleada por la estructura
  array_goldbach_destroy(&solver -> array);
  free(solver);
}

void create_threads(solver_t* solver) {
  assert(solver);
  uint32_t thread_count = solver -> thread_count;
  // Inicializar arreglo de hilos y estructura de datos privados
  pthread_t* threads = (pthread_t*) calloc(thread_count, sizeof(pthread_t));
  private_data_t* private_data =  (private_data_t*) calloc(thread_count,
                                                    sizeof(private_data_t));
  if (threads && private_data) {
    uint32_t array_size = array_goldbach_get_count(&solver -> array);
    // Calcular la distribución del trabajo entre los hilos
    uint32_t values_per_thread = array_size / thread_count;
    uint32_t remaining_values = array_size % thread_count;
    uint32_t current_index = 0;
    uint32_t remaining_index = 0;
    for (uint32_t index = 0; index < thread_count; ++index) {
      // Delimitar el rango sobre el arreglo en el que un hilo trabaja
      private_data[index].start = current_index;
      if (remaining_index < remaining_values) {
        private_data[index].finish = private_data[index].start +
                                     values_per_thread;
        ++remaining_index;
      } else {
        private_data[index].finish = private_data[index].start +
                                     values_per_thread - 1;
      }
      current_index = ++private_data[index].finish;
      private_data[index].solver = solver;
      // Crear los hilos y asignarles su trabajo a hacer
      pthread_create(&threads[index], NULL, calculate, &private_data[index]);
    }
    join_threads(threads, thread_count);  // Hacer join a todos los hilos
    solver_print(solver);  // Imprimir las Sumas de Goldbach
    // Liberar memoria utilizada por los hilos
    free(private_data);
    free(threads);
  }
}

void join_threads(pthread_t* threads, uint32_t thread_count) {
  // Hacer join a cada hilo del arreglo de hilos
  for (uint32_t index = 0; index < thread_count; ++index)
    pthread_join(threads[index], NULL);
}

void* calculate(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*) data;
  solver_t* solver = private_data -> solver;
  goldbach_t** elements = array_goldbach_get_elements(&solver -> array);
  uint32_t start_point = private_data -> start;
  uint32_t finish_point = private_data -> finish;
  // Calcular las Sumas de Goldbach para cada valor del arreglo
  for (uint32_t index = start_point; index < finish_point; ++index)
    goldbach_run(elements[index]);
  return NULL;
}
