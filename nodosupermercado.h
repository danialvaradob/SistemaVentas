#ifndef NODOSUPERMERCADO_H
#define NODOSUPERMERCADO_H
#include <arbolsupermercados.h>
#include <arbolcategorias.h>


class NodoSupermercado
{
public:
    NodoSupermercado();

    NodoSupermercado *Hizq, *Hder;
    ArbolCategorias* Categorias;
    int FB;


private:
    ArbolCategorias *_ArbolCategorias;
};

#endif // NODOSUPERMERCADO_H
