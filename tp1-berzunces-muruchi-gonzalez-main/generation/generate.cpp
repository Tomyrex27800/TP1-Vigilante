#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../utils/utils.h"
#include "generation.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Procedimiento de lanzamiento de " << NUM_SPACESHIPS << " naves espaciales iniciado." << endl;

    // Inicializamos la semilla para la generación de números aleatorios
    // srand(time(NULL)); -> Semilla basada en el tiempo actual
    // srand(atoi(argv[1])); -> Semilla fija por medio de un argumento (sobre todo para testear)
    int seed = (argc == 2) ? atoi(argv[1]) : time(NULL);
    srand(seed);

    cout << "Semilla utilizada: " << seed << endl;

    generateLaunchInfo();

    return 0;
}