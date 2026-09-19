#include <iostream>
#include "interfaz.h"
#include "bits.h"

using namespace std;

char convertir_codigo_a_caracter(unsigned char codigo) {
    switch (codigo) {
    case 0: return ' ';
    case 1: return 'A';
    case 2: return 'B';
    case 3: return 'C';
    case 4: return 'D';
    case 5: return 'E';
    case 6: return 'F';
    default: return '?';
    }
}

void mostrar_tablero_fichas(const unsigned char* tablero, int filas, int cols) {
    cout << "\n--- TABLERO DE JUEGO (" << filas << "x" << cols << ") ---\n\n" << flush;

    cout << "    ";
    for (int c = 0; c < cols; ++c) {
        cout << c << " ";
    }
    cout << "\n  ";

    for (int i = 0; i < cols * 2 + 3; ++i) {
        cout << "-";
    }
    cout << "\n" << flush;

    for (int f = 0; f < filas; ++f) {
        cout << f << " | ";
        for (int c = 0; c < cols; ++c) {
            unsigned char cod = obtener_ficha(tablero, f, c, cols);
            cout << convertir_codigo_a_caracter(cod) << " ";
        }
        cout << "|\n" << flush;
    }

    cout << "  ";
    for (int i = 0; i < cols * 2 + 3; ++i) {
        cout << "-";
    }
    cout << "\n" << flush;
}

void mostrar_trama_binaria(const unsigned char* tablero, int filas, int cols) {
    int total_bytes = calcular_bytes_necesarios(filas, cols);

    cout << "\n    TRAMA CONTINUA DE BITS EN MEMORIA    \n" << flush;
    cout << "Total Bytes: " << total_bytes << "\n[ " << flush;

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            unsigned char cod = obtener_ficha(tablero, f, c, cols);

            cout << ((cod >> 2) & 1)
                 << ((cod >> 1) & 1)
                 << (cod & 1) << " ";
        }
    }
    cout << "]\n" << flush;
}