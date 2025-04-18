#include <iostream>
#include <fstream>
#include "../utils/utils.h"

using namespace std;

void generateLaunchInfo() {
    cout << "Generando información de lanzamiento para " << NUM_SPACESHIPS << " naves espaciales..." << endl;

    // Si la carpeta "info" existe, eliminamos su contenido
    // Si no existe, la creamos
    if (system("test -d info") != 0) { // Verificar si la carpeta "info" existe
        system("mkdir info"); // Crear la carpeta "info" si no existe
    } else {
        system("rm -rf info/*"); // Limpiar el contenido de la carpeta "info"
    }

    for (int i = 1; i <= NUM_SPACESHIPS; i++) {
        // Genero carpeta para cada nave
        string folderName = "info/nave_" + to_string(i);
        if (system(("mkdir " + folderName).c_str()) != 0) {
            cout << "Error al crear la carpeta para la nave " << i << endl;
            cout << "Saliendo del programa." << endl;
            exit(1);
        }
        // Genero archivo de información
        string fileName = folderName + "/info.txt";
        ofstream file(fileName);

        if (file.is_open()) {
            file << boxedText("Información de la nave " + spaceships[i % NUM_SPACESHIPS] + "  ") << endl;
            file << "==== Datos de la nave ====" << endl;
            file << "Nombre de la nave: " << spaceships[i % NUM_SPACESHIPS] << endl;
            file << "Ciudad de lanzamiento: " << cities[i % NUM_CITIES] << endl;
            file << "Destino: " << planets[i % NUM_PLANETS] << endl;
            file << endl;
            file << "==== Datos meteorológicos ====" << endl;
            file << "Temperatura: " << (rand() % 41) - 10 << " °C" << endl; // Temperatura entre -10 y 30
            file << "Humedad: " << (rand() % 101) << " %" << endl; // Humedad entre 0 y 100
            file << "Viento: " << (rand() % 61) << " km/h" << endl; // Viento entre 0 y 60
            file << "Condiciones: " << (rand() % 2 == 0 ? "Despejado" : "Nublado") << endl;
            file << "Visibilidad: " << (rand() % 101) << " %" << endl; // Visibilidad entre 0 y 100
            file << endl;
            file << "==== Información adicional ====" << endl;
            file << "Capacidad de carga: " << (rand() % 2501) + 1000 << " kg" << endl; // Capacidad entre 1000 y 3500 kg
            file << "Combustible: " << (rand() % 1001) + 500 << " litros" << endl; // Combustible entre 500 y 1500 litros
            file << "Duración del viaje: " << (rand() % 101) + 50 << " horas" << endl; // Duración entre 50 y 150 horas
            file.close();
        } else {
            cout << "Error al crear el archivo de información para la nave " << i << endl;
            cout << "Saliendo del programa." << endl;
            exit(1);
        }
    }

    cout << "Información generada con éxito." << endl;
}