#include <iostream>
#include "arbolsupermercados.h"
#include "arbolclientes.h"
#include "listalugares.h"
#include <fstream>
#include <cstring>

using namespace std;



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
    ArbolClientes *arbol = new ArbolClientes();
    leerArchClientes(arbol);

    cout << "Hello, World!" << endl;


    return 0;
}