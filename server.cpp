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
#include "arbolproveedores.h"
#include "arbolclientes.h"
#include "arbolsupermercados.h"
#include "arbolcategorias.h"
#include "arbolproductos.h"
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
    char buffer[256];
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
    char* nombreCliente,dirCliente;


    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    while (1) {


        if (( memcmp( buffer, "END", strlen( "END"))) == 0) {

            n = write(newsockfd, "Proceso Terminado", strlen("Proceso Terminado"));
            break;
        }

        if (bandera == PRIMERA_VEZ) {
            //la primera vez entra aca para verificar el cliente, obtiene el ID del cliente
            //Si no esta se prepara para almacenar los datos




            //si no entra en un ciclo para obtener los datos


            for (int i = 0; i < 4; i++) {
                bzero(buffer, 256);
                n = read(newsockfd, buffer, 255);
                if (i == 0) {
                    // registra el ID
                    //revisa si el cliente existe
                    //si existe continua y le agrega una compra
                    idCliente = atoi(buffer);
                    //if (existeCliente(int idCliente)) {
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
                    char msgNombreSavedDir[] = "Nombre guardado\nDigite su direecion";
                    n = write(newsockfd, msgNombreSavedDir, strlen(msgNombreSavedDir));

                }else if (i == 2) {
                    // registra la direccion
                    n = write(newsockfd, "Direccion guardado", strlen("Direccion guardada"));
                    n = write(newsockfd, "Digite su numero de telefono", strlen("Digite su numero de telefono"));

                }else if (i == 3) {
                    // registra el telefono
                    int telefonoCliente = atoi(buffer);
                    n = write(newsockfd, "Telefono guardado", strlen("Telefono guardada"));

                    //Agrega el cliente por completo con todos sus datos ya obtenidos
                    _arbolClientes->IniciarInsercionB(idCliente,idCliente,nombreCliente,dirCliente,telefonoCliente);
                    //dirCliente,telefonoCliente)
                    //

                }
                bandera = 0;

            }

        }

        if (bandera == OPCION_VENTA) {

            //4 veces para poder obtener lo de la venta
            for (int i = 0;i<4;i++) {


                bzero(buffer,256);
                n = read(newsockfd,buffer,255);

                if (i == 0) {
                    //se esta tomando el codigo del Super


                    //Y se crean todos los nodos la primera vez para despues utilizarlos

                    codSuper = atoi(buffer);
                    char msg[] = "Codigo del Super recibido\n";
                    n = write(newsockfd, msg, strlen(msg));

                    //write(newsockfd, "Codigo de Super recibido\n", strlen("Codigo de Super recibido\n"));

                    n = write(newsockfd, "Digite el Codigo de Categoria", strlen("Digite el Codigo de Categoria"));
                } else if (i == 1) {

                    codCat = atoi(buffer);
                    char msgCatRecibidaPro[] = "Codigo de Categoria recibido\nDigite el Codigo de Producto";
                    n = write(newsockfd, msgCatRecibidaPro, strlen(msgCatRecibidaPro));
                } else if (i == 2) {

                    codPro = atoi(buffer);
                    n = write(newsockfd, "Codigo de Producto recibido\n", strlen("Codigo de Producto recibido\n"));
                    n = write(newsockfd, "Digite la cantidad que desea", strlen("Digite la cantidad que desea"));

                } else if (i == 3) {
                    cantidad = atoi(buffer);
                    n = write(newsockfd, "VENTA REALIZADA", strlen("VENTA REALIZADA"));

                }



                //ACA luego de tener todos esos datos crea el nodo venta
                //Determina en cada uno si el dato esta, si no esta simplemente cambia el valor de i
                // y se sale del ciclo que esta ahi

                //close(newsockfd);


            }

            bandera = 0;

        }else if (bandera == OPCION_PROVEEDOR_MAS_VENTAS ) {
            //determina el Proveedor con mas ventas

            bzero(buffer,256);
            n = read(newsockfd,buffer,255);

            n = write(newsockfd, "El proveedor con mas ventas es:  ", strlen("El proveedor con mas ventas es: "));

            //Entra en un ciclo donde determina el proveedor con mas ventas
            //arbolProveedores
            //


        }else if (bandera == OPCION_CLIENTE_MAS_COMPRO) {
            //determina el Cliente con mas ventas
            bzero(buffer,256);
            n = read(newsockfd,buffer,255);
            n = write(newsockfd, "El cliente con mas ventas es:  ", strlen("El cliente con mas ventas es: "));
            //



            bandera = 0;



        }else if (bandera == OPCION_PRODUCTO_MAS_VENDIDO) {
            //determina el Producto con mas Ventas
            bzero(buffer,256);
            n = read(newsockfd,buffer,255);
            char msgNoExiste[] = "Codigo NO EXISTE";


            ArbolCategorias* arbolCategorias = new ArbolCategorias();
            ArbolProductos* arbolProductos = new ArbolProductos();


            for (int i = 0; i < 3; i++) {

                if (i == 0 ) {
                    // ademas aca la primera vez, saca todos los nodos para asi revisarlos

                    codSuper = atoi(buffer);

                    //Verifica si existe dicho codigo
                    if (!_arbolSupermercados->existeCategoria(codSuper,codCat,_arbolSupermercados->raiz)) {
                        char msgNoExiste[] = "Codigo NO EXISTE";
                        n = write(newsockfd,msgNoExiste, strlen(msgNoExiste));
                        break;
                    }

                    n = write(newsockfd, "Codigo de Super recibido", strlen("Codigo de Super recibido"));
                    n = write(newsockfd, "Por favor digite el codigo de la categoria que desea: ", strlen("Por favor digite el codigo de la categoria que desea: "));

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

                    n = write(newsockfd, "Codigo de Categoria recibido\n", strlen("Codigo de Categoria recibido\n"));
                    n = write(newsockfd, "Digite el Codigo de Producto", strlen("Digite el Codigo de Producto"));

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
                    //
                    //productoMasVendido->

                    n = write(newsockfd, "Codigo de Producto recibido\n", strlen("Codigo de Producto recibido\n"));




                }

                bandera = 0;

            }



        } else if (bandera == 5) {
            //Productos que cambiaron el stock

            for (int i = 0; i < 3; i++) {

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



        }else if (bandera == 6) {
            //OBTENER CATEGORIA MAS VENDIDA

            for (int i = 0; i < 2; i++) {

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
                    // nodocategoria* categoria = new nodocategoria()
                    //
                    n = write(newsockfd, "Codigo de Categoria recibido", strlen("Codigo de Categoria recibido"));
                    n = write(newsockfd, "Categoria Mas Vendida", strlen("Categoria Mas Vendida"));

                }
                bandera = 0;

            }



        }else if (bandera == 7) {
            //Supermercado con mas ventas
            //NodoSupermercado* supermercado = new NodoSupermercado()





        }else if (bandera == 10) {

            for (int i = 0; i < 4; i++) {

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
                    n = write(newsockfd,"Desea ELIMINAR el producto? (S/N)",strlen("Desea ELIMINAR el producto? (S/N)"));

                    //
                    //ArbolProductos* arbolProductos = new ArbolProductos()
                    //arbolCategorias->getArbolProd(arbolCategorias->raiz,codCat,arbolProductos);
                    //NodoProducto productoEliminar = new NodoProducto();
                    //arbolProductos->
                    //

                }else if (i == 3) {
                    if (( memcmp( buffer, "10", strlen( "10"))) == 0 ) {
                        //productoEliminar
                        //arbolProductos->eliminarProducto(codPro)
                        //

                    }



                }
                bandera = 0;
            }


        }else{

            /* newsockfd = accept(sockfd,
                               (struct sockaddr *) &cli_addr,
                               &clilen);
            */



            bzero(buffer,256);
            n = read(newsockfd,buffer,255);

            if(( memcmp( buffer, "Message", strlen( "Message"))) == 0 ) {
                // do something
                n = write(newsockfd,"I got your message",18);
                printf("Here is the message: %s\n",buffer);

            }else if (( memcmp( buffer, "END", strlen( "END"))) == 0 )  {
                n = write(newsockfd, "Proceso Terminado", strlen("Proceso Terminado"));
                break;

                /*}else if (existeCliente(buffer)) {
                    n = write(newsockfd, "Existe CLIENTE", strlen("Existe Cliente"));
                */
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


