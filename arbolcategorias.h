#ifndef ARBOLCATEGORIAS_H
#define ARBOLCATEGORIAS_H

#include <iostream>
#include "nodocategoria.h"
//ARBOL ROJINEGRO

class ArbolCategorias
{
public:
    ArbolCategorias();
    void Borrar(nodocategoria *nodo);

private:
    nodocategoria *raiz;
};

#endif // ARBOLCATEGORIAS_H
