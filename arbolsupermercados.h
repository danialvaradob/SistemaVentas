#ifndef SISTEMAVENTAS2_ARBOLSUPERMERCADOS_H
#define SISTEMAVENTAS2_ARBOLSUPERMERCADOS_H

#include "arbolcategorias.h"
#include "arbolproductos.h"
#include "nodosupermercado.h"
#include <string>
using namespace std;

//ARBOL AVL

class ArbolSupermercados
{
public:
    ArbolSupermercados():raiz(NULL){};

    NodoSupermercado *raiz;



    //CAMBIAR ESTAS
    void preordenI(NodoSupermercado *k);
    string inordenI();
    void postordenI();

    bool Hh;


    //ESCRIBIR ESTAS EN CODIGO
    void equilibrar1(NodoSupermercado *n, bool);
    void equilibrar2(NodoSupermercado *n, bool);
    void insertarBalanceado(NodoSupermercado *ra, bool Hh, int _codSuper,int _codLugar, string _nombre );
    void rotacionDobleIzquierda(NodoSupermercado *n1, NodoSupermercado *n2);
    void rotacionDobleDerecha(NodoSupermercado *n1, NodoSupermercado *n2);
    void rotacionSimpleIzquierda(NodoSupermercado *n1, NodoSupermercado *n2);
    void rotacionSimpleDerecha(NodoSupermercado *n1, NodoSupermercado *n2);

    //++++++++++++++++++Inserciones +++++++++++++++++++++++++++++++++++++++++

    //void InsertaNodoTransporte(NodoHotel *n,int idHotel, int idTransporte);
    //void InsertaNodoOferta(NodoHotel *R,int idHotel, int  idOferta,int  precioInd,int precioDoble,int cantI,int  cantD);


    //Agregar Categoria (a un arbol de categorias)

    void agregarCategoria(NodoSupermercado* nodoSupermercado,int _codSuper,int _codCat, string _descCat); // inserta un nodo a un arbol RN
    void agregarProducto();  // inserta un nodo a un arbol AA
    bool existeSupermercado(int _codNuevoSuper, NodoSupermercado* _raiz);

    bool existeCategoria(int _codSuper,int _codCat, NodoSupermercado* _raiz);

    NodoSupermercado* getSuper(int _codSuper);
    // no se logro hacer
    ArbolCategorias* getCategorias(int _codSuper,int _codCat,NodoSupermercado* _raiz);

};


/*

void leerArchSupermercado(ArbolSupermercados * _supermercado){
    string nombreArchivo = "Supermercados.txt";

    ifstream archivoEntrada;
    string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, ios::in);

    if (archivoEntrada.fail()) {
        cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        string codSuper(std::strtok (lineaValores, ";"));
        string codLugar(std::strtok (NULL, ";"));
        string nombre(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;

        int codSint = atoi(codSuper.c_str());
        int codLint = atoi(codLugar.c_str());
        if (_supermercado->existeSupermercado(codSint,_supermercado->raiz)) {
            cout << "Supermercado ya existe, codigo: " << codSuper << endl;
            continue;
        }else{
            cout << "Codigo Supermercado: " << codSuper << " Nombre: "<< nombre << endl;
            //_supermercado->insertarNodoSupermercado(codSint,codLint,nombre);
            _supermercado->insertarBalanceado(_supermercado->raiz,false,codSint,codLint,nombre);
        }
    }
    archivoEntrada.close();

}


 */


#endif // ARBOLSUPERMERCADOS_H
