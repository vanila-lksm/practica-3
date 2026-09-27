#include "encriptacion_bits.h"
#include <iostream>
#include "RLE.h"
using namespace std;

int longitud_N(const char* texto)
{
    int n = 0;
    while (texto[n] != '\0') n++;
    return n;
}

unsigned char rotar_izquierda(unsigned char b, int n)
{
    return (unsigned char)((b << n) | (b >> (8 - n)));
}

unsigned char rotar_derecha(unsigned char b, int n)
{
    return (unsigned char)((b >> n) | (b << (8 - n)));
}

void encriptar(char* texto, int largo, int n, unsigned char K)
{
    for (int i = 0; i < largo; i++)
    {
        unsigned char b= (unsigned char)texto[i];
        texto[i] = (char)rotar_izquierda(b, n) ^ K;
    }
}

void desencriptar(char* texto, int largo, int n, unsigned char K)
{
    if (n <= 0 || n >= 8) throw "n debe estar entre 1 y 7";
    for (int i = 0; i < largo; i++)
    {
        unsigned char b= (unsigned char)texto[i];
        texto[i] = (char)rotar_derecha(b ^ K, n);
    }
}

void bits_5_3()
{
    int n;
    cout<<"ingrese la frase a encriptar: ";
    char* texto=new char[200];
    cin.getline(texto, 200);
    cout<<"ingrese la cantidad de posiciones a mover (0<n<8): ";
    cin>>n;
    if (n <= 0 || n >= 8) throw "n debe estar entre 1 y 7";
    char* N_texto=comprimir_RLE(texto);
    delete [] texto;
    cout<<"texto comprimido: " <<N_texto<<endl;
    int largo=longitud_N(N_texto);
    encriptar(N_texto,largo,n,'k');
    cout<<"texto encriptado: ";
    for (int i = 0; i < largo; i++)
    {
        unsigned char b = (unsigned char)N_texto[i];
        if (b < 32 || b == 127)
            cout << '.';
        else
            cout << N_texto[i];
    }
    cout << endl;
    desencriptar(N_texto,largo,n,'k');
    cout<<"texto desencriptado: ";
    cout <<N_texto <<endl;
    delete[] N_texto;

}
