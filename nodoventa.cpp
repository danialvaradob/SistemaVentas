#include "nodoventa.h"
#include <sstream>

string NodoVenta::toString() {
    stringstream flujo;
    stringstream flujo1;
    stringstream flujo2;
    stringstream flujo3;
    stringstream flujo4;
    stringstream flujo5;
    stringstream flujo6;
    string _codProv;
    string _codCliente;
    string _cant;
    string _monto;
    string _codProd;
    string _codCat;
    string _precioXunidad;

    flujo << codigoProv;
    _codProv = flujo.str();
    flujo2 << codigoCliente;
    _codCliente = flujo2.str();
    flujo1 << cantidadComprada;
    _cant = flujo1.str();
    flujo3 << monto;
    _monto = flujo3.str();
    flujo4 << codProd;
    _codProd = flujo4.str();
    flujo5 << codCategoria;
    _codCat = flujo5.str();
    flujo6 << precioPorUnidad;
    _precioXunidad = flujo6.str();


    return "Nombre del proveedor: "+nombreProv+
            "\nCodigo del proveedor: "+_codProv+
            "\nNombre del cliente: "+nombreCliente+
            "\nCodigo del cliente: "+_codCliente+
            "\nDescripcion de la categoria: "+descCategoria+
            "\nCodigo de la categoria: "+_codCat+
            "\nNombre del producto: "+nombreProducto+
            "\nCodigo del producto: "+_codProd+
            "\nPrecio por unidad: "+_precioXunidad+
            "\nCantidad comprada del producto: "+_cant+
            "\nMonto a pagar: "+_monto;
}

