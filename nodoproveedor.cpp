#include "nodoproveedor.h"

nodoProveedor::nodoProveedor()
{

}

string nodoProveedor::getID(){
    return identificacion;
}

string nodoProveedor::getNombre(){
    return nombre;
}

string nodoProveedor::getDireccion(){
    return direccion;
}

string nodoProveedor::getTelefono(){
    return telefono;
}

nodoProveedor* nodoProveedor::getAnterior(){
    return anterior;
}
nodoProveedor* nodoProveedor::getSiguiente(){
    return siguiente;
}

void nodoProveedor::setAnterior(nodoProveedor* _anterior){
    anterior = _anterior;
}


void nodoProveedor::setSiguiente(nodoProveedor* _siguiente){
    anterior = _siguiente;
}

int nodoProveedor::getCantidadDeVentas(){
    return cantidadDeVentas;
}
