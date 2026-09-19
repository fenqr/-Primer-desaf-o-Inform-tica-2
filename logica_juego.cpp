#include <iostream>
#include <cstdlib>
#include "logica_juego.h"
#include "bits.h"

// 1. Detectar combinaciones horizontales y verticales (alineaciones de 3 o mas)
bool* detectar_combinaciones(const unsigned char* tablero, int filas, int cols, bool& hay_combinacion) {
    int total = filas * cols;
    bool* marcas = new bool[total](); // Inicializado en false
    hay_combinacion = false;

    // Revision Horizontal
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols - 2; ++c) {
            unsigned char f1 = obtener_ficha(tablero, f, c, cols);
            unsigned char f2 = obtener_ficha(tablero, f, c + 1, cols);
            unsigned char f3 = obtener_ficha(tablero, f, c + 2, cols);

            if (f1 != 0 && f1 == f2 && f2 == f3) {
                marcas[f * cols + c] = true;
                marcas[f * cols + (c + 1)] = true;
                marcas[f * cols + (c + 2)] = true;
                hay_combinacion = true;
            }
        }
    }

    // Revision Vertical
    for (int f = 0; f < filas - 2; ++f) {
        for (int c = 0; c < cols; ++c) {
            unsigned char f1 = obtener_ficha(tablero, f, c, cols);
            unsigned char f2 = obtener_ficha(tablero, f + 1, c, cols);
            unsigned char f3 = obtener_ficha(tablero, f + 2, c, cols);

            if (f1 != 0 && f1 == f2 && f2 == f3) {
                marcas[f * cols + c] = true;
                marcas[(f + 1) * cols + c] = true;
                marcas[(f + 2) * cols + c] = true;
                hay_combinacion = true;
            }
        }
    }

    return marcas;
}

// 2. Eliminar fichas marcadas reemplazandolas por el codigo 0
int eliminar_fichas_marcadas(unsigned char* tablero, const bool* marcas, int filas, int cols) {
    int eliminadas = 0;
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            if (marcas[f * cols + c]) {
                guardar_ficha_en_bits(tablero, f, c, cols, 0);
                eliminadas++;
            }
        }
    }
    return eliminadas;
}

// 3. Aplicar fisica de gravedad (las fichas caen sobre los espacios en 0)
void aplicar_gravedad(unsigned char* tablero, int filas, int cols) {
    for (int c = 0; c < cols; ++c) {
        for (int f = filas - 1; f >= 0; --f) {
            if (obtener_ficha(tablero, f, c, cols) == 0) {
                for (int k = f - 1; k >= 0; --k) {
                    unsigned char arriba = obtener_ficha(tablero, k, c, cols);
                    if (arriba != 0) {
                        guardar_ficha_en_bits(tablero, f, c, cols, arriba);
                        guardar_ficha_en_bits(tablero, k, c, cols, 0);
                        break;
                    }
                }
            }
        }
    }
}

// 4. Rellenar las casillas superiores vacias con fichas aleatorias
void rellenar_espacios_superiores(unsigned char* tablero, int filas, int cols) {
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            if (obtener_ficha(tablero, f, c, cols) == 0) {
                unsigned char nueva = CODIGOS_FICHAS[rand() % 6];
                guardar_ficha_en_bits(tablero, f, c, cols, nueva);
            }
        }
    }
}

// 5. Eliminar ficha elegida por el usuario
void eliminar_ficha_usuario(unsigned char* tablero, int fila, int col, int cols,
                            int& elim_usuario,
                            int& total_fichas_eliminadas,
                            int& puntuacion) {

    unsigned char ficha_actual = obtener_ficha(tablero, fila, col, cols);

    if (ficha_actual != 0) {
        guardar_ficha_en_bits(tablero, fila, col, cols, 0);
        elim_usuario++;
        total_fichas_eliminadas++;
        puntuacion += 10; // +10 pts seleccion manual
    }
}

// 6. Procesar ciclo de cascadas en bucle
void procesar_cascadas(unsigned char* tablero, int filas, int cols,
                       int& total_fichas_eliminadas,
                       int& combinaciones_detectadas,
                       int& cascadas_jugada_actual,
                       int& puntuacion) {

    bool hay_combinacion = false;

    do {
        hay_combinacion = false;
        // 1. Buscar si hay alineaciones de 3 o mas
        bool* marcas = detectar_combinaciones(tablero, filas, cols, hay_combinacion);

        if (hay_combinacion) {
            combinaciones_detectadas++;
            cascadas_jugada_actual++;

            // 2. Borrar fichas marcadas
            int eliminadas_en_paso = eliminar_fichas_marcadas(tablero, marcas, filas, cols);
            total_fichas_eliminadas += eliminadas_en_paso;
            puntuacion += (eliminadas_en_paso * 15);

            delete[] marcas;
            marcas = nullptr;

            // 3. Hacer caer las fichas y rellenar con nuevas
            aplicar_gravedad(tablero, filas, cols);
            rellenar_espacios_superiores(tablero, filas, cols);
        } else {
            delete[] marcas;
            marcas = nullptr;
        }

    } while (hay_combinacion); // Repite MIENTRAS sigan apareciendo combinaciones
}