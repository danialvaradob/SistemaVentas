#ifndef NODOVENTA_H
#define NODOVENTA_H



class nodoVenta {
public:

    nodoVenta() {
        codigoCliente = "";
        codigoProveedor = "";
        descuentoAplicado = 0;
        montoTotal = 0;


        siguiente = NULL;
        anterior = NULL;

        primeroProductoComprado = NULL;

    }

    nodoVenta(string _codigoCliente, string _codigoProveedor,int _descApl, double _monTotal){
        codigoCliente = _codigoCliente;
        codigoProveedor = _codigoProveedor;
        descuentoAplicado = _descApl;
        montoTotal = _monTotal;

        siguiente = NULL;
        anterior = NULL;

        primeroProductoComprado = NULL;

    }

    void setValores(string _codigoCliente, string _codigoProveedor,int _descApl, double _monTotal);

    nodoVenta *getSiguiente();
    void setSiguiente(nodoVenta* _siguiente);
    nodoVenta *getAnterior();
    void setAnterior(nodoVenta* _anterior);
    nodoProductoComprado *getPrimerProducto(){return primeroProductoComprado;}
    void setPrimeroProducto( nodoProductoComprado* _primerProducto);

    string getCodigoCli() {return codigoCliente;};
    string getCodigoProvee() {return codigoProveedor;};
    int getDescuentoApl() {return descuentoAplicado;};
    float getMontoTotal() {return montoTotal;};

    void setCodigoCliente(string _codigoCliente);
    void setCodigoProveedor(string _codigoProveedor);
    void setDescuentoAplicado(int _descuentoAplicado);
    void setMontoTotal(double _montoTotal);

    void insertarProductoComprado(string _codigoP, string _codigoC, int _unidadesComp);



private:
    string codigoCliente;
    string codigoProveedor;
    int descuentoAplicado;
    double montoTotal;

    nodoVenta* siguiente;
    nodoVenta* anterior;
    nodoProductoComprado* primeroProductoComprado;

    friend class ListaVentas;

};

#endif // NODOVENTA_H
