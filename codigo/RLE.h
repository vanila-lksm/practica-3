#ifndef RLE_H
#define RLE_H
#include <string>
using namespace std;
void cerrar_racha(string& resultado, int cantidad, char letra);
string comprimir_RLE(const string& texto);
string descomprimir_RLE(const string& comprimida);
void problema_5_1();
#endif // RLE_H
