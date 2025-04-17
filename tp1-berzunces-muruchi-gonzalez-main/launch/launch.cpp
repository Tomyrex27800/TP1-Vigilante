#include <iostream>
#include "../utils/utils.h"
#include <fstream>
#include <vector>
#include <unistd.h> // Para utilizar la función fork
#include <wait.h> // Para utilizar la función wait

using namespace std;

void readLaunchInfo(int shipIndex, string &name, string &city, string &planet, int &temperature, int &humidity, int &wind, string &conditions, int &visibility, int &loadCapacity, int &fuelAmount, int &duration) {
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
                lista_valores=split(line,SIMBOLO,true);
                city = lista_valores[0];
                contador=contador+1;
                continue;
            }
            if (contador==8){
                lista_valores=split(line,SIMBOLO,true);
                planet = lista_valores[0];
                contador=contador+1;
                continue;
            }
            if (contador==11){ // Si llegamos a la línea de la temperatura
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                temperature = stoi(lista_valores[0]); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==12){ // Si llegamos a la línea de la humedad
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                humidity = stoi(lista_valores[0]); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==13){ // Si llegamos a la línea de la dirección del viento
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                wind = stoi(lista_valores[0]); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==14){ // Si llegamos a la línea de la condición meteorológica
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                conditions = lista_valores[0]; // Lo guarda en la variable
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==15){ // Si llegamos a la línea de la visibilidad
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                visibility = stoi(lista_valores[0]); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==18){ // Si llegamos a la línea de la capacidad de carga
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                loadCapacity = stoi(lista_valores[0]); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                continue; // Salta al siguiente ciclo
            }
            if (contador==19){ // Si llegamos a la línea de la cantidad de combustible
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                fuelAmount = stoi(lista_valores[0]); // Lo convierte a entero
                contador=contador+1; // Pasa al siguiente contador
                cout << "FuelAmount: " << fuelAmount << endl;
                continue; // Salta al siguiente ciclo
            }
            if (contador==20){ // Si llegamos a la línea de la duración del vuelo
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                duration = stoi(lista_valores[0]); // Lo convierte a entero
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
    
    //throw runtime_error("Not Implemented: No se ha implementado la función readLaunchInfo.");
}

