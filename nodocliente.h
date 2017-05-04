#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H



class nodoCliente {
public:


    nodoCliente(string _id, string _nombre, string _direccion, string _telefono)
    {
        idx = _id;
        nombre = _nombre;
        direccion = _direccion;
        telefono = _telefono;
        siguiente = NULL;
        anterior = NULL;

        cantidadDeCompras = 0;

    }


    nodoCliente *getSiguiente();
    void setSiguiente(nodoCliente* _siguiente);
    nodoCliente *getAnterior();
    void setAnterior(nodoCliente* _anterior);

    string getNombre();
    string getDireccion();
    string getID();
    string getTelefono();
    int getCantidadCompras();
    void aumentarVentas(){cantidadDeCompras++;}





private:
    string idx;
    nodoCliente *siguiente;
    nodoCliente *anterior;
    string nombre;
    string direccion;
    string telefono;

    int cantidadDeCompras;

    //friend class ListaProveedores;
    friend class ListaClientes;

};



#endif // NODOCLIENTE_H
