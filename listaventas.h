#ifndef LISTAVENTAS_H
#define LISTAVENTAS_H

#include "nodoventa.h"
#include <string>
using namespace std;

class ListaVentas {
public:
    ListaVentas() {primero = NULL;}

    void insertar(NodoVenta *_venta);
    bool listaVacia() {return primero == NULL;}

    NodoVenta* getPrimero() {return primero;};

private:
    NodoVenta* primero;

};

#endif // LISTAVENTAS_H
