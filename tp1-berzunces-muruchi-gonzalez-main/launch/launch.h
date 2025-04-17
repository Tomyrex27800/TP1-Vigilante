#include <string>

using namespace std;

/**
 * @brief Lee la información del lanzamiento de la nave.
 * @details La información se encuentra en el archivo "info/nave_<shipIndex>/info.txt".
 * @param shipIndex Índice de la nave.
 * @param name Nombre de la nave.
 * @param city Ciudad de lanzamiento.
 * @param planet Planeta de lanzamiento.
 * @param temperature Temperatura en grados.
 * @param humidity Humedad en porcentaje.
 * @param wind Velocidad del viento.
 * @param conditions Condiciones meteorológicas.
 * @param visibility Visibilidad.
 * @param loadCapacity Capacidad de carga.
 * @param fuelAmount Cantidad de combustible.
 * @param duration Duración del vuelo.
 */
void readLaunchInfo(int shipIndex, string& name, string& city, string& planet, int& temperature, int& humidity, int& wind, string& conditions, int& visibility, int& loadCapacity, int& fuelAmount, int& duration);

/**
 * @brief Realiza los chequeos de lanzamiento de la nave.
 * @param shipIndex Índice de la nave.
 */
void shipLaunchChecks(int shipIndex);

/**
 * @brief Realiza los chequeos meteorológicos de la nave.
 * @details Guarda el resultado en el archivo "info/nave_<shipIndex>/meteorologic.txt".
 * @param shipIndex Índice de la nave.
 * @param temperature Temperatura en grados.
 * @param humidity Humedad en porcentaje.
 * @param wind Velocidad del viento.
 * @param conditions Condiciones meteorológicas.
 * @param visibility Visibilidad.
 */
void meteorologicalChecks(int shipIndex, int temperature, int humidity, int wind, string conditions, int visibility);

/**
 * @brief Realiza los chequeos de vuelo de la nave.
 * @details Guarda el resultado en el archivo "info/nave_<shipIndex>/flight.txt".
 * @param shipIndex Índice de la nave.
 * @param loadCapacity Capacidad de carga.
 * @param fuelAmount Cantidad de combustible.
 * @param duration Duración del vuelo.
 */
void flightChecks(int shipIndex, int loadCapacity, int fuelAmount, int duration);