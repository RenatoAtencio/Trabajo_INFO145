# Trabajo_INFO145
Trabajo de diseño y análisis de algoritmos

VARIABLES DE ENTORNO(config/.env):
    EPSILON=10
    MEAN=25
    STDDEV=5
    ITERACIONES=100

COMPILACION
    1) Ejecutar en consola:
        make

EJECUCION:
    1) Crear carpeta out. (Estar en el directorio Trabajo_INFO145) 
        Trabajo_Info145
           |out 
           |src
    2) Ejecutar en consola
        2.1) set -o allexport       | Permite cargar las variables de entorno
        2.2) source config/.env     | Volver a usar si se actualiza el .env
    3) Ejecutar el prog a eleccion
        3.1) ./normal n
        3.2) ./gap n
        3.3) ./huffman n


sizeof(int *) = 4 o 8 bytes, 4 si es sistema operativo de 32 bits, 8 si es de 64 bits.

1 byte = 8 bits 

char: 1byte = 4 bits = 16 codigos de huffman
int: 4 bytes = 32 bits =	4.3M codigos de huffman
int*: 8 bytes = 64 bits = 18x10^18 codigos de huffman
long: 8 bytes = 64 bits = 18x10^18 codigos de huffman
short int: 2 bytes = 8 bits = 65536 codigos de huffman

sizeof arr = 8, aveces porque da los bytes del puntero