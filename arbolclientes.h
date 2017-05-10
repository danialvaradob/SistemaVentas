#ifndef ARBOLCLIENTES_H
#define ARBOLCLIENTES_H
#include <iostream>
#include <string>
#include "nodocliente.h"

using namespace std;
//ARBOL B


class ArregloClaves
{
public:

    ArregloClaves(){

        for(int clave = 0; clave < 5; clave++){
            arregloClaves[clave] = NULL;
        }
    }

    void InsertarClave(pNodoCliente Clave, int Numero);
    int ObtenerClave(int Numero);
    pNodoCliente ObtenerApuntadorClave(int Numero);


private:

    pNodoCliente arregloClaves[5];

    friend class Pagina;
};

void ArregloClaves::InsertarClave(pNodoCliente Clave, int Numero)
{
    arregloClaves[Numero] = Clave;
}

int ArregloClaves::ObtenerClave(int Numero)
{
    pNodoCliente Clave;
    Clave = arregloClaves[Numero];
    int numero = Clave->numero;
    return numero;
}

pNodoCliente ArregloClaves::ObtenerApuntadorClave(int Numero)
{
    pNodoCliente Clave;
    Clave = arregloClaves[Numero];
    return Clave;
}

typedef ArregloClaves *ApuntadorClaves;

class Pagina;
typedef Pagina *ApuntadorPagina;

class ArregloRamas
{
public:

    ArregloRamas(){
        for(int k = 0; k < 5; k++){
            arregloRamas[k] = NULL;
        }
    }
    void InsertarRama(ApuntadorPagina Rama, int Numero);
    ApuntadorPagina ObtenerRama(int Numero);

private:

    ApuntadorPagina arregloRamas[5];

    friend class Pagina;
};

typedef ArregloRamas *ApuntadorRamas;

void ArregloRamas::InsertarRama(ApuntadorPagina Rama, int Numero)
{
    arregloRamas[Numero] = Rama;
}

ApuntadorPagina ArregloRamas::ObtenerRama(int Numero)
{
    ApuntadorPagina AP;
    AP = arregloRamas[Numero];
    return AP;
}

class Pagina
{
public:

    Pagina(){
        cuenta = 0;
        Claves = new ArregloClaves();
        Ramas = new ArregloRamas();
        EmpujarArriba = false;
        X = 0;
        Xr = NULL;
        K = 0;
        Esta = false;
        llamadas = 0;
    }



    //private:

    int cuenta;
    ApuntadorClaves Claves;
    ApuntadorRamas Ramas;
    bool EmpujarArriba;
    int X;
    ApuntadorPagina Xr;
    int K;
    bool Esta;
    int llamadas;

    friend class ArbolClientes;

};

class ArbolClientes
{
public:

    ArbolClientes(){raizB = NULL;}
    bool BVacio(){return raizB == NULL;}
    void EstablecerRaizB(ApuntadorPagina Raiz);
    void IniciarInsercionB(int Numero, int _id, string _nombre, string _direccion, int _telefono);
    ApuntadorPagina InsertarB(ApuntadorPagina Raiz, int Numero,  int _id, string _nombre, string _direccion, int _telefono);
    ApuntadorPagina EmpujarB(ApuntadorPagina Raiz, int Numero, int _id, string _nombre, string _direccion, int _telefono);
    ApuntadorPagina BuscarNodoB(ApuntadorPagina Raiz, int Numero);
    ApuntadorPagina MeterHojaB(ApuntadorPagina Raiz, int _id, string _nombre, string _direccion, int _telefono);
    ApuntadorPagina DividirNodoB(ApuntadorPagina Raiz,  int _id, string _nombre, string _direccion, int _telefono);
    void IniciarRecorridoB();
    void RecorridoInordenB(ApuntadorPagina Raiz);
    bool existeCliente(ApuntadorPagina Raiz,int _Numero);


    // Funcion que simplemente agrega un cliente usando IniciarInsercionB(para Numero se utiliza el mismo _id, son 2 _id
    // en total)
    void Clientes();


    //private:

    ApuntadorPagina raizB;

};


void ArbolClientes::EstablecerRaizB(ApuntadorPagina Raiz)
{
    raizB = Raiz;
}

void ArbolClientes::IniciarInsercionB(int Numero, int _id, string _nombre, string _direccion, int _telefono)
{
    ApuntadorPagina Raiz = raizB;
    raizB = InsertarB(Raiz,Numero,  _id,  _nombre,  _direccion,  _telefono);
}

