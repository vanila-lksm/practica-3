#ifndef LZ78_H
#define LZ78_H
struct entrada
{
    int prefijo;
    char caracter;
};

int longitud(const char* texto);
int buscar_ubicacion(entrada* dic, int lonDic, int prefijo, char c);
int comprimir_LZ78(const char* texto, entrada*& pares);
void imprimir_compresion(entrada*& pares,int cantidad);
void escribir_frase(entrada* dic, int k, char* texto, int& pos);
char* descomprimir_LZ78(entrada* pares, int cantidad);
bool sonIguales(const char *texto, const char *texto_desencriptado);
void todo_LZ78();
#endif // LZ78_H
