/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "goldbach.h"

typedef struct goldbach {
  bool is_valid;
  bool is_negative;
  bool is_even_number;
  uint32_t value;
  uint32_t count;
  array_char_t entry;
  array_uint32_t prime_numbers;
  array_uint32_t sums;
} goldbach_t;

/**
 * @brief Valida la entrada
 * @details Revisa que la entrada proporcionada sea un caracter válido
 * @code
 *   bool is_valid = valdiate_value("-21");
 * @endcode
 * @param entry cadena de caracteres
 * @return 
 *   true: si la entrada es válida
 *   false: si la entrada es inválida
 */
bool validate_value(char* entry);

/**
 * @brief Valida si la entrada es o no un valor negativo
 * @details Revisa que la cadena de entrada contenga "-" en la posición 0 
 *          del arreglo de caracteres
 * @code
 *   bool is_negative = valdiate_negative("-21");
 * @endcode
 * @param entry cadena de caracteres 
 * @return
 *   true: si entry[0] == '-'
 *   false: si si entry[0] != '-'
 */
bool validate_negative(char* entry);

/**
 * @brief Valida si la entrada corresponde a un número par o no
 * @code
 *   bool even_number = valdiate_even_number("10");
 * @endcode
 * @param entry cadena de caracteres 
 * @return 
 *   true: si el número es par
 *   false: si el número es impar  
 */
bool validate_even_number(char* entry);

/**
 * @brief Valida que un número sea primo
 * @code
 *   bool is_prime = validate_is_prime(7);
 * @endcode
 * @param number número a validar
 * @return 
 *   true: si el número es primo
 *   false: si el número no es primo 
 */
bool validate_is_prime(uint32_t number);

/**
 * @brief Extrae el valor proporcionado en la enterada
 * @details Convierte la entrada que es char* a uint32_t si es un valor válido para que 
 *          pueda ser usado en posteriores calculos con mayor facilidad.
 * @code
 *   uint32_t value = extract_value("-317");
 * @endcode
 * @param entry cadena de caracteres 
 * @return uint32_t contenido de la entrada convertido a entero positivo de 64 bits
 */
uint32_t extract_value(char* entry);

/**
 * @brief Retorna arreglo con números primos
 * @details Crea un arreglo de uint32_t que genera todos los números primos desde el dos
 *          hasta el número proporcionado por parámetro. Este algoritmo es fuerza bruta.
 * @code
 *   uint32_t* primes = generate_prime_numbers(10);
 *   //Retorna: [2, 3, 5, 7] para el caso de 10
 * @endcode
 * @param number número hasta el cual se generan primos    
 * @return array_uint32_t arreglo con números primos
 */
array_uint32_t generate_prime_numbers(uint32_t number);

/**
 * @brief Retorna arreglo con Sumas de Goldbach válidas para el valor de la estructura
 * @details Al detectarse una combinación de dos valores ambos se agregan al arreglo, le 
 *          corresponderá a otro método separar los elementos del arreglo en las determinadas 
 *          parejas de números que forman la Suma de Goldbach
 * @code
 *   uint32_t* weak_sums = generate_weak_sums(12, prime_numbers);
 *   //Con goldbach -> value = 10 retorna [3, 7, 5, 5], este arreglo corresponde a resultados
 *   //[3, 7] y [5, 5]
 * @endcode
 * @param number número resultado de las Sumas de Goldbach
 * @param prime_numbers arreglo con números primos desde dos hasta el number
 * @return array_uint32_t elementos de las soluciones de Sumas de Goldbach
 */
array_uint32_t generate_strong_sums(uint32_t number,
                                    array_uint32_t prime_numbers);

/**
 * @brief Retorna arreglo con Sumas de Goldbach válidas para el valor de la estructura
 * @details Al detectarse una conbinación de tres valores ambos se agregan al arreglo, le 
 *          corresponderá a otro separar los elementos del arreglo en los determinados 
 *          trios de números que forman la Suma de Goldbach
 * @code
 *   uint32_t* strong_sums = generate_strong_sums(15, prime_numbers);
 *   //Con goldbach -> value = 9 retorna [3,3,3], este arreglo corresponde a resultados
 *   //[3,3,3]
 * @endcode
 * @param number número resultado de las Sumas de Goldbach
 * @param prime_numbers arreglo con números primos desde dos hasta el number
 * @return array_uint32_t elementos de las soluciones de Sumas de Goldbach
 */
array_uint32_t generate_weak_sums(uint32_t number,
                                  array_uint32_t prime_numbers);

