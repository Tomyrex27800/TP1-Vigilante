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
            if (contador==5){
                lista_valores=split(line,SIMBOLO,false);
                if (lista_valores.size() > 1) {
                    name = lista_valores[1];
                }
            } else if (contador==6){
                lista_valores=split(line,SIMBOLO,true);
                if (lista_valores.size() > 1) {
                    city = lista_valores[1];
                }
            } else if (contador==7){
                lista_valores=split(line,SIMBOLO,true);
                if (lista_valores.size() > 1) {
                    planet = lista_valores[1];
                }
            } else if (contador==10){ // Si llegamos a la línea de la temperatura
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                if (lista_valores.size() > 1) {
                    string temp_str = lista_valores[1];
                    size_t pos_grados = temp_str.find("°");
                    size_t pos_celsius = temp_str.find("C");
                    if (pos_grados != string::npos) temp_str.erase(pos_grados, 1); // Borra "°" (1 caracter)
                    if (pos_celsius != string::npos) temp_str.erase(pos_celsius, 1); // Borra "C" (1 caracter)
                    temperature = stoi(trim(temp_str));
                }
            } else if (contador==11){ // Si llegamos a la línea de la humedad
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                if (lista_valores.size() > 1) {
                    string hum_str = lista_valores[1];
                    size_t pos_percentaje = hum_str.find("%");
                    if (pos_percentaje != string::npos) hum_str.erase(pos_percentaje, 1); // Borra "%" (1 caracter)
                    humidity = stoi(trim(hum_str));
                }
            } else if (contador==12){ // Si llegamos a la línea de la dirección del viento
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                if (lista_valores.size() > 1) {
                    string wind_str = lista_valores[1];
                    size_t pos_kmh = wind_str.find("km/h");
                    if (pos_kmh != string::npos) wind_str.erase(pos_kmh, 4); // Borra "km/h" (4 caracteres)
                    wind = stoi(trim(wind_str));
                }
            } else if (contador==13){ // Si llegamos a la línea de la condición meteorológica
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                if (lista_valores.size() > 1) {
                    conditions = lista_valores[1]; // Lo guarda en la variable
                }
            } else if (contador==14){ // Si llegamos a la línea de la visibilidad
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                if (lista_valores.size() > 1) {
                    string vis_str = lista_valores[1];
                    size_t pos_percentaje = vis_str.find("%");
                    if (pos_percentaje != string::npos) vis_str.erase(pos_percentaje, 1); // Borra "%" (1 caracter)
                    visibility = stoi(trim(vis_str));
                }
            } else if (contador==17){ // Si llegamos a la línea de la capacidad de carga
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                if (lista_valores.size() > 1) {
                    string load_str = lista_valores[1];
                    size_t pos_kg = load_str.find("kg");
                    if (pos_kg != string::npos) load_str.erase(pos_kg, 2); // Borra "kg" (2 caracteres)
                    loadCapacity = stoi(trim(load_str));
                }
            } else if (contador==18){ // Si llegamos a la línea de la cantidad de combustible
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                if (lista_valores.size() > 1) {
                    string fuel_str = lista_valores[1];
                    size_t pos_litros = fuel_str.find("litros");
                    if (pos_litros != string::npos) fuel_str.erase(pos_litros, 6); // Borra "litros" (6 caracteres)
                    fuelAmount = stoi(trim(fuel_str));
                }
            } else if (contador==19){ // Si llegamos a la línea de la duración del vuelo
                lista_valores=split(line,SIMBOLO,true); // Lo separa por el simbolo ":"
                if (lista_valores.size() > 1) {
                    string duration_str = lista_valores[1];
                    size_t pos_horas = duration_str.find("horas");
                    if (pos_horas != string::npos) duration_str.erase(pos_horas, 5); // Borra "horas" (5 caracteres)
                    duration = stoi(trim(duration_str));
                }
            }
            contador++;
        }
        read_file.close();
    }
    else {
        throw runtime_error("No se pudo abrir el archivo de información de la nave " + to_string(shipIndex));
    }

}

