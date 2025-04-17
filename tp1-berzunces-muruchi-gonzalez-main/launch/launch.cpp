#include <iostream>
#include "../utils/utils.h"
#include <fstream>
#include <vector>
#include <unistd.h> // Para utilizar la función fork
#include <wait.h> // Para utilizar la función wait

using namespace std;

void readLaunchInfo(int shipIndex, string& name, string& city, string& planet, int& temperature, int& humidity, int& wind, string& conditions, int& visibility, int& loadCapacity, int& fuelAmount, int& duration) {
    //Abre el archivo usando el 'ifstream'
    ifstream read_file("info/nave_" + to_string(shipIndex) + "/info.txt");
    string line;
    vector<string> lista_valores;
    int contador=0;
    const char SIMBOLO = ':';
    
    if (read_file.is_open()){
        while (getline(read_file,line)){ // Lee la línea del archivo
            if (contador==6){
                lista_valores=split(line,SIMBOLO,true);
                name = lista_valores[0];
                contador=contador+1;
                continue;
            }
            if (contador==7){
                split(line,SIMBOLO,true);
                city = line;
                contador=contador+1;
                continue;
            }
            if (contador==8){
                split(line,SIMBOLO,true);
                planet = line;
                contador=contador+1;
                continue;
            }

            if (contador==11){ // Si llegamos a la línea de la temperatura
                split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                temperature = stoi(line); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==12){ // Si llegamos a la línea de la humedad
                split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                humidity = stoi(line); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==13){ // Si llegamos a la línea de la dirección del viento
                split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                wind = stoi(line); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==14){ // Si llegamos a la línea de la condición meteorológica
                split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                conditions = line; // Lo guarda en la variable
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==15){ // Si llegamos a la línea de la visibilidad
                split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                visibility = stoi(line); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==18){ // Si llegamos a la línea de la capacidad de carga
                split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                loadCapacity = stoi(line); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==19){ // Si llegamos a la línea de la cantidad de combustible
                split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                fuelAmount = stoi(line); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==20){ // Si llegamos a la línea de la duración del vuelo
                split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                duration = stoi(line); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
        }
    }
    else if (!read_file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de información de la nave " + to_string(shipIndex));
    }



    // Recopilar información del lanzamiento
    // Esta información se encuentra en el archivo "info/nave_<shipIndex>/info.txt"
    // Para el formato específico del archivo, revisar la consigna
    
    throw runtime_error("Not Implemented: No se ha implementado la función readLaunchInfo.");
}

void meteorologicalChecks(int shipIndex, int temperature, int humidity, int wind, string conditions, int visibility) {
    // Aquí se pueden realizar los chequeos meteorológicos necesarios
    // Recuerden que deben guardar la información en el archivo "info/nave_<shipIndex>/meteorologic.txt"
    // El formato del archivo es el siguiente:
    // - Si TODAS las condiciones son adecuadas, escribir en la última línea "SUCCESS"
    // - Si alguna de las condiciones no es adecuada, escribir en la última línea "FAIL"
    // Adicionalmente, pueden agregar información a lo largo del chequeo
    // para que quede registrado en el archivo de log

    // NO OLVIDEN QUE LA ÚLTIMA LÍNEA DEL ARCHIVO DEBE SER "SUCCESS" O "FAIL"
    // NO AGREGAR UN SALTO DE LÍNEA DESPUÉS DE "SUCCESS" O "FAIL"

    throw runtime_error("Not Implemented: No se ha implementado la función meteorologicalChecks.");
}

void flightChecks(int shipIndex, int loadCapacity, int fuelAmount, int duration) {
    // Aquí se pueden realizar los chequeos de vuelo necesarios
    // Recuerden que deben guardar la información en el archivo "info/nave_<shipIndex>/flight.txt"
    // El formato del archivo es el siguiente:
    // - Si TODOS los chequeos son exitosos, escribir en la última línea "SUCCESS"
    // - Si alguno de los chequeos no es exitoso, escribir en la última línea "FAIL"
    // Adicionalmente, pueden agregar información a lo largo del chequeo
    // para que quede registrado en el archivo de log

    // NO OLVIDEN QUE LA ÚLTIMA LÍNEA DEL ARCHIVO DEBE SER "SUCCESS" O "FAIL"
    // NO AGREGAR UN SALTO DE LÍNEA DESPUÉS DE "SUCCESS" O "FAIL"

    throw runtime_error("Not Implemented: No se ha implementado la función flightChecks.");
}

void shipLaunchChecks(int shipIndex) {
    // Leemos la información del archivo de información de la nave
    // Tenemos la función readLaunchInfo que recibe el índice de la nave y 
    // referencias a las variables donde se guardará la información
    string name, city, planet, conditions;
    int temperature, humidity, wind, visibility, loadCapacity, fuelAmount, duration;
    readLaunchInfo(shipIndex, name, city, planet, temperature, humidity, wind, conditions, visibility, loadCapacity, fuelAmount, duration);

    string messageStart = "[" + name + "] ";
    
    // Abrimos un archivo de log para guardar la información del lanzamiento
    // El archivo se guardará en "info/nave_<shipIndex>/log.txt"
    ofstream log("info/nave_" + to_string(shipIndex) + "/log.txt");
    if (!log.is_open()) exit(1);

    log << messageStart << city << " \u21E8 " << planet << endl;
    log << messageStart << "Comenzando preparación para el lanzamiento..." << endl;
    
    log << messageStart << "Iniciando sensores meteorológicos..." << endl;

    // A partir de aquí, tienen que completar el código

    // Recuerden verificar si el fork() fue exitoso o no
    // Si el fork() no fue exitoso, el valor de retorno será negativo

    // Reucerden que el log debe tener como última línea "SUCCESS" o "FAIL", 
    // sin salto de línea después de "SUCCESS" o "FAIL"

    // Una recomendación es que loggeen todo lo que pasa, esto les permitirá
    // ver qué está pasando en cada momento y si algo falla, podrán saber dónde

    // Les dejo un órden de ejecución sugerido:

    // 1. Forkeo para el chequeo meteorológico
    // 2. En el hijo, se ejecuta la función meteorologicalChecks, 
    //    NO OLVIDEN TERMINAR EL PROCESO HIJO DESPUÉS DE EJECUTAR LA FUNCIÓN
    // 3. En el padre, forkeo para el chequeo de vuelo
    // 4. En el hijo, se ejecuta la función flightChecks
    //    NO OLVIDEN TERMINAR EL PROCESO HIJO DESPUÉS DE EJECUTAR LA FUNCIÓN
    // 5. Esperar a que ambos hijos terminen. Recuerden que no queremos forzar un órden
    //    entre los dos hijos, ya que son chequeos que pueden hacerse en "paralelo".
    // 6. En el padre, chequear los logs correspondientes a cada chequeo (meteorológico y de vuelo)
    // 7. Si ambos chequeos son exitosos, escribir en el log del padre "SUCCESS"
    //    Si alguno de los chequeos falla, escribir "FAIL"
    // 8. Cerrar el log del padre
}