#ifndef NODOPRODUCTOCOMPRADO_H
#define NODOPRODUCTOCOMPRADO_H


class NodoProductoComprado {

public:
    NodoProductoComprado(string _codigoP, string _codigoC, int _unidadesComp){

        codigoProducto = _codigoP;
        codigoCategoria = _codigoC;
        unidadesCompradas = _unidadesComp;

        siguiente = NULL;
        anterior = NULL;
    }

    NodoProductoComprado *getSiguiente();
    void setSiguiente(NodoProductoComprado* _siguiente);
    NodoProductoComprado *getAnterior();
    void setAnterior(NodoProductoComprado* _anterior);

    string getCodigoProd() {return codigoProducto;}
    string getCodigoCat() {return codigoCategoria;}
    int getUnidadesComp() {return unidadesCompradas;}


private:
    string codigoProducto;
    string codigoCategoria;
    int unidadesCompradas;
    NodoProductoComprado* siguiente;
    NodoProductoComprado* anterior;\

    friend class nodoVenta;
    friend class ListaVentas;


};
#endif // NODOPRODUCTOCOMPRADO_H
