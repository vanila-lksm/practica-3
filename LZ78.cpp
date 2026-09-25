#include <iostream>
#include "LZ78.h"
using namespace std;

int longitud(const char* texto)
{
    int n = 0;
    while (texto[n] != '\0') n++;
    return n;
}
int buscar_ubicacion(entrada *dic, int tamanio, int prefijo, char c)
{
    for (int i = 1; i < tamanio; i++)
    {
        if (dic[i].prefijo == prefijo && dic[i].caracter == c)
        {
            return i;
        }
    }
    return 0;
}
int comprimir_LZ78(const char* texto,entrada*& pares)
{
    int n = longitud(texto),lonDic=1,prefijo_actual=0;
    entrada *dic = new entrada[n + 1];

    for(int i=0;texto[i]!='\0';i++)
    {
        char c=texto[i];
        int indice=buscar_ubicacion(dic,lonDic,prefijo_actual,c);
        if(indice!=0)
        {
            prefijo_actual=indice;
        }
        else
        {
            dic[lonDic].prefijo=prefijo_actual;
            dic[lonDic].caracter=c;
            lonDic++;
            prefijo_actual=0;
        }
    }
    if (prefijo_actual != 0)
    {
        dic[lonDic].prefijo= prefijo_actual;
        dic[lonDic].caracter = '\0';
        lonDic++;
    }
    pares=dic;
    return lonDic-1;
}
void imprimir_compresion(entrada*& pares,int cantidad)
{
    for (int p = 1; p <= cantidad; p++)
    {
        cout << "(" << pares[p].prefijo << ", " << pares[p].caracter << ") ";
    }
}

void escribir_frase(entrada* dic, int k, char* texto, int& pos)
{
    if (k == 0) return;
    escribir_frase(dic, dic[k].prefijo, texto, pos);
    texto[pos] = dic[k].caracter;
    pos++;
}

char* descomprimir_LZ78(entrada* pares, int cantidad)
{
    int total = 0;
    for (int p = 1; p <= cantidad; p++)
    {
        int k = (pares[p].caracter == '\0') ? pares[p].prefijo : p;
        while (k != 0)
        {
            total++;
            k = pares[k].prefijo;
        }
    }

    entrada* dic = new entrada[cantidad + 1];
    char* texto = new char[total + 1];
    int pos = 0;
    for (int p = 1; p <= cantidad; p++)
    {
        dic[p] = pares[p];
        if (pares[p].caracter == '\0')
            escribir_frase(dic, pares[p].prefijo, texto, pos);
        else
            escribir_frase(dic, p, texto, pos);
    }
    texto[total] = '\0';

    delete[] dic;
    return texto;
}

bool sonIguales(const char* texto, const char* texto_descomprimido)
{
    int i = 0;
    while (texto[i] != '\0' && texto[i] == texto_descomprimido[i])
    {
        i++;
    }
    return texto[i] == texto_descomprimido[i];
}

void todo_LZ78()
{
    cout<<"ingrese su texto: ";
    char texto[200];
    cin.getline(texto, 200);
    entrada* pares = nullptr;
    char* recuperado = nullptr;
    int cantidad = comprimir_LZ78(texto, pares);
    recuperado = descomprimir_LZ78(pares, cantidad);

    cout << "Original:      " << texto << endl;
    imprimir_compresion(pares,cantidad);
    cout << "Descomprimido: " << recuperado << endl;

    if (sonIguales(texto, recuperado))
        cout << "Los textos coinciden" << endl;
    else
        cout << "Los textos NO coinciden" << endl;
    delete[] pares;
    delete[] recuperado;
}








