#include <iostream>
#include <unistd.h> // Para utilizar la función sleep
#include <string>
#include <sstream>
#include <fstream>
#include "utils.h"
#include <vector>
#include <algorithm>

using namespace std;


// Función para eliminar espacios en blanco al principio y al final de una cadena
string trim(const string& str) {
    string s = str;
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
    return s;
}


vector<string> split(const string& str, char delimiter, bool trim_flag) {
    //string es la linea del txt (getline)
    //delimiter es el ":"
    //trim se encarga de eliminar los espacios blancos cuando es "TRUE" y vicebersa
    
    stringstream ss;
    ss << str;
    string string_temporal;
    vector<string> v_line;
    while (getline(ss, string_temporal, delimiter)) {
        if (trim_flag) {
            v_line.push_back(trim(string_temporal));
        } else {
            v_line.push_back(string_temporal);
        }
    }
    return v_line;

}

string readLastLine(ifstream& fileStream) {
    string lastLine;
    string currentLine;

    if (fileStream.is_open()) {
        while (getline(fileStream, currentLine)) {
            lastLine = currentLine;
        }
        fileStream.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << endl;
    }
    return lastLine;
}

string boxedText(const string& text) {
    int length = text.length();
    int boxWidth = length + 4; // 2 espacios de margen a cada lado y 2 para los bordes
    stringstream ss;
    ss << "╔";
    for (int i = 0; i < boxWidth - 1; i++) {
        ss << "═";
    }
    ss << "╗\n";
    ss << "║  " << text << "  ║\n";
    ss << "╚";
    for (int i = 0; i < boxWidth - 1; i++) {
        ss << "═";
    }
    ss << "╝\n";
    return ss.str();
}

void welcomeScreen() {
    cout << endl;
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════╗" << endl; 
    cout << "║                                                                                        ║" << endl;
    cout << "║         :::::::::::     :::::::::::     :::                :::         :::    :::      ║" << endl;
    cout << "║            :+:             :+:         :+:              :+: :+:       :+:    :+:       ║" << endl;
    cout << "║           +:+             +:+         +:+             +:+   +:+      +:+    +:+        ║" << endl;
    cout << "║          +#+             +#+         +#+            +#++:++#++:     +#++:++#++         ║" << endl;
    cout << "║         +#+             +#+         +#+            +#+     +#+     +#+    +#+          ║" << endl;
    cout << "║        #+#     #+#     #+#     #+# #+#        #+# #+#     #+# #+# #+#    #+# #+#       ║" << endl;
    cout << "║    ########### ### ########### ### ########## ### ###     ### ### ###    ### ###       ║" << endl;
    cout << "║                                                                                        ║" << endl;
    cout << "╚════════════ Instituto de Investigación y Lanzamiento Aeroespacial Huergo ══════════════╝" << endl;
    cout << endl;

    cout << "[System] Iniciando el programa...\n";
    usleep(SLEEP_TIME);

    cout << "[System] Cargando cálculos de trayectorias...\n";
    usleep(SLEEP_TIME); 

    cout << "[System] Midiendo datos meteorológicos...\n";

    usleep(SLEEP_TIME); 

    cout << "[System] Procedimiento de lanzamiento de " << NUM_SPACESHIPS << " naves espaciales iniciado." << endl;

    usleep(SLEEP_TIME);
}

void failedLaunch(int shipIndex, string details) {
    cout << "[";
    // Cambio color a rojo
    cout << "\033[31m"; // Cambia el color a rojo
    cout << "FAIL";
    cout << "\033[0m"; // Restablece el color
    cout << "] ";
    cout << "Lanzamiento de la nave " << spaceships[shipIndex - 1] << " fallido. " << details << endl;
}

void successfulLaunch(int shipIndex, string details) {
    cout << "[";
    // Cambio color a verde
    cout << "\033[32m"; // Cambia el color a verde
    cout << "SUCCESS";
    cout << "\033[0m"; // Restablece el color
    cout << "] ";
    cout << "Lanzamiento exitoso de la nave " << spaceships[shipIndex - 1] << "! " << details << endl;
}
