#ifndef NODOPRODUCTO_H
#define NODOPRODUCTO_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;




class NodoProducto {
public:
    NodoProducto(int _codigoProducto, int _codigoCategoria, string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock){

        codigoProducto = _codigoProducto;
        codigoCategoria = _codigoCategoria;
        nombreProducto = _nombreProducto;
        precioPorUnidad = _precioPorUnidad;
        cantidadEnStock = _cantidadEnStock;
        cantidadAlInicio = _cantidadEnStock;


        cont = 0;
        nivel = 0;
        cantidadProductoVendido = 0;

        padre = NULL;
        raiz = NULL;
        izq = NULL;
        der = NULL;

    }

    NodoProducto *getSiguiente();
    void setSiguiente(NodoProducto* _siguiente);
    NodoProducto *getAnterior();
    void setAnterior(NodoProducto* _anterior);
    NodoProducto *getPrimerProducto();
    void setPrimeroProducto( NodoProducto* _primerProducto);

    int getCodigoProducto();
    int getCodigoCategoria();
    string getNombreProducto();
    double getPrecioPorUnidad();
    int getCantidadEnStock();
    void setCantidadEnStock(int _cantidadNueva);
    int getCantidadAlInicio() { return cantidadAlInicio;}
    void aumentarCantidadProductosVendidos() {cantidadProductoVendido++;}
    int getCantidadProVend() {return cantidadProductoVendido;}


    // especiales para Nodos de un arbol AA
    NodoProducto* izq;
    NodoProducto* der;
    NodoProducto* padre;
    NodoProducto* raiz;

    int cont;
    int nivel;





private:
    int cantidadProductoVendido;
    int codigoProducto;
    int codigoCategoria;
    string nombreProducto;
    double precioPorUnidad;
    int cantidadEnStock;
    int cantidadAlInicio;

    NodoProducto *siguiente;
    NodoProducto *anterior;

    friend class NodoCategoria;


};


#endif // NODOPRODUCTO_H
