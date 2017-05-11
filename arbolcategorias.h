#ifndef ARBOLCATEGORIAS_H
#define ARBOLCATEGORIAS_H

#include <iostream>
#include "nodocategoria.h"
//ARBOL ROJINEGRO



class ArbolCategorias
{
public:
    ArbolCategorias(){
        raiz = NULL;
    }

    void insertarValorNodoRN (int _idCategoria, string _descrip);
    void inordenRN(nodocategoria *R);
    void levelOrder();

    void rotarIzquierda(nodocategoria *&, nodocategoria *&);
    void rotarDerecha(nodocategoria *&, nodocategoria *&);
    void aplicarReglas(nodocategoria *&, nodocategoria *&);
    nodocategoria* InsertarNodoRN(nodocategoria* RaizRN, nodocategoria *pt);
    bool existeCategoria(int _id, nodocategoria *_raiz);
    void InordenRN(nodocategoria *T);
    nodocategoria *raiz;
};

#endif // ARBOLCATEGORIAS_H
