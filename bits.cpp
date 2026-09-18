#include "bits.h"

int calcular_bytes_necesarios(int filas, int cols) {
    int total_bits = filas * cols * 3;
    return (total_bits + 7) / 8;
}

void guardar_ficha_en_bits(unsigned char* tablero, int fila, int col, int num_cols, unsigned char valor_ficha) {
    int pos_bit_inicio = (fila * num_cols + col) * 3;
    int byte_idx = pos_bit_inicio / 8;
    int bit_offset = pos_bit_inicio % 8;

    // Limpiar los 3 bits destino
    for (int i = 0; i < 3; ++i) {
        int current_bit = bit_offset + i;
        int current_byte = byte_idx + (current_bit / 8);
        int bit_in_byte = 7 - (current_bit % 8);
        tablero[current_byte] &= ~(1 << bit_in_byte);
    }


    for (int i = 0; i < 3; ++i) {
        if ((valor_ficha >> (2 - i)) & 1) {
            int current_bit = bit_offset + i;
            int current_byte = byte_idx + (current_bit / 8);
            int bit_in_byte = 7 - (current_bit % 8);
            tablero[current_byte] |= (1 << bit_in_byte);
        }
    }
}

unsigned char obtener_ficha(const unsigned char* tablero, int fila, int col, int num_cols) {
    int pos_bit_inicio = (fila * num_cols + col) * 3;
    unsigned char valor = 0;

    for (int i = 0; i < 3; ++i) {
        int current_bit = pos_bit_inicio + i;
        int current_byte = current_bit / 8;
        int bit_in_byte = 7 - (current_bit % 8);

        if ((tablero[current_byte] >> bit_in_byte) & 1) {
            valor |= (1 << (2 - i));
        }
    }
    return valor;
}

void generar_tablero_aleatorio(unsigned char* tablero, int filas, int cols) {
    int total_bytes = calcular_bytes_necesarios(filas, cols);
    for (int i = 0; i < total_bytes; ++i) {
        tablero[i] = 0;
    }

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            unsigned char ficha = CODIGOS_FICHAS[rand() % 6];
            guardar_ficha_en_bits(tablero, f, c, cols, ficha);
        }
    }
}