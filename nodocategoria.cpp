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
