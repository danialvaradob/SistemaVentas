
//#include "arbolsupermercados.h"
//#include "arbolclientes.h"
//#include "listalugares.h"
//#include "arbolproveedores.h"
//#include "server.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include "arbolproveedores.h"
#include "arbolclientes.h"
#include "arbolsupermercados.h"
#include "listalugares.h"
#include "listaventas.h"

//#include <iostream>
const int PRIMERA_VEZ = -1;
const int OPCION_VENTA = 1;
const int OPCION_PROVEEDOR_MAS_VENTAS = 2;
const int OPCION_CLIENTE_MAS_COMPRO = 3;
const int OPCION_PRODUCTO_MAS_VENDIDO = 4;
const int OPCION_PRODUCTOS_CAMBIARON_STOCK = 5;
const int OPCION_CATEGORIA_MAS_VENDIDA = 6;
const int OPCION_SUPERMERCADO_MAS_VENTAS = 7;
const int OPCION_LUGAR_CON_MAS_SUPERMERCADOS = 8;
const int OPCION_IMPRIMIR_ARBOL_PREORDEN = 9;
const int OPCION_ELIMINAR_PRODUCTO = 10;
const int OPCION_ELIMINAR_CLIENTE = 11;
const int OPCION_FACTURA = 12;
const int TAMANHO_BUFFER = 256;



void error(const char *msg) {
    perror(msg);
    exit(1);
}



std::string retrieveString( char* buf, int max ) {

    size_t len = 0;
    while( (len < max) && (buf[ len ] != '\0') ) {
        len++;
    }

    return std::string( buf, len );

}

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

        double precioPorUnidad = atof(precioPorUnidadSt.c_str());
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
        //_proveedores->InordenI(_proveedores->raiz);
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
        NodoCliente *_nuevo = new NodoCliente(idCliente, idCliente, nombre, direccion, intTelefono);
        _ArbolClientes->IniciarInsercionB(_nuevo);


    }
    archivoEntrada.close();
}

const int portno = 7777;


