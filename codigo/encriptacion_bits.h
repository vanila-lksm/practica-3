#ifndef ENCRIPTACION_BITS_H
#define ENCRIPTACION_BITS_H
int longitud_N(const char* texto);
unsigned char rotar_izquierda(unsigned char b, int n);
unsigned char rotar_derecha(unsigned char b, int n);
void encriptar(unsigned char* datos, int largo, int n, unsigned char K);
void desencriptar(unsigned char* datos, int largo, int n, unsigned char K);
void bits_5_3();
#endif // ENCRIPTACION_BITS_H