void meteorologicalChecks(int shipIndex, int temperature, int humidity, int wind, string conditions, int visibility) {
    
    const int MIN_TEMPERATURE = 0; // En grados Celsius
    const int MAX_TEMPERATURE = 25; // En grados Celsius

    const int MIN_HUMIDITY = 15; // En porcentaje
    const int MAX_HUMIDITY = 85; // En porcentaje

    const int MAX_WIND = 45; // En km/h
    const int REQUIRED_VISIBILITY = 5; // En pocentaje

    bool verfication_1 = false; // Verificación de temperatura
    bool verfication_2 = false; // Verificación de humedad
    bool verfication_3 = false; // Verificación de viento
    bool verfication_4 = false; // Verificación de visibilidad
    bool verfication_5 = false; // Verificación de clima
    
    //Abrimos un archivo de log para guardar la información de chequeo meteorológico
    ofstream meteorologic_log("info/nave_" + to_string(shipIndex) + "/meteorologic.txt");
    if (!meteorologic_log.is_open()) {
        cerr << "No se pudo abrir el archivo de log para la nave " << shipIndex << endl;
        cerr << "Se abortará la misión" << endl;
        exit(1);
    } else { 
        
        meteorologic_log << boxedText("Inicio chequeo meteorologico") << endl;


        //Aquí se pueden realizar los chequeos de temperatura necesarios
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
        
        //Aquí se pueden realizar los chequeos de humedad necesarios
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
        
        //Aquí se pueden realizar los chequeos de viento necesarios
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
        
        //Aquí se pueden realizar los chequeos de visibilidad necesarios
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
        
        //Aquí se pueden realizar los chequeos de clima necesarios
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
    }
}

void flightChecks(int shipIndex, int loadCapacity, int fuelAmount, int duration) {

    const double DENSITY= 0.81; // En 0.81 kg/l
    double combustible_weight = fuelAmount * DENSITY ; // Calculo del peso del combustible
    
    bool verification_1 = false; // Verificación de capacidad de carga
    bool verification_2 = false; // Verificación de combustible

    //Abrimos un archivo de log para guardar la información de chequeo de vuelo
    ofstream flight_log("info/nave_" + to_string(shipIndex) + "/flight.txt");

    if (!flight_log.is_open()) {
        cerr << "No se pudo abrir el archivo de log para la nave " << shipIndex << endl;
        cerr << "Se abortará la misión" << endl;
        exit(1);
    } else { 

        flight_log << boxedText("Inicio chequeo de vuelo") << endl;

        //Aquí se pueden realizar los chequeos de capacidad de carga necesarios
        flight_log << "==== Iniciando verificación de capacidad de carga ====" << endl;
        if (loadCapacity >= (combustible_weight*2)){
            flight_log << "La capcidad de la nave es " << loadCapacity << " kg" << endl;
            flight_log << "La capacidad de carga de la nave es suficiente para soportar el cargamiento de la nave" << endl;
            flight_log << "SUCCESS" << endl;
            verification_1=true;
        } else{
            flight_log << "La capacidad de carga de la nave es " << loadCapacity << " kg" << endl;
            flight_log << "La capacidad de carga de la nave no es suficiente para soportar el cargamiento de la nave" << endl;
            flight_log << "FAIL" << endl;
        }

        //Aquí se pueden realizar los chequeos de vuelo necesarios
        flight_log << "" << endl;
        flight_log << "==== Iniciando verificación de combustible ====" << endl;
        if ((fuelAmount/8.0) >= duration){
            flight_log << "La cantidad de combustible es " << fuelAmount << " litros" << endl;
            flight_log << "La cantidad de combustible es suficiente para soportar el vuelo" << endl;
            flight_log << "SUCCESS" << endl;
            verification_2=true;
        } else{
            flight_log << "La cantidad de combustible es " << fuelAmount << " litros" << endl;
            flight_log << "La cantidad de combustible no es suficiente para soportar el vuelo" << endl;
            flight_log << "FAIL" << endl;
        }

        //Aquí se pueden realizar los chequeos de vuelo necesarios
        flight_log << "" << endl;
        flight_log << "==== Iniciando verificación de todos los chequeos de vuelo ====" << endl;
        if (verification_1 && verification_2){
            flight_log << "Todos los chequeos son exitosos" << endl;
            flight_log << "SUCCESS" << endl;
        } else{
            flight_log << "Alguno de los chequeos no es exitoso" << endl;
            flight_log << "FAIL" << endl;
        }

    }
}

