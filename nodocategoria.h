//
// Created by Daniel Alvarado on 5/8/17.
//

#ifndef SISTEMAVENTAS2_NODOCATEGORIA_H
#define SISTEMAVENTAS2_NODOCATEGORIA_H


#include <iostream>
#include "arbolproductos.h"
using namespace std;

enum Color {RED, BLACK};

class nodocategoria {
public:
    nodocategoria(int _codigo, string _desc){
        codigo = _codigo;
        descripcion = _desc;
        bestScore = 0;
        padre = NULL;
        tio = NULL;
        abuelo = NULL;
        izq = NULL;
        der = NULL;
        color = RED;

        punteroArbolProductos = NULL;
    }

    string toString();
    int getCodigo() {return codigo;};
    string getDesc() {return descripcion;};
    void incBestScore(){bestScore++;};

    nodocategoria *padre;
    nodocategoria *tio;
    nodocategoria *abuelo;
    nodocategoria *izq;
    nodocategoria *der;
    Color color;

    ArbolProductos* punteroArbolProductos;

private:

    int codigo;
    string descripcion;
    int bestScore;

};


#endif //SISTEMAVENTAS2_NODOCATEGORIA_H
