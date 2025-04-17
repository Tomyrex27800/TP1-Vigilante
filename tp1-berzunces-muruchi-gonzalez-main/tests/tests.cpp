#include <gtest/gtest.h>
#include "../utils/utils.h"
#include "../launch/launch.h"
#include "../generation/generation.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Test for split function
TEST(UtilsTest, SplitFunction) {
    string input = "key:value";
    vector<string> result = split(input, ':');
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "key");
    EXPECT_EQ(result[1], "value");
}

// Test for split function with the delimiter at the beginning
TEST(UtilsTest, SplitFunctionWithDelimiterAtBeginning) {
    string input = ":value:other";
    vector<string> result = split(input, ':');
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "value");
    EXPECT_EQ(result[2], "other");
}

// Test for split function with the delimiter at the end
TEST(UtilsTest, SplitFunctionWithDelimiterAtEnd) {
    string input = "key:value:";
    vector<string> result = split(input, ':');
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "key");
    EXPECT_EQ(result[1], "value");
}

// Test for split function with multiple delimiters
TEST(UtilsTest, SplitFunctionWithMultipleDelimiters) {
    string input = "key:value:other:key2:value2";
    vector<string> result = split(input, ':');
    ASSERT_EQ(result.size(), 5);
    EXPECT_EQ(result[0], "key");
    EXPECT_EQ(result[1], "value");
    EXPECT_EQ(result[2], "other");
    EXPECT_EQ(result[3], "key2");
    EXPECT_EQ(result[4], "value2");
}

// Test for split function without trimming
TEST(UtilsTest, SplitFunctionWithoutTrimming) {
    string input = "  key : value  ";
    vector<string> result = split(input, ':', false);
    ASSERT_EQ(result.size(), 2);
    
    EXPECT_EQ(result[0], "  key ");
    EXPECT_EQ(result[1], " value  ");
}

// Test for split function with trimming
TEST(UtilsTest, SplitFunctionWithTrimming) {
    string input = "  key : value  ";
    vector<string> result = split(input, ':', true);
    ASSERT_EQ(result.size(), 2);
    
    EXPECT_EQ(result[0], "key");
    EXPECT_EQ(result[1], "value");
}
    

// Test for readLastLine function
TEST(UtilsTest, ReadLastLineFunction) {
    ofstream testFile("test.txt");
    testFile << "Line 1\nLine 2\nLine 3";
    testFile.close();

    ifstream fileStream("test.txt");
    string lastLine = readLastLine(fileStream);
    EXPECT_EQ(lastLine, "Line 3");

    remove("test.txt");
}

// Test for readLastLine function with empty file
TEST(UtilsTest, ReadLastLineFunctionEmptyFile) {
    ofstream testFile("empty.txt");
    testFile.close();

    ifstream fileStream("empty.txt");
    string lastLine = readLastLine(fileStream);
    EXPECT_EQ(lastLine, "");

    remove("empty.txt");
}

// Test for readLastLine function with file not found
TEST(UtilsTest, ReadLastLineFunctionFileNotFound) {
    ifstream fileStream("non_existent_file.txt");
    string lastLine = readLastLine(fileStream);
    EXPECT_EQ(lastLine, "");
}

// Test for meteorologicalChecks function
TEST(LaunchTest, MeteorologicalChecksSuccess) {
    int shipIndex = 1;
    int temperature = 20;
    int humidity = 50;
    int wind = 10;
    string conditions = "Despejado";
    int visibility = 10;

    meteorologicalChecks(shipIndex, temperature, humidity, wind, conditions, visibility);

    ifstream file("info/nave_1/meteorologic.txt");
    ASSERT_TRUE(file.is_open());
    string lastLine = readLastLine(file);
    EXPECT_EQ(lastLine, "SUCCESS");
    file.close();
}

TEST(LaunchTest, MeteorologicalChecksFail) {
    int shipIndex = 1;
    int temperature = -20; // Invalid temperature
    int humidity = 50;
    int wind = 10;
    string conditions = "Despejado";
    int visibility = 10;

    meteorologicalChecks(shipIndex, temperature, humidity, wind, conditions, visibility);

    ifstream file("info/nave_1/meteorologic.txt");
    ASSERT_TRUE(file.is_open());
    string lastLine = readLastLine(file);
    EXPECT_EQ(lastLine, "FAIL");
    file.close();
}

