#include "arbolsupermercados.h"
#include "nodosupermercado.h"
#include <iostream>

//ARBOL AVL


void ArbolSupermercados::insertarNodoSupermercado(string _codSuper,string _codLugar, string _nombre )
{
    if(raiz==NULL){
        raiz = new NodoSupermercado(  _codSuper, _codLugar,  _nombre );
    }else{
        raiz->insertarNodo( _codSuper, _codLugar,  _nombre );
    }
}

void ArbolSupermercados::insertarBalanceado(NodoSupermercado *ra, string _codSuper,string _codLugar, string _nombre ){
    NodoSupermercado *n1;

    int numero = stoi(_codSuper);
    int valor = stoi(codSuper);

    if(raiz==NULL){
        ra=new NodoSupermercado( _codSuper, _codLugar,  _nombre );
        Hh = true;
    }else{
        cout<<endl;
        if(numero<=ra->obtenerValor()){

            insertarBalanceado(ra->Hizq, _codSuper, _codLugar, _nombre);

            if(Hh){
                switch(ra->obtenerValor()){
                    case 1: ra->FB=0;
                        Hh = false;
                        break;
                    case 0: ra->FB  = -1;
                        break;
                    case -1: n1=ra->Hizq;
                        if(n1->FB =-1){
                            rotacionSimpleIzquierda(ra,n1);
                        }else{
                            rotacionDobleIzquierda(ra,n1);
                        }
                        Hh = false;
                        break;
                }
            }
        }else{
            if(pIdHotel>ra->obtenerValor()){
                insertarBalanceado(ra->Hder, _codSuper, _codLugar, _nombre);

                if(Hh){
                    switch(ra->FB){
                        case -1: ra->FB=0;
                            Hh = false;
                            break;
                        case 0: ra->FB=1;
                            break;
                        case 1:n1=ra->Hder;
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

void AVL::Equilibrar1(NodoHotel* n, bool Hh){
    NodoHotel *n1;
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
                    RotacionSimpleDerecha(n, n1);
                }else{
                    RotacionDobleDerecha(n, n1);
                }
            }
    }
}

void AVL::Equilibrar2(NodoHotel* n, bool Hh){
    NodoHotel *n1;
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
                    RotacionSimpleIzquierda(n, n1);
                }else{
                    RotacionDobleIzquierda(n, n1);
                }
            }
    }
}



void AVL::RotacionDobleIzquierda(NodoHotel* n, NodoHotel* n1){
    NodoHotel *n2;
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

void AVL::RotacionDobleDerecha(NodoHotel* n, NodoHotel* n1){
    NodoHotel *n2;
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

void AVL::RotacionSimpleDerecha(NodoHotel* n, NodoHotel* n1){
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

void AVL::RotacionSimpleIzquierda(NodoHotel* n, NodoHotel* n1){
    n->Hizq=n1->Hder;
    n1->Hder=n;

    if(n1->FB==-1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=-1;
        n1->FB=-1;
    }
    n=n1;
}

void AVL::PreordenI(NodoHotel *R){
    if(R==NULL){
        return;
    }else{
        cout<<R->obtenerValor()<<endl;
        PreordenI(R->Hizq);
        PreordenI(R->Hder);
    }
}

//++++++++++++++++++++ inserciones de archivo+++++++++++++++++++++++++++++
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