ApuntadorPagina ArbolClientes::InsertarB(ApuntadorPagina Raiz, int Numero, int _id, string _nombre, string _direccion, int _telefono)
{
    ApuntadorPagina P = NULL;

    Raiz = EmpujarB(Raiz,Numero,  _id,  _nombre,  _direccion,  _telefono);
    if(Raiz->EmpujarArriba){
        P = new Pagina();
        P->cuenta = 1;
        pNodoCliente Auxiliar = new NodoCliente(Raiz->X,  _id,  _nombre,  _direccion, _telefono);
        P->Claves->InsertarClave(Auxiliar,1);
        P->Ramas->InsertarRama(Raiz->Xr,1);
        if(Raiz->llamadas == 1){
            P->Ramas->InsertarRama(NULL,0);
        }
        else{
            P->Ramas->InsertarRama(Raiz,0);
        }

        Raiz = P;
    }
    return Raiz;


}

ApuntadorPagina ArbolClientes::EmpujarB(ApuntadorPagina Raiz, int Numero, int _id, string _nombre, string _direccion, int _telefono)
{
    if(Raiz == NULL){
        Raiz = new Pagina();
        Raiz->EmpujarArriba = true;
        Raiz->X = Numero;
        Raiz->Xr = NULL;
        Raiz->llamadas++;
        return Raiz;
    }

    else{
        Raiz = BuscarNodoB(Raiz,Numero);
        if(Raiz->Esta){
            cout << "Elemento Repetido" << endl;
        }
        if(Raiz->K == 0){

        }
        ApuntadorPagina Aux;
        Aux = EmpujarB(Raiz->Ramas->ObtenerRama(Raiz->K),Numero,  _id,  _nombre,  _direccion,  _telefono);
        Raiz->EmpujarArriba = Aux->EmpujarArriba;
        Raiz->X = Aux -> X;
        Raiz->Xr = Aux->Xr;
        if(Raiz->EmpujarArriba){
            if(Raiz->cuenta < 4){
                Raiz->EmpujarArriba = false;
                Raiz = MeterHojaB(Raiz,  _id,  _nombre,  _direccion,  _telefono);
            }
        }
        else{
            Raiz->EmpujarArriba = true;
            Raiz = DividirNodoB(Raiz,  _id,  _nombre,  _direccion,  _telefono);

        }
        return Raiz;

    }
}

ApuntadorPagina ArbolClientes::BuscarNodoB(ApuntadorPagina Raiz, int Numero)
{
    int PClave1 = Raiz->Claves->ObtenerClave(1);
    if(Numero < PClave1){
        Raiz->Esta = false;
        Raiz->K = 0;
    }
    else{
        Raiz->K = Raiz->cuenta;
        while(Numero < Raiz->Claves->ObtenerClave(Raiz->K) && Raiz->K > 1){
            Raiz->K--;
        }
        if(Numero == Raiz->Claves->ObtenerClave(Raiz->K)){
            Raiz->Esta = true;
        }
    }
    Raiz->llamadas++;
    return Raiz;
}

ApuntadorPagina ArbolClientes::MeterHojaB(ApuntadorPagina Raiz, int _id, string _nombre, string _direccion, int _telefono)
{
    int I;
    I = Raiz->cuenta;
    while(I >= Raiz->K + 1){
        Raiz->Claves->InsertarClave(Raiz->Claves->ObtenerApuntadorClave(I),I+1);
        Raiz->Ramas->InsertarRama(Raiz->Ramas->ObtenerRama(I),I+1);
        I--;
    }
    pNodoCliente X = new NodoCliente(Raiz->X, _id,  _nombre,  _direccion,  _telefono);
    Raiz->Claves->InsertarClave( X,Raiz->K + 1);
    Raiz->Ramas->InsertarRama(Raiz->Xr ,Raiz->K + 1);
    Raiz->cuenta++;


    return Raiz;


}

ApuntadorPagina ArbolClientes::DividirNodoB(ApuntadorPagina Raiz, int _id, string _nombre, string _direccion, int _telefono)
{
    int I;
    int Posmda;
    ApuntadorPagina Mder;
    int Mda;

    if(Raiz->K <= 2){
        Posmda = 2;
    }
    else{
        Posmda = 3;
    }

    Mder = new Pagina();
    I = Posmda + 1;
    while(I <= 4){
        Mder->Claves->InsertarClave(Raiz->Claves->ObtenerApuntadorClave(I) ,I - Posmda);
        Mder->Ramas->InsertarRama(Raiz->Ramas->ObtenerRama(I) ,I - Posmda);
        I++;
    }
    Mder->cuenta = 4 - Posmda;
    Raiz->cuenta = Posmda;

    if(Raiz->K <= 2){
        Raiz = MeterHojaB(Raiz,   _id,  _nombre,  _direccion,  _telefono);
    }
    else{
        Mder->X = Raiz->X;
        Mder->Xr = Raiz->Xr;
        Mder->K = Raiz->K - Posmda;
        Mder = MeterHojaB(Mder,  _id,  _nombre,  _direccion,  _telefono);
    }
    Mda = Raiz->Claves->ObtenerClave(Raiz->cuenta);
    Raiz->X = Mda;
    Mder->Ramas->InsertarRama(Raiz->Ramas->ObtenerRama(Raiz->cuenta),0);
    Raiz->cuenta--;
    Raiz->Xr = Mder;
    return Raiz;
}

