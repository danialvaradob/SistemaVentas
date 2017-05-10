#ifndef NODOVENTA_H
#define NODOVENTA_H
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include "nodoproductocomprado.h"
using namespace std;

class NodoVenta {
public:

    NodoVenta() {
        codigoCliente = "";
        codigoProveedor = "";
        descuentoAplicado = 0;
        montoTotal = 0;


        siguiente = NULL;
        anterior = NULL;

        primeroProductoComprado = NULL;

    }

    NodoVenta(string _codigoCliente, string _codigoProveedor,int _descApl, double _monTotal){
        codigoCliente = _codigoCliente;
        codigoProveedor = _codigoProveedor;
        descuentoAplicado = _descApl;
        montoTotal = _monTotal;

        siguiente = NULL;
        anterior = NULL;

        primeroProductoComprado = NULL;

    }

    void setValores(string _codigoCliente, string _codigoProveedor,int _descApl, double _monTotal);

    NodoVenta *getSiguiente();
    void setSiguiente(NodoVenta* _siguiente);
    NodoVenta *getAnterior();
    void setAnterior(NodoVenta* _anterior);
    NodoProductoComprado *getPrimerProducto(){return primeroProductoComprado;}
    void setPrimeroProducto( NodoProductoComprado* _primerProducto);

    string getCodigoCli() {return codigoCliente;};
    string getCodigoProvee() {return codigoProveedor;};
    int getDescuentoApl() {return descuentoAplicado;};
    float getMontoTotal() {return montoTotal;};

    void setCodigoCliente(string _codigoCliente);
    void setCodigoProveedor(string _codigoProveedor);
    void setDescuentoAplicado(int _descuentoAplicado);
    void setMontoTotal(double _montoTotal);

    void insertarProductoComprado(string _codigoP, string _codigoC, int _unidadesComp);



private:
    string codigoCliente;
    string codigoProveedor;
    int descuentoAplicado;
    double montoTotal;

    NodoVenta* siguiente;
    NodoVenta* anterior;
    NodoProductoComprado* primeroProductoComprado;

    friend class ListaVentas;

};

#endif // NODOVENTA_H
