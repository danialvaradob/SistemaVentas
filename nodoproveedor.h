#ifndef NODOPROVEEDOR_H
#define NODOPROVEEDOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;




class NodoProveedor {
public:

    NodoProveedor() {
            numero = 0;
            nombre = " ";
            direccion = " ";
            telefono = 0;

            siguiente = NULL;
            anterior = NULL;

            cantidadDeVentas = 0;
            Hizq=NULL;
            Hder=NULL;



    }

    NodoProveedor(int _codP, string _nombre, string _dir, int _tel){
        numero = _codP;
        nombre = _nombre;
        direccion = _dir;
        telefono = _tel;

        siguiente = NULL;
        anterior = NULL;

        cantidadDeVentas = 0;
        Hizq=NULL;
        Hder=NULL;

    }

    string toString();

    NodoProveedor *getSiguiente();
    void setSiguiente(NodoProveedor* _siguiente);
    NodoProveedor *getAnterior();
    void setAnterior(NodoProveedor* _anterior);

    string getNombre();
    string getDireccion();
    int getID();
    int getTelefono();
    int getCantidadDeVentas();
    void aumentarVentas(){cantidadDeVentas++;}

    // Metodo utilizado para agregar un nodo de forma correcta
    void insertarProveedor(int idProveedor,string nombre,string direccion,int intTel);

    NodoProveedor *Hizq;
    NodoProveedor *Hder;




private:
    int numero;
    string nombre;
    string direccion;
    int telefono;
    int bestScore;
    NodoProveedor *siguiente;
    NodoProveedor *anterior;

    int cantidadDeVentas;

    friend class ArbolProveedores;


};

typedef NodoProveedor* pNodoProveedor;

#endif // NODOPROVEEDOR_H
