#include "nodocliente.h"

NodoCliente::NodoCliente()
{

}


nodoCliente* nodoCliente::getSiguiente(){
    return siguiente;
}

nodoCliente* nodoCliente::getAnterior(){
    return anterior;
}

void nodoCliente::setSiguiente(nodoCliente* _siguiente){
    siguiente = _siguiente;
}

void nodoCliente::setAnterior(nodoCliente* _anterior){
    anterior = _anterior;
}

string nodoCliente::getNombre(){
    return nombre;
}

string nodoCliente::getDireccion(){
    return direccion;
}

string nodoCliente::getID(){
    return idx;
}

string nodoCliente::getTelefono(){
    return telefono;
}

int nodoCliente::getCantidadCompras(){
    return cantidadDeCompras;
}