void shipLaunchChecks(int shipIndex) {
    // Leemos la información del archivo de información de la nave
    // Tenemos la función readLaunchInfo que recibe el índice de la nave y 
    // referencias a las variables donde se guardará la información
    string name, city, planet, conditions;
    int temperature, humidity, wind, visibility, loadCapacity, fuelAmount, duration;
    readLaunchInfo(shipIndex, name, city, planet, temperature, humidity, wind, conditions, visibility, loadCapacity, fuelAmount, duration);


    string flight_file = "info/nave_" + to_string(shipIndex) + "/flight.txt";
    string meteorologic_file = "info/nave_" + to_string(shipIndex) + "/meteorologic.txt";
    string log_file = "info/nave_" + to_string(shipIndex) + "/log.txt";

    string messageStart = "[" + name + " ] ";

    ofstream log(log_file);
    if (!log.is_open()) {
        cerr << "No se pudo abrir el archivo de log para la nave " << shipIndex << endl;
        cerr << "Se abortará la misión" << endl;
        exit(1);
    }
    
    log << messageStart << city << " --> " << planet << endl;
    log << messageStart << "Comenzando preparación para el lanzamiento..." << endl;
    log << messageStart << "Iniciando chequeo generales..." << endl;
    log << messageStart << "Iniciando sensores meteorológicos..." << endl;
    log << messageStart << "Iniciando sensores de vuelo..." << endl;
    pid_t meteorologic_pid , flight_pid;
    int meteorologic_status, flight_status;
    meteorologic_pid = fork();

    if (meteorologic_pid == -1) {
        cerr << "Error al crear el proceso hijo para el chequeo meteorológico de la nave " << shipIndex << endl;
        log << "Error: No se pudo iniciar el proceso hijo para el chequeo meteorológico de la nave " << shipIndex << endl;
        log << "FAIL" << endl;
    } else if (meteorologic_pid == 0) {
        log << messageStart << "Ejecutando chequeo meteorológico..." << endl;
        meteorologicalChecks(shipIndex, temperature, humidity, wind, conditions, visibility);
        log << messageStart << "Chequeo meteorológico finalizado." << endl;
        exit(0);
    } else {

        flight_pid = fork();
        
        if (flight_pid == -1) {
            cerr << "Error al crear el proceso hijo para el chequeo de vuelo de la nave " << shipIndex << endl;
            log << "Error: No se pudo iniciar el proceso hijo para el chequeo de vuelo de la nave " << shipIndex << endl;
            log << "FAIL" << endl;
            kill(meteorologic_pid, SIGKILL);
        } else if (flight_pid == 0) {
            log << messageStart << "Ejecutando chequeo de vuelo..." << endl;
            flightChecks(shipIndex, loadCapacity, fuelAmount, duration);
            log << messageStart << "Chequeo de vuelo finalizado." << endl;
            exit(0);
        } else {
            waitpid(meteorologic_pid, &meteorologic_status, 0);
            waitpid(flight_pid, &flight_status, 0);
        
            bool meteorologic_check = false;
            bool flight_check = false;

            log << messageStart << "Recopilando informacion de los chequeos..." << endl;
            ifstream meteorologic_log(meteorologic_file);
            string lastMeteoLogicLine = readLastLine(meteorologic_log);
            if (lastMeteoLogicLine == "SUCCESS") {
                meteorologic_check = true;
            } else {
                log << messageStart << "Condiciones meteorológicas no adecuadas para el lanzamiento." << endl;
            }
            meteorologic_log.close();

            ifstream flight_log(flight_file);
            string lastFlightLine = readLastLine(flight_log);
            if (lastFlightLine == "SUCCESS") {
                flight_check = true;
            } else {
                log << messageStart << "Condiciones de vuelo no adecuadas para el lanzamiento." << endl;
            }
                flight_log.close();

            if (meteorologic_check && flight_check) {
                log << "SUCCESS" << endl;
            } else {
                log << "FAIL" << endl;
            }
        }
    }
}