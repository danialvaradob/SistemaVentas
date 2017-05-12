#include "arbolcategorias.h"
#include <iostream>
//Arbol ROJINEGRO

bool ArbolCategorias::existeCategoria(int _id, nodocategoria *_raiz) {
    if(_raiz==NULL){
        cout << "Final de un nodo" << endl;
        return false;
    }else if (_raiz->getCodigo() == _id) {
        cout << "Encontrado" << endl;
        return true;
    }else{
        cout << "buscando" << endl;
        return  existeCategoria(_id,_raiz->izq) || existeCategoria(_id,_raiz->der);
    }
}

bool ArbolCategorias::existeProducto(int _codProducto, int _codCategoria, nodocategoria *_raiz) {
    if(_raiz==NULL){
        return false;
    }else if (_raiz->getCodigo() == _codCategoria) {
        return _raiz->punteroArbolProductos->existeProducto(_raiz->punteroArbolProductos->raiz,_codProducto);
    }else{
        return  existeCategoria(_codCategoria,_raiz->izq) || existeCategoria(_codCategoria,_raiz->der);
    }
}

nodocategoria *ArbolCategorias::InsertarNodoRN(nodocategoria* RaizRN, nodocategoria *pt){
    if (RaizRN == NULL)
        return pt;

    if (pt->getCodigo() < RaizRN->getCodigo()){
        RaizRN->izq  = InsertarNodoRN(RaizRN->izq, pt);
        RaizRN->izq->padre = RaizRN;
    }
    else if (pt->getCodigo() > RaizRN->getCodigo())
    {
        RaizRN->der = InsertarNodoRN(RaizRN->der, pt);
        RaizRN->der->padre = RaizRN;
    }

    return RaizRN;
}



void ArbolCategorias :: rotarIzquierda(nodocategoria *&RaizRN, nodocategoria *&pt){
    nodocategoria *pt_der = pt->der;

    pt->der = pt_der->izq;

    if (pt->der != NULL)
        pt->der->padre = pt;

    pt_der->padre = pt->padre;

    if (pt->padre == NULL)
        RaizRN = pt_der;

    else if (pt == pt->padre->izq)
        pt->padre->izq = pt_der;

    else
        pt->padre->der = pt_der;

    pt_der->izq = pt;
    pt->padre = pt_der;
}

void ArbolCategorias ::rotarDerecha(nodocategoria *&RaizRN, nodocategoria *&pt){
    nodocategoria *pt_izq = pt->izq;

    pt->izq = pt_izq->der;

    if (pt->izq != NULL)
        pt->izq->padre = pt;

    pt_izq->padre = pt->padre;

    if (pt->padre == NULL)
        RaizRN = pt_izq;

    else if (pt == pt->padre->izq)
        pt->padre->izq = pt_izq;

    else
        pt->padre->der = pt_izq;

    pt_izq->der = pt;
    pt->padre = pt_izq;
}


void ArbolCategorias ::aplicarReglas(nodocategoria *&RaizRN, nodocategoria *&pt){
    nodocategoria *padre_pt = NULL;
    nodocategoria *abuelo_pt = NULL;

    while ((pt != RaizRN) && (pt->color != BLACK) &&
           (pt->padre->color == RED))
    {

        padre_pt = pt->padre;
        abuelo_pt = pt->padre->padre;

        /*  Case : A
            Parent of pt is left child of Grand-parent of pt */
        if (padre_pt == abuelo_pt->izq){
            nodocategoria *tio_pt = abuelo_pt->der;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (tio_pt != NULL && tio_pt->color == RED){
                abuelo_pt->color = RED;
                padre_pt->color = BLACK;
                tio_pt->color = BLACK;
                pt = abuelo_pt;
            }

            else{
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == padre_pt->der)
                {
                    rotarIzquierda(RaizRN, padre_pt);
                    pt = padre_pt;
                    padre_pt = pt->padre;
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotarDerecha(RaizRN, abuelo_pt);
                swap(padre_pt->color, abuelo_pt->color);
                pt = padre_pt;
            }
        }

            /* Case : B
               Parent of pt is right child of Grand-parent of pt */
        else{
            nodocategoria *tio_pt = abuelo_pt->izq;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((tio_pt != NULL) && (tio_pt->color == RED)){
                abuelo_pt->color = RED;
                padre_pt->color = BLACK;
                tio_pt->color = BLACK;
                pt = abuelo_pt;
            }
            else{
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == padre_pt->izq){
                    rotarDerecha(RaizRN, padre_pt);
                    pt = padre_pt;
                    padre_pt = pt->padre;
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotarIzquierda(RaizRN, abuelo_pt);
                swap(padre_pt->color, abuelo_pt->color);
                pt = padre_pt;
            }
        }
    }

    RaizRN->color = BLACK;
}

void ArbolCategorias ::insertarValorNodoRN(int _id,string _desc){

    nodocategoria *pt = new nodocategoria (_id,_desc);

    raiz = InsertarNodoRN(raiz, pt);

    aplicarReglas(raiz, pt);

}

void ArbolCategorias::agregarProducto(nodocategoria *raiz, int codProI, int codCatI, string nombreProducto,
                                      int precioPorUnidad, int cantidadEnStock) {

    if (raiz == NULL) {
        return;
    } else if (raiz->getCodigo() == codCatI){
        // primero revisa si esta vacio el arbol
        if (raiz->punteroArbolProductos == NULL) {
            //crea el arbol y le agrega la categoria
            raiz->punteroArbolProductos = new ArbolProductos();
            raiz->punteroArbolProductos->buscar( codProI,  codCatI,  nombreProducto,
                     precioPorUnidad,  cantidadEnStock);

        } else {
            raiz->punteroArbolProductos->buscar( codProI,  codCatI,  nombreProducto,
                                                 precioPorUnidad,  cantidadEnStock);
        }
        //si no esta vacio lo agrega

    } else{
        agregarProducto(raiz->izq,  codProI,  codCatI,  nombreProducto,
                 precioPorUnidad,  cantidadEnStock);
        agregarProducto(raiz->der,  codProI,  codCatI,  nombreProducto,
                 precioPorUnidad,  cantidadEnStock);

    }

}

ArbolProductos* ArbolCategorias::getArbolProductos(nodocategoria *_raiz, int _codCat) {
        if (_raiz == NULL) return NULL;

        else if (_raiz->getCodigo() ==_codCat ) {
            return _raiz->punteroArbolProductos;
        } else {
            if (_raiz->der != NULL) {
                return getArbolProductos(_raiz->der,  _codCat);
            }
            if (_raiz->izq != NULL) {
                return getArbolProductos(_raiz->izq,  _codCat);
            }
        }
}

void ArbolCategorias::getArbolProd(nodocategoria *_raiz, int codCat, ArbolProductos *&arbolProductos) {
    if (_raiz == NULL) return;

    else if (_raiz->getCodigo() == codCat) {
        arbolProductos = _raiz->punteroArbolProductos;
    } else {
        getArbolProd( _raiz->der,codCat,arbolProductos);
        getArbolProd(  _raiz->izq,codCat,arbolProductos);
    }
}