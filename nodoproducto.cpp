#include "nodoproducto.h"



string NodoProducto::getCodigoProducto(){
    return codigoProducto;
}

string NodoProducto::getCodigoCategoria(){
    return codigoCategoria;
}

string NodoProducto::getNombreProducto(){
    return nombreProducto;
}

double NodoProducto::getPrecioPorUnidad(){
    return precioPorUnidad;
}

int NodoProducto::getCantidadEnStock(){
    return cantidadEnStock;
}

NodoProducto* NodoProducto::getAnterior(){
    return anterior;
}
NodoProducto* NodoProducto::getSiguiente(){
    return siguiente;
}

void NodoProducto::setAnterior(NodoProducto* _anterior){
    anterior = _anterior;
}


void NodoProducto::setSiguiente(NodoProducto* _siguiente){
    anterior = _siguiente;
}

void NodoProducto::setCantidadEnStock(int _cantidadNueva){
    cantidadEnStock = _cantidadNueva;

}
