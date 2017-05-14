#ifndef NODOSUPERMERCADO_H
#define NODOSUPERMERCADO_H

#include "arbolcategorias.h"
#include "arbolproductos.h"
#include <string>
using namespace std;

class NodoSupermercado {
public:

    NodoSupermercado() {
            codSuper = 0;
            codLugar = 0;
            nombre = " ";
            FB = 0;
            cantidadVentas = 0;
            Hder = NULL;
            Hizq = NULL;
            punteroProductos = NULL;
            punteroCategorias = NULL;

    }

    NodoSupermercado(int _codSuper,int _codLugar, string _nombre ){
        codSuper = _codSuper;
        codLugar = _codLugar;
        nombre = _nombre;
        FB = 0;
        cantidadVentas = 0;
        Hder = NULL;
        Hizq = NULL;
        punteroProductos = NULL;
        punteroCategorias = NULL;
    }

    void insertarNodo(int _codSuper,int _codLugar, string _nombre );
    void aumentarVentas() {cantidadVentas++;}
    int obtenerValor();
    int getCodSuper() {return codSuper;}
    int getCodLugar() {return codLugar;}
    string getNombre() {return nombre;}
    int getCantidadVentas() {return cantidadVentas;}

    NodoSupermercado *Hizq, *Hder;
    ArbolCategorias* punteroCategorias;
    ArbolProductos*  punteroProductos;

    int FB;


private:
    string  nombre;
    int  codSuper;
    int  codLugar;
    int cantidadVentas;

    friend class ArbolCategorias;
    friend class ArbolSupermercados;
};

#endif // NODOSUPERMERCADO_H
