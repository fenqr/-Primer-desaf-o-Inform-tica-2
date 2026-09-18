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
    cout << "\n --- TABLERO DE JUEGO (" << filas << "x" << cols << ")    \n\n";

    cout << "    ";
    for (int c = 0; c < cols; ++c) {
        cout << c << " ";
    }

    cout << "\n  ";
    for (int i = 0; i < cols * 2 + 3; ++i) {
        cout << "-";
    }
    cout << "\n";


    for (int f = 0; f < filas; ++f) {
        cout << f << " | ";
        for (int c = 0; c < cols; ++c) {
            unsigned char cod = obtener_ficha(tablero, f, c, cols);
            cout << convertir_codigo_a_caracter(cod) << " ";
        }
        cout << "|\n";
    }


    cout << "  ";
    for (int i = 0; i < cols * 2 + 3; ++i) {
        cout << "-";
    }
    cout << "\n";
}
void mostrar_trama_binaria(const unsigned char* tablero, int filas, int cols) {
    int total_bytes = calcular_bytes_necesarios(filas, cols);

    cout << "\n    TRAMA CONTINUA DE BITS EN MEMORIA    \n";
    cout << "Total Bytes: " << total_bytes << "\n[ ";

    for (int i = 0; i < total_bytes; ++i) {
        unsigned char b = tablero[i];
        for (int bit = 7; bit >= 0; --bit) {
            cout << ((b >> bit) & 1);
        }
        cout << " ";
    }
    cout << "]\n";
}