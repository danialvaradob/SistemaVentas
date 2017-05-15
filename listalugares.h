#ifndef LISTALUGARES_H
#define LISTALUGARES_H

#include "nodolugar.h"



//LISTA CIRCULAR DOBLE

class ListaLugares {
public:
    ListaLugares() {primero = actual = NULL;}
    ~ListaLugares();

    bool listaVacia() {return primero == NULL;}

    int largoLista();
    void insertarLugar(int _codigo, std::string _nombre);
    bool existeLugar(int _codigo);
    void aumentarCantidadDeSupermercados(int codLugar);
    void getLugarMasSuper(NodoLugar*&_lugarMasSupermercados);

private:
    NodoLugar* primero;
    NodoLugar* actual;

};

#endif // LISTALUGARES_H