void meteorologicalChecks(int shipIndex, int temperature, int humidity, int wind, string conditions, int visibility) {
    
    ofstream meteorologic_log("info/nave_" + to_string(shipIndex) + "/meteorologic.txt");

    const int MIN_TEMPERATURE = 0; // En grados Celsius
    const int MAX_TEMPERATURE = 25; // En grados Celsius

    const int MIN_HUMIDITY = 15; // En porcentaje
    const int MAX_HUMIDITY = 85; // En porcentaje

    const int MAX_WIND = 0; // En km/h
    const int REQUIRED_VISIBILITY = 5; // En pocentaje

    bool verfication_1 = false;
    bool verfication_2 = false;
    bool verfication_3 = false;
    bool verfication_4 = false;
    bool verfication_5 = false;

    meteorologic_log << boxedText("Inicio chequeo meteorologico") << endl;


    meteorologic_log << "==== Iniciando verificación de temperatura ====" << endl;
    if (temperature > MIN_TEMPERATURE && temperature < MAX_TEMPERATURE){
        meteorologic_log << "La temperatura del sistema es " << temperature << "°C" << endl;
        meteorologic_log << "La temperatura esta entre " << MIN_TEMPERATURE << "°C y " << MAX_TEMPERATURE << "°C" << endl;
        meteorologic_log << "SUCCESS" << endl;
        verfication_1= true;
    } else{
        meteorologic_log << "La temperatura del sistema es " << temperature << "°C" << endl;
        meteorologic_log << "La temperatura debe esta>r entre " << MIN_TEMPERATURE << "°C y " << MAX_TEMPERATURE << "°C" << endl;
        meteorologic_log << "FAIL" << endl;
    }
    
    meteorologic_log << "" << endl;
    meteorologic_log << "==== Iniciando verificación de humedad ====" << endl;
    if (humidity > MIN_HUMIDITY && humidity < MAX_HUMIDITY){
        meteorologic_log << "El humedad del sistema es " << humidity << "%" << endl;
        meteorologic_log << "El humedad esta entre " << MIN_HUMIDITY << "% y " << MAX_HUMIDITY << "%" << endl;
        meteorologic_log << "SUCCESS" << endl;
        verfication_2= true;
    } else{
        meteorologic_log << "El humedad del sistema es " << humidity << "%" << endl;
        meteorologic_log << "El humedad debe estar entre " << MIN_HUMIDITY << "% y " << MAX_HUMIDITY << "%" << endl;
        meteorologic_log << "FAIL" << endl;
    }
    
    meteorologic_log << "" << endl;
    meteorologic_log << "==== Iniciando verificación de viento ====" << endl;
    if (wind < MAX_WIND){
        meteorologic_log << "El viento del sistema es " << wind << "km/h" << endl;
        meteorologic_log << "El viento es menor a " << MAX_WIND << "km/h" << endl;
        meteorologic_log << "SUCCESS" << endl;
        verfication_3= true;
    } else{
        meteorologic_log << "El viento del sistema es " << wind << "km/h" << endl;
        meteorologic_log << "El viento debe se menor a " << MAX_WIND << "km/h" << endl;
        meteorologic_log << "FAIL" << endl;
    }
    
    meteorologic_log << "" << endl;
    meteorologic_log << "==== Iniciando verificación de visibilidad ====" << endl;
    if (visibility > REQUIRED_VISIBILITY){
        meteorologic_log << "La visibilidad del sistema es " << visibility << "%" << endl;
        meteorologic_log << "La visibilidad es ser mayor a " << REQUIRED_VISIBILITY << "%" << endl;
        meteorologic_log << "SUCCESS" << endl;
        verfication_4= true;
    } else{
        meteorologic_log << "La visibilidad del sistema es " << visibility << "%" << endl;
        meteorologic_log << "La visibilidad debe ser mayor a " << REQUIRED_VISIBILITY << "%" << endl;
        meteorologic_log << "FAIL" << endl;
    }
    
    meteorologic_log << "" << endl;
    meteorologic_log << "==== Iniciando verificación de clima ====" << endl;
    if (conditions == "Despejado"){
        meteorologic_log << "El clima del sistema es " << conditions << endl;
        meteorologic_log << "El clima esta despejado" << endl;
        meteorologic_log << "SUCCESS" << endl;
        verfication_5= true;
    } else if (conditions == "Nublado"){
        meteorologic_log << "El clima del sistema es " << conditions << endl;
        meteorologic_log << "El clima esta nublado" << endl;
        meteorologic_log << "FAIL" << endl;
    } else{
        meteorologic_log << "El clima del sistema es " << conditions << endl;
        meteorologic_log << "El clima esta desconocido" << endl;
        meteorologic_log << "FAIL" << endl;
    }

    // Aquí se pueden realizar los chequeos meteorológicos necesarios
    meteorologic_log << "" << endl;
    meteorologic_log << "==== Iniciando verificación de todos los chequeos meteorológicos ====" << endl;
    if (verfication_1 && verfication_2 && verfication_3 && verfication_4 && verfication_5){
        meteorologic_log << "Todos los chequeos son exitosos" << endl;
        meteorologic_log << "SUCCESS" << endl;
    } else{
        meteorologic_log << "Alguno de los chequeos no es exitoso" << endl;
        meteorologic_log << "FAIL" << endl;
    }
    
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

    ofstream flight_log("info/nave_" + to_string(shipIndex) + "/flight.txt");

    const double DENSIDAD= 0.81; // 0.81 kg/l
    const double F_GRAVEDAD = 9.81; // 9.81 m/s²
    double peso_combustible = loadCapacity * DENSIDAD ;
    
    bool cargador = false;
    bool combustible = false;

    if (loadCapacity >= (peso_combustible*2)){
        flight_log << "La capacidad de carga de la nave es suficiente para soportar el cargamiento de la nave" << endl;
        cargador=true;
    } else{
        flight_log << "El cargador no puede soportar el cargamiento de la nave" << endl;
    }

    if ((fuelAmount/8.0) >= duration){
        flight_log << "El vuelo tiene el ccombustible suficiente para soportar el vuelo" << endl;
        combustible=true;
    } else{
        flight_log << "El combustible no puede soportar el vuelo de la nave" << endl;
    }
    if (combustible && cargador){
        flight_log << "Todos los chequeos son exitosos" << endl;
        flight_log << "SUCCESS" << endl;
    } else{
        flight_log << "Alguno de los chequeos no es exitoso" << endl;
        flight_log << "FAIL" << endl;
    }


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
    if (!log.is_open()) {
        cerr << "No se pudo abrir el archivo de log para la nave " << shipIndex << endl;
        cerr << "Se abortará la misión" << endl;
        exit(1);
    }
    else {
        log << messageStart << city << " --> " << planet << endl;
        log << messageStart << "Comenzando preparación para el lanzamiento..." << endl;   
        log << messageStart << "Iniciando sensores meteorológicos..." << endl;
        log << messageStart << "Iniciando sensores de vuelo..." << endl;
        meteorologicalChecks(shipIndex, temperature, humidity, wind, conditions, visibility);
        flightChecks(shipIndex, loadCapacity, fuelAmount, duration);
        log << messageStart << "Finalizando sensores meteorológicos..." << endl;
        log << messageStart << "Finalizando sensores de vuelo..." << endl;


    }
    
    exit(1);


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