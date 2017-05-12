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
        cantidadSupermercados = 0;

        siguiente = NULL;
        anterior = NULL;

    }

    int getCodigo() {return codigo;}
    string getNombre() {return nombre;}
    NodoLugar* getAnteior() {return anterior;}
    NodoLugar* getSiguiente() {return siguiente;}
    int getCantidad() {return cantidadSupermercados;}
    void aumentarCantidadSuper() {cantidadSupermercados++;}


private:
    int codigo;
    string nombre;
    int cantidadSupermercados;
    NodoLugar* siguiente;
    NodoLugar* anterior;
    friend class ListaLugares;

};


#endif //SISTEMAVENTAS2_NODOLUGAR_H
