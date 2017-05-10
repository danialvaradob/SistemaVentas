#include <iostream>
#include "arbolsupermercados.h"
#include "arbolclientes.h"
#include <fstream>
using namespace std;


void leerArchClientes(ArbolClientes * _ArbolClientes){
    string nombreArchivo = "Desktop/Archivos de prueba/ArchivosProgra2-Datos/Clientes.txt";

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

        int idCliente = stoi(id);

        // ... crear el nodo
        if ( _ArbolClientes->existeCliente(_ArbolClientes->raizB, idCliente)){
            continue;
        }else{
            cout <<"Codigo Cliente: "<< id << "," << nombre << "," << direccion << "," << telefono << endl;
            int intTelefono = stoi(telefono);
            _ArbolClientes->IniciarInsercionB(idCliente,idCliente,nombre,direccion,intTelefono);
        }
    }

    archivoEntrada.close();
}




int main() {
    cout << "Hello, World!" << std::endl;


    return 0;
}