int main() {

/*

    ArbolProductos* AA = new ArbolProductos();

    AA->raiz = AA->insertar(AA->raiz,6,99,"K",10,10);
    AA->raiz = AA->insertar(AA->raiz,50,99,"K",10,10);
    AA->raiz = AA->insertar(AA->raiz,90,99,"K",10,10);
    AA->raiz = AA->insertar(AA->raiz,1,99,"K",10,10);
    AA->raiz = AA->insertar(AA->raiz,7,99,"K",10,10);

    AA->raiz = AA->borrar(AA->raiz,6);
    AA->raiz = AA->borrar(AA->raiz,50);

    std::string preorden;
    AA->PreordenSocket(AA->raiz,preorden);

*/



    ListaLugares* _listaLugares = new ListaLugares();
    leerArchLugares(_listaLugares);

    ArbolClientes *_arbolClientes = new ArbolClientes();
    leerArchClientes(_arbolClientes);

    ArbolProveedores* _arbolProveedores = new ArbolProveedores();
    leerArchProveedores(_arbolProveedores);

    ArbolSupermercados *_arbolSupermercados = new ArbolSupermercados();
    leerArchSupermercado(_arbolSupermercados,_listaLugares);
    leerArchCategorias(_arbolSupermercados);
    leerArchProductos(_arbolSupermercados);





    int codProveedor;
    std::cout << "\nDIGITE EL CODIGO DE PROVEEDOR: ";
    while (1) {
        std::cin >> codProveedor;
        if (_arbolProveedores->existeProveedor(codProveedor, _arbolProveedores->raiz)){
            std::cout << "Sistema ACTIVADO" << std::endl;
            break;
        }else {
            std::cout << "DIGITE UN PROVEEDOR VALIDO" << std::endl;
        }
    }

    ListaVentas* listaVentas = new  ListaVentas();

    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[TAMANHO_BUFFER];
    struct sockaddr_in serv_addr, cli_addr;
    long n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //portno = port; //atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);



    int bandera = PRIMERA_VEZ;
    int codSuper,codCat,codPro,cantidad,idCliente;
    std::string nombreCliente,dirCliente;

    bool banderaCLIENTENUEVO = false;

    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    while (1) {
        //bzero(buffer,TAMANHO_BUFFER);
        //n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);
        int codSuper,codCat,codPro;

        if (( memcmp( buffer, "END", strlen( "END"))) == 0) {
            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);
            n = write(newsockfd, "Proceso Terminado", strlen("Proceso Terminado"));
            break;
        }

        if (bandera == PRIMERA_VEZ) {
            //la primera vez entra aca para verificar el cliente, obtiene el ID del cliente
            //Si no esta se prepara para almacenar los datos
            //printf("Esto mando el usuario %s",buffer);
            banderaCLIENTENUEVO = false;

            for (int i = 0; i < 4; i++) {
                bzero(buffer, TAMANHO_BUFFER);
                n = read(newsockfd, buffer, TAMANHO_BUFFER - 1);
                if (i == 0) {

                    // registra el ID
                    //revisa si el cliente existe
                    //si existe continua y le agrega una compra
                    idCliente = atoi(buffer);
                    bool existeCliente = false;
                    _arbolClientes->existeCliente(_arbolClientes->raizB,idCliente,existeCliente);
                    if (existeCliente) {
                        std::cout << "ENTRO ACA" << std::endl;
                        char msgIdguardada[] = "CLIENTE EXISTE\nPorfavor digite la OPCION deseada";
                        write(newsockfd,msgIdguardada, strlen(msgIdguardada));
                        bandera = 0;
                        break;

                    }
                    // le agrega una compra al cliente
                    //  agregar compra al cliente
                    // agregarCompra(idCliente)
                    // break
                    //}

                    char msgIdguardada[] = "Identificacion guardada\nDigite su nombre para ser registrado ";
                    n = write(newsockfd,msgIdguardada, strlen(msgIdguardada));
                    banderaCLIENTENUEVO = true;



                }else if (i == 1) {
                    // registra el nombre
                    //transforma de caracter a str
                    //std::string nombreCliente(buffer);

                    nombreCliente.assign(buffer, buffer + 16);
                    //std::string strNombre(buffer, std::find(buffer,buffer + 16, '\n'));



                    //std::cout << nombreCliente << std::endl;

                    char msgNombreSavedDir[] = "Nombre guardado\nDigite su direecion";
                    n = write(newsockfd, msgNombreSavedDir, strlen(msgNombreSavedDir));

                }else if (i == 2) {
                    // registra la direccion

                    dirCliente.assign(buffer, buffer + 16);
                    n = write(newsockfd, "Direccion Guardada\nDigite su numero de telefono", strlen("Direccion Guardada\nDigite su numero de telefono"));

                }else if (i == 3) {
                    // registra el telefono
                    int telefonoCliente = atoi(buffer);
                    n = write(newsockfd, "CLIENTE GUARDADO\nDigite una opcion", strlen("CLIENTE GUARDADO\nDigite una opcion"));

                    //Agrega el cliente por completo con todos sus datos ya obtenidos
                    NodoCliente *nuevo = new NodoCliente(idCliente,idCliente,nombreCliente,dirCliente,telefonoCliente);
                    _arbolClientes->IniciarInsercionB(nuevo);


                }
                bandera = 0;

            }
        }else if (bandera == OPCION_VENTA) {
            //ArbolSupermercados *_arbolSupermercados = new ArbolSupermercados();
            ArbolCategorias *_arbolCategorias = new ArbolCategorias();
            ArbolProductos *_arbolProductos = new ArbolProductos();
            NodoSupermercado *_nodoSup = new NodoSupermercado();
            nodocategoria *_nodoCat = new nodocategoria();
            NodoProducto *_nodoProd = new NodoProducto();
            NodoProveedor *_nodoProv = new NodoProveedor();
            NodoCliente *_nodoCliente = new NodoCliente();

            //4 veces para poder obtener lo de la venta
            for (int i = 0; i < 4; i++) {


                bzero(buffer, TAMANHO_BUFFER);
                n = read(newsockfd, buffer, TAMANHO_BUFFER - 1);

                if (i == 0) {
                    //se esta tomando el codigo del Super
                    //
                    // Y se crean todos los nodos la primera vez para despues utilizarlos

                    codSuper = atoi(buffer);
                    if (!_arbolSupermercados->existeSupermercado(codSuper, _arbolSupermercados->raiz)) {
                        n = write(newsockfd, "El codigo de supermercado no existe\n",
                                  strlen("El codigo de supermercado no existe"));
                        break;
                    }

                    _arbolSupermercados->getNodoSupermercado(codSuper, _arbolSupermercados->raiz, _nodoSup);
                    char msgSuperR[] = "Codigo del Super recibido\nDigite el Codigo de Categoria";
                    n = write(newsockfd, msgSuperR, strlen(msgSuperR));

                } else if (i == 1) {

                    codCat = atoi(buffer);

                    _arbolSupermercados->getArbolCat(codSuper, _arbolSupermercados->raiz, _arbolCategorias);
                    if (!_arbolCategorias->existeCategoria(codCat, _arbolCategorias->raiz)) {
                        n = write(newsockfd, "El codigo de categoria no existe\n",
                                  strlen("El codigo de categoria no existe"));
                        break;
                    }
                    char msgCodR[] = "Codigo de Categoria recibido\nDigite el Codigo de Producto";
                    n = write(newsockfd, msgCodR, strlen(msgCodR));
                    _arbolCategorias->getNodoCat(_arbolCategorias->raiz, codCat, _nodoCat);

                } else if (i == 2) {

                    codPro = atoi(buffer);
                    _arbolCategorias->getArbolProd(_arbolCategorias->raiz, codCat, _arbolProductos);
                    if (!_arbolProductos->existeProducto(_arbolProductos->raiz, codPro)) {
                        n = write(newsockfd, "El codigo de producto no existe\n",
                                  strlen("El codigo de producto no existe"));
                        break;
                    }
                    char msgProductoR[] = "Codigo de Producto recibido\nDigite la cantidad que desea";
                    n = write(newsockfd, msgProductoR, strlen(msgProductoR));
                    _arbolProductos->getNodoProducto(codPro, _arbolProductos->raiz, _nodoProd);


                } else if (i == 3) {
                    cantidad = atoi(buffer);

                    if (cantidad <= _nodoProd->getCantidadEnStock()) {

                        _arbolProveedores->getNodoProveedor(codProveedor, _arbolProveedores->raiz, _nodoProv);
                        _arbolClientes->getCliente(_arbolClientes->raizB, _nodoCliente, idCliente);
                        _nodoCliente->aumentarVentas();
                        _nodoProv->aumentarVentas();
                        _nodoProd->setCantidadEnStock(cantidad);
                        _nodoCat->incBestScore();
                        _nodoSup->aumentarVentas();

                        if (banderaCLIENTENUEVO) {
                            NodoVenta *_nodoVenta = new NodoVenta(_nodoProv->getID(), _nodoProv->getNombre(),
                                                                  _nodoCliente->getID(),
                                                                  _nodoCliente->getNombre(), _nodoCat->getCodigo(),
                                                                  _nodoCat->getDesc(),
                                                                  _nodoProd->getCodigoProducto(),
                                                                  _nodoProd->getNombreProducto(),
                                                                  _nodoProd->getPrecioPorUnidad(), cantidad,
                                                                  _nodoProd->getPrecioPorUnidad() * cantidad);
                            listaVentas->insertar(_nodoVenta);

                        }else {


                            NodoVenta *_nodoVenta = new NodoVenta(_nodoProv->getID(), _nodoProv->getNombre(),
                                                                  _nodoCliente->getID(),
                                                                  _nodoCliente->getNombre(), _nodoCat->getCodigo(),
                                                                  _nodoCat->getDesc(),
                                                                  _nodoProd->getCodigoProducto(),
                                                                  _nodoProd->getNombreProducto(),
                                                                  _nodoProd->getPrecioPorUnidad(), cantidad,
                                                                  ((_nodoProd->getPrecioPorUnidad() * cantidad)) - (_nodoProd->getPrecioPorUnidad() * cantidad * 0.05));
                            listaVentas->insertar(_nodoVenta);
                        }

                        n = write(newsockfd, "VENTA REALIZADA", strlen("VENTA REALIZADA"));

                    } else {
                        char msgNo[] = "Venta NO realizada, porfavor digite una cantidad adecuada";
                        n = write(newsockfd, msgNo, strlen(msgNo));
                    }
                }
            }
            bandera = 0;

        }else if (bandera == OPCION_PROVEEDOR_MAS_VENTAS ) {
            //determina el Proveedor con mas ventas

            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

            //Entra en un ciclo donde determina el proveedor con mas ventas
            NodoProveedor* proveedorMasVentas = new NodoProveedor();
            _arbolProveedores->getNodoProveedorMasVentas(_arbolProveedores->raiz,proveedorMasVentas);

            std::string nombre = proveedorMasVentas->getNombre();
            std::vector<char> v(nombre.begin(), nombre.end());
            v.push_back('\0'); // Make sure we are null-terminated
            char* msgCodSR = &v[0];
            n = write(newsockfd, msgCodSR, strlen(msgCodSR));
            bandera = 0;
            //


        }else if (bandera == OPCION_CLIENTE_MAS_COMPRO) {
            //determina el Cliente con mas ventas
            bzero(buffer, TAMANHO_BUFFER);
            n = read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            NodoCliente* Clmascompro = new NodoCliente();
            _arbolClientes->getClienteMasCompras(_arbolClientes->raizB,Clmascompro);
            std::string nombre = Clmascompro->getNombre();
            std::vector<char> v(nombre.begin(), nombre.end());
            v.push_back('\0'); // Make sure we are null-terminated
            char* msgCodSR = &v[0];
            n = write(newsockfd, msgCodSR, strlen(msgCodSR));


            bandera = 0;



        }else if (bandera == OPCION_PRODUCTO_MAS_VENDIDO) {
            //determina el Producto con mas Ventas
            //bzero(buffer,TAMANHO_BUFFER);
            //n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);
            char msgNoExiste[] = "Codigo NO EXISTE";


            ArbolCategorias* arbolCategorias = new ArbolCategorias();
            ArbolProductos* arbolProductos = new ArbolProductos();


            for (int i = 0; i < 2; i++) {
                bzero(buffer,TAMANHO_BUFFER);
                n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

                if (i == 0 ) {
                    // ademas aca la primera vez, saca todos los nodos para asi revisarlos

                    codSuper = atoi(buffer);

                    //Verifica si existe dicho codigo
                    if (!_arbolSupermercados->existeSupermercado(codSuper, _arbolSupermercados->raiz)) {
                        char msgNoExiste[] = "Codigo NO EXISTE";
                        n = write(newsockfd,msgNoExiste, strlen(msgNoExiste));
                        break;
                    }

                    char msgSuperR[] = "Codigo del Super recibido\nDigite el Codigo de Categoria";
                    n = write(newsockfd, msgSuperR, strlen(msgSuperR));
                }else if ( i == 1) {



                    //aca es donde se van metiendo en los valores los codigos
                    codCat = atoi(buffer);
                    //

                    _arbolSupermercados->getArbolCat(codSuper,_arbolSupermercados->raiz,arbolCategorias);
                    //Verifica si existe dicho codigo
                    if (!arbolCategorias->existeCategoria(codCat,arbolCategorias->raiz)) {
                        n = write(newsockfd,msgNoExiste, strlen(msgNoExiste));
                        break;
                    }
                    /*
                    // aca pone
                    char msgCodR[] = "Codigo de Categoria recibido\nDigite el Codigo de Producto";
                    n = write(newsockfd, msgCodR, strlen(msgCodR));



                    //aca es donde se van metiendo en los valores los codigos
                    codPro = atoi(buffer);

                    //

                    arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);
                    if (!arbolProductos->existeProducto(arbolProductos->raiz,codPro)) {
                        n = write(newsockfd,msgNoExiste, strlen(msgNoExiste));
                        break;
                    }
                    */
                    arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);

                    NodoProducto* productoMasVendido = new NodoProducto();
                    arbolProductos->getProductoMasVendido(arbolProductos->raiz,productoMasVendido);

                    //productoMasVendido->

                    std::string nombre = productoMasVendido->getNombreProducto();
                    if (nombre != "") {
                        std::vector<char> v(nombre.begin(), nombre.end());
                        v.push_back('\0'); // Make sure we are null-terminated
                        char* productoCh = &v[0];
                        n = write(newsockfd,productoCh , strlen(productoCh));
                    } else {
                        n = write(newsockfd,"No se han comprado productos", strlen("No se han comprado productos"));
                    }



                }



            }
            bandera = 0;


//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
        } else if (bandera == OPCION_PRODUCTOS_CAMBIARON_STOCK) {
            //Productos que cambiaron el stock

            ArbolCategorias *arbolCategorias = new ArbolCategorias();
            ArbolProductos *arbolProductos = new ArbolProductos();
            //NodoSupermercado *_nodoSup = new NodoSupermercado();
           //NodoProducto *_nodoProd = new NodoProducto();

            char msgNoExiste[] = "Codigo NO EXISTE";

            for (int i = 0; i < 2; i++) {
                bzero(buffer,TAMANHO_BUFFER);
                n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

                codCat = 0;
                if (i == 0 ) {

                    //existe
                    codSuper = atoi(buffer);

                    //Verifica si existe dicho codigo
                    if (!_arbolSupermercados->existeSupermercado(codSuper, _arbolSupermercados->raiz)) {
                        n = write(newsockfd,msgNoExiste, strlen(msgNoExiste));
                        break;
                    }

                    char msgSuperR[] = "Codigo del Super recibido\nDigite el Codigo de Categoria";
                    n = write(newsockfd, msgSuperR, strlen(msgSuperR));


                }else if ( i == 1) {



                    //aca es donde se van metiendo en los valores los codigos
                    //codCat = atoi(buffer);
                    codCat = atoi(buffer);
                    //
                    _arbolSupermercados->getArbolCat(codSuper,_arbolSupermercados->raiz,arbolCategorias);
                    //Verifica si existe dicho codigo
                    if (!arbolCategorias->existeCategoria(codCat,arbolCategorias->raiz)) {
                        n = write(newsockfd,msgNoExiste, strlen(msgNoExiste));
                        break;
                    }
                    // aca pone
                    //char msgCodR[] = "Codigo de Categoria recibido\nDigite el Codigo de Producto";
                    //n = write(newsockfd, msgCodR, strlen(msgCodR));




                    //aca es donde se van metiendo en los valores los codigos
                    //codPro = atoi(buffer);
                    //n = write(newsockfd, "Codigo de Producto recibido\n", strlen("Codigo de Producto recibido\n"));
                    //arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);
                    //if (!arbolProductos->existeProducto(arbolProductos->raiz,codPro)) {
                    //    n = write(newsockfd,msgNoExiste, strlen(msgNoExiste));
                    //    break;
                    //}
                    arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);

                    std::string productosCambiaronStock = "";
                    arbolProductos->getProductosCambiaronStock(arbolProductos->raiz,productosCambiaronStock);
                    std::cout << productosCambiaronStock << std::endl;

                    std::vector<char> v(productosCambiaronStock.begin(), productosCambiaronStock.end());
                    v.push_back('\0'); // Make sure we are null-terminated
                    char* msgCodSR = &v[0];
                    n = write(newsockfd, msgCodSR, strlen(msgCodSR));


                }
                bandera = 0;

            }



        }else if (bandera == OPCION_CATEGORIA_MAS_VENDIDA) {
            ArbolCategorias *_arbolCategorias = new ArbolCategorias();
            nodocategoria *_nodoCat = new nodocategoria();
            //OBTENER CATEGORIA MAS VENDIDA

            for (int i = 0; i < 1; i++) {
                bzero(buffer,TAMANHO_BUFFER);
                n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

                if (i == 0 ) {
                    // ademas aca la primera vez, saca todos los nodos para asi revisarlos

                    //verifica que existe
                    codSuper = atoi(buffer);
                    if(!_arbolSupermercados->existeSupermercado(codSuper, _arbolSupermercados->raiz)){
                        n = write(newsockfd, "Error en el codigo de Supermercado\n", strlen("Error en el codigo de Supermercado\n"));
                    }
                    _arbolSupermercados->getCatMasVendidaS(_arbolSupermercados->raiz, codSuper, _nodoCat);
                    std::string nombre = _nodoCat->getDesc();
                    std::vector<char> v(nombre.begin(), nombre.end());
                    v.push_back('\0'); // Make sure we are null-terminated
                    char* msgCodSR = &v[0];
                    n = write(newsockfd, msgCodSR, strlen(msgCodSR));
                }
            }
            bandera = 0;





        }else if (bandera == OPCION_SUPERMERCADO_MAS_VENTAS) {
            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);
            //Supermercado con mas ventas
            //NodoSupermercado* supermercado = new NodoSupermercado()

            NodoSupermercado* supermercado = new NodoSupermercado();
            _arbolSupermercados->getSuperMasVendido(_arbolSupermercados->raiz,supermercado);


            std::string nombre = supermercado->getNombre();
            std::vector<char> v(nombre.begin(), nombre.end());
            v.push_back('\0'); // Make sure we are null-terminated
            char* msgCodSR = &v[0];
            n = write(newsockfd, msgCodSR, strlen(msgCodSR));


            bandera = 0;


        }else if (bandera == OPCION_LUGAR_CON_MAS_SUPERMERCADOS) {
            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);
            NodoLugar* lugar = new NodoLugar();
            _listaLugares->getLugarMasSuper(lugar);
            std::string nombre = lugar->getNombre();
            std::vector<char> v(nombre.begin(), nombre.end());
            v.push_back('\0'); // Make sure we are null-terminated
            char* msgCodSR = &v[0];
            n = write(newsockfd, msgCodSR, strlen(msgCodSR));

            bandera = 0;

        }else if (bandera == OPCION_ELIMINAR_PRODUCTO) {


            ArbolCategorias* arbolCategorias = new ArbolCategorias();
            ArbolProductos* arbolProductos = new ArbolProductos();
            //NodoProducto* productoEliminar = new NodoProducto();

            char msgNoExiste[] = "Codigo NO EXISTE";
            for (int i = 0; i < 4; i++) {
                bzero(buffer,TAMANHO_BUFFER);
                n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);
                if (i == 0) {
                    // ademas aca la primera vez, saca todos los nodos para asi revisarlos


                    //funcion que verifica el codigo del super


                    //existe
                    codSuper = atoi(buffer);

                    //Verifica si existe dicho codigo
                    if (!_arbolSupermercados->existeSupermercado(codSuper,_arbolSupermercados->raiz)) {
                        n = write(newsockfd, msgNoExiste, strlen(msgNoExiste));
                        bandera = 0;
                        break;
                    }

                    char msgSuperR[] = "Codigo del Super recibido\nDigite el Codigo de Categoria";
                    n = write(newsockfd, msgSuperR, strlen(msgSuperR));

                } else if (i == 1) {



                    //aca es donde se van metiendo en los valores los codigos
                    codCat = atoi(buffer);
                    //

                    //_arbolSupermercados->getArbolCat(codSuper, _arbolSupermercados->raiz, arbolCategorias);
                    //Verifica si existe dicho codigo
                    _arbolSupermercados->getArbolCat(codSuper, _arbolSupermercados->raiz, arbolCategorias);
                    if (!arbolCategorias->existeCategoria(codCat, arbolCategorias->raiz)) {
                        n = write(newsockfd, "El codigo de categoria no existe\n",
                                  strlen("El codigo de categoria no existe"));
                        bandera = 0;
                        break;
                    }

                    // aca pone
                    //_arbolSupermercados->getArbolCat(codSuper, _arbolSupermercados->raiz, arbolCategorias);
                    char msgCodR[] = "Codigo de Categoria recibido\nDigite el Codigo de Producto";
                    n = write(newsockfd, msgCodR, strlen(msgCodR));

                } else if (i == 2) {

                    //aca es donde se van metiendo en los valores los codigos
                    codPro = atoi(buffer);

                    if (!arbolCategorias->existeProducto(codPro, codCat, arbolCategorias->raiz)) {
                        n = write(newsockfd, msgNoExiste, strlen(msgNoExiste));
                        bandera = 0;
                        break;

                    }

                    char msgAccept[] = "Codigo de Producto recibido\nDesea ELIMINAR el producto? (S/N)\n";

                    n = write(newsockfd, msgAccept, strlen(msgAccept));

                    //
                    //ArbolProductos* arbolProductos = new ArbolProductos()
                    //arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);
                    //NodoProducto productoEliminar = new NodoProducto();
                    //arbolProductos->
                    //

                } else if (i == 3) {
                    if ((memcmp(buffer, "S", strlen("S"))) == 0) {
                        //productoEliminar
                        arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);
                        //arbolProductos->eliminarProducto(codPro)
                        //arbolProductos->getNodoProducto(codPro ,arbolProductos->raiz,productoEliminar);


                        //arbolProductos->eliminar(arbolProductos->raiz,codPro);

                        //arbolProductos->raiz = arbolProductos->eliminar(arbolProductos->raiz,codPro);

                        arbolProductos->raiz = arbolProductos->borrar(arbolProductos->raiz,codPro);


                        char msgEliminadoP[] = "El producto fue ELIMINADO con exito\n";
                        n = write(newsockfd, msgEliminadoP, strlen(msgEliminadoP));

                        //

                    } else {
                        char msgNoEliminado[] = "El produco NO fue eliminado\n";
                        n = write(newsockfd, msgNoEliminado, strlen(msgNoEliminado));
                        bandera = 0;
                        break;

                    }


                }
                bandera = 0;

            }


        }else if (bandera == OPCION_ELIMINAR_CLIENTE) {
            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

            int codCliente = atoi(buffer);

            //_arbolClientes->Eliminar(codCliente,_arbolClientes->raizB);
            char msgClienteElim[] = "NO FUNCIONA";
            n = write(newsockfd, msgClienteElim, strlen(msgClienteElim));

            bandera = 0;


        }else if (bandera == OPCION_IMPRIMIR_ARBOL_PREORDEN) {

            //COMPARA TODOS
            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);


            if ((memcmp(buffer, "1", strlen("1"))) == 0) {
                std::string nombre = "Arbol de Supermercados: \n";
                _arbolSupermercados->PreordenSocket(_arbolSupermercados->raiz, nombre);
                std::vector<char> v(nombre.begin(), nombre.end());
                v.push_back('\0'); // Make sure we are null-terminated
                char *msgCodSR = &v[0];
                n = write(newsockfd, msgCodSR, strlen(msgCodSR));
                std::cout << nombre << std::endl;
                //char msgCodClientPreorden[] = "REVISAR SERVIDOR";
                //write(newsockfd, msgCodClientPreorden, strlen(msgCodClientPreorden));


            } else if ((memcmp(buffer, "2", strlen("1"))) == 0) {
                ArbolCategorias *_arbolCategorias;
                n = write(newsockfd, "Digite el codigo de Supermercado: \n", strlen("Digite el codigo de Supermercado: \n"));
                for (int i = 0; i < 1; i++) {
                    bzero(buffer, TAMANHO_BUFFER);
                    n = read(newsockfd, buffer, TAMANHO_BUFFER - 1);

                    if (i == 0) {
                        //verifica que existe
                        codSuper = atoi(buffer);
                        if (!_arbolSupermercados->existeSupermercado(codSuper, _arbolSupermercados->raiz)) {
                            n = write(newsockfd, "Error en el codigo de Supermercado\n",
                                      strlen("Error en el codigo de Supermercado\n"));
                            break;
                        }
                        std::string nombre = "Arbol de Categorias: \n";;
                        _arbolSupermercados->getArbolCat(codSuper, _arbolSupermercados->raiz, _arbolCategorias);
                        _arbolCategorias->PreordenSocket(_arbolCategorias->raiz, nombre);
                        std::vector<char> v(nombre.begin(), nombre.end());
                        v.push_back('\0'); // Make sure we are null-terminated
                        char *msgCodCatPreorden = &v[0];
                        n = write(newsockfd, msgCodCatPreorden, strlen(msgCodCatPreorden));
                        std::cout << nombre << std::endl;

                        //char msgCodClientPreorden[] = "REVISAR SERVIDOR";
                        //write(newsockfd, msgCodClientPreorden, strlen(msgCodClientPreorden));

                    }
                }

            } else if ((memcmp(buffer, "3", strlen("1"))) == 0) {
                ArbolCategorias *_arbolCategorias;
                ArbolProductos *_arbolProductos;
                n = write(newsockfd, "Digite el codigo de Supermercado: \n", strlen("Digite el codigo de Supermercado: \n"));
                for (int i = 0; i <= 1; i++) {
                    bzero(buffer, TAMANHO_BUFFER);
                    n = read(newsockfd, buffer, TAMANHO_BUFFER - 1);

                    if (i == 0) {
                        codSuper = atoi(buffer);
                        //verifica que existe el codigo de super
                        if (!_arbolSupermercados->existeSupermercado(codSuper, _arbolSupermercados->raiz)) {
                            n = write(newsockfd, "Error en el codigo de Supermercado\n", strlen("Error en el codigo de Supermercado\n"));
                            break;
                        }
                        _arbolSupermercados->getArbolCat(codSuper, _arbolSupermercados->raiz, _arbolCategorias);
                        n = write(newsockfd, "Codigo de supermercado valido\nDigite el codigo de Categoria:", strlen("Codigo de supermercado valido\nDigite el codigo de Categoria:"));


                    }else if(i == 1){
                        codCat = atoi(buffer);
                        //verifica que existe el codigo de categoria
                        if(!_arbolCategorias->existeCategoria(codCat, _arbolCategorias->raiz)){
                            n = write(newsockfd, "Error en el codigo de Categoria\n", strlen("Error en el codigo de Categoria\n"));
                            break;
                        }
                        std::string nombre = "Arbol de productos: \n";
                        _arbolCategorias->getArbolProd(_arbolCategorias->raiz, codCat, _arbolProductos);
                        _arbolProductos->PreordenSocket(_arbolProductos->raiz, nombre);
                        std::vector<char> v(nombre.begin(), nombre.end());
                        v.push_back('\0'); // Make sure we are null-terminated
                        char *msgCodProdPreorden = &v[0];
                        n = write(newsockfd, msgCodProdPreorden, strlen(msgCodProdPreorden));
                        std::cout << nombre << std::endl;
                        //std::cout << nombre << std::endl;

                        //char msgCodClientPreorden[] = "REVISAR SERVIDOR";
                        //write(newsockfd, msgCodClientPreorden, strlen(msgCodClientPreorden));

                    }
                }

            } else if ((memcmp(buffer, "4", strlen("1"))) == 0) {
                std::string nombre = "Arbol de Clientes: \n";
                _arbolClientes->PreordenSocket(_arbolClientes->raizB, nombre);
                //std::vector<char> v(nombre.begin(), nombre.end());
                //v.push_back('\0'); // Make sure we are null-terminated
                //char *msgCodClientPreorden = &v[0];
                //n = write(newsockfd, msgCodClientPreorden, strlen(msgCodClientPreorden));
                std::cout << nombre << std::endl;

                char msgCodClientPreorden[] = "REVISAR SERVIDOR";
                write(newsockfd, msgCodClientPreorden, strlen(msgCodClientPreorden));


            } else if ((memcmp(buffer, "5", strlen("1"))) == 0) {
                std::string nombre = "Arbol de Proveedores: \n";
                _arbolProveedores->PreordenSocket(_arbolProveedores->raiz, nombre);
                std::vector<char> v(nombre.begin(), nombre.end());
                v.push_back('\0'); // Make sure we are null-terminated
                char *msgCodProvPreorden = &v[0];
                n = write(newsockfd, msgCodProvPreorden, strlen(msgCodProvPreorden));
                std::cout << nombre << std::endl;
            }
            bandera = 0;



        }else if(bandera == OPCION_FACTURA) {
            if(!listaVentas->listaVacia()){
                listaVentas->crearFactura();
                n = write(newsockfd, "FACTURA CREADA\n", strlen("FACTURA CREADA\n"));
            }else{
                n = write(newsockfd, "No hay ventas para facturar\n", strlen("No hay ventas para facturar\n"));
                break;
            }
            bandera = 0;

        }else{

            /* newsockfd = accept(sockfd,
                               (struct sockaddr *) &cli_addr,
                               &clilen);
            */

            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

            if (( memcmp( buffer, "END", strlen( "END"))) == 0 )  {
                n = write(newsockfd, "Proceso Terminado", strlen("Proceso Terminado"));
                break;

            }else if (( memcmp( buffer, "10", strlen( "10"))) == 0 ) {

                char msgEliminarPro[] = "ELIMINANDO PRODUCTO\nDigite el codigo del super";
                n = write(newsockfd, msgEliminarPro, strlen(msgEliminarPro));


                bandera = OPCION_ELIMINAR_PRODUCTO;

            }else if (( memcmp( buffer, "11", strlen( "11"))) == 0 ) {
                char msgEliminarCl[] = "ELIMINANDO CLIENTE\nDigite el codigo del cliente";
                n = write(newsockfd, msgEliminarCl, strlen(msgEliminarCl));

                bandera = OPCION_ELIMINAR_CLIENTE;



            }else if(( memcmp( buffer, "12", strlen( "12"))) == 0 ){
                char msgFact[] = "CREANDO FACTURA\n";
                n = write(newsockfd, msgFact, strlen(msgFact));

                bandera = OPCION_FACTURA;

            }else if (( memcmp( buffer, "1", strlen( "1"))) == 0 )  {

                //
                char msgVenta[] = "ESPERANDO VENTA\nDigite el codigo del super";
                n = write(newsockfd, msgVenta, strlen(msgVenta));
                bandera = OPCION_VENTA;

            }else if (( memcmp( buffer, "2", strlen( "2"))) == 0 ) {
                //proveedor con mas ventas
                //n = write(newsockfd, "ESPERANDO VENTA", strlen("ESPERANDO VENTA"));
                char msgPROVEE[] = "PROVEEDOR CON MAS VENTAS\nDigite ok";
                n = write(newsockfd, msgPROVEE, strlen(msgPROVEE));

                bandera = OPCION_PROVEEDOR_MAS_VENTAS;


            }else if (( memcmp( buffer, "3", strlen( "3"))) == 0 ) {
                //Cliente que mas compro
                //getCliente
                char msgCMC[] = "CLIENTE QUE MAS COMPRO\nDigite OK";
                n = write(newsockfd, msgCMC, strlen(msgCMC));

                bandera = OPCION_CLIENTE_MAS_COMPRO;




            }else if (( memcmp( buffer, "4", strlen( "4"))) == 0 ) {
                //Producto mas vendido neceista cod del super y de la categoria
                char msgPMV[] = "PRODUCTO MAS VENDIDO\nDigite el codigo del super";
                n = write(newsockfd, msgPMV, strlen(msgPMV));

                bandera = OPCION_PRODUCTO_MAS_VENDIDO;

            }else if (( memcmp( buffer, "5", strlen( "5"))) == 0 ) {
                //Productos que el stock
                char msgPQBS[] = "PRODUCTOS QUE BAJARON STOCK\nDigite el codigo del super";
                n = write(newsockfd,msgPQBS, strlen(msgPQBS));
                bandera = OPCION_PRODUCTOS_CAMBIARON_STOCK;


            }else if (( memcmp( buffer, "6", strlen( "6"))) == 0 ) {
                //Categoria mas vendid
                char msgCMV[] = "CATEGORIA MAS VENDIDA\nDigite el codigo del super";
                n = write(newsockfd, msgCMV, strlen(msgCMV));
                bandera = OPCION_CATEGORIA_MAS_VENDIDA;

            }else if (( memcmp( buffer, "7", strlen( "7"))) == 0 ) {
                //Supermercado con mas ventas
                char msgSUPER[] = "SUPERMERCADO CON MAS VENTAS\nDigite ok";
                n = write(newsockfd, msgSUPER, strlen(msgSUPER));
                bandera = OPCION_SUPERMERCADO_MAS_VENTAS;

            }else if (( memcmp( buffer, "8", strlen( "8"))) == 0 ) {
                //lugar con mas supermercados
                char msgLUGARMS[] = "LUGAR CON MAS SUPERMERADOS\nDigite ok";
                n = write(newsockfd, msgLUGARMS, strlen(msgLUGARMS));
                bandera = OPCION_LUGAR_CON_MAS_SUPERMERCADOS;

            }else if (( memcmp( buffer, "9", strlen( "9"))) == 0 ) {
                //Determina arbol que desea imprimir

                char msgPreorden[] = "Digite 1 si desea un arbol de supermercados\nDigite 2 si desea un arbol de categorias\n"
                        "Digite 3 si desea un arbol de productos\nDigite 4 si desea un arbol de clientes\n"
                        "Digite 5 si desea un arbol de proveedores\n";
                n = write(newsockfd,msgPreorden, strlen(msgPreorden));

                bandera = OPCION_IMPRIMIR_ARBOL_PREORDEN;


            }else if (( memcmp( buffer, "CAMBIAR", strlen( "CAMBIAR"))) == 0 ) {
                char msgCambiarCliente[] = "Porfavor digite el nuevo ID";
                n = write(newsockfd,msgCambiarCliente, strlen(msgCambiarCliente));

                bandera = PRIMERA_VEZ;


            }else {
                n = write(newsockfd, "OTRO", strlen("OTRO"));
            }

            //close(newsockfd);
        }



    }
    close(newsockfd);
    close(sockfd);

    return 0;



}





