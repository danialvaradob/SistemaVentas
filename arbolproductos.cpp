#include "arbolproductos.h"
#include <string>
#include <iostream>
//ARBOL ArbolProductos

using namespace std;

void ArbolProductos::buscar(int _codigoProducto, int _codigoCategoria, string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock)
{
    NodoProducto *temp = new NodoProducto( _codigoProducto,  _codigoCategoria,  _nombreProducto,  _precioPorUnidad,  _cantidadEnStock);
    temp->nivel = 1;
    temp->cont = 0;
    temp->izq = NULL;
    temp->der = NULL;
    temp->padre = NULL;
    temp=insertarNodo(raiz, temp);
}

void ArbolProductos::girar(NodoProducto  *&temp)
{
    NodoProducto *ptr = temp->izq;
    if (temp->padre->izq == temp)
        temp->padre->izq = ptr;
    else
        temp->padre->der = ptr;
    ptr->padre = temp->padre;
    temp->padre = ptr;
    temp->izq = ptr->der;
    if (temp->izq != NULL)
        temp->izq->padre = temp;
    ptr->der = temp;
    temp->nivel = (temp->izq ? temp->izq->nivel + 1 : 1);
}

bool ArbolProductos::dividir(NodoProducto  *&temp)
{
    NodoProducto * ptr = temp->der;
    if (ptr && ptr->der && (ptr->der->nivel == temp->nivel))
    {
        if (temp->padre->izq == temp)
            temp->padre->izq = ptr;
        else
            temp->padre->der = ptr;
        ptr->padre = temp->padre;
        temp->padre = ptr;
        temp->der = ptr->izq;
        if (temp->der != NULL)
            temp->der->padre = temp;
        ptr->izq = temp;
        ptr->nivel = temp->nivel + 1;
        return true;
    }
    return false;
}

void ArbolProductos::balancear(NodoProducto *& temp)
{
    temp->izq = NULL;
    temp->der = NULL;
    temp->nivel = 1;
    for (temp = temp->padre; temp != raiz; temp = temp->padre)
    {
        if (temp->nivel != (temp->izq ? temp->izq->nivel + 1 : 1 ))
        {
            girar(temp);
            if (temp->der == NULL)
                temp = temp->padre;
            else if (temp->nivel != temp->der->nivel)
                temp = temp->padre;
        }
        if (temp->padre != raiz)
        {
            if (dividir(temp->padre) == false)
                break;
        }
    }
}

NodoProducto* ArbolProductos::insertarNodo(NodoProducto * &temp, NodoProducto * &ins)
{
    if (raiz == NULL)
    {
        ins->cont = 1;
        ins->padre = NULL;
        ins->izq = NULL;
        ins->der = NULL;
        raiz = ins;
        return temp;
    }
    if (ins->getCodigoProducto() < temp->getCodigoProducto())
    {
        if (temp->izq)
            return insertarNodo(temp->izq, ins);
        temp->izq = ins;
        ins->padre = temp;
        ins->cont = 1;
        balancear(ins);
        return ins;
    }
    if (ins->getCodigoProducto() > temp->getCodigoProducto())
    {
        if (temp->der)
            return insertarNodo(temp->der, ins);
        temp->der = ins;
        ins->padre = temp;
        ins->cont = 1;
        balancear(ins);
        return ins;
    }
    temp->cont++;
    delete ins;
    return temp;
}



bool ArbolProductos::existeProducto(NodoProducto *_raiz, int _codProducto) {
    if(_raiz==NULL){
        //cout << "Final de un nodo" << endl;
        return false;
    }else if (_raiz->getCodigoProducto() == _codProducto) {
        //cout << "Encontrado" << endl;
        return true;
    }else{
        //cout << "buscando" << endl;
        return  existeProducto(_raiz->izq,_codProducto) || existeProducto(_raiz->der,_codProducto);
    }
}

