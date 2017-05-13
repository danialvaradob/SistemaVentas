#include <iostream>
#include "arbolsupermercados.h"
#include "arbolclientes.h"
#include "listalugares.h"
#include "arbolproveedores.h"
#include <fstream>
#include <cstring>

using namespace std;


//// PARA PRUEBA A VER SI REGISTRA BIEN UN PRODUCTO
void leerArchProductos(ArbolSupermercados* _supermercados) {

    string nombreArchivo = "Productos.txt";

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
        string codigoCategoria(std::strtok (NULL, ";"));
        string codigoProducto(std::strtok (NULL, ";"));
        string nombreProducto(std::strtok (NULL, ";"));

        string precioPorUnidadSt(std::strtok (NULL, ";"));
        string cantidadEnStockSt(std::strtok (NULL, ";"));

        int codProI = atoi(codigoProducto.c_str());
        int codCatI = atoi(codigoCategoria.c_str());
        int codSupI = atoi(codSuper.c_str());

        float precioPorUnidad = atof(precioPorUnidadSt.c_str());
        int cantidadEnStock = atoi(cantidadEnStockSt.c_str());


        ArbolCategorias* arbolCategorias = new ArbolCategorias();
        _supermercados->getArbolCat(codSupI,_supermercados->raiz,arbolCategorias);

        ArbolProductos* productos = new ArbolProductos();
        arbolCategorias->getArbolProd(arbolCategorias->raiz,codCatI,productos);

        // ... crear el nodo
        if (productos != NULL && productos->existeProducto(productos->raiz,codProI)){
            continue;
        }else{

            cout <<codigoProducto << "," << codigoCategoria << "," << nombreProducto<< "," << precioPorUnidadSt<< ","
                << cantidadEnStockSt << endl;
            //_categoria->insertarProducto(codigoProducto, codigoCategoria, nombreProducto, precioPorUnidad, cantidadEnStock);
            _supermercados->agregarProducto(_supermercados->raiz,codSupI,codCatI,codProI,nombreProducto, precioPorUnidad,
                                            cantidadEnStock);

        }
    }
    archivoEntrada.close();


}


void leerArchCategorias(ArbolSupermercados* _supermercados) {
    string nombreArchivo = "Categorias.txt";
    ifstream file;
    string lineaEnArchivo;
    int codigo;
    int codigoSup;
    int cont = 0;
    file.open(nombreArchivo,ios::in);
    if (file.fail()) {
        cout << "Unable to open file";
    }else{
        while(file>>lineaEnArchivo){
            char *valorEnLinea = new char[lineaEnArchivo.length()+1];
            strcpy(valorEnLinea, lineaEnArchivo.c_str());

            string _codigoSup(std::strtok (valorEnLinea, ";") );
            codigoSup = atoi(_codigoSup.c_str());
            string _codigo(std::strtok (NULL, ";") );
            codigo = atoi(_codigo.c_str());
            string descripcion(std::strtok (NULL, ";") );
            //nodocategoria *nuevo = new nodocategoria(codigo, descripcion);

            if(cont==0){
                //arbolCategorias->insertarValorNodoRN(codigo, descripcion);
                _supermercados->agregarCategoria(_supermercados->raiz,codigoSup,codigo,descripcion);
                cont++;
                cout << "primera vez" << endl;

            }else{
                if(!_supermercados->existeCategoria(codigoSup,codigo,_supermercados->raiz)) {
                    _supermercados->agregarCategoria(_supermercados->raiz,codigoSup,codigo,descripcion);
                    cout <<"Codigo Categoria: "<< _codigo << "," << descripcion << endl;
                    cont++;
                }
            }
        }
        //leerArchProductos("Productos.txt");
    }
    file.close();

}


void leerArchSupermercado(ArbolSupermercados * _supermercado, ListaLugares* _lugares){
    bool Hh = false;
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
            //_supermercado->insertarNodoSupermercado(codSint,codLint,nombre);

            _supermercado->insertarBalanceado(_supermercado->raiz, Hh,codSint,codLint,nombre);
            _lugares->aumentarCantidadDeSupermercados(codLint);
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
    ListaLugares* listaLugares = new ListaLugares();
    leerArchLugares(listaLugares);

    ArbolClientes *arbolClientes = new ArbolClientes();
    //leerArchClientes(arbolClientes);

    ArbolProveedores* arbolProveedores = new ArbolProveedores();
    //leerArchProveedores(arbolProveedores);

    ArbolSupermercados *arbolSupermercados = new ArbolSupermercados();
    leerArchSupermercado(arbolSupermercados,listaLugares);

    leerArchCategorias(arbolSupermercados);

    //arbolClientes->RecorridoInordenB(arbolClientes->raizB);
    leerArchProductos(arbolSupermercados);

    //PRUEBAS
/*
    ArbolCategorias* AC = new ArbolCategorias();
    arbolSupermercados->getArbolCat(66,arbolSupermercados->raiz,AC);
    AC->raiz->incBestScore();

    ArbolCategorias* PAC = new ArbolCategorias();
    arbolSupermercados->getArbolCat(66,arbolSupermercados->raiz,PAC);
    int SCORE = PAC->raiz->getBestScore();

*/


    cout << "Hello, World!" << endl;


    return 0;
}