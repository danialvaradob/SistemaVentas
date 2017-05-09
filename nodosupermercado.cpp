#include "nodosupermercado.h"

NodoSupermercado::NodoSupermercado(string _codSuper,string _codLugar, string _nombre )
{
    nombre = _nombre;
    codLugar = _codLugar;
    codSuper = _codSuper;
    FB=0;
    Categorias=NULL;
    Hizq=NULL;
    Hder=NULL;
}

void NodoSupermercado::insertarNodo(string _codSuper, string _codLugar, string _nombre) {
    int numero = stoi(_codSuper);
    int valor = stoi(codSuper);

    if(numero<valor){
        if(Hizq==NULL){
            Hizq = new NodoSupermercado(_codSuper, _codLugar,_nombre);
        }else{
            Hizq->insertarNodo(_codSuper, _codLugar,_nombre);
        }
    }if(numero>valor){
        if(Hder==NULL){
            Hder = new NodoSupermercado(_codSuper, _codLugar,_nombre);
            Hder->insertarNodo(_codSuper, _codLugar,_nombre);
        }
    }

}

int NodoSupermercado::obtenerValor() {
    return stoi(codSuper);
}