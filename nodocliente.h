#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H



class NodoCliente {
public:


    NodoCliente(string _id, string _nombre, string _direccion, string _telefono)
    {
        idx = _id;
        nombre = _nombre;
        direccion = _direccion;
        telefono = _telefono;
        siguiente = NULL;
        anterior = NULL;

        cantidadDeCompras = 0;

    }


    NodoCliente *getSiguiente();
    void setSiguiente(NodoCliente* _siguiente);
    NodoCliente *getAnterior();
    void setAnterior(NodoCliente* _anterior);

    string getNombre();
    string getDireccion();
    string getID();
    string getTelefono();
    int getCantidadCompras();
    void aumentarVentas(){cantidadDeCompras++;}





private:
    string idx;
    NodoCliente *siguiente;
    NodoCliente *anterior;
    string nombre;
    string direccion;
    string telefono;

    int cantidadDeCompras;

    //friend class ListaProveedores;
    friend class ListaClientes;

};



#endif // NODOCLIENTE_H
