#include <iostream>
#include "funciones.h"
using namespace std;
int lonNumeros(int numero)
{
    if(numero == 1)
        return 1;

    if(numero < 0)
        numero = -numero;

    int contador = 0;
    while(numero > 0)
    {
        numero /= 10;
        contador++;
    }
    return contador;
}
int potencia(int numero,int ala_q)
{
    int resultado = 1;
    for (int c = 0; c < ala_q; c++)
    {
        resultado = resultado * numero;
    }
    return resultado;
}
void problema_5_1()
{
    char *N_frase=new char [400],letra,*frase=new char[200];
    int cantidad=0,guardado=0,controlador,poten;
    cout<<"ingrese su cadena de caracteres: ";
    cin.getline(frase,200);
    letra=frase[0];
    for(short int i=0;;i++)
    {
        if(letra!=frase[i])
        {
            poten=lonNumeros(cantidad);
            while(poten>0)
            {
                controlador=potencia(10,(--poten));
                N_frase[guardado]=(cantidad / controlador)+'0';
                cantidad=cantidad % controlador;
                guardado++;
            }
            N_frase[guardado]=letra;
            guardado++;
            if(frase[i]=='\0')break;
            letra=frase[i];
            cantidad=0;
        }
        cantidad++;
    }
    N_frase[guardado]='\0';
    delete [] frase;
    cout<<"frase comprimida: "<<N_frase<<endl;
    descomprimir_RLE(N_frase);
    delete [] N_frase;
}
void descomprimir_RLE(char *comprimida)
{
    char *frase=new char [200];
    int cantidad = 0, guardado = 0;

    for (short int i = 0; comprimida[i] != '\0'; i++)
    {
        char c = comprimida[i];
        if (c >= '0' && c <= '9')
        {
            cantidad = cantidad * 10 + (c - '0');
        }
        else
        {
            for (int k = 0; k < cantidad && guardado < 199; k++)
            {
                frase[guardado] = c;
                guardado++;
            }
            cantidad = 0;
        }
    }
    frase[guardado] = '\0';
    cout <<"frase descomprimida: " << frase << endl;
    delete [] frase;
}


