#include "RLE.h"
#include "LZ78.h"
#include "encriptacion_bits.h"
#include "archivos.h"
#include <iostream>
#include <fstream>

char* leer_archivo(const char* nombre_archivo)
{
    ifstream fin(nombre_archivo);
    if (!fin.is_open()) throw "no se pudo abrir el archivo de entrada";
    int n = 0;
    char c;
    while (fin.get(c)) n++;
    fin.close();

    char* texto = new char[n + 1];
    fin.clear();
    fin.open(nombre_archivo);
    int i = 0;
    while (i < n && fin.get(c))
    {
        texto[i] = c;
        i++;
    }
    texto[i] = '\0';
    if(texto[i]==0)
    fin.close();
    return texto;
}

void escribir_archivo(const char* nombre, const char* texto)
{
    ofstream fout(nombre);
    if (!fout.is_open()) throw "no se pudo crear el archivo de salida";
    fout << texto;
    fout.close();
}

