//
// Created by Daniel Alvarado on 5/10/17.
//

#ifndef SISTEMAVENTAS2_NODOLUGAR_H
#define SISTEMAVENTAS2_NODOLUGAR_H

#include <string>
//#include <iostream>


class NodoLugar {
public:
    NodoLugar() {
            codigo = 0;
            nombre = " ";
            cantidadSupermercados = 0;

            siguiente = NULL;
            anterior = NULL;

    }

    NodoLugar(int _codigo, std::string _nombre) {
        codigo = _codigo;
        nombre = _nombre;
        cantidadSupermercados = 0;

        siguiente = NULL;
        anterior = NULL;

    }

    int getCodigo() {return codigo;}
    std::string getNombre() {return nombre;}
    NodoLugar* getAnteior() {return anterior;}
    NodoLugar* getSiguiente() {return siguiente;}
    int getCantidad() {return cantidadSupermercados;}
    void aumentarCantidadSuper() {cantidadSupermercados++;}


private:
    int codigo;
    std::string nombre;
    int cantidadSupermercados;
    NodoLugar* siguiente;
    NodoLugar* anterior;
    friend class ListaLugares;

};


#endif //SISTEMAVENTAS2_NODOLUGAR_H
