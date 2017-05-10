#ifndef NODOVENTA_H
#define NODOVENTA_H
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include "nodoproductocomprado.h"
using namespace std;

class NodoVenta {
public:
    NodoVenta(int _codP, string _nombreP, int _codC, string _nombreC, int cant, double _monto){
        codigoProv = _codP;
        nombreProv = _nombreP;
        codigoCliente = _codC;
        nombreCliente = _nombreC;
        cantidadComprada = cant;
        monto = _monto;
        siguiente = NULL;
        anterior = NULL;
        primero = NULL;

    }

    string toString();

    NodoVenta *getSiguiente(){ return siguiente;};
    void setSiguiente(NodoVenta* _siguiente){siguiente = _siguiente;};
    NodoVenta *getAnterior(){ return anterior;};
    void setAnterior(NodoVenta* _anterior){anterior = _anterior ;};
    NodoVenta *getPrimero(){return primero;}
    void setPrimero( NodoVenta* _primerProducto){primero = _primerProducto;};
    int getCodClient(){ return codigoCliente;};
    int getCodProv(){ return codigoProv;};
    int getCant(){return cantidadComprada;};
    string getNomClien() {return nombreCliente;};
    string getNomProv() {return nombreProv;};
    double getMontoTotal() {return monto;};

private:
    int codigoProv;
    string nombreProv;
    int codigoCliente;
    string nombreCliente;
    int cantidadComprada;
    double monto;

    NodoVenta* siguiente;
    NodoVenta* anterior;
    NodoVenta* primero;

    friend class ListaVentas;

};

#endif // NODOVENTA_H
