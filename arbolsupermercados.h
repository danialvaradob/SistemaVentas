#ifndef SISTEMAVENTAS2_ARBOLSUPERMERCADOS_H
#define SISTEMAVENTAS2_ARBOLSUPERMERCADOS_H
#include "arbolcategorias.h"
#include "nodosupermercado.h"
#include <string>
using namespace std;

//ARBOL AVL

class ArbolSupermercados
{
public:
    ArbolSupermercados():raiz(NULL){};

    NodoSupermercado *raiz;

    void insertarNodoSupermercado(string _codSuper,string _codLugar, string _nombre );


    //CAMBIAR ESTAS
    void PreordenI(NodoSupermercado *k);
    string InordenI();
    void PostordenI();

    bool Hh;


    //ESCRIBIR ESTAS EN CODIGO
    void equilibrar1(NodoSupermercado *n, bool);
    void equilibrar2(NodoSupermercado *n, bool);
    void insertarBalanceado(NodoSupermercado *ra, string _codSuper,string _codLugar, string _nombre );
    void rotacionDobleIzquierda(NodoSupermercado *n1, NodoSupermercado *n2);
    void rotacionDobleDerecha(NodoSupermercado *n1, NodoSupermercado *n2);
    void rotacionSimpleIzquierda(NodoSupermercado *n1, NodoSupermercado *n2);
    void rotacionSimpleDerecha(NodoSupermercado *n1, NodoSupermercado *n2);

    //++++++++++++++++++Inserciones +++++++++++++++++++++++++++++++++++++++++

    //void InsertaNodoTransporte(NodoHotel *n,int idHotel, int idTransporte);
    //void InsertaNodoOferta(NodoHotel *R,int idHotel, int  idOferta,int  precioInd,int precioDoble,int cantI,int  cantD);


    //Agregar Categoria (a un arbol de categorias)

    void agregarCategoria();
    void agregarProducto();

};

#endif // ARBOLSUPERMERCADOS_H
