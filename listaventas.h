#ifndef LISTAVENTAS_H
#define LISTAVENTAS_H
#include <nodoventa.h>
#include <string>
using namespace std;




class ListaVentas {
public:
    ListaVentas() {primero = actual = NULL;}
    ~ListaVentas();

    void insertar(string _codCliente, string _codProveedor , int _descApl, float _monTotal);
    void insertarNodoVacio(nodoVenta* _nuevo);
    void eliminarFinal();
    bool listaVacia() {return primero == NULL;}
    int largoLista();
    bool verificarClienteProveedor(string _codCliente, string _codProveedor);

    //... funcion que dice
    //... si ya un cliente
    string getProveedorMasVentas(ListaProveedores* _ListaProveedores);
    string getClienteMasCompras(ListaClientes* _ListaClientes);
    string getProductoMasVendido(ListaCategorias* _ListaCategorias);
    string getCategoriaMasVendida(ListaCategorias* _ListaCategorrias);

    nodoVenta* getPrimero() {return primero;};


    //... elimina el nodo que el monto pagado es 0;
    //... no realizo venta
    void eliminarNodo();


private:
    nodoVenta* primero;
    nodoVenta* actual;

};


#endif // LISTAVENTAS_H
