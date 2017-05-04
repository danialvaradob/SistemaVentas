#ifndef NODOPRODUCTO_H
#define NODOPRODUCTO_H




class nodoProducto {
public:
    nodoProducto(string _codigoProducto, string _codigoCategoria, string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock){

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

    nodoProducto *getSiguiente();
    void setSiguiente(nodoProducto* _siguiente);
    nodoProducto *getAnterior();
    void setAnterior(nodoProducto* _anterior);
    nodoProducto *getPrimerProducto();
    void setPrimeroProducto( nodoProducto* _primerProducto);

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

    nodoProducto *siguiente;
    nodoProducto *anterior;

    friend class nodoCategoria;
    friend class ListaCategorias;


};


#endif // NODOPRODUCTO_H