/**
 * @brief Determina si invocar y retornar generate_weak_sums o generate_strong_sums
 * @details Determina cual método usar basandose en si even_number es true o false
 * @code
 *   uint32_t* sums = generate_sums(12, true, prime_numbers);
 * @endcode
 * @param number número a calcularle las Sumas de Goldbach
 * @param even_number booleano que indica si number es par o impar
 * @param prime_numbers arreglo con números primos desde dos hasta el number
 * @return array_uint32_t elementos de las soluciones de Sumas de Goldbach 
 */
array_uint32_t generate_sums(uint32_t number, bool even_number,
                             array_uint32_t prime_numbers);

/**
 * @brief Retorna la cantidad de sumas de Goldabch para el value dado
 * @details Para encontrar la cantidad de soluciones se divide la cantidad de elementos
 *          del arreglo entre dos si even_number es true y entre tres si even_number es
 *          false
 * @code
 *   uint32_t count = generate_count(true, sums);
 * @endcode
 * @param even_number booleano que indica si número es par o impar
 * @param sums arreglo con las soluciones a las Sumas de Goldbach 
 * @return uint32_t cantidad de Sumas de Goldbach 
 */
uint32_t generate_count(bool even_number, array_uint32_t sums);

goldbach_t* goldbach_create(char* entry) {
  // Crear e inicializar campos de la estructura
  goldbach_t* goldbach = (goldbach_t*) calloc(1, sizeof(goldbach_t));
  array_char_init(&goldbach -> entry);
  for (uint32_t index = 0; entry[index]; ++index)
    array_char_add(&goldbach -> entry, entry[index]);
  goldbach -> count = 0;
  goldbach -> is_valid = validate_value(entry);
  array_uint32_init(&goldbach -> prime_numbers);
  array_uint32_init(&goldbach -> sums);
  // Hacer validaciones genrales
  if (goldbach -> is_valid) {
    goldbach -> value = extract_value(entry);
    goldbach -> is_negative = validate_negative(entry);
    goldbach -> is_even_number = validate_even_number(entry);
  }
  return goldbach;
}

void goldbach_run(goldbach_t* goldbach) {
  assert(goldbach);
  // Si la entrada es válida calcular los números primos y Sumas de Goldbach
  if (goldbach -> is_valid) {
    goldbach -> prime_numbers = generate_prime_numbers(goldbach -> value);
    goldbach -> sums = generate_sums(goldbach -> value,
                                     goldbach -> is_even_number,
                                     goldbach -> prime_numbers);
    goldbach -> count = generate_count(goldbach -> is_even_number,
                                       goldbach -> sums);
  }
}

void goldbach_print(goldbach_t* goldbach) {
  assert(goldbach);
  uint32_t entry_size = array_char_get_count(&goldbach -> entry);
  char* entry = array_char_get_elements(&goldbach -> entry);
  // Imprimir las Sumas de Goldbach con el formato indicado según validaciones
  for (uint32_t index = 0; index < entry_size; ++index)
    printf("%c", entry[index]);
  printf(": ");
  uint32_t* current_sums = array_uint32_get_elements(&goldbach -> sums);
  if (goldbach -> is_valid) {
    if (goldbach -> count != 0) {
      printf("%" PRIu32 " sums", goldbach -> count);
      if (goldbach -> is_negative) {
        printf(": ");
        uint32_t count = array_uint32_get_count(&goldbach -> sums);
        if (goldbach -> is_even_number) {
          for (uint32_t index = 1; index < count; index += 2) {
            printf("%" PRIu32 " + ", current_sums[index - 1]);
            printf("%" PRIu32, current_sums[index]);
            if (index + 1 != count)
              printf(", ");
          }
        } else {
          for (uint32_t index = 2; index < count; index += 3) {
            printf("%" PRIu32 " + ", current_sums[index - 2]);
            printf("%" PRIu32 " + ", current_sums[index - 1]);
            printf("%" PRIu32, current_sums[index]);
            if (index + 1 != count)
              printf(", ");
          }
        }
      }
    } else {
      printf("NA");
    }
  } else {
    printf("VALUE IS NOT VALID");
  }
  printf("\n");
}

void goldbach_destroy(goldbach_t* goldbach) {
  assert(goldbach);
  // Liberar memoria empleada por la estructura
  array_char_destroy(&goldbach -> entry);
  array_uint32_destroy(&goldbach -> prime_numbers);
  array_uint32_destroy(&goldbach -> sums);
  free(goldbach);
}

