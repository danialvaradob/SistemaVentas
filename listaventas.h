#ifndef LISTAVENTAS_H
#define LISTAVENTAS_H

#include "nodoventa.h"
#include "arbolcategorias.h"
#include "arbolclientes.h"
#include "arbolproductos.h"
#include "arbolsupermercados.h"
#include "arbolproveedores.h"
#include <string>

class ListaVentas {
public:
    ListaVentas() {primero = NULL;}

    void insertar(NodoVenta *_venta);
    bool listaVacia() {return primero == NULL;}
    string getProveedorMasVentas(ArbolProveedores* _ListaProveedores);
    string getClienteMasCompras(ArbolClientes * _arbolClientes);
    string getProductoMasVendido(ArbolSupermercados* _arbolSuper, int _codCategoria, int _codProducto);
    string getCategoriaMasVendida(ArbolSupermercados* _arbolSuper, int _codCategoria);


    NodoVenta* getPrimero() {return primero;};

private:
    NodoVenta* primero;

};

#endif // LISTAVENTAS_H
