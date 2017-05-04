#ifndef NODOPRODUCTO_H
#define NODOPRODUCTO_H




class NodoProducto {
public:
    NodoProducto(string _codigoProducto, string _codigoCategoria, string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock){

        codigoProducto = _codigoProducto;
        codigoCategoria = _codigoCategoria;
        nombreProducto = _nombreProducto;
        precioPorUnidad = _precioPorUnidad;
        cantidadEnStock = _cantidadEnStock;
        cantidadAlInicio = _cantidadEnStock;

        siguiente = NULL;
        anterior = NULL;
        //cambioStock = false;

    }

    NodoProducto *getSiguiente();
    void setSiguiente(NodoProducto* _siguiente);
    NodoProducto *getAnterior();
    void setAnterior(NodoProducto* _anterior);
    NodoProducto *getPrimerProducto();
    void setPrimeroProducto( NodoProducto* _primerProducto);

    string getCodigoProducto();
    string getCodigoCategoria();
    string getNombreProducto();
    double getPrecioPorUnidad();
    int getCantidadEnStock();
    void setCantidadEnStock(int _cantidadNueva);
    int getCantidadAlInicio() { return cantidadAlInicio;}





private:
    string codigoProducto;
    string codigoCategoria;
    string nombreProducto;
    double precioPorUnidad;
    int cantidadEnStock;
    int cantidadAlInicio;

    NodoProducto *siguiente;
    NodoProducto *anterior;

    friend class nodoCategoria;
    friend class ListaCategorias;


};


#endif // NODOPRODUCTO_H
