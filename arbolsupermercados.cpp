#include "arbolsupermercados.h"
#include "nodosupermercado.h"
#include <iostream>

//ARBOL AVL



void ArbolSupermercados::insertarBalanceado(NodoSupermercado *ra,bool Hh, int _codSuper,int _codLugar, string _nombre ){
    NodoSupermercado *n1;



    if(raiz==NULL){
        ra=new NodoSupermercado( _codSuper, _codLugar,  _nombre );
        Hh = true;
    }else{
        cout<<endl;
        if(_codSuper<=ra->obtenerValor()){

            insertarBalanceado(ra->Hizq,Hh, _codSuper, _codLugar, _nombre);

            if(Hh){
                switch(ra->obtenerValor()){
                    case 1: (ra->FB=0);
                        Hh = false;
                        break;
                    case 0: (ra->FB  = -1);
                        break;
                    case -1: (n1=ra->Hizq);
                        if(n1->FB ==-1){
                            rotacionSimpleIzquierda(ra,n1);
                        }else{
                            rotacionDobleIzquierda(ra,n1);
                        }
                        Hh = false;
                        break;
                }
            }
        }else{
            if(_codSuper>ra->obtenerValor()){
                insertarBalanceado(ra->Hder,Hh, _codSuper, _codLugar, _nombre);

                if(Hh){
                    switch(ra->FB){
                        case -1:( ra->FB=0);
                            Hh = false;
                            break;
                        case 0: (ra->FB=1);
                            break;
                        case 1:(n1=ra->Hder);
                            if(n1->FB=1){
                                rotacionSimpleDerecha(ra, n1);
                            }else{
                                rotacionDobleDerecha(ra, n1);
                            }
                            Hh=false;
                            break;
                    }
                }
            }
        }
    }
}
void ArbolSupermercados::equilibrar1(NodoSupermercado *n, bool) {
    NodoSupermercado *n1;
    switch (n->FB){
        case -1: n->FB = 0;
            break;
        case 0: n->FB = 1;
            Hh = false;
            break;
        case 1: n1 = n->Hder;
            if(n1->FB>=0){
                if(n1->FB=0){
                    Hh = false;
                    rotacionSimpleDerecha(n, n1);
                }else{
                    rotacionDobleDerecha(n, n1);
                }
            }
    }
}

void ArbolSupermercados::equilibrar2(NodoSupermercado *n, bool) {
    NodoSupermercado *n1;
    switch (n->FB){
        case 1: n->FB = 0;
            break;
        case 0: n->FB = 1;
            Hh = false;
            break;
        case -1: n1 = n->Hizq;
            if(n1->FB<=0){
                if(n1->FB=0){
                    Hh = false;
                    rotacionSimpleIzquierda(n, n1);
                }else{
                    rotacionDobleIzquierda(n, n1);
                }
            }
    }
}


void ArbolSupermercados::rotacionDobleIzquierda(NodoSupermercado *n, NodoSupermercado *n1) {
    NodoSupermercado *n2;
    n2=n1->Hder;
    n->Hizq = n2->Hder;
    n2->Hder=n;
    n1->Hder=n2->Hizq;
    n2->Hizq=n1;

    if(n2->FB==1){
        n1->FB=-1;
    }else{
        n1->FB=0;
    }
    if(n2->FB==-1){
        n->FB=1;
    }else{
        n->FB=0;
    }
    n2->FB=0;
    n=n2;
}
void ArbolSupermercados::rotacionDobleDerecha(NodoSupermercado *n, NodoSupermercado *n1) {
    NodoSupermercado *n2;
    n2=n1->Hizq;
    n->Hder = n2->Hizq;
    n2->Hizq=n;
    n1->Hizq=n2->Hder;
    n2->Hder=n1;

    if(n2->FB==1){
        n->FB=-1;
    }else{
        n->FB=0;
    }
    if(n2->FB==-1){
        n1->FB=1;
    }else{
        n1->FB=0;
    }
    n2->FB=0;
    n=n2;
}
void ArbolSupermercados::rotacionSimpleDerecha(NodoSupermercado *n, NodoSupermercado *n1) {
    n->Hder=n1->Hizq;
    n1->Hizq=n;

    if(n1->FB==1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=1;
        n1->FB=-1;
    }
    n=n1;
}

void ArbolSupermercados::rotacionSimpleIzquierda(NodoSupermercado *n, NodoSupermercado *n1) {

    n->Hizq = n1->Hder;
    n1->Hder = n;

    if(n1->FB==-1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=-1;
        n1->FB=-1;
    }
    n=n1;
}
void ArbolSupermercados::preordenI(NodoSupermercado *R) {
    if(R==NULL){
        return;
    }else{
        cout<<R->obtenerValor()<<endl;
        preordenI(R->Hizq);
        preordenI(R->Hder);
    }
}

