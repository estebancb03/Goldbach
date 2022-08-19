# **Diseño de estructuras de datos**

![Diagrama UML](../images/goldbachStructures.png "Diagrama UML")
![Diagrama explicativo](../images/memoryDiagram.png "Diagrama de memoria")

## Array_char

Esta estructura se encarga del almacenamiento de elementos de tipo char. Se plantea una estructura aparte dedicada para este fin en vez de un arreglo normal para manejar de mejor manera los errores de desbordamiento de memoria como buffer overflow. La estructura de datos se ve implementada en C de la siguiente forma:

```C
typedef struct array_char {
  uint32_t count;
  uint32_t capacity;
  char* elements;
} array_char_t;
```

Esta estructura de datos cuenta con tres campos, en ```count``` se guarda la cantidad de elementos almacenados en la estructura mientras que ```capacity``` guarda la capacidad de elementos que pueden ser almacenados, si se diera la eventual situación de que se llena por completo la capacidad, esta puede ser ampleada. Por otra parte, el campo ```elements``` es un arreglo sencillo el cual guarda los elementos. En el constructor se recibe un objeto de tipo array_char_t cuyos campos estén sin inicializar.
## Array_uint32

Esta estructura se encarga del almacenamiento de elementos de tipo uint64_t. Se plantea una estructura aparte dedicada para este fin en vez de un arreglo normal para manejar de mejor manera los errores de desbordamiento de memoria como buffer overflow. La estructura de datos se ve implementada en C de la siguiente forma:

```C
typedef struct array_uint64 {
  uint32_t count;
  uint32_t capacity;
  uint32_t* elements;
} array_uint64_t;
```

Esta estructura de datos cuenta con tres campos, en ```count``` se guarda la cantidad de elementos almacenados en la estructura mientras que ```capacity``` guarda la capacidad de elementos que pueden ser almacenados, si se diera la eventual situación de que se llena por completo la capacidad, esta puede ser ampleada. Por otra parte, el campo ```elements``` es un arreglo sencillo el cual guarda los elementos. En el constructor se recibe un objeto de tipo array_uint64_t cuyos campos estén sin inicializar.

## Goldbach

Esta estructura se encarga de recibir el valor de entrada y hacer los cálculos correspondientes para brindar las sumas de Goldbach aplicables al valor de entrada. La estructura de datos se ve implementada en C de la siguiente forma:

```C
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
```

En el constructor de goldbach se recibirá unicamente una cadena de caracteres que se almacenará en el campo ```entry```. Después de pasar una serie de validaciones y asegurarse de que es una entrada válida, es decir, un número entero se procede a convertir la cadena en un entero de 64 bits sin signo el cual se almacena en el campo ```value```, en el caso de que el número sea negativo se convierte a positivo para fines de realizar los cálculos.

Al validar la entrada se obtienen los valores correspondientes a ```is_valid```, ```is_negative``` y ```is_even_number```. Es necesaria la existencia de estos campos principalmente porque dependiendo de sus valores se escribirá la salida de una forma u otra.

Esta estructura cuenta además con dos arreglos, ```prime_numbers``` en el cual se llena con todos los números enteros primos existentes hasta el ```value``` y ```sums``` en el cual se almacenan los elementos de las Sumas de Goldbach aplicables al valor dado. Por último la cantidad de Sumas de Goldbach aplicables al valor introducido se guardará en el campo ```count``` de la estructura.

## Array_goldbach

Esta estructura se encarga del almacenamiento de elementos de tipo goldbach_t*. Se plantea una estructura aparte dedicada para este fin en vez de un arreglo normal para manejar de mejor manera los errores de desbordamiento de memoria como buffer overflow. La estructura de datos se ve implementada en C de la siguiente forma:

```C
typedef struct array_goldbach {
  uint32_t count;
  uint32_t capacity;
  goldbach_t** elements;
} array_goldbach_t;
```

Esta estructura de datos cuenta con tres campos, en ```count``` se guarda la cantidad de elementos almacenados en la estructura mientras que ```capacity``` guarda la capacidad de elementos que pueden ser almacenados, si se diera la eventual situación de que se llena por completo la capacidad, esta puede ser ampleada. Por otra parte, el campo ```elements``` es un arreglo sencillo el cual guarda los elementos. En el constructor se recibe un objeto de tipo array_goldbach_t cuyos campos estén sin inicializar.

## Solver

Para recorrer cada archivo introducido y calcular las Sumas de Goldbach para todos los valores contenidos se plantea el uso de un arreglo dinámico. Para cada valor introducido por el usuario se crea un objeto goldbach_t* y se almacena en el campo ```array``` de la estructura. La estructura de datos se ve implementada en C de la siguiente forma:

```C
typedef struct solver {
  uint32_t position;
  uint32_t thread_count;
  array_goldbach_t buffer;
  pthread_mutex_t can_access_position;
} solver_t

typedef struct private_data {
  solver_t* solver;
} private_data_t;
```

La estructura ```solver``` se encarga de almacenar los datos compartidos entre los diferentes hilos, posee los campos ```position``` que es la variable contadora para la reparticion de celdas del arreglo entre los hilos, ```thread_count``` que guarda la cantidad de hilos a crear para resolver las operaciones, ```buffer``` que almacena los objetos goldbach_t* correspondientes a cada valor y ```can_access_position``` que es un mutex que controla la lectura y modificación del campo position. El método constructor no requiere parámetros.

Por último, la estructura ```private_data``` contiene la información exclusiva para cada hilo, tiene como único campo un puntero que apunta a los datos compartidos que sería ```solver```.

## Navegación

* [README principal](../README.md)
* [README de reporte](../report/README.md)