QT += core
QT -= gui

CONFIG += c++11

TARGET = SistemaVentasArboles
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    nodocliente.cpp \
    nodoproveedor.cpp \
    nodoproducto.cpp \
    arbolproveedores.cpp \
    arbolcategorias.cpp \
    arbolproductos.cpp \
    arbolclientes.cpp \
    arbolsupermercados.cpp \
    listalugares.cpp \
    nodoventa.cpp \
    listaventas.cpp \
    nodoproductocomprado.cpp

HEADERS += \
    nodocliente.h \
    nodoproveedor.h \
    nodoproducto.h \
    arbolproveedores.h \
    arbolcategorias.h \
    arbolproductos.h \
    arbolclientes.h \
    arbolsupermercados.h \
    listalugares.h \
    nodoventa.h \
    listaventas.h \
    nodoproductocomprado.h
