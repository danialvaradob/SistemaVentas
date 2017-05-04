#include "nodoproveedor.h"

NodoProveedor::NodoProveedor()
{

}

string NodoProveedor::getID(){
    return identificacion;
}

string NodoProveedor::getNombre(){
    return nombre;
}

string NodoProveedor::getDireccion(){
    return direccion;
}

string NodoProveedor::getTelefono(){
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
    anterior = _siguiente;
}

int NodoProveedor::getCantidadDeVentas(){
    return cantidadDeVentas;
}
