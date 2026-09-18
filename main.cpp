#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bits.h"
#include "interfaz.h"
#include "logica_juego.h"

using namespace std;

int main() {
    srand(time(nullptr));

    int filas = 0;
    int cols = 0;

    cout << "BIENVENIDO A SWEET CRUSH\n";
    cout << "Ingrese el numero de filas: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas: ";
    cin >> cols;

    if (filas <= 0 || cols <= 0) return 1;

    int bytes_necesarios = calcular_bytes_necesarios(filas, cols);
    unsigned char* tablero = new unsigned char[bytes_necesarios];

    generar_tablero_aleatorio(tablero, filas, cols);

    cout << "\n--- TABLERO INICIAL ---";
    mostrar_tablero_fichas(tablero, filas, cols);

    procesar_cascadas(tablero, filas, cols);

    delete[] tablero;
    tablero = nullptr;

    return 0;
}