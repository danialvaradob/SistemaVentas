// Created by Daniel Alvarado on 5/13/17.
//
//
//  main.cpp
//  servidorPrueva
//
//  Created by Daniel Alvarado on 5/12/17.
//  Copyright © 2017 TEC. All rights reserved.
//

/* A simple server in the internet domain using TCP
 The port number is passed as an argument */

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
const int TAMANHO_BUFFER = 100000000;



void error(const char *msg)
{
    perror(msg);
    exit(1);
}
const int portno = 9090;

void socketMain(ArbolSupermercados*& _arbolSupermercados, ArbolProveedores*& _arbolProveedores, ArbolClientes*& _arbolClientes,
                      ListaLugares*& _listaLugares) {


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


    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    while (1) {
        bzero(buffer,TAMANHO_BUFFER);
        n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

        if (( memcmp( buffer, "END", strlen( "END"))) == 0) {
            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);
            n = write(newsockfd, "Proceso Terminado", strlen("Proceso Terminado"));
            break;
        }

        if (bandera == PRIMERA_VEZ) {
            //la primera vez entra aca para verificar el cliente, obtiene el ID del cliente
            //Si no esta se prepara para almacenar los datos




            //si no entra en un ciclo para obtener los datos


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
                        char msgIdguardada[] = "CLIENTE EXISTE";
                        write(newsockfd,msgIdguardada, strlen(msgIdguardada));
                        break;
                    }
                    // le agrega una compra al cliente
                    //  agregar compra al cliente
                    // agregarCompra(idCliente)
                    // break
                    //}
                    char msgIdguardada[] = "Identificacion guardada\nDigite su nombre para ser registrado ";
                    n = write(newsockfd,msgIdguardada, strlen(msgIdguardada));




                }else if (i == 1) {
                    // registra el nombre
                    //transforma de caracter a str
                    std::string nombreCliente(buffer);

                    //std::cout << nombreCliente << std::endl;

                    char msgNombreSavedDir[] = "Nombre guardado\nDigite su direecion";
                    n = write(newsockfd, msgNombreSavedDir, strlen(msgNombreSavedDir));

                }else if (i == 2) {
                    // registra la direccion

                    std::string dirCliente(buffer);

                    n = write(newsockfd, "Direccion guardado", strlen("Direccion guardada"));
                    n = write(newsockfd, "Digite su numero de telefono", strlen("Digite su numero de telefono"));

                }else if (i == 3) {
                    // registra el telefono
                    int telefonoCliente = atoi(buffer);
                    n = write(newsockfd, "CLIENTE GUARDADO", strlen("CLIENTE GUARDADO"));

                    //Agrega el cliente por completo con todos sus datos ya obtenidos
                    _arbolClientes->IniciarInsercionB(idCliente,idCliente,nombreCliente,dirCliente,telefonoCliente);


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
                    _arbolProveedores->getNodoProveedor(codPro, _arbolProveedores->raiz, _nodoProv);
                    _arbolClientes->getCliente(_arbolClientes->raizB, _nodoCliente, idCliente);
                    _nodoCliente->aumentarVentas();
                    _nodoProv->aumentarVentas();
                    _nodoProd->setCantidadEnStock(cantidad);
                    _nodoCat->incBestScore();
                    _nodoSup->aumentarVentas();
                    NodoVenta *_nodoVenta = new NodoVenta(_nodoProv->getID(), _nodoProv->getNombre(),
                                                          _nodoCliente->getID(),
                                                          _nodoCliente->getNombre(), _nodoCat->getCodigo(),
                                                          _nodoCat->getDesc(),
                                                          _nodoProd->getCodigoProducto(),
                                                          _nodoProd->getNombreProducto(),
                                                          _nodoProd->getPrecioPorUnidad(), cantidad,
                                                          (_nodoProd->getPrecioPorUnidad() * cantidad) * 0.05);

                    n = write(newsockfd, "VENTA REALIZADA", strlen("VENTA REALIZADA"));
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

            //


        }else if (bandera == OPCION_CLIENTE_MAS_COMPRO) {
            //determina el Cliente con mas ventas
            bzero(buffer, TAMANHO_BUFFER);
            n = read(newsockfd, buffer, TAMANHO_BUFFER - 1);


            n = write(newsockfd, "El cliente con mas ventas es:  ", strlen("El cliente con mas ventas es: "));
            //



            bandera = 0;



        }else if (bandera == OPCION_PRODUCTO_MAS_VENDIDO) {
            //determina el Producto con mas Ventas
            bzero(buffer,TAMANHO_BUFFER);
            n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);
            char msgNoExiste[] = "Codigo NO EXISTE";


            ArbolCategorias* arbolCategorias = new ArbolCategorias();
            ArbolProductos* arbolProductos = new ArbolProductos();


            for (int i = 0; i < 3; i++) {
                bzero(buffer,TAMANHO_BUFFER);
                n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

                if (i == 0 ) {
                    // ademas aca la primera vez, saca todos los nodos para asi revisarlos

                    codSuper = atoi(buffer);

                    //Verifica si existe dicho codigo
                    if (!_arbolSupermercados->existeCategoria(codSuper,codCat,_arbolSupermercados->raiz)) {
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
                    // aca pone
                    char msgCodR[] = "Codigo de Categoria recibido\nDigite el Codigo de Producto";
                    n = write(newsockfd, msgCodR, strlen(msgCodR));

                }else if (i == 2) {

                    //aca es donde se van metiendo en los valores los codigos
                    codPro = atoi(buffer);

                    //

                    arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);
                    if (!arbolProductos->existeProducto(arbolProductos->raiz,codPro)) {
                        n = write(newsockfd,msgNoExiste, strlen(msgNoExiste));
                        break;
                    }
                    NodoProducto* productoMasVendido = new NodoProducto();
                    arbolProductos->getProductoMasVendido(arbolProductos->raiz,productoMasVendido);

                    //productoMasVendido->
                    std::string nombre = productoMasVendido->getNombreProducto();
                    std::vector<char> v(nombre.begin(), nombre.end());
                    v.push_back('\0'); // Make sure we are null-terminated
                    char* productoCh = &v[0];
                    n = write(newsockfd,productoCh , strlen(productoCh));

                }

                bandera = 0;

            }


