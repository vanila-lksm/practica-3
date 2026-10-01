#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include "LZ78.h"
char* leer_archivo(const char* nombre_archivo);
void escribir_archivo(const char* nombre, const char* texto);
void escribir_binario(const char* nombre, const char* datos, int largo);
char* pares_a_bytes(entrada* pares, int cantidad, int& largo);
void comprimir_archivo();
#endif // ARCHIVOS_H
