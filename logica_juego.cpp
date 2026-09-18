#include <cstdlib>
#include <iostream>
#include "logica_juego.h"
#include "bits.h"
#include "interfaz.h"

using namespace std;

bool* detectar_combinaciones(const unsigned char* tablero, int filas, int cols, bool& hay_combinacion) {
    int total_casillas = filas * cols;
    if (filas < 1 || cols < 1) {
        hay_combinacion = false;
        return nullptr;
    }

    bool* marcas = new bool[total_casillas]();
    hay_combinacion = false;

    // horizontal
    if (cols >= 3) {
        for (int f = 0; f < filas; ++f) {
            for (int c = 0; c <= cols - 3; ++c) {
                unsigned char f1 = obtener_ficha(tablero, f, c, cols);
                if (f1 == 0) continue; // ignora las casillas vacias

                unsigned char f2 = obtener_ficha(tablero, f, c + 1, cols);
                unsigned char f3 = obtener_ficha(tablero, f, c + 2, cols);

                if (f1 == f2 && f2 == f3) {
                    int idx = f * cols + c;
                    marcas[idx] = true;
                    marcas[idx + 1] = true;
                    marcas[idx + 2] = true;
                    hay_combinacion = true;
                }
            }
        }
    }

    //vertical
    if (filas >= 3) {
        for (int c = 0; c < cols; ++c) {
            for (int f = 0; f <= filas - 3; ++f) {
                unsigned char f1 = obtener_ficha(tablero, f, c, cols);
                if (f1 == 0) continue; // Ignorar casillas vacías

                unsigned char f2 = obtener_ficha(tablero, f + 1, c, cols);
                unsigned char f3 = obtener_ficha(tablero, f + 2, c, cols);

                if (f1 == f2 && f2 == f3) {
                    int idx = f * cols + c;
                    marcas[idx] = true;
                    marcas[idx + cols] = true;
                    marcas[idx + (2 * cols)] = true;
                    hay_combinacion = true;
                }
            }
        }
    }

    return marcas;
}

int eliminar_fichas_marcadas(unsigned char* tablero, const bool* marcas, int filas, int cols) {
    int eliminadas = 0;
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            int idx = f * cols + c;
            if (marcas[idx]) {
                guardar_ficha_en_bits(tablero, f, c, cols, 0); // Escribir 0 (Espacio vacío)
                eliminadas++;
            }
        }
    }
    return eliminadas;
}

void aplicar_gravedad(unsigned char* tablero, int filas, int cols) {
    for (int c = 0; c < cols; ++c) {
        int destino = filas - 1;
        for (int f = filas - 1; f >= 0; --f) {
            unsigned char ficha = obtener_ficha(tablero, f, c, cols);
            if (ficha != 0) {
                if (f != destino) {
                    guardar_ficha_en_bits(tablero, destino, c, cols, ficha);
                    guardar_ficha_en_bits(tablero, f, c, cols, 0);
                }
                destino--;
            }
        }
    }
}

void rellenar_espacios_superiores(unsigned char* tablero, int filas, int cols) {
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            if (obtener_ficha(tablero, f, c, cols) == 0) {
                unsigned char nueva_ficha = CODIGOS_FICHAS[rand() % 6];
                guardar_ficha_en_bits(tablero, f, c, cols, nueva_ficha);
            }
        }
    }
}

void procesar_cascadas(unsigned char* tablero, int filas, int cols) {
    bool hay_combinacion = false;

    do {
        bool* marcas = detectar_combinaciones(tablero, filas, cols, hay_combinacion);

        if (hay_combinacion) {
            int eliminadas = eliminar_fichas_marcadas(tablero, marcas, filas, cols);
            cout << "\nFichas eliminadas: " << eliminadas << "\n";
            mostrar_tablero_fichas(tablero, filas, cols);

            aplicar_gravedad(tablero, filas, cols);
            rellenar_espacios_superiores(tablero, filas, cols);

            cout << "\n--- TABLERO TRAS CAIDA Y RELLENADO ---";
            mostrar_tablero_fichas(tablero, filas, cols);

        }

        delete[] marcas;
    } while (hay_combinacion);

    cout << "\n    El tablero ha quedado estable.   \n";
}