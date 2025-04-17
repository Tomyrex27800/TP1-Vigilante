#include <string>
#include <vector>
using namespace std;

// 200ms en microsegundos para dramatismo, 
// pueden cambiarlo a 0 cuando les empiece a molestar
const int SLEEP_TIME = 0;

/**
 * @brief Lista de los nombres de las ciudades.
 * @details Esta lista contiene los nombres de las ciudades desde donde se lanzarán las naves espaciales.
 * Cada ciudad tiene un nombre único y se utiliza para identificar el lugar de lanzamiento.
 */
const string cities[] = {
    "Tecnobitlán",
    "Puerto Kernel",
    "Valle del Clock",
    "Ciudad Thread",
    "Memorina",
    "Stackópolis",
    "Segfault City",
    "Bahía del Buffer",
    "San Forkencio",
    "Monte Exec",
    "Arenas del Input",
    "Puerto Waitón",
    "Neuronia",
    "Colonia Byte",
    "Tandilinux",
    "Villa Concurrencia",
    "Loopazo del Norte",
    "Bahía Binaria",
    "Nueva Fstream",
    "Terraplén del Ping"
};

/**
 * @brief Lista de los nombres de los planetas.
 * @details Esta lista contiene los nombres de los planetas a los que se enviarán las naves espaciales.
 * Cada planeta tiene un nombre único y se utiliza para identificar el destino de la nave.
 */
const string planets[] = {
    "Algoritmia",
    "Nebulix",
    "Hexón",
    "Parseida",
    "Planix",
    "Reticulón V",
    "Compilatia",
    "Syntaxis",
    "Orbitex",
    "Glitchmar",
    "Debuglia",
    "RAMdora",
    "Semantix",
    "Cronux",
    "Z-Bufferia",
    "Looparis",
    "PX-404",
    "Forkonia",
    "Execdora",
    "Varion Prime"
};

/**
 * @brief Lista de los nombres de las naves espaciales.
 * @details Esta lista contiene los nombres de las naves espaciales que se utilizarán en la simulación.
 * Cada nave tiene un nombre único y se utiliza para identificar la nave en el lanzamiento.
 */
const string spaceships[] = {
    "Iilah One",
    "AO-6X",
    "Fork Falcon",
    "Execplorer",
    "Bitrunner",
    "CompuSat",
    "Semaphore IX",
    "Vectorial 3000",
    "Nodo Alfa",
    "Stack Rider",
    "Process One",
    "Concurrentor",
    "AO-Rion",
    "Static 5",
    "Kernel Wings",
    "WaitStorm",
    "Mainthread",
    "Rocket.h",
    "SyncFly",
    "AO-Delta"
};

/**
 * @brief Número de ciudades.
 * @details Este valor define la cantidad total de ciudades disponibles para el lanzamiento de naves espaciales.
 */
const int NUM_CITIES = sizeof(cities) / sizeof(cities[0]);

/**
 * @brief Número de planetas.
 * @details Este valor define la cantidad total de planetas disponibles como destino para las naves espaciales.
 */
const int NUM_PLANETS = sizeof(planets) / sizeof(planets[0]);

/**
 * @brief Número de naves espaciales.
 * @details Este valor define la cantidad total de naves espaciales disponibles para el lanzamiento.
 */
const int NUM_SPACESHIPS = sizeof(spaceships) / sizeof(spaceships[0]);

/**
 * @brief Muestra la pantalla de bienvenida y solicita el número de naves espaciales a lanzar.
 * @details Esta función muestra un mensaje de bienvenida y solicita al usuario que ingrese el número de naves espaciales a lanzar.
 * @return El número de naves espaciales a lanzar.
 * @note Si el número ingresado es menor que el mínimo o mayor que el máximo, se mostrará un mensaje de error y se cerrará el programa.
 */
void welcomeScreen();

/**
 * @brief Divide una cadena en partes utilizando un delimitador.
 * @details Esta función toma una cadena y la divide en partes utilizando un delimitador especificado.
 * Si se especifica, también eliminará los espacios en blanco al principio y al final de cada parte.
 * @param str La cadena a dividir.
 * @param delimiter El delimitador utilizado para dividir la cadena.
 * @param trim Si es verdadero, eliminará los espacios en blanco al principio y al final de cada parte.
 * @return Un vector de cadenas que contiene las partes divididas.
 * @note Esta función es útil para procesar cadenas de texto que contienen información separada por un delimitador específico.
 */
vector<string> split(const string& str, char delimiter, bool trim = true);

/**
 * @brief Genera un texto enmarcado con caracteres especiales.
 * @details Esta función toma un texto y lo envuelve en caracteres especiales para crear un efecto de marco.
 * @param text El texto a enmarcar.
 * @return El texto enmarcado.
 * @note Esta función es útil para resaltar información importante en la salida del programa.
 */
string boxedText(const string& text);

/**
 * @brief Muestra un mensaje correspondiente al lanzamiento fallido de una nave.
 * @details Esta función muestra un mensaje indicando que el lanzamiento de una nave ha fallado.
 * @param shipIndex El índice de la nave que falló en el lanzamiento.
 * @param details Detalles adicionales sobre el fallo (opcional).
 */
void failedLaunch(int shipIndex, string details = "");

/**
 * @brief Muestra un mensaje correspondiente al lanzamiento exitoso de una nave.
 * @details Esta función muestra un mensaje indicando que el lanzamiento de una nave ha sido exitoso.
 * @param shipIndex El índice de la nave que tuvo un lanzamiento exitoso.
 * @param details Detalles adicionales sobre el éxito (opcional).
 * @note Esta función es útil para mostrar información sobre el estado de las naves después del lanzamiento.
 */
void successfulLaunch(int shipIndex, string details = "");

/**
 * @brief Lee la última línea de un archivo.
 * @details Esta función toma la ruta de un archivo y devuelve la última línea del archivo.
 * @param fileStream El flujo de entrada del archivo.
 * @returns La última línea del archivo como una cadena.
 * @note Esta función es útil para obtener información específica de un archivo sin cargar todo su contenido en memoria.
 */
string readLastLine(ifstream& fileStream);
