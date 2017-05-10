#ifndef ARBOLPROVEEDORES_H
#define ARBOLPROVEEDORES_H
#include "nodoproveedor.h"
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

    void insertarNodoProveedor(NodoProveedor *_prov);
    //++++++++++++ Ordenes ++++++++++++++++++++++++
    void PreordenI(NodoProveedor *R);
    void InordenI(NodoProveedor *R);
    void PostordenI(NodoProveedor *R);

    //+++++++++++ Recorrido +++++++++++++
    int RecorrerV(NodoProveedor * R);

    //¿Existe proveedor?
    bool existeProveedor(int _id, NodoProveedor* _raiz);
    //Aumenta las ventas de un proveedor determinado
    void aumentarVentas(int _id, NodoProveedor *_raiz);

    string getNombreProveedor(int _id, NodoProveedor *_raiz);
};

#endif // ARBOLPROVEEDORES_H
