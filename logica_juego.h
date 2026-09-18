#ifndef LOGICA_JUEGO_H
#define LOGICA_JUEGO_H

bool* detectar_combinaciones(const unsigned char* tablero, int filas, int cols, bool& hay_combinacion);
int eliminar_fichas_marcadas(unsigned char* tablero, const bool* marcas, int filas, int cols);
void aplicar_gravedad(unsigned char* tablero, int filas, int cols);
void rellenar_espacios_superiores(unsigned char* tablero, int filas, int cols);
void procesar_cascadas(unsigned char* tablero, int filas, int cols);

#endif