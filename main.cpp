#include <iostream>
#include "arbolsupermercados.h"
#include "arbolclientes.h"
#include "listalugares.h"
#include "arbolproveedores.h"
#include <fstream>
#include <cstring>

using namespace std;

void leerArchSupermercado(ArbolSupermercados * _supermercado){
    string nombreArchivo = "Supermercados.txt";

    ifstream archivoEntrada;
    string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, ios::in);

    if (archivoEntrada.fail()) {
        cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        string codSuper(std::strtok (lineaValores, ";"));
        string codLugar(std::strtok (NULL, ";"));
        string nombre(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;

        int codSint = atoi(codSuper.c_str());
        int codLint = atoi(codLugar.c_str());
        if (_supermercado->existeSupermercado(codSint,_supermercado->raiz)) {
            cout << "Supermercado ya existe, codigo: " << codSuper << endl;
            continue;
        }else{
            cout << "Codigo Supermercado: " << codSuper << " Nombre: "<< nombre << endl;
            _supermercado->insertarNodoSupermercado(codSint,codLint,nombre);
        }
    }
    archivoEntrada.close();

}




void leerArchProveedores(ArbolProveedores * _proveedores){
    string nombreArchivo = "Proveedores.txt";

    ifstream archivoEntrada;
    string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, ios::in);

    if (archivoEntrada.fail()) {
        cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        string id(std::strtok (lineaValores, ";"));
        string nombre(std::strtok (NULL, ";"));
        string direccion(std::strtok (NULL, ";"));
        string telefono(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;

        int idProveedor = atoi(id.c_str());
        int intTel = atoi(telefono.c_str());
        //cout << "COMENZANDO A EVALUAR" << endl;
        _proveedores->InordenI(_proveedores->raiz);
        if (_proveedores->existeProveedor(idProveedor,_proveedores->raiz)) {
            cout << "Proveedor ya existe, codigo: " << id << endl;
            continue;
        }else{
            cout << "Codigo Proveedor: " << id << " Nombre: "<< nombre << endl;
            //NodoProveedor* nodoProveedor = new NodoProveedor(idProveedor,nombre,direccion,intTel);
            _proveedores->insertarNodoProveedor(idProveedor,nombre,direccion,intTel);
        }
    }
    archivoEntrada.close();

}



void leerArchLugares(ListaLugares * _lugares){
    string nombreArchivo = "Lugares.txt";

    ifstream archivoEntrada;
    string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, ios::in);

    if (archivoEntrada.fail()) {
        cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        string id(std::strtok (lineaValores, ";"));
        string nombre(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;
        int codigoL = atoi(id.c_str());


        if (_lugares->existeLugar(codigoL))
            continue;
        else{
            cout << "Codigo Lugares: " << id << endl;
            _lugares->insertarLugar(codigoL,nombre);
        }
    }
    archivoEntrada.close();
    cout << _lugares->largoLista() << endl;
}


void leerArchClientes(ArbolClientes * _ArbolClientes){
    string nombreArchivo = "Clientes.txt";
    cout << "entro" << endl;

    ifstream archivoEntrada;
    string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, ios::in);

    if (archivoEntrada.fail()) {
        cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        string id(std::strtok (lineaValores, ";"));
        string nombre(std::strtok (NULL, ";"));
        string direccion(std::strtok (NULL, ";"));
        string telefono(std::strtok (NULL, ";"));

        int idCliente = atoi(id.c_str());

        // ... crear el nodo
        /*if ( _ArbolClientes->existeCliente(_ArbolClientes->raizB, idCliente)){
            cout << "Entro1" << endl;
            continue;
        }else{
         */
            cout <<"Codigo Cliente: "<< id << "," << nombre << "," << direccion << "," << telefono << endl;
            int intTelefono = atoi(telefono.c_str());

            _ArbolClientes->IniciarInsercionB(idCliente,idCliente,nombre,direccion,intTelefono);

    }

    archivoEntrada.close();
}




int main() {
    ArbolClientes *arbolClientes = new ArbolClientes();
    //leerArchClientes(arbolClientes);

    ArbolProveedores* arbolProveedores = new ArbolProveedores();
    leerArchProveedores(arbolProveedores);


    cout << "Hello, World!" << endl;


    return 0;
}