// Test for flightChecks function
TEST(LaunchTest, FlightChecksSuccess) {
    int shipIndex = 1;
    int loadCapacity = 2000;
    int fuelAmount = 1000;
    int duration = 100;

    flightChecks(shipIndex, loadCapacity, fuelAmount, duration);

    ifstream file("info/nave_1/flight.txt");
    ASSERT_TRUE(file.is_open());
    string lastLine = readLastLine(file);
    EXPECT_EQ(lastLine, "SUCCESS");
    file.close();
}

TEST(LaunchTest, FlightChecksFail) {
    int shipIndex = 1;
    int loadCapacity = 1000; // Load capacity is less than required
    int fuelAmount = 1000;
    int duration = 100;

    flightChecks(shipIndex, loadCapacity, fuelAmount, duration);

    ifstream file("info/nave_1/flight.txt");
    ASSERT_TRUE(file.is_open());
    string lastLine = readLastLine(file);
    EXPECT_EQ(lastLine, "FAIL");
    file.close();
}

void testWithExpected(bool expectedResults[]){
    // Perform the launch checks
    for (int i = 1; i <= NUM_SPACESHIPS; i++) {
        pid_t processPID = fork();
        ASSERT_TRUE(processPID >= 0) << "Fork failed for ship " << i;
        if (processPID == 0) {
            // Child process: Execute the launch checks
            shipLaunchChecks(i);
            exit(0); // Exit child process after execution
        } else {
            // Parent process: Wait for the child process to finish
            int status;
            waitpid(processPID, &status, 0);
        }

        string folderName = "info/nave_" + to_string(i);
        string fileName = folderName + "/log.txt";

        ifstream file(fileName);
        ASSERT_TRUE(file.is_open());

        string lastLine = readLastLine(file);
        file.close();

        ASSERT_FALSE(lastLine.empty()) << "Log file is empty for ship " << i;

        // Check if the last line is "SUCCESS" or "FAIL"
        if (expectedResults[i - 1]) {
            EXPECT_TRUE(lastLine == "SUCCESS") << "Expected SUCCESS for ship " << i << " found: " << lastLine;
        } else {
            EXPECT_TRUE(lastLine == "FAIL") << "Expected FAIL for ship " << i << " found: " << lastLine;
        }
    }
}

void testWithSeed(int seed, bool expectedResults[]) {
    // Set the random seed for reproducibility
    srand(seed);
    // Generate launch info for the test
    generateLaunchInfo();

    testWithExpected(expectedResults);

}

// Test for shipLaunchChecks function
TEST(LaunchTest, ShipLaunchChecksRandom) {

    bool expectedResults[NUM_SPACESHIPS] = {
        false, false, true, false, false, true, false, false, false, true,
        false, false, false, false, false, false, true, false, false, false
    };

    testWithSeed(2, expectedResults);
}

// Test for shipLaunchChecks with different seed
TEST(LaunchTest, ShipLaunchChecksRandom2){

    bool expectedResults[NUM_SPACESHIPS] = {
        false, true, false, false, false, true, true, false, false, false,
        false, false, false, false, false, false, false, true, false, false
    };

    testWithSeed(5497111, expectedResults);
}

TEST(LaunchTest, ShipLaunchChecksAllSuccess){

    bool expectedResults[NUM_SPACESHIPS];
    fill(begin(expectedResults), end(expectedResults), true);

    // Write the files directly
    if (system("test -d info") != 0) {
        system("mkdir info");
    } else {
        system("rm -rf info/*");
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
            file << "Temperatura: " << 20 << " °C" << endl;
            file << "Humedad: " << 70 << " %" << endl;
            file << "Viento: " << 10 << " km/h" << endl;
            file << "Condiciones: " << "Despejado" << endl;
            file << "Visibilidad: " << 100 << " %" << endl;
            file << endl;
            file << "==== Información adicional ====" << endl;
            file << "Capacidad de carga: " << 3500 << " kg" << endl; // Capacidad entre 1000 y 3500 kg
            file << "Combustible: " << 1000 << " litros" << endl; // Combustible entre 500 y 1500 litros
            file << "Duración del viaje: " << 50 << " horas" << endl; // Duración entre 50 y 150 horas
            file.close();
        } else {
            cout << "Error al crear el archivo de información para la nave " << i << endl;
            cout << "Saliendo del programa." << endl;
            exit(1);
        }
    }

    testWithExpected(expectedResults);
}