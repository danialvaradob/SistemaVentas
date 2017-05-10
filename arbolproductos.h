#ifndef ARBOLPRODUCTOS_H
#define ARBOLPRODUCTOS_H

#include <string>
#include "nodoproducto.h"
using namespace std;
//ARBOL AA

class ArbolProductos
{
public:

    NodoProducto* raiz;

    ArbolProductos():raiz(NULL){}
    void lookup(string _codigoProducto, string _codigoCategoria, string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock);
    void girar(NodoProducto  *temp);  //se utiliza skew en ingles
    bool dividir(NodoProducto  *temp);
    void rebal(NodoProducto * temp);
    NodoProducto* insertarNodo(NodoProducto * temp, NodoProducto * ins);
    void print(NodoProducto*H);

    void PreordenI(NodoProducto *R);

    int obtenerPrecioOferta(NodoProducto *O,int r,int ci,int cd);


};

#endif // ARBOLPRODUCTOS_H
