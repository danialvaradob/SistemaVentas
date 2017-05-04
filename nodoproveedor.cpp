#include "nodoproveedor.h"
using namespace std;



void NodoProveedor::insertarProveedor(string _id, string _nombre, string _direccion, string _telefono)
{
    int numero = stoi(_id);
    int valor = stoi(identificacion);

    if(numero < valor){
        if(Hizq==NULL){
            Hizq = new NodoProveedor(_id,  _nombre,  _direccion,  _telefono);
        }else{
            Hizq->insertarProveedor(_id,  _nombre,  _direccion,  _telefono);
        }
    }else{
        if(Hder==NULL){
            Hder = new NodoProveedor(_id,  _nombre,  _direccion,  _telefono);
        }else{
            Hder->insertarProveedor(_id,  _nombre,  _direccion,  _telefono);
        }
    }
}

string NodoProveedor::getID(){
    return identificacion;
}

string NodoProveedor::getNombre(){
    return nombre;
}

string NodoProveedor::getDireccion(){
    return direccion;
}

string NodoProveedor::getTelefono(){
    return telefono;
}

NodoProveedor* NodoProveedor::getAnterior(){
    return anterior;
}
NodoProveedor* NodoProveedor::getSiguiente(){
    return siguiente;
}

void NodoProveedor::setAnterior(NodoProveedor* _anterior){
    anterior = _anterior;
}


void NodoProveedor::setSiguiente(NodoProveedor* _siguiente){
    siguiente = _siguiente;
}

int NodoProveedor::getCantidadDeVentas(){
    return cantidadDeVentas;
}
