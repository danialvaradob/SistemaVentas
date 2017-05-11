//
// Created by Daniel Alvarado on 5/10/17.
//

#ifndef SISTEMAVENTAS2_NODOLUGAR_H
#define SISTEMAVENTAS2_NODOLUGAR_H

#include <string>
#include <iostream>
using namespace std;

class NodoLugar {
    NodoLugar(int _codigo, string _nombre) {
        codigo = _codigo;
        nombre = _nombre;

        siguiente = NULL;
        anterior = NULL;

    }

    int getCodigo() {return codigo;}
    string getNombre() {return nombre;}
    NodoLugar* getAnteior() {return anterior;}
    NodoLugar* getSiguiente() {return siguiente;}


private:
    int codigo;
    string nombre;
    NodoLugar* siguiente;
    NodoLugar* anterior;
    friend class ListaLugares;

};


#endif //SISTEMAVENTAS2_NODOLUGAR_H
