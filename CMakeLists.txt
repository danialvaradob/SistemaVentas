cmake_minimum_required(VERSION 3.7)
project(SistemaVentas2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp nodocategoria.cpp nodocategoria.h arbolsupermercados.cpp arbolsupermercados.h arbolcategorias.cpp arbolcategorias.h arbolclientes.cpp arbolclientes.h
        arbolproductos.cpp arbolproductos.h arbolproveedores.cpp arbolproveedores.h listalugares.cpp listalugares.h listaventas.cpp listaventas.h nodoproveedor.cpp nodoproveedor.h
        nodosupermercado.cpp nodosupermercado.h nodocliente.cpp nodocliente.h nodoproducto.cpp nodoproducto.h
        nodoventa.cpp nodoventa.h nodolugar.cpp nodolugar.h socket.c leerArchivos.cpp)
add_executable(SistemaVentas2 ${SOURCE_FILES})