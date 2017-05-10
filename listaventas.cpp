#include "listaventas.h"

void ListaVentas::insertar(NodoVenta *v)
{
    if (listaVacia())
    {
        primero = v;
        primero->anterior=primero;
        primero->siguiente=primero;
    }
    else
    {
        NodoVenta *nuevo = v;
        nuevo->anterior = primero->anterior;
        nuevo->siguiente=primero->anterior->siguiente;
        primero->anterior->siguiente=nuevo;
        primero->anterior=nuevo;
    }
}