#include "nodoventa.h"
#include <sstream>

string NodoVenta::toString() {
    stringstream flujo;
    stringstream flujo1;
    stringstream flujo2;
    stringstream flujo3;
    string _codP;
    string _codC;
    string _cant;
    string _monto;

    flujo << codigoProv;
    _codP = flujo.str();
    flujo2 << codigoCliente;
    _codC = flujo2.str();
    flujo1 << cantidadComprada;
    _cant = flujo1.str();
    flujo3 << monto;
    _monto = flujo3.str();


    return "Nombre del proveedor: "+nombreProv+"\nCodigo del proveedor: "+_codP+"\nNombre del cliente: "+nombreCliente+"\nCodigo del cliente: "+_codC+"\nCantidad comprada del producto: "+_cant+"\nMonto a pagar: "+_monto;
}

