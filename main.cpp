#include <iostream>
#include "arbolsupermercados.h"
#include "arbolclientes.h"
#include "listalugares.h"
#include "arbolproveedores.h"
#include <fstream>
#include "leerArchivos.cpp"

using namespace std;


int main() {
    ListaLugares* listaLugares = new ListaLugares();
    leerArchLugares(listaLugares);

    ArbolClientes *arbolClientes = new ArbolClientes();
    leerArchClientes(arbolClientes);
    arbolClientes->RecorridoInordenB(arbolClientes->raizB);

    ArbolProveedores* arbolProveedores = new ArbolProveedores();
    //leerArchProveedores(arbolProveedores);

    ArbolSupermercados *arbolSupermercados = new ArbolSupermercados();
    //leerArchSupermercado(arbolSupermercados,listaLugares);

    //leerArchCategorias(arbolSupermercados);

    //arbolClientes->RecorridoInordenB(arbolClientes->raizB);
    //leerArchProductos(arbolSupermercados);

    //PRUEBAS
/*
    ArbolCategorias* AC = new ArbolCategorias();
    arbolSupermercados->getArbolCat(66,arbolSupermercados->raiz,AC);
    AC->raiz->incBestScore();

    ArbolCategorias* PAC = new ArbolCategorias();
    arbolSupermercados->getArbolCat(66,arbolSupermercados->raiz,PAC);
    //int SCORE = PAC->raiz->getBestScore();


    nodocategoria* nodocate = new nodocategoria();
    PAC->getNodoCat(PAC->raiz,45,nodocate);
*/



    cout << "Hello, World!" << endl;


    return 0;
}