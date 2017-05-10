#include <iostream>
#include "arbolsupermercados.h"
#include "arbolclientes.h"
#include <fstream>
#include <cstring>

using namespace std;


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
    ArbolClientes *arbol = new ArbolClientes();
    leerArchClientes(arbol);

    cout << "Hello, World!" << endl;


    return 0;
}