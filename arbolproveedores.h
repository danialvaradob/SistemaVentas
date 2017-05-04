#ifndef ARBOLPROVEEDORES_H
#define ARBOLPROVEEDORES_H
#include <nodoproveedor.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
//ARBOL BINARIO DE BUSQUEDA

class ArbolProveedores
{
public:

    NodoProveedor *raiz;
    ArbolProveedores():raiz(NULL){};

   //++++Insersion al arbol+++++++++++++++++++++

    void insertarNodoProveedor(string _id, string _nombre, string _direccion, string _telefono);
    //++++++++++++ Ordenes ++++++++++++++++++++++++
    void PreordenI(NodoViaje *R);
    void InordenI(NodoViaje *R);
    void PostordenI(NodoViaje *R);

    //+++++++++++ Recorrido +++++++++++++
    int RecorrerV(NodoViaje * R);

    //¿Existe proveedor?
    bool existeProveedor(string _id);
};

#endif // ARBOLPROVEEDORES_H
