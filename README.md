# Trabajo_INFO145

### Trabajo de diseño y análisis de algoritmos, Primer Semestre de 2024.

---

## Integrantes
- Renato Atencio
- Tomas Contreras
- Handel Venegas
- Jorge Cheuqueman

---

## Variables de Entorno

Archivo de configuración: `config/.env`

```ini
EPSILON=10
MEAN=25
STDDEV=5
ITERACIONES=100
```

---

## Compilación

Para compilar el proyecto, ejecutar el siguiente comando en la consola:

```bash
make
```

---

## Ejecución

### 1. Crear Estructura de Carpetas

Desde el directorio `Trabajo_INFO145`, crear la siguiente estructura de carpetas:

```
Trabajo_Info145
│
├── out
│   ├── normal
│   ├── huffman
│   └── gap
│
└── src
```

### 2. Cargar Variables de Entorno

Para cargar las variables de entorno, ejecutar los siguientes comandos en la consola:

```bash
set -o allexport       # Permite cargar las variables de entorno
source config/.env     # Volver a usar si se actualiza el .env
```

### 3. Ejecutar el Programa

Para ejecutar el programa, elige uno de los siguientes comandos según el caso deseado:

```bash
./normal n     # Ejecuta el Caso 1 (Búsqueda Binaria Directa)
./gap n        # Ejecuta el Caso 2 (Búsqueda con Gap & Sample)
./huffman n    # Ejecuta el Caso 3 (Búsqueda con Gap_Codificado & Sample)
```

---

