//
// Created by Daniel Alvarado on 5/8/17.
//

#include "nodocategoria.h"
#include <sstream>

string nodocategoria::toString() {
    stringstream flujo;
    stringstream flujo2;
    string _cod;
    string _bestScore;

    flujo << codigo;
    _cod = flujo.str();
    flujo2 << bestScore;
    _bestScore = flujo2.str();

    return "Codigo de categoria: "+_cod+"\nDescripcion del producto: "+descripcion;
}

void nodocategoria::setAnterior(nodocategoria *nodo) {
    anterior = nodo;
}

nodocategoria *nodocategoria::getAnterior() {
    return anterior;
}

void nodocategoria::setSiguiente(nodocategoria *nodo) {
    siguiente = nodo;
}

nodocategoria *nodocategoria::getSiguiente() {
    return siguiente;
}

void nodocategoria::setHDer(nodocategoria *nodo) {
    der = nodo;
}

nodocategoria *nodocategoria::getHDer() {
    return der;
}

void nodocategoria::setHIzq(nodocategoria *nodo) {
    izq = nodo;
}

nodocategoria *nodocategoria::getHIzq() {
    return izq;
}