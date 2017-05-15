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



void error(const char *msg)
{
    perror(msg);
    exit(1);
}
const int portno = 9090;

void socketMain() {


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
                    n = write(newsockfd, "Nombre guardado\n", strlen("Nombre guardada\n"));
                    n = write(newsockfd, "Digite su direecion", strlen("Digite su direecion"));

                }else if (i == 2) {
                    // registra la direccion
                    n = write(newsockfd, "Direccion guardado", strlen("Direccion guardada"));
                    n = write(newsockfd, "Digite su numero de telefono", strlen("Digite su numero de telefono"));

                }else if (i == 3) {
                    // registra el telefono
                    int telefonoCliente = atoi(buffer);
                    n = write(newsockfd, "Telefono guardado", strlen("Telefono guardada"));

                    //Agrega el cliente por completo con todos sus datos ya obtenidos
                    //arbolClientes->iniciarInsercionB(idCliente,idCliente,nombreCliente
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
                    n = write(newsockfd, "Codigo de Categoria recibido\n", strlen("Codigo de Categoria recibido\n"));
                    n = write(newsockfd, "Digite el Codigo de Producto", strlen("Digite el Codigo de Producto"));
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



        }else if (bandera == 4 ) {
            //determina el Producto con mas Ventas
            bzero(buffer,256);
            n = read(newsockfd,buffer,255);

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
                    //arbolProductos->getProductoMasVendido(arbolProductos->raiz,NodoProducto* &_nuevoNodo)
                    //
                    //productoMasVendido->




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
                n = write(newsockfd, "ESPERANDO VENTA", strlen("ESPERANDO VENTA"));
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));

                bandera = 1;

            }else if (( memcmp( buffer, "2", strlen( "2"))) == 0 ) {
                //proveedor con mas ventas
                //n = write(newsockfd, "ESPERANDO VENTA", strlen("ESPERANDO VENTA"));
                n = write(newsockfd, "Digite OK", strlen("Digite OK"));

                bandera = OPCION_PROVEEDOR_MAS_VENTAS;


            }else if (( memcmp( buffer, "3", strlen( "3"))) == 0 ) {
                //Cliente que mas compro
                //getCliente
                n = write(newsockfd, "Digite OK", strlen("Digite OK"));

                bandera = 3;




            }else if (( memcmp( buffer, "4", strlen( "4"))) == 0 ) {
                //Producto mas vendido neceista cod del super y de la categoria
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));

                bandera = 4;

            }else if (( memcmp( buffer, "5", strlen( "5"))) == 0 ) {
                //Productos que el stock
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));
                bandera = 5;


            }else if (( memcmp( buffer, "6", strlen( "6"))) == 0 ) {
                //Categoria mas vendid
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));
                bandera = 6;

            }else if (( memcmp( buffer, "7", strlen( "7"))) == 0 ) {
                //Supermercado con mas ventas
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));
                bandera = 7;

            }else if (( memcmp( buffer, "8", strlen( "8"))) == 0 ) {
                //lugar con mas supermercados
                n = write(newsockfd, "Digite OK", strlen("Digite OK"));
                bandera = 8;

            }else if (( memcmp( buffer, "9", strlen( "9"))) == 0 ) {
                //Determina arbol que desea imprimir
                n = write(newsockfd, "Digite 1 si desea un arbol de supermercados", strlen("Digite 1 si desea un arbol de supermercados"));
                n = write(newsockfd, "Digite 2 si desea un arbol de categorias", strlen("Digite 2 si desea un arbol de categorias"));
                n = write(newsockfd, "Digite 3 si desea un arbol de proveedores", strlen("Digite 2"));
                n = write(newsockfd, "Digite 4 si desea un arbol de clientes", strlen("Digite 4 si desea un arbol de clientes"));
                n = write(newsockfd, "Digite 5 si desea el arbol de proveedores", strlen("Digite 5 si desea el arbol de proveedores"));
                n = write(newsockfd, "Digite 6", strlen("Digite 2"));
                bandera = 9;

            }else if (( memcmp( buffer, "10", strlen( "10"))) == 0 ) {


                n = write(newsockfd, "ELIMINANDO PRODUCTO", strlen("ELIMINANDO PRODUCTO"));
                n = write(newsockfd, "Digite el codigo del super", strlen("Digite el codigo del super"));

                bandera = 10;

            }if (( memcmp( buffer, "10", strlen( "10"))) == 0 ) {



            }else {
                n = write(newsockfd, "OTRO", strlen("OTRO"));
            }

            //close(newsockfd);
        }



    }
    close(newsockfd);
    close(sockfd);




}


