#include "nodoproveedor.h"
#include <sstream>
using namespace std;

string NodoProveedor::toString() {
    stringstream flujo;
    stringstream flujo1;
    stringstream flujo2;
    string _codP;
    string _telefono;
    string _bestScore;

    flujo << numero;
    _codP = flujo.str();
    flujo2 << telefono;
    _telefono = flujo2.str();
    flujo1 << bestScore;
    _bestScore = flujo1.str();


    return "Codigo del proveedor: "+_codP+"\nNombre del proveedor: "+nombre+"\nDireccion del proveedor: "+direccion+"\nTelefono del proveedor: "+_telefono;
}



void NodoProveedor::insertarProveedor(NodoProveedor *raiz,NodoProveedor *_prov)
{
    int numero = _prov->getID();
    int valor = raiz->getID();

    if(numero <= valor){
        if(raiz->Hizq==NULL){
            raiz->Hizq = _prov;
        }else{
            raiz->Hizq->insertarProveedor(raiz->Hizq, _prov);
        }
    }else{
        if(raiz->Hder==NULL){
            raiz->Hder = _prov;
        }else{
            raiz->Hder->insertarProveedor(raiz->Hizq, _prov);
        }
    }
}

int NodoProveedor::getID(){
    return numero;
}

string NodoProveedor::getNombre(){
    return nombre;
}

string NodoProveedor::getDireccion(){
    return direccion;
}

int NodoProveedor::getTelefono(){
    return telefono;
}

NodoProveedor* NodoProveedor::getAnterior(){
    return anterior;
}
NodoProveedor* NodoProveedor::getSiguiente(){
    return siguiente;
}

void NodoProveedor::setAnterior(NodoProveedor* _anterior){
    anterior = _anterior;
}


void NodoProveedor::setSiguiente(NodoProveedor* _siguiente){
    siguiente = _siguiente;
}

int NodoProveedor::getCantidadDeVentas(){
    return cantidadDeVentas;
}
