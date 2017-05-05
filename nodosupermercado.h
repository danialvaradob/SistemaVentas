#ifndef NODOSUPERMERCADO_H
#define NODOSUPERMERCADO_H
#include <arbolsupermercados.h>
#include <arbolcategorias.h>
#include <string>


class NodoSupermercado
{
public:
    NodoSupermercado(string _codSuper,string _codLugar, string _nombre );

    void aumentarVentas() {cantidadVentas++;}

    NodoSupermercado *Hizq, *Hder;
    ArbolCategorias* Categorias;
    int FB;


private:
    string  nombre;
    string  codSuper;
    string  codLugar;
    int cantidadVentas;

    friend class ArbolCategorias;
    friend class ArbolSupermercados;
};

#endif // NODOSUPERMERCADO_H
