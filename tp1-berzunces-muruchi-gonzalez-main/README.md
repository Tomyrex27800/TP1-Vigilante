[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Yp-Nx20W)
# Guía para compilar y ejecutar este TP

Esto es una guía para este trabajo práctico en particular. Ya que tiene una estructura un poco diferente a la de los talleres.

## Estructura del TP

El TP no tiene una estructura de carpetas estándar. Esto es así para que puedan encontrar las cosas más fácilmente. En los siguientes trabajos iremos adaptando la estructura a la de un proyecto real. Por ahora, la estructura es la siguiente:

- `build/`: Carpeta donde se generan los archivos de compilación. **No la modifiquen a mano. Siempre generenla con CMake**
- `CMakeLists.txt`: Archivo de configuración de CMake. **No lo modifiquen**.
- `main.cpp`: Archivo principal del programa. Aquí se encuentra el `main` y la lógica del programa. Pueden modificarlo para hacer pruebas, pero no deberían necesitar hacerlo. Recuerden que siempre pueden mirar el historial de _git_ si necesitan volver la versión original.
- `utils/`: Carpeta donde se encuentran los archivos de código fuente y de cabecera de algunas funciones que se utilizan en varios otros archivos. Aquí tendrán que completar algunas implementaciones. No modifiquen las declaraciones de las funciones (nombre, tipo de retorno y parámetros que reciben), ya que son parte de la interfaz del programa. El TP está pensado para que no necesiten agregar nuevas funciones, pero si lo hacen, asegúrense de agregar las declaraciones en el archivo de cabecera correspondiente. Los archivos de código fuente son `utils.cpp` y `utils.h`. En `utils.cpp` encontrarán la implementación de las funciones que tienen que completar. En `utils.h` encontrarán las declaraciones de las funciones.
- `generation/`: Carpeta donde se encuentran los archivos de código fuente y de cabecera de la generación de información para los lanzamientos. **No lo modifiquen**.
- `tests/`: Carpeta donde se encuentran los tests. Pueden visitarla para ver cómo se utilizan las funciones que tienen que implementar. No modifiquen los tests, ya que son parte de la evaluación del TP. Todas las pruebas que quieran hacer, deberían poder hacerlas utilizando el ejecutable `generate` y el ejecutable `main`.
- `launch/`: Carpeta donde se encuentran los archivos de código fuente y de cabecera de los lanzamientos. En esta carpeta encontrarán los archivos `launch.cpp` y `launch.h`. En `launch.cpp` encontrarán la implementación de las funciones que tienen que completar. En `launch.h` encontrarán las declaraciones de las funciones. No modifiquen las declaraciones de las funciones (nombre, tipo de retorno y parámetros que reciben), ya que son parte de la interfaz del programa. El TP está pensado para que no necesiten agregar nuevas funciones, pero si lo hacen, asegúrense de agregar las declaraciones en el archivo de cabecera correspondiente.
- `README.md`: Este archivo. Aquí encontrarán información sobre cómo compilar y ejecutar el TP. También encontrarán información sobre cómo correr los tests y cómo generar los archivos de información de las naves.
- `.gitignore`: Archivo de configuración de _git_. Aquí se encuentran los archivos y carpetas que no deberían ser subidos al repositorio. **No lo modifiquen.**
- `info/`: Carpeta donde se almacenan los archivos de información generados por el programa. Pueden modificarlos a mano si quieren probar alguna cosa en particular, pero asegúrense de seguir el formato de la generación automática. De lo contrario, es muy probable que luego su código no pase los tests.

## Targets de CMake disponibles

Recuerden que para compilar un _target_ en particular, deben correr el comando `cmake --build build --target <target>`.

Los targets disponibles son:

- `main`: Compila el programa principal.
- `tp_tests`: Compila los tests. Si no se compilan los tests, no se pueden correr. No hace falta correrlo manualmente, ya que se corre automáticamente al correr `ctest`.
- `generate`: Compila únicamente el programa que genera los archivos de información de las naves.
- `all`: Compila todo. Es lo mismo que correr `cmake --build build`.
- `clean`: Borra los archivos generados por CMake. Es lo mismo que correr `cmake --build build --target clean`.

## Compilación y ejecución

Para compilar el TP, deben correr los siguientes comandos:

```bash
cmake -S . -B build
cmake --build build
```

Esto generará la carpeta `build/` y compilará el programa.

Una vez que hayan compilado el programa, pueden ejecutarlo con el siguiente comando:

```bash
./build/generate
```

Esto generará los archivos de información de las naves en la carpeta `info/`. Si no existe, la creará automáticamente. Y si existe la borrará y la volverá a crear. Esto es para que no tengan que preocuparse por los archivos de información de las naves. Si quieren ver cómo se generan, pueden abrir el archivo `generation/generation.cpp` y ver cómo se generan los archivos.

Luego, pueden ejecutar el programa principal con el siguiente comando:

```bash
./build/main
```

Esto ejecutará el programa principal. Si no existe la carpeta `info/`, el programa no podrá ejecutarse. Si existe, el programa leerá los archivos de información de las naves e intentará iniciar los lanzamientos. Si en algún momento aparece el error `"Not Implemented"`, significa que todavía no implementaron alguna función de las que tienen que completar.

## Correr los tests

Para correr los tests, deben correr el siguiente comando:

```bash
cmake --build build --target tp_tests
```

Y luego, pueden correr los tests con el siguiente comando **desde la carpeta build**:

```bash
ctest --output-on-failure
```

Esto correrá todos los tests y mostrará el resultado de cada uno. Si alguno falla, se mostrará un mensaje de error con el nombre del test que falló y el motivo del fallo. Si todo sale bien, verán un mensaje que dice `100% tests passed`.

## Funciones útiles

- `wait(NULL)` es la función que podemos utilizar para esperar a que un hijo termine. Además, ésta devuelve un número entero que, si es mayor que cero, indica que hay más procesos hijos que todavía no han terminado. **Esto puede ser útil**.
- `exit()` es la función que se utiliza para terminar un proceso. Puede recibir un código de estado que indica si el proceso terminó correctamente o con errores. Usualmente, vamos a usar `exit(0)` para indicar que el proceso terminó correctamente y `exit(1)` para indicar que el proceso terminó con errores. **No olviden usarla**.
