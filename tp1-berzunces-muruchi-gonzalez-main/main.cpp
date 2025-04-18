#include "utils/utils.h"
#include "launch/launch.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // Para utilizar la función sleep y fork
#include <wait.h> // Para utilizar la función wait
#include <fstream> 

using namespace std;

int main() {
    welcomeScreen();

    for(int i = 1; i <= NUM_SPACESHIPS; i++) {
        pid_t shipPID = fork();
        
        if (shipPID < 0) {
            cerr << "Error al crear el proceso para la nave " << i << endl;
            cerr << "Se abortará la misión" << i << endl;
            exit(1);
        } else if (shipPID == 0) {
            // Proceso hijo: Ejecutar el chequeo de lanzamiento de la nave con índice i
            shipLaunchChecks(i);

            // Terminar el proceso hijo una vez que haya terminado su tarea
            // Esto es importante para evitar que el proceso hijo continúe ejecutando el código del padre
            exit(0);
        }
    }

    while (wait(NULL) > 0); // Esperar a que todos los procesos hijos terminen

    // Ahora, vemos el resultado de cada lanzamiento
    for(int i = 1; i <= NUM_SPACESHIPS; i++) {
        usleep(SLEEP_TIME);
        string logFilePath = "info/nave_" + to_string(i) + "/log.txt";
        ifstream logFile(logFilePath);

        if (!logFile.is_open()) {
            failedLaunch(i, "No se pudo abrir el archivo de log. Asumimos que el lanzamiento falló.");
            continue;
        }

        string line = readLastLine(logFile);
        logFile.close(); // Cerrar el archivo de log inmediatamente después de leer
        if (line == "SUCCESS") {
            successfulLaunch(i);
        } else if (line == "FAIL") {
            failedLaunch(i, "Verifique el log para más información.");
        } else {
            failedLaunch(i, "Estado desconocido. Asumimos que el lanzamiento falló.");
        }
    }

    return 0;
}