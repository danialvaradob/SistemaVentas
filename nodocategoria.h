//
// Created by Daniel Alvarado on 5/8/17.
//

#ifndef SISTEMAVENTAS2_NODOCATEGORIA_H
#define SISTEMAVENTAS2_NODOCATEGORIA_H


#include <iostream>
using namespace std;

class nodocategoria {
public:
    nodocategoria(int _codigo, string _desc){
        codigo = _codigo;
        descripcion = _desc;
        bestScore = 0;
        siguiente = NULL;
        anterior = NULL;

        izq = NULL;
        der = NULL;



    }
    string toString();
    int getCodigo() {return codigo;};
    string getNombre() {return descripcion;};
    void incBestScore(){bestScore++;};
    void setHIzq(nodocategoria *nodo);
    nodocategoria *getHIzq();
    void setHDer(nodocategoria *nodo);
    nodocategoria *getHDer();
    void setSiguitente(nodocategoria *nodo);
    nodocategoria *getSiguiente();
    void setAnterior(nodocategoria *nodo);
    nodocategoria *getAnterior();


private:
    nodocategoria *siguiente;
    nodocategoria *anterior;
    nodocategoria *izq;
    nodocategoria *der;
    int codigo;
    string descripcion;
    int bestScore;

};


#endif //SISTEMAVENTAS2_NODOCATEGORIA_H
