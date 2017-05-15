
#include "arbolsupermercados.h"
#include "arbolclientes.h"
#include "listalugares.h"
#include "arbolproveedores.h"
#include <fstream>
//#include "server.cpp"



//// PARA PRUEBA A VER SI REGISTRA BIEN UN PRODUCTO
void leerArchProductos(ArbolSupermercados* _supermercados) {

    std::string nombreArchivo = "Productos.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string codSuper(std::strtok (lineaValores, ";"));
        std::string codigoCategoria(std::strtok (NULL, ";"));
        std::string codigoProducto(std::strtok (NULL, ";"));
        std::string nombreProducto(std::strtok (NULL, ";"));

        std::string precioPorUnidadSt(std::strtok (NULL, ";"));
        std::string cantidadEnStockSt(std::strtok (NULL, ";"));

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

            std::cout <<codigoProducto << "," << codigoCategoria << "," << nombreProducto<< "," << precioPorUnidadSt<< ","
                      << cantidadEnStockSt << std::endl;
            //_categoria->insertarProducto(codigoProducto, codigoCategoria, nombreProducto, precioPorUnidad, cantidadEnStock);
            _supermercados->agregarProducto(_supermercados->raiz,codSupI,codCatI,codProI,nombreProducto, precioPorUnidad,
                                            cantidadEnStock);

        }
    }
    archivoEntrada.close();


}


