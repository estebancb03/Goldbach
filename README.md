# **Goldbach Calculator**
## Descripción del problema

Este programa se encarga de obtener las sumas de Goldbach de uno o varios valores dados que el usuario puede ingresar. El matemático Christian Goldbach propuso que todo número entero mayor que cinco se puede expresar como la suma de un conjunto de números primos. Esta propuesta se divide en dos conjeturas:

* ```Conjetura fuerte:``` Todo número par se puede escribir como la suma de dos números primos. Ejemplo: 8 = 3 + 5.
  
* ```Conjetura débil:``` Todo número impar se puede escribir como la suma de tres números primos. Ejemplo: 9 = 2 + 2 + 5.

## Manual de uso

La solución esta implementada en C, usa la entrada estandar para leer los datos y realiza los cálculos para obtener los resultados de forma concurrente. En la salida proporcionada por el programa, se mostrarán los datos y la cantidad de sumas de Golbach válidas para cada valor. En el caso del que el usuario ingrese algún número negativo el programa lo entenderá como que aparte de lo anterior el usuario solicita que se listen las sumas de Goldbach para ese valor. Por otro lado, si se ingresa un valor menor que cinco se mostrará un NA (No Aplica) y en el caso de que se ingrese un dato inválido (un caracter que no sea un número o un número excesivamente grande) se validará y se desplegará un mensaje de error en la salida. Ejemplo:


| Input            | Output                                                         |
|------------------|----------------------------------------------------------------|
|a                 | VALUE IS NOT VALID                                             |
|2                 | NA                                                             |
|7                 | 1 sums                                                         |
|-21               | 5 sums:  2 + 2 + 17, 3 + 5 + 13, 3 + 7 + 11, 5 + 5 + 11, 7 + 7 |

### Compilar el código fuente

Para compilar el código se utiliza el siguiente comando:

```
make
```

Este comando generará una carpeta ```bin``` en la cual se guardará el archivo ```Goldbach-Calculator.o```

### Ejecutar el programa

Existen dos formas de ejecutar el programa, la primera forma es insertando los datos al digitarlos manualmente en la entrada estandar. Para ello se debe utilizar el siguiente comando:

```
bin/Goldbach-Calculator
```

Opcionalmente también se puede ingresar la cantidad de hilos deseados para resolver la ejecución del programa, en caso de no brindar ningún número se utilizará la máxima capacidad que el hardware pueda brindar. Para introducir la cantidad de hilos deseados siga el siguiente ejemplo donde se solicita utilizar diez hilos:

```
bin/Goldbach-Calculator 10
```

Después de introducir el comando, se podrán digitar los datos y por cada dato introducido el programa brindará instantaneamente un resultado. Para indicarle al programa que ya no debe leer más datos presione ```ctrl + d```.

Si en cambio se desea evaluar algún archivo .txt que contengan los datos se le debe pasar la ruta del archivo a analizar. Ejemplo del comando a usar:

```
bin/Goldbach-Calculator < test/input001.txt
bin/Goldbach-Calculator 10 < test/input001.txt
```

Con los comandos indicados anteriormente, las Sumas de Goldbach correspondientes se mostrarán en la consola. Si se desea crear un archivo aparte con las soluciones se utiliza el > seguido de la ruta y nombre del archivo a crear. Ejemplo:

```
bin/Goldbach-Calculator > solutions.txt
bin/Goldbach-Calculator 10 > solutions.txt
bin/Goldbach-Calculator < test/input001.txt > solutions.txt
bin/Goldbach-Calculator 10 < test/input001.txt > solutions.txt
```

### Ejemplo de ejecución

En la carpeta ```test``` existen muchos archivos de prueba para ejecutar, para este ejemplo se utilizará el archivo [personalized_input001.txt](test/personalized_input001.txt), el cual tiene el siguiente contenido:

```
0
1
2
3
4
5
40
42
44
    31
000033
35
-12
-14
-16
-000021
    -23
-25
--13
13--
werweslkdas
///><///
--0wr45__??
```

A la hora de compilar y ejecutar el programa, se brinda esta salida [personalized_ouput001.txt](test/personalized_output001.txt):

```
0: NA
1: NA
2: NA
3: NA
4: NA
5: NA
40: 3 sums
42: 4 sums
44: 3 sums
31: 6 sums
000033: 9 sums
35: 8 sums
-12: 1 sums: 5 + 7
-14: 2 sums: 3 + 11, 7 + 7
-16: 2 sums: 3 + 13, 5 + 11
-000021: 5 sums: 2 + 2 + 17, 3 + 5 + 13, 3 + 7 + 11, 5 + 5 + 11, 7 + 7 + 7
-23: 5 sums: 2 + 2 + 19, 3 + 3 + 17, 3 + 7 + 13, 5 + 5 + 13, 5 + 7 + 11
-25: 5 sums: 3 + 3 + 19, 3 + 5 + 17, 3 + 11 + 11, 5 + 7 + 13, 7 + 7 + 11
--13: VALUE IS NOT VALID
13--: VALUE IS NOT VALID
werweslkdas: VALUE IS NOT VALID
///><///: VALUE IS NOT VALID
--0wr45__??: VALUE IS NOT VALID
```

## Créditos

* Proyecto desarrollado por Esteban Castañeda Blanco, correo: esteban.castaneda@ucr.ac.cr.

## Navegación

* [README del diseño](design/README.md)
* [README de reporte](report/README.md)