bool validate_value(char* entry) {
  bool answer = true;
  /* Recorrer cada campo de la entrada verificando que no existan dígitos 
     inválidos */
  if (entry[0] == '-') {
    for (uint32_t index = 1; entry[index] && answer; ++index) {
      if (!isdigit(entry[index]))
        answer = false;
    }
  } else {
    for (uint32_t index = 0; entry[index] && answer; ++index) {
      if (!isdigit(entry[index]))
        answer = false;
    }
  }
  return answer;
}

bool validate_negative(char* entry) {
  // Averiguar si la entrada es negtiva o no
  return entry[0] == '-' ? true : false;
}

bool validate_even_number(char* entry) {
  bool answer = false;
  uint32_t value = extract_value(entry);
  // Averiguar si la entrada es un número par o impar
  if (value %2 == 0)
    answer = true;
  return answer;
}

bool validate_is_prime(uint32_t number) {
  if (number == 2 || number == 3)
    return true;
  if (number %2 == 0 || number %3 == 0)
    return false;
  for (uint32_t index = 5; index * index <= number; index += 6) {
    if (number %index == 0 || number %(index+2) == 0)
      return false;
  }
  return true;
}

uint32_t extract_value(char* entry) {
  // Convertir entry a entero de 64 bits positivo
  uint32_t value = (uint32_t) atoi(entry);
  if (validate_negative(entry))
    value *= -1;
  return value;
}

array_uint32_t generate_prime_numbers(uint32_t number) {
  array_uint32_t prime_numbers;
  array_uint32_init(&prime_numbers);
  if (number > 5) {
    // Generar números primos desde 2 hasta number y guardarlos en el arreglo
    for (uint32_t index = 2; index <= number; ++index) {
      if (validate_is_prime(index))
        array_uint32_add(&prime_numbers, index);
    }
  }
  return prime_numbers;
}

array_uint32_t generate_sums(uint32_t number, bool even_number,
                             array_uint32_t prime_numbers) {
  /* Si even_number es true retornar generate_strong_sums si no retornar 
     generate_weak_sums */
  return even_number ? generate_strong_sums(number, prime_numbers)
                     : generate_weak_sums(number, prime_numbers);
}

array_uint32_t generate_strong_sums(uint32_t number,
                                    array_uint32_t prime_numbers) {
  array_uint32_t sums;
  array_uint32_init(&sums);
  uint32_t index_number = 0;
  uint32_t jindex_number = 0;
  uint32_t prime_numbers_count = array_uint32_get_count(&prime_numbers);
  uint32_t* prime_numbers_elements = array_uint32_get_elements(&prime_numbers);
  // Generar combinaciones de números
  for (uint32_t index = 0; index < prime_numbers_count; ++index) {
    index_number = prime_numbers_elements[index];
    for (uint32_t jindex = index; jindex < prime_numbers_count; ++jindex) {
      jindex_number = prime_numbers_elements[jindex];
      /* Si la suma de los números actuales de las repeticiones son iguales al
         valor y su suma es válida agregar números de recorridos a sums */
      if (index_number + jindex_number == number) {
        array_uint32_add(&sums, index_number);
        array_uint32_add(&sums, jindex_number);
      }
    }
  }
  return sums;
}

array_uint32_t generate_weak_sums(uint32_t number,
                                  array_uint32_t prime_numbers) {
  array_uint32_t sums;
  array_uint32_init(&sums);
  uint32_t index_number = 0;
  uint32_t jindex_number = 0;
  uint32_t kindex_number = 0;
  uint32_t prime_numbers_count = array_uint32_get_count(&prime_numbers);
  uint32_t* prime_numbers_elements = array_uint32_get_elements(&prime_numbers);
  // Generar combinaciones de números
  for (uint32_t index = 0; index < prime_numbers_count; ++index) {
    index_number = prime_numbers_elements[index];
    for (uint32_t jindex = index; jindex < prime_numbers_count; ++jindex) {
      jindex_number = prime_numbers_elements[jindex];
      for (uint32_t kindex = jindex; kindex < prime_numbers_count; ++kindex) {
        kindex_number = prime_numbers_elements[kindex];
        /* Si la suma de los números actuales de las repeticiones son iguales al
           valor y su suma es válida agregar números de recorridos a sums */
        if (index_number + jindex_number + kindex_number == number) {
          array_uint32_add(&sums, index_number);
          array_uint32_add(&sums, jindex_number);
          array_uint32_add(&sums, kindex_number);
        }
      }
    }
  }
  return sums;
}

uint32_t generate_count(bool even_number, array_uint32_t sums) {
  // Averiguar la cantidad de sumas encontradas
  return even_number ? array_uint32_get_count(&sums) / 2
                     : array_uint32_get_count(&sums) / 3;
}
