#include <iostream>
#include "arbolproveedores.h"

using namespace std;

//ARBOL BINARIO DE BUSQUEDA

//+++++++++++++++++++++ Insertar Nodo +++++++++++++++++++++++

void ArbolProveedores::insertarNodoProveedor(NodoProveedor *_prov) {
    if(raiz==NULL){
        raiz = _prov;
    }else{
        raiz->insertarProveedor(raiz, _prov);
    }
}

// funcion utilizada para verificar si ya existe un proveedor
bool ArbolProveedores::existeProveedor(int _id, NodoProveedor *_raiz){
    if(_raiz==NULL){
        return false;
    }else if (_raiz->getID() == _id) {
        return true;
    }else{

        existeProveedor(_id,_raiz->Hizq);
        existeProveedor(_id,_raiz->Hder);
    }
}

//funcion que aumenta la cantidad de ventas de un nodo
void ArbolProveedores::aumentarVentas(int _id, NodoProveedor *_raiz) {
    if (_raiz == NULL) {
        return;
    }
    else if (_raiz->getID() == _id) {
        _raiz->aumentarVentas();

    } else {
        aumentarVentas(_id,_raiz->Hder);
        aumentarVentas(_id,_raiz->Hizq);
    }
}
//retorna el nombre de un _id dado
string ArbolProveedores::getNombreProveedor(int _id, NodoProveedor *_raiz) {
    if (_raiz == NULL) {
        return "";
    }
    else if (_raiz->getID() == _id) {
        return _raiz->getNombre();

    } else {
        getNombreProveedor(_id,_raiz->Hder);
        getNombreProveedor(_id,_raiz->Hizq);
    }
}

// Recorridos
void ArbolProveedores::PreordenI(NodoProveedor *R){
    if(R==NULL){
        return;
    }else{
        cout<<R->getID()<<endl;
        PreordenI(R->Hizq);
        PreordenI(R->Hder);
    }
}

void ArbolProveedores::InordenI(NodoProveedor *R){
    if(R==NULL){
        return;
    }else{
        InordenI(R->Hizq);
        cout<<R->getID()<<endl;
        InordenI(R->Hder);
    }
}

void ArbolProveedores::PostordenI(NodoProveedor *R){
     if(R==NULL){
        return;
    }else{
        PostordenI(R->Hizq);
        PostordenI(R->Hder);
        cout<<R->getID()<<"-";

    }
}
