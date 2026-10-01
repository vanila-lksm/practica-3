#include "RLE.h"
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
    while (fin.get(c))
    {
        n++;
    }
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

void escribir_binario(const char* nombre, const char* datos, int largo)
{
    ofstream fout(nombre, ios::binary);
    if (!fout.is_open()) throw "no se pudo crear el archivo codificado";
    fout.write(datos, largo);
    fout.close();
}

char* pares_a_bytes(entrada* pares, int cantidad, int& largo)
{
    largo = cantidad * 5;
    char* datos = new char[largo];
    int j = 0;
    for (int p = 1; p <= cantidad; p++)
    {
        int pre = pares[p].prefijo;
        datos[j]     = (char)(pre & 0xFF);
        datos[j + 1] = (char)((pre >> 8) & 0xFF);
        datos[j + 2] = (char)((pre >> 16) & 0xFF);
        datos[j + 3] = (char)((pre >> 24) & 0xFF);
        datos[j + 4] = pares[p].caracter;
        j += 5;
    }
    return datos;
}

void comprimir_archivo()
{
    char* texto = nullptr;
    entrada* pares = nullptr;
    char* datos = nullptr;
    char* recuperado = nullptr;
    char* releido = nullptr;
    const unsigned char K = 'k';

    try
    {
        int metodo, n;
        cout << "Metodo de compresion (1 = RLE, 2 = LZ78): ";
        cin >> metodo;
        if (metodo != 1 && metodo != 2) throw "metodo invalido";

        cout << "Posiciones a rotar (1 a 7): ";
        cin >> n;
        if (n <= 0 || n >= 8) throw "n debe estar entre 1 y 7";

        texto = leer_archivo("texto.txt");

        if (metodo == 1)
        {
            string comprimida = comprimir_RLE(texto);
            int largo = (int)comprimida.size();
            datos = new char[largo];
            for (int i = 0; i < largo; i++)
            {
                datos[i] = comprimida[i];
            }

            encriptar(datos, largo, n, K);
            escribir_binario("codificado.bin", datos, largo);
            desencriptar(datos, largo, n, K);

            string recuperada = descomprimir_RLE(string(datos, largo));
            escribir_archivo("salida.txt", recuperada.c_str());
        }
        else
        {
            int cantidad = comprimir_LZ78(texto, pares);
            int largo = (cantidad + 1) * sizeof(entrada);

            encriptar((char*)pares, largo, n, K);
            escribir_binario("codificado.bin", (char*)pares, largo);
            desencriptar((char*)pares, largo, n, K);

            recuperado = descomprimir_LZ78(pares, cantidad);
            escribir_archivo("salida.txt", recuperado);
        }
        cout << "Archivo final creado: salida.txt" << endl;

        releido = leer_archivo("salida.txt");
        if (sonIguales(texto, releido))
            cout << "Verificacion: el texto final coincide con el original" << endl;
        else
            cout << "Verificacion: el texto final NO coincide con el original" << endl;
    }
    catch (const char* e)
    {
        cout << "Error: " << e << endl;
    }

    delete[] texto;
    delete[] pares;
    delete[] datos;
    delete[] recuperado;
    delete[] releido;
}