void ArbolProductos::eliminar(NodoProducto *&_raiz, int _codigoProducto) {
    if( _codigoProducto > _raiz->getCodigoProducto()) {
        eliminar(_raiz->der, _codigoProducto);
    } else if(_codigoProducto < _raiz->getCodigoProducto()) {
        if (_raiz->izq == NULL && _raiz->der == NULL) {
            return;
        } else if (_raiz->izq == NULL) {
            //
        }

    }

}


void ArbolProductos::PreordenI(NodoProducto *R){
    if(R==NULL){
        return;
    }else{

        cout << "Nombre del producto: " << R->getNombreProducto() << endl;
        cout << "Codigo del producto: " << R->getCodigoProducto() << endl;
        cout << "Pertenece a la categoria: " << R->getCodigoCategoria() << endl;
        PreordenI(R->izq);
        PreordenI(R->der);
    }
}

void ArbolProductos::cambiarStock(NodoProducto *&_raiz,int _codProducto, int _cantidad) {
    if (_raiz == NULL) return;
/*
    else {
        if (_raiz->getCodigoProducto() == _codProducto) {
            _raiz->getCantidadEnStock()

        }

    }*/
}


void ArbolProductos::getNodoProducto(int _codProducto, NodoProducto* _raiz, NodoProducto *&_nuevoNodo) {
    if (_raiz == NULL) return;

    else if (_codProducto == _raiz->getCodigoProducto()) {
            _nuevoNodo = _raiz;
        }
    else {
        getNodoProducto(_codProducto, _raiz->izq,_nuevoNodo);
        getNodoProducto(_codProducto, _raiz->der,_nuevoNodo);
    }
}


/*
 *
 *
 *
 *
 *


void ArbolProductos::PreordenI(NodoProducto *R){
    if(R==NULL){
        return;
    }else{
        cout<<"El id de la oferta es : "<<R->getCodigoProducto()<<endl;
        cout<<"Los precios de la oferta individual es :"<<R->obtenerI()<<" Y quedan :"<<R->obtenerCI()<<endl;
        cout<<"Los precios de la oferta Doble es :"<<R->obtenerD()<<" Y quedan :"<<R->obtenerCD()<<endl;
        PreordenI(R->izq);
        PreordenI(R->der);
    }
}



 void ArbolProductos::print(NodoProducto* temp)
{
    if (!temp)
        return;
    print(temp->izq);
    cout <<"Value: "<<temp->getCodigoProducto() << "  cont:" << temp->obtenerCI();
    cout<<"  nivel: "<<temp->obtenerCD()<<endl;
    print(temp->der);
}

void ArbolProductos::PreordenI(NodoProducto *R){
    if(R==NULL){
        return;
    }else{
        cout<<"El id de la oferta es : "<<R->getCodigoProducto()<<endl;
        cout<<"Los precios de la oferta individual es :"<<R->obtenerI()<<" Y quedan :"<<R->obtenerCI()<<endl;
        cout<<"Los precios de la oferta Doble es :"<<R->obtenerD()<<" Y quedan :"<<R->obtenerCD()<<endl;
        PreordenI(R->izq);
        PreordenI(R->der);
    }
}

int ArbolProductos::obtenerPrecioOferta(NodoProducto *O,int r,int ci,int cd){
    if(O==NULL){
        cout<<" El numero que usted ingreso no es de las ofertas"<<endl;
        return 0;
    }
    else if(O->getCodigoProducto()==r){
        if(O->obtenerCI()<ci){
            cout<<"No se tienen suficientes habitaciones simples."<<endl;
            return 0;
        }
        else if(O->obtenerCD()<cd){
            cout<<"No se tienen suficientes habitaciones dobles."<<endl;
            return 0;
        }
        else{
            return O->obtenerI()*ci + O->obtenerD()*cd;
        }
    }
    else{
        obtenerPrecioOferta(O->izq, r, ci, cd);
        obtenerPrecioOferta(O->der, r, ci, cd);
    }

}

 */

