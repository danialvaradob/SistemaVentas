#include "arbolproveedores.h"

//ARBOL BINARIO DE BUSQUEDA

//+++++++++++++++++++++ Insertar Nodo +++++++++++++++++++++++

void ArbolProveedores::insertarNodoProveedor(string _id, string _nombre, string _direccion, string _telefono) {
    if(raiz==NULL){
        raiz = new NodoProveedor( _id,  _nombre,  _direccion,  _telefono);
    }else{
        raiz->insertarProveedor( _id,  _nombre,  _direccion,  _telefono);
    }
}

// funcion utilizada para verificar si ya existe un proveedor
bool ArbolProveedores::existeProveedor(string _id){



}