//retornta true si el codigo de supermercado buscado existe
bool ArbolSupermercados::existeSupermercado(int _codNuevoSuper, NodoSupermercado* _raiz) {

    if (_raiz == NULL) {
        return false;
    } else if (_raiz->getCodSuper() == _codNuevoSuper) {
        return true;
    } else {

        return existeSupermercado(_codNuevoSuper,_raiz->Hizq) || existeSupermercado(_codNuevoSuper,_raiz->Hder);
        existeSupermercado(_codNuevoSuper, _raiz->Hizq);
        existeSupermercado(_codNuevoSuper, _raiz->Hder);

    }
}

void ArbolSupermercados::agregarCategoria(NodoSupermercado *nodoSupermercado,int _codSuper,int _codCat, string _descCat) {
    if (raiz == NULL) {
        return;
    } else if (raiz->codSuper == _codSuper){
        // primero revisa si esta vacio el arbol
        if (raiz->punteroCategorias == NULL) {
            //crea el arbol y le agrega la categoria
            raiz->punteroCategorias = new ArbolCategorias();
            raiz->punteroCategorias->insertarValorNodoRN(_codCat,_descCat);

        } else {
            raiz->punteroCategorias->insertarValorNodoRN(_codCat,_descCat);
        }
        //si no esta vacio lo agrega

    } else{
        agregarCategoria(raiz->Hizq,_codSuper,_codCat,_descCat);
        agregarCategoria(raiz->Hder,_codSuper,_codCat,_descCat);
    }

}

bool ArbolSupermercados::existeCategoria(int _codSuper,int _codCat, NodoSupermercado *_raiz) {
    if (raiz == NULL) return false;

    else if (raiz->punteroCategorias != NULL) {
            return raiz->punteroCategorias->existeCategoria(_codCat,raiz->punteroCategorias->raiz);
    } else {
        return existeCategoria(_codSuper, _codCat,raiz->Hizq) || existeCategoria(_codSuper, _codCat,raiz->Hder);
    }

}


/*
ArbolCategorias* ArbolSupermercados::getCategorias(int _codSuper,NodoSupermercado* _raiz) {
    if (raiz == NULL) return NULL;

    else if (raiz->codSuper == _codSuper) {
        return raiz->punteroCategorias;
    } else {
        return getCategorias(_codSuper,raiz->Hizq) || getCategorias(_codSuper,raiz->Hder);
    }
}
*/
/*/++++++++++++++++++++ inserciones de archivo+++++++++++++++++++++++++++++
 *
 * MODIFICAR Y CAMBIAR A insertarNodoCat  (RN)
 *                       inserntarNodoPro (AA)
 *
void AVL :: InsertaNodoTransporte(NodoHotel *H,int idHotel, int idTransporte, int tipoT,string origen, string destino,string salida,string horaSalida ,string Llegada,string horaLlegada,string compannia ,int  plazas,int precio,int cantT){
    if (H==NULL){
        return;
    }
    else{
        if (H->obtenerValor()==idHotel){
            if (H->siguiente==NULL){
                H->siguiente=new RNegro();
            }
            H->siguiente->insertarValorNodoRN(idTransporte,tipoT,origen, destino, salida, horaSalida, Llegada, horaLlegada,compannia, plazas, precio,  cantT  );
            return;

        }

        else{
            InsertaNodoTransporte(H->Hizq,idHotel, idTransporte,tipoT,origen, destino, salida, horaSalida, Llegada, horaLlegada,compannia, plazas, precio,  cantT );
            InsertaNodoTransporte(H->Hder,idHotel, idTransporte,tipoT,origen, destino, salida, horaSalida, Llegada, horaLlegada,compannia, plazas, precio,  cantT );
        }
    }
}
void AVL:: InsertaNodoOferta(NodoHotel *H,int idHotel, int  idOferta,int  precioInd,int precioDoble,int cantI,int  cantD){
    if (H==NULL){
        return;
    }
    else{
        if (H->obtenerValor()==idHotel){
            if (H->anterior==NULL){
                H->anterior=new AA();
            }
            H->anterior->lookup( idOferta,  precioInd,  precioDoble,  cantI,  cantD);
            return;
        }
        else{
            InsertaNodoOferta(H->Hizq, idHotel,  idOferta,  precioInd,  precioDoble,  cantI,  cantD);
            InsertaNodoOferta(H->Hder, idHotel,  idOferta,  precioInd,  precioDoble,  cantI,  cantD);
        }
    }
}

 */