/*


int main() {


    ListaLugares *listaLugares = new ListaLugares();
    leerArchLugares(listaLugares);

    ArbolClientes *arbolClientes = new ArbolClientes();
    leerArchClientes(arbolClientes);
    //arbolClientes->RecorridoInordenB(arbolClientes->raizB);

    ArbolProveedores *arbolProveedores = new ArbolProveedores();
    leerArchProveedores(arbolProveedores);

    ArbolSupermercados *arbolSupermercados = new ArbolSupermercados();
    leerArchSupermercado(arbolSupermercados, listaLugares);

    leerArchCategorias(arbolSupermercados);

    leerAarchProductos(arbolSupermercados);

    //socketMain(arbolSupermercados,arbolProveedores,arbolClientes,listaLugares);

    //socketServer(arbolSupermercados,arbolProveedores,arbolClientes,listaLugares);

    //arbolClientes->RecorridoInordenB(arbolClientes->raizB);
    //leerArchProductos(arbolSupermercados);

    //PRUEBAS
    ArbolCategorias *AC = new ArbolCategorias();
    arbolSupermercados->getArbolCat(66, arbolSupermercados->raiz, AC);
    AC->raiz->incBestScore();

    ArbolCategorias *PAC = new ArbolCategorias();
    arbolSupermercados->getArbolCat(66, arbolSupermercados->raiz, PAC);
    //int SCORE = PAC->raiz->getBestScore();


    nodocategoria *nodocate = new nodocategoria();
    PAC->getNodoCat(PAC->raiz, 45, nodocate);

    arbolClientes->RecorridoInordenB(arbolClientes->raizB);


    return 0;
}

*/
