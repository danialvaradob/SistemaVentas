#include "arbolproveedores.h"

//ARBOL BINARIO DE BUSQUEDA

//+++++++++++++++++++++ Insertar Nodo +++++++++++++++++++++++

void ArbolProveedores::insertarNodoProveedor(string _id, string _nombre, string _direccion, string _telefono) {
    if(raiz==NULL){
        raiz = new NodoProveedor( _id,  _nombre,  _direccion,  _telefono);
    }else{
        raiz->InsertaBinarioViaje(num, origen, destino, fechaSalida, fechaLlegada,costo, numeroPlazas, cantidadPaquetes);
    }
}
