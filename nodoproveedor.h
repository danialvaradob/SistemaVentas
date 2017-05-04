#ifndef NODOPROVEEDOR_H
#define NODOPROVEEDOR_H




class nodoProveedor {
public:


    nodoProveedor(string _id, string _nombre, string _direccion, string _telefono){
        identificacion = _id;
        nombre = _nombre;
        direccion = _direccion;
        telefono = _telefono;
        siguiente = NULL;
        anterior = NULL;

        cantidadDeVentas = 0;

    }


    nodoProveedor *getSiguiente();
    void setSiguiente(nodoProveedor* _siguiente);
    nodoProveedor *getAnterior();
    void setAnterior(nodoProveedor* _anterior);

    string getNombre();
    string getDireccion();
    string getID();
    string getTelefono();
    int getCantidadDeVentas();
    void aumentarVentas(){cantidadDeVentas++;}





private:
    string identificacion;
    nodoProveedor *siguiente;
    nodoProveedor *anterior;
    string nombre;
    string direccion;
    string telefono;

    int cantidadDeVentas;

    friend class ListaProveedores;


};


#endif // NODOPROVEEDOR_H
