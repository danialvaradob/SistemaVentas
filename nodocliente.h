#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;


class NodoCliente {
public:


    NodoCliente(int _numero, int _id, string _nombre, string _direccion, int _telefono)
    {
        numero = _numero;
        idx = _id;
        nombre = _nombre;
        direccion = _direccion;
        telefono = _telefono;
        siguiente = NULL;
        anterior = NULL;
        izq = NULL;
        der = NULL;
        cantidadDeCompras = 0;
    }

    string toString();

    void setHIzq(NodoCliente *nodo);
    NodoCliente *getHIzq(){return izq;};
    void setHDer(NodoCliente *nodo);
    NodoCliente *getHDer(){return der;};
    void setSiguiente(NodoCliente *nodo);
    NodoCliente *getSiguiente(){return siguiente;};
    void setAnterior(NodoCliente *nodo);
    NodoCliente *getAnterior(){return anterior;}

    int getNumero(){return numero;};
    string getNombre(){return nombre;};
    string getDireccion(){ return direccion;};
    int getID(){ return idx;};
    int getTelefono(){ return telefono;};
    int getCantidadCompras(){ return cantidadDeCompras;};
    void aumentarVentas(){cantidadDeCompras++;}

private:
    int numero;
    int idx;
    string nombre;
    string direccion;
    int telefono;
    int cantidadDeCompras;
    NodoCliente* izq;
    NodoCliente* der;
    NodoCliente *siguiente;
    NodoCliente *anterior;

    //friend class ListaProveedores;
    friend class ArbolClientes;
    friend class Pagina;
    friend class ArregloClaves;

};

typedef NodoCliente* pNodoCliente;


#endif // NODOCLIENTE_H
