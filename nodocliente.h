#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;


class NodoCliente {
public:


    NodoCliente(int _numero, int _id, string _nombre, string _direccion, string _telefono)
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



    int getNumero() {return numero;}
    string getNombre();
    string getDireccion();
    int getID();
    string getTelefono();
    int getCantidadCompras();
    void aumentarVentas(){cantidadDeCompras++;}

    NodoCliente* izq;
    NodoCliente* der;
    NodoCliente *siguiente;
    NodoCliente *anterior;




private:
    int numero;
    int idx;

    string nombre;
    string direccion;
    string telefono;

    int cantidadDeCompras;

    //friend class ListaProveedores;
    friend class ArbolClientes;
    friend class Pagina;
    friend class ArregloClaves;

};

typedef NodoCliente* pNodoCliente;


#endif // NODOCLIENTE_H
