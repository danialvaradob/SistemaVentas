#ifndef NODOPROVEEDOR_H
#define NODOPROVEEDOR_H
#include <stdio.h>
#include <stdlib.h>
#include <arbolproveedores.h>
#include <string>
using namespace std;




class NodoProveedor {
public:


    NodoProveedor(string _id, string _nombre, string _direccion, string _telefono){
        identificacion = _id;
        nombre = _nombre;
        direccion = _direccion;
        telefono = _telefono;
        siguiente = NULL;
        anterior = NULL;

        cantidadDeVentas = 0;
        Hizq=NULL;
        Hder=NULL;

    }


    NodoProveedor *getSiguiente();
    void setSiguiente(NodoProveedor* _siguiente);
    NodoProveedor *getAnterior();
    void setAnterior(NodoProveedor* _anterior);

    string getNombre();
    string getDireccion();
    string getID();
    string getTelefono();
    int getCantidadDeVentas();
    void aumentarVentas(){cantidadDeVentas++;}

    // Metodo utilizado para agregar un nodo de forma correcta
    insertarProveedor(string _id, string _nombre, string _direccion, string _telefono);

    NodoProveedor *Hiz;
    NodoProveedor *Hder;




private:
    string identificacion;
    NodoProveedor *siguiente;
    NodoProveedor *anterior;
    string nombre;
    string direccion;
    string telefono;

    int cantidadDeVentas;

    friend class ArbolProveedores;


};

typedef NodoProveedor* pNodoProveedor;

#endif // NODOPROVEEDOR_H
