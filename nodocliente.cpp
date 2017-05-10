#include "nodocliente.h"
#include <sstream>

string NodoCliente::toString() {
    stringstream flujo;
    stringstream flujo2;
    stringstream flujo3;
    string _idCliente;
    string _telefono;
    string _bestScore;

    flujo << idx;
    _idCliente = flujo.str();
    flujo2 << telefono;
    _telefono = flujo2.str();
    flujo3 << cantidadDeCompras;
    _bestScore = flujo3.str();

    return "Numero de identificacion: "+_idCliente+"\nNombre del cliente: "+nombre+"\nDireccion del cliente: "+direccion+"\nNumero de telefono: "+_telefono;
}

void NodoCliente::setHIzq(NodoCliente *nodo) {
    izq = nodo;
}

void NodoCliente::setHDer(NodoCliente *nodo) {
    der = nodo;
}

void NodoCliente::setSiguiente(NodoCliente *_siguiente) {
    siguiente = _siguiente;
}

void NodoCliente::setAnterior(NodoCliente *_anterior){
    anterior = _anterior;
}

string NodoCliente::getNombre(){
    return nombre;
}

string NodoCliente::getDireccion(){
    return direccion;
}

int NodoCliente::getID(){
    return idx;
}

int NodoCliente::getTelefono(){
    return telefono;
}

int NodoCliente::getCantidadCompras(){
    return cantidadDeCompras;
}