void ArbolClientes::IniciarRecorridoB()
{
    ApuntadorPagina Raiz = raizB;
    RecorridoInordenB(Raiz);
}

void ArbolClientes::RecorridoInordenB(ApuntadorPagina Raiz){
    if(Raiz == NULL){
        return;
    }
    else{
        RecorridoInordenB(Raiz->Ramas->ObtenerRama(0));
        int I = 1;
        while(I <= Raiz->cuenta){
            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            cout<< "idCliente: "<< Recorrido->getID() << endl;
            cout << "Nombre: " << Recorrido->getNombre()<< endl;
            cout << "Cantidad de Compras: " << Recorrido->getCantidadCompras()<< endl;
            cout << "Ciudad: " << Recorrido->getDireccion()<< endl;
            cout << "Telefono: " << Recorrido->getTelefono() << endl;
            cout << "\n" << endl;

            RecorridoInordenB(Raiz->Ramas->ObtenerRama(I));

            I++;
        }
    }
}

bool ArbolClientes::existeCliente(ApuntadorPagina Raiz ,int _Numero) {
    if (Raiz == NULL) {
        return false;

    } else {
        existeCliente(Raiz->Ramas->ObtenerRama(0), _Numero);
        int I = 1;
        while (I <= Raiz->cuenta) {
            if (Raiz->Claves->ObtenerApuntadorClave(I)->getID() == _Numero) return true;

            existeCliente(Raiz->Ramas->ObtenerRama(I),_Numero);
            I++;
        }

    }

}

//-----------Pila-----------//
/*
class PilaB {
public:
    PilaB() : plistaB(NULL) {}

    void Push(pNodoCliente);

    bool Vacia() { return plistaB == NULL; }
    pNodoCliente Pop();
    int Size();

    pNodoCliente plistaB;
};

void PilaB::Push(pNodoCliente v)
{
    if(Vacia()) {
        plistaB = v;
    }else{
        NodoCliente *aux = plistaB;
        while(aux->siguiente){
            aux = aux->siguiente;
        }
        aux->siguiente = v;
        v->anterior = aux;

    }
}

pNodoCliente PilaB::Pop()
{
    NodoCliente *borrar = NULL;
    NodoCliente *salida = NULL;
    if(Vacia()){
        cout<<"Pila Vacia"<<endl;
    }else{
        borrar = plistaB;
        while(borrar->siguiente){
            borrar=borrar->siguiente;
        }
        if(Size()>1){
            salida = borrar;
            borrar->anterior->siguiente=NULL;
            borrar = NULL;
            delete borrar;
        }else{
            salida = plistaB;
            plistaB = NULL;
        }
    }
    return salida;
}
*/
/*
int PilaB::Size(){
    while(plistaB && plistaB->anterior) plistaB = plistaB->anterior;
    int cont=0;
    NodoCliente *aux;
    aux = plistaB;
    while(aux){
        cont++;
        aux = aux->siguiente;
    }
    return cont;
}

void Arbol::Clientes(){
    fstream ficheroEntrada;
    string frase;
    string caracter;
    string palabra;
    int idCliente;
    string nombre;
    string telefono;
    string apellido;
    string ciudad;
    int cont=1;

    ficheroEntrada.open("C:/Users/carlo/Desktop/Proyectos y Tareas C++/Proyecto_3/Clientes.txt" , ios::in);
    if (ficheroEntrada.is_open()) {
        while (! ficheroEntrada.eof() ) {
            getline (ficheroEntrada,frase);
            int largo=frase.size();
            for (int i=0;i<=largo;i++){
                caracter=frase[i];
                if (caracter!=";"){
                    palabra+=caracter;
                }
                else{
                    switch(cont){
                        case 1:
                            idCliente=transformar(palabra);
                        case 2:
                            nombre=palabra;
                            break;
                        case 3:
                            apellido=palabra;
                            break;
                        case 4:
                            ciudad=palabra;
                            break;
                    }
                    cont++;
                    palabra="";
                }
            }
            cont=1;
            telefono=palabra;
            palabra="";
            IniciarInsercionB(idCliente,idCliente,nombre,apellido, ciudad, telefono);
        }
        ficheroEntrada.close();
    }
}
 */

#endif // ARBOLCLIENTES_H