//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
        } else if (bandera == OPCION_PRODUCTOS_CAMBIARON_STOCK) {
            //Productos que cambiaron el stock

            for (int i = 0; i < 3; i++) {
                bzero(buffer,TAMANHO_BUFFER);
                n = read(newsockfd,buffer,TAMANHO_BUFFER - 1);

                if (i == 0 ) {
                    // ademas aca la primera vez, saca todos los nodos para asi revisarlos


                    //funcion que verifica el codigo del super


                    //existe
                    codSuper = atoi(buffer);

                    //Verifica si existe dicho codigo
                    // if (!arbolSupermercados->existeCategoria(arbolSupermercados->raiz,codSuper))
                    // aca pone
                    //n = write(newsockfd, "Codigo de Super recibido", strlen("Codigo de Super recibido"));
                    //
                    n = write(newsockfd, "Codigo de Super recibido", strlen("Codigo de Super recibido"));
                    n = write(newsockfd, "Por favor digite el codigo de la categoria que desea: ", strlen("Por favor digite el codigo de la categoria que desea: "));

                }else if ( i == 1) {



                    //aca es donde se van metiendo en los valores los codigos
                    codCat = atoi(buffer);
                    //
                    //ArbolCategorias* arbolCategorias = new ArbolCategorias()
                    //arbolSupermercados->getArbolCat(codSuper, arbolSupermecados->raiz, ArbolCategorias*& arbolCategorias);
                    //Verifica si existe dicho codigo
                    // if (!arbolCategorias->existeCategoria(arbolCategorias->raiz,codCat))
                    // aca pone

                    n = write(newsockfd, "Codigo de Categoria recibido\n", strlen("Codigo de Categoria recibido\n"));
                    n = write(newsockfd, "Digite el Codigo de Producto", strlen("Digite el Codigo de Producto"));

                }else if (i == 2) {

                    //aca es donde se van metiendo en los valores los codigos
                    codPro = atoi(buffer);
                    n = write(newsockfd, "Codigo de Producto recibido\n", strlen("Codigo de Producto recibido\n"));
                    //
                    //ArbolProductos* arbolProductos = new ArbolProductos()
                    //arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);
                    //NodoProducto productoMasVendido = new NodoProducto();
                    //arbolProductos->
                    //

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


        }else if (bandera == OPCION_ELIMINAR_PRODUCTO) {


            ArbolCategorias* arbolCategorias = new ArbolCategorias();
            ArbolProductos* arbolProductos = new ArbolProductos();
            NodoProducto* productoEliminar = new NodoProducto();

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
                    if (!arbolCategorias->existeCategoria(codCat, arbolCategorias->raiz)) {
                        n = write(newsockfd, msgNoExiste, strlen(msgNoExiste));
                        break;
                    }
                    // aca pone
                    _arbolSupermercados->getArbolCat(codSuper, _arbolSupermercados->raiz, arbolCategorias);
                    char msgCodR[] = "Codigo de Categoria recibido\nDigite el Codigo de Producto";
                    n = write(newsockfd, msgCodR, strlen(msgCodR));

                } else if (i == 2) {

                    //aca es donde se van metiendo en los valores los codigos
                    codPro = atoi(buffer);

                    if (!arbolCategorias->existeProducto(codPro, codCat, arbolCategorias->raiz)) {
                        n = write(newsockfd, msgNoExiste, strlen(msgNoExiste));
                        break;

                    }

                    char msgAccept[] = "Codigo de Producto recibido\nDesea ELIMINAR el producto? (S/N)";

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
                        arbolProductos->getNodoProducto(codPro ,arbolProductos->raiz,productoEliminar);
                        arbolProductos->eliminar(arbolProductos->raiz,codPro);
                        char msgEliminadoP[] = "El producto fue ELIMINADO con exite";
                        n = write(newsockfd, msgEliminadoP, strlen(msgEliminadoP));

                        //

                    } else {
                        char msgNoEliminado[] = "El produco NO fue eliminado";
                        n = write(newsockfd, msgNoEliminado, strlen(msgNoEliminado));
                        break;

                    }


                }
                bandera = 0;

            }


        }else if (bandera == OPCION_ELIMINAR_CLIENTE) {



        }else if (bandera == OPCION_IMPRIMIR_ARBOL_PREORDEN) {



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
\
            }else if (( memcmp( buffer, "1", strlen( "1"))) == 0 )  {

                //
                char msgVenta[] = "ESPERANDO VENTA\nDigite el codigo del super";
                n = write(newsockfd, msgVenta, strlen(msgVenta));
                bandera = OPCION_VENTA;

            }else if (( memcmp( buffer, "2", strlen( "2"))) == 0 ) {
                //proveedor con mas ventas
                //n = write(newsockfd, "ESPERANDO VENTA", strlen("ESPERANDO VENTA"));
                n = write(newsockfd, "Digite OK", strlen("Digite OK"));

                bandera = OPCION_PROVEEDOR_MAS_VENTAS;


            }else if (( memcmp( buffer, "3", strlen( "3"))) == 0 ) {
                //Cliente que mas compro
                //getCliente
                n = write(newsockfd, "Digite OK", strlen("Digite OK"));

                bandera = OPCION_CLIENTE_MAS_COMPRO;




            }else if (( memcmp( buffer, "4", strlen( "4"))) == 0 ) {
                //Producto mas vendido neceista cod del super y de la categoria
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));

                bandera = OPCION_PRODUCTO_MAS_VENDIDO;

            }else if (( memcmp( buffer, "5", strlen( "5"))) == 0 ) {
                //Productos que el stock
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));
                bandera = OPCION_PRODUCTOS_CAMBIARON_STOCK;


            }else if (( memcmp( buffer, "6", strlen( "6"))) == 0 ) {
                //Categoria mas vendid
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));
                bandera = OPCION_CATEGORIA_MAS_VENDIDA;

            }else if (( memcmp( buffer, "7", strlen( "7"))) == 0 ) {
                //Supermercado con mas ventas
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));
                bandera = OPCION_SUPERMERCADO_MAS_VENTAS;

            }else if (( memcmp( buffer, "8", strlen( "8"))) == 0 ) {
                //lugar con mas supermercados
                n = write(newsockfd, "Digite OK", strlen("Digite OK"));
                bandera = OPCION_LUGAR_CON_MAS_SUPERMERCADOS;

            }else if (( memcmp( buffer, "9", strlen( "9"))) == 0 ) {
                //Determina arbol que desea imprimir

                char msgPreorden[] = "Digite 1 si desea un arbol de supermercados\nDigite 2 si desea un arbol de categorias\n"
                        "Digite 3 si desea un arbol de proveedores\nDigite 4 si desea un arbol de clientes\n"
                        "Digite 4 si desea un arbol de clientes\nDigite 5 si desea el arbol de proveedores";
                n = write(newsockfd,msgPreorden, strlen(msgPreorden));

                bandera = OPCION_IMPRIMIR_ARBOL_PREORDEN;

            }else if (( memcmp( buffer, "10", strlen( "10"))) == 0 ) {

                char msgEliminarPro[] = "ELIMINANDO PRODUCTO\nDigite el codigo del super";
                n = write(newsockfd, msgEliminarPro, strlen(msgEliminarPro));


                bandera = OPCION_ELIMINAR_PRODUCTO;

            }if (( memcmp( buffer, "11", strlen( "11"))) == 0 ) {
                char msgEliminarCl[] = "ELIMINANDO CLIENTE\nDigite el codigo del cliente";
                n = write(newsockfd, msgEliminarCl, strlen(msgEliminarCl));

                bandera = OPCION_ELIMINAR_PRODUCTO;



            }else {
                n = write(newsockfd, "OTRO", strlen("OTRO"));
            }

            //close(newsockfd);
        }



    }
    close(newsockfd);
    close(sockfd);




}


