#include "nodocliente.h"





NodoCliente* NodoCliente::getSiguiente(){
    return siguiente;
}

NodoCliente* NodoCliente::getAnterior(){
    return anterior;
}

void NodoCliente::setSiguiente(NodoCliente* _siguiente){
    siguiente = _siguiente;
}

void NodoCliente::setAnterior(NodoCliente* _anterior){
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

string NodoCliente::getTelefono(){
    return telefono;
}

int NodoCliente::getCantidadCompras(){
    return cantidadDeCompras;
}
