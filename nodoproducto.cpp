#include "nodoproducto.h"

nodoProducto::nodoProducto()
{
    //constructor
}

string nodoProducto::getCodigoProducto(){
    return codigoProducto;
}

string nodoProducto::getCodigoCategoria(){
    return codigoCategoria;
}

string nodoProducto::getNombreProducto(){
    return nombreProducto;
}

double nodoProducto::getPrecioPorUnidad(){
    return precioPorUnidad;
}

int nodoProducto::getCantidadEnStock(){
    return cantidadEnStock;
}

nodoProducto* nodoProducto::getAnterior(){
    return anterior;
}
nodoProducto* nodoProducto::getSiguiente(){
    return siguiente;
}

void nodoProducto::setAnterior(nodoProducto* _anterior){
    anterior = _anterior;
}


void nodoProducto::setSiguiente(nodoProducto* _siguiente){
    anterior = _siguiente;
}

void nodoProducto::setCantidadEnStock(int _cantidadNueva){
    cantidadEnStock = _cantidadNueva;

}