void leerArchCategorias(ArbolSupermercados* _supermercados) {
    std::string nombreArchivo = "Categorias.txt";
    std::ifstream file;
    std::string lineaEnArchivo;
    int codigo;
    int codigoSup;
    int cont = 0;
    file.open(nombreArchivo,std::ios::in);
    if (file.fail()) {
        std::cout << "Unable to open file";
    }else{
        while(file>>lineaEnArchivo){
            char *valorEnLinea = new char[lineaEnArchivo.length()+1];
            strcpy(valorEnLinea, lineaEnArchivo.c_str());

            std::string _codigoSup(std::strtok (valorEnLinea, ";") );
            codigoSup = atoi(_codigoSup.c_str());
            std::string _codigo(std::strtok (NULL, ";") );
            codigo = atoi(_codigo.c_str());
            std::string descripcion(std::strtok (NULL, ";") );
            //nodocategoria *nuevo = new nodocategoria(codigo, descripcion);

            if(cont==0){
                //arbolCategorias->insertarValorNodoRN(codigo, descripcion);
                _supermercados->agregarCategoria(_supermercados->raiz,codigoSup,codigo,descripcion);
                cont++;
                std::cout << "primera vez" << std::endl;

            }else{
                if(!_supermercados->existeCategoria(codigoSup,codigo,_supermercados->raiz)) {
                    _supermercados->agregarCategoria(_supermercados->raiz,codigoSup,codigo,descripcion);
                    std::cout <<"Codigo Categoria: "<< _codigo << "," << descripcion << std::endl;
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
    std::string nombreArchivo = "Supermercados.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string codSuper(std::strtok (lineaValores, ";"));
        std::string codLugar(std::strtok (NULL, ";"));
        std::string nombre(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;

        int codSint = atoi(codSuper.c_str());
        int codLint = atoi(codLugar.c_str());
        if (_supermercado->existeSupermercado(codSint,_supermercado->raiz)) {
            std::cout << "Supermercado ya existe, codigo: " << codSuper << std::endl;
            continue;
        }else{
            std::cout << "Codigo Supermercado: " << codSuper << " Nombre: "<< nombre << std::endl;
            //std::cout << "Codigo LUGAR: " << codLugar << std::endl;
            //_supermercado->insertarNodoSupermercado(codSint,codLint,nombre);

            _supermercado->insertarBalanceado(_supermercado->raiz, Hh,codSint,codLint,nombre);
            _lugares->aumentarCantidadDeSupermercados(codLint);
        }
    }
    archivoEntrada.close();


}



void leerArchProveedores(ArbolProveedores * _proveedores){
    std::string nombreArchivo = "Proveedores.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string id(std::strtok (lineaValores, ";"));
        std::string nombre(std::strtok (NULL, ";"));
        std::string direccion(std::strtok (NULL, ";"));
        std::string telefono(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;

        int idProveedor = atoi(id.c_str());
        int intTel = atoi(telefono.c_str());
        //cout << "COMENZANDO A EVALUAR" << endl;
        _proveedores->InordenI(_proveedores->raiz);
        if (_proveedores->existeProveedor(idProveedor,_proveedores->raiz)) {
            std::cout << "Proveedor ya existe, codigo: " << id << std::endl;
            continue;
        }else{
            std::cout << "Codigo Proveedor: " << id << " Nombre: "<< nombre << std::endl;
            //NodoProveedor* nodoProveedor = new NodoProveedor(idProveedor,nombre,direccion,intTel);
            _proveedores->insertarNodoProveedor(idProveedor,nombre,direccion,intTel);
        }
    }
    archivoEntrada.close();

}

void leerArchLugares(ListaLugares * _lugares){
    std::string nombreArchivo = "Lugares.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string id(std::strtok (lineaValores, ";"));
        std::string nombre(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;
        int codigoL = atoi(id.c_str());


        if (_lugares->existeLugar(codigoL))
            continue;
        else{
            std::cout << "Codigo Lugares: " << id << std::endl;
            _lugares->insertarLugar(codigoL,nombre);
        }
    }
    archivoEntrada.close();
    std::cout << _lugares->largoLista() << std::endl;
}


void leerArchClientes(ArbolClientes * _ArbolClientes){
    std::string nombreArchivo = "Clientes.txt";
    std::cout << "entro" << std::endl;

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo) {
        char *lineaValores = new char[lineaEnArchivo.length() + 1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string id(std::strtok(lineaValores, ";"));
        std::string nombre(std::strtok(NULL, ";"));
        std::string direccion(std::strtok(NULL, ";"));
        std::string telefono(std::strtok(NULL, ";"));

        int idCliente = atoi(id.c_str());

        // ... crear el nodo

        std::cout << "Codigo Cliente: " << id << "," << nombre << "," << direccion << "," << telefono << std::endl;
        int intTelefono = atoi(telefono.c_str());

        _ArbolClientes->IniciarInsercionB(idCliente, idCliente, nombre, direccion, intTelefono);


    }
    archivoEntrada.close();
}







int main() {



    ListaLugares* listaLugares = new ListaLugares();
    //leerArchLugares(listaLugares);

    ArbolClientes *arbolClientes = new ArbolClientes();
    //leerArchClientes(arbolClientes);
    //arbolClientes->RecorridoInordenB(arbolClientes->raizB);

    ArbolProveedores* arbolProveedores = new ArbolProveedores();
    leerArchProveedores(arbolProveedores);

    ArbolSupermercados *arbolSupermercados = new ArbolSupermercados();
    //leerArchSupermercado(arbolSupermercados,listaLugares);

    //leerArchCategorias(arbolSupermercados);

    //leerArchProductos(arbolSupermercados);

    //socketMain(arbolSupermercados,arbolProveedores,arbolClientes,listaLugares);


    //arbolClientes->RecorridoInordenB(arbolClientes->raizB);
    //leerArchProductos(arbolSupermercados);

    //PRUEBAS
/*
    ArbolCategorias* AC = new ArbolCategorias();
    arbolSupermercados->getArbolCat(66,arbolSupermercados->raiz,AC);
    AC->raiz->incBestScore();

    ArbolCategorias* PAC = new ArbolCategorias();
    arbolSupermercados->getArbolCat(66,arbolSupermercados->raiz,PAC);
    //int SCORE = PAC->raiz->getBestScore();


    nodocategoria* nodocate = new nodocategoria();
    PAC->getNodoCat(PAC->raiz,45,nodocate);
*/




    return 0;
}