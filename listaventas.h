#ifndef LISTAVENTAS_H
#define LISTAVENTAS_H
#include <nodoventa.h>
#include <arbolproveedores.h>
#include <arbolclientes.h>
#include <arbolcategorias.h>
#include <string>
using namespace std;




class ListaVentas {
public:
    ListaVentas() {primero = actual = NULL;}
    ~ListaVentas();

    void insertar(string _codCliente, string _codProveedor , int _descApl, float _monTotal);
    void insertarNodoVacio(NodoVenta* _nuevo);
    void eliminarFinal();
    bool listaVacia() {return primero == NULL;}
    int largoLista();
    bool verificarClienteProveedor(string _codCliente, string _codProveedor);

    //... funcion que dice
    //... si ya un cliente
    string getProveedorMasVentas(ArbolProveedores* _ListaProveedores);
    string getClienteMasCompras(ArbolClientes* _ListaClientes);
    string getProductoMasVendido(ArbolCategorias* _ListaCategorias);
    string getCategoriaMasVendida(ArbolCategorias* _ListaCategorrias);

    NodoVenta* getPrimero() {return primero;};


    //... elimina el nodo que el monto pagado es 0;
    //... no realizo venta
    void eliminarNodo();


private:
    NodoVenta* primero;
    NodoVenta* actual;

};


#endif // LISTAVENTAS_H
