#include "arbolclientes.h"

//ARBOL B

void ArregloClaves::InsertarClave(pNodoCliente Clave, int Numero){
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
