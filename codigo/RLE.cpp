#include <iostream>
#include "RLE.h"

const char MARCA = '\x01';   // caracter reservado: no puede aparecer en el texto

void cerrar_racha(string& resultado, int cantidad, char letra)
{
    resultado += to_string(cantidad);
    resultado += letra;
    if (letra >= '0' && letra <= '9')
        resultado += MARCA;
}

string comprimir_RLE(const string& texto)
{
    string comprimida = "";
    if (texto.empty())
    {
        return comprimida;
    }
    char letra = texto[0];
    int cantidad = 0;
    for (size_t i = 0; i < texto.size(); i++)
    {
        if (texto[i] == MARCA)
        {
            throw "el texto contiene el caracter reservado de marca";
        }
        if (texto[i] == letra)
        {
            cantidad++;
        }
        else
        {
            cerrar_racha(comprimida, cantidad, letra);
            letra = texto[i];
            cantidad = 1;
        }
    }
    cerrar_racha(comprimida, cantidad, letra);
    return comprimida;
}
string descomprimir_RLE(const string& comprimida)
{
    string resultado = "";
    int acumulado = 0;

    for (size_t i = 0; i < comprimida.size(); i++)
    {
        char c = comprimida[i];
        if (c >= '0' && c <= '9')
        {
            acumulado = acumulado * 10 + (c - '0');
        }
        else if (c == MARCA)
        {
            if (acumulado < 10)
            {
                throw "datos RLE invalidos";
            }
            resultado.append(acumulado / 10, (char)('0' + acumulado % 10));
            acumulado = 0;
        }
        else
        {
            resultado.append(acumulado, c);
            acumulado = 0;
        }
    }
    return resultado;
}
void problema_5_1()
{
    string frase;
    cout << "ingrese su cadena de caracteres: ";
    getline(cin, frase);

    try
    {
        string comprimida = comprimir_RLE(frase);
        string recuperada = descomprimir_RLE(comprimida);
        cout <<"comprimida: "<<comprimida <<endl;
        cout <<"descomprimida: " <<recuperada << endl;
        if(recuperada==frase)
        {
            cout<<"funcionamiento correcto"<<endl;
        }
    }
    catch (const char* e)
    {
        cout << "Error: " << e << endl;
    }
}