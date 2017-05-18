#include <sstream>
#include "arbolclientes.h"
//#include <iostream>
//#include <string>
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

void ArbolClientes::IniciarInsercionB(NodoCliente *_C1)
{
    ApuntadorPagina Raiz = raizB;
    InsertarB(_C1, Raiz);
}

void ArbolClientes::InsertarB(NodoCliente *_C1, ApuntadorPagina Raiz){
    bool EA;
    NodoCliente *_X = NULL;
    ApuntadorPagina Xr = NULL;

    EmpujarB(_C1, Raiz, EA, _X, Xr);
    /*if (Raiz->Esta) {
        Raiz->Esta = false;
    }*/
    if(EA){
        ApuntadorPagina P = new Pagina();
        P->cuenta = 1;
        P->Claves->arregloClaves[1] = _X;
        P->Ramas->arregloRamas[0] = Raiz;
        P->Ramas->arregloRamas[1] = Xr;

        raizB = P;
    }


}

void ArbolClientes::EmpujarB(NodoCliente *_C1,ApuntadorPagina R, bool &EA, NodoCliente *&Mdana, ApuntadorPagina &Xr)
{
    int K = 0;
    bool Esta = false;

    if(R == NULL){
        EA = true;
        Mdana = _C1;
        Xr = NULL;

    }else
    {
        BuscarNodoB(R ,_C1->getID(),Esta, K);
        if(Esta){
            std::cout << "Elemento Repetido" << std::endl;
        }else{
            EmpujarB(_C1, R->Ramas->ObtenerRama(K), EA, Mdana, Xr);
            if(EA) {
                if (R->cuenta < 4) {
                    EA = false;
                    MeterHojaB(Mdana, Xr, R, K);
                } else {
                    EA = true;
                    DividirNodoB(Mdana, Xr, R, K, Mdana, Xr);
                }
            }
        }
    }
}

void ArbolClientes::BuscarNodoB(ApuntadorPagina P, int Clave, bool &Encontrado, int &K)
{
    if(Clave < P->Claves->arregloClaves[1]->getID()){
        Encontrado = false;
        K = 0;
    }
    else{
        K = P->cuenta;
        while(Clave < P->Claves->arregloClaves[K]->getID() && K > 1){
            K--;
        }
        if(Clave == P->Claves->arregloClaves[K]->getID()){
            Encontrado = true;
        }
    }
}

void ArbolClientes::MeterHojaB(NodoCliente *_X, ApuntadorPagina Xder, ApuntadorPagina &P, int K)
{
    int I;
    for(I=P->cuenta; I>=K+1; I--){
        P->Claves->arregloClaves[I+1] = P->Claves->ObtenerApuntadorClave(I);
        P->Ramas->arregloRamas[I+1] = P->Ramas->ObtenerRama(I);
        I--;
    }
    P->Claves->arregloClaves[K+1] = _X;
    P->Ramas->arregloRamas[K+1] = Xder;
    P->cuenta++;

}

void ArbolClientes::DividirNodoB(NodoCliente *_X, ApuntadorPagina Xder, ApuntadorPagina &P, int K, NodoCliente *&Mda, ApuntadorPagina &Mder) {
    int I;
    int Posmda;

    if(K <= 2){
        Posmda = 2;
    }
    else{
        Posmda = 3;
    }
    Mder = new Pagina();
    for(I=Posmda+1; I<=4; I++){
        Mder->Claves->arregloClaves[I-Posmda] = P->Claves->ObtenerApuntadorClave(I);
        Mder->Ramas->arregloRamas[I-Posmda] = P->Ramas->ObtenerRama(I);
    }
    Mder->cuenta = 4 - Posmda;
    P->cuenta = Posmda;

    if(K <= 2){
        MeterHojaB(_X, Xder, P,  K);
    }
    else{
        MeterHojaB(_X, Xder, Mder,  K-Posmda);
    }
    Mda = P->Claves->ObtenerApuntadorClave(P->cuenta);
    Mder->Ramas->arregloRamas[0] = P->Ramas->ObtenerRama(P->cuenta);
    P->cuenta--;
}

void ArbolClientes::IniciarRecorridoB()
{
    ApuntadorPagina Raiz = raizB;
    RecorridoInordenB(Raiz);
}



void ArbolClientes::existeCliente(ApuntadorPagina Raiz, int _Numero, bool& _existe) {
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            if (Recorrido->getID() == _Numero)
                _existe = true;

            if(I==1){
                existeCliente(Raiz->Ramas->ObtenerRama(I-1), _Numero, _existe);
            }
            existeCliente(Raiz->Ramas->ObtenerRama(I), _Numero, _existe);

            I++;
        }
    }

}


void ArbolClientes::agregarCompra(ApuntadorPagina Raiz, int _codCliente) {
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            if (Recorrido->getID() == _codCliente){
                Recorrido->aumentarVentas();
            }

            if(I==1){
                agregarCompra(Raiz->Ramas->ObtenerRama(I-1),_codCliente);
            }
            agregarCompra(Raiz->Ramas->ObtenerRama(I),_codCliente);

            I++;
        }
    }

}


void ArbolClientes::getClienteMasCompras(ApuntadorPagina Raiz, NodoCliente *&_clienteMasCompras) {
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            if (Recorrido->cantidadDeCompras > _clienteMasCompras->cantidadDeCompras) _clienteMasCompras = Recorrido;

            if(I==1){
                getClienteMasCompras(Raiz->Ramas->ObtenerRama(I-1),_clienteMasCompras);
            }
            getClienteMasCompras(Raiz->Ramas->ObtenerRama(I),_clienteMasCompras);

            I++;
        }
    }

}

void ArbolClientes::getCliente(ApuntadorPagina Raiz, NodoCliente *&_cliente, int _id) {
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            if (Recorrido->getID() == _id) _cliente = Recorrido;

            if(I==1){
                getCliente(Raiz->Ramas->ObtenerRama(I-1), _cliente, _id);
            }
            getCliente(Raiz->Ramas->ObtenerRama(I), _cliente, _id);

            I++;
        }
    }
}

void ArbolClientes::PreordenSocket(ApuntadorPagina _raiz, std::string &_string) {
    if(_raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= _raiz->cuenta){

            pNodoCliente Recorrido = _raiz->Claves->ObtenerApuntadorClave(I);
            std::stringstream flujo;
            flujo << Recorrido->getID();
            std::string nombre = flujo.str();
            _string += nombre + "\n";

            if(I==1){
                PreordenSocket(_raiz->Ramas->ObtenerRama(I-1), _string);
            }
            PreordenSocket(_raiz->Ramas->ObtenerRama(I), _string);
            I++;
        }
    }

}

void ArbolClientes::RecorridoInordenB(ApuntadorPagina Raiz){
    if(Raiz == NULL){
        return;
    }
    else{
        //RecorridoInordenB(Raiz->Ramas->ObtenerRama(0));
        int I = 1;
        while(I <= Raiz->cuenta){
            NodoCliente* Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            std::cout<< "idCliente: "<< Recorrido->getID() << std::endl;
            std::cout << "\n" << std::endl;

            if(I==1){
                RecorridoInordenB(Raiz->Ramas->ObtenerRama(I-1));
            }
            RecorridoInordenB(Raiz->Ramas->ObtenerRama(I));

            I++;
        }
    }
}

void ArbolClientes::BuscarNodo(int Clave, ApuntadorPagina P, bool & Encontrado, int & K)
{
// Este método examina la pagina referenciada por P. De no //encontrarse el valor nuevo, K será el índice de la rama por //donde bajar

    {
        int C =  P->Claves->ObtenerApuntadorClave(1)->getID();
        if (Clave < C)   // recuerde que los arreglos aquí inician en 1
        {
            //P->K = 0;
            //P->Esta = 0;
            Encontrado=false;
            K=0; //rama por donde descender
        }
        else
        {
            //Examina claves de la pagina
            K=P->cuenta; // Numero de claves de la Pagina
            while(Clave<P->Claves->ObtenerApuntadorClave(K)->getID() and (K>1))
            {
                K=K-1;
            }

            if (Clave==P->Claves->ObtenerApuntadorClave(K)->getID()){
                Encontrado=true;
            }

        }
    }
}


//Tiene como funcion devolver la nueva raiz si la raiz inicial se ha quedado sin claves
void ArbolClientes::Eliminar (int C1, ApuntadorPagina Raiz){

    bool Encontrado;
    ApuntadorPagina P;
    {
        EliminarRegistro(C1,Raiz,Encontrado);
        if (!Encontrado){
            std::cout<< "El elemento no se encuentra en el árbol"<<std::endl;
        }

        else{

            if (Raiz->cuenta == 0) // la raíz ha quedado vacia
            {
                P= Raiz;
                Raiz= Raiz->Ramas->ObtenerRama(0);
                delete(P);
            }
        }
    }
}



//Este metodo controla el proceso de borrado de una clave
//Primero busca en el nodo donde se encuentra la clave a eliminar
//Si es una hoja, llama a elimina
// Si no es hoja, se busca el sucesor inmediato, se coloca en el elemento a eliminar
//Luego se suprime el sucesor  en la hoja
void ArbolClientes::EliminarRegistro(int C1, ApuntadorPagina Raiz, bool & Encontrado)
{
    int K;

    if (BVacio())
        Encontrado= false; // se ha llegado debajo de una hoja, la clave no esta en el arbol
    else
    {
        //with Raiz
        {
            BuscarNodo(C1,Raiz,Encontrado,K);
            if (Encontrado)
            {
                if (Raiz->Ramas->ObtenerRama(K-1)==NULL)//Las ramas estan indexadas desde 0 a Max, por lo que este nodo es hoja
                {
                    Quitar(Raiz,K);
                    std::cout<<"Despues de Quitar: " << Raiz->Claves->ObtenerApuntadorClave(1)->getID()<<std::endl;

                }
                else //No es hoja
                {
                    Sucesor(Raiz,K); //reemplaza  Claves[K] por su sucesor
                    EliminarRegistro(Raiz->Claves->ObtenerApuntadorClave(K)->getID(), Raiz->Ramas->ObtenerRama(K),Encontrado);  //Elimina la clave sucesora en su nodo
                    if (!Encontrado) //inconsistencia debe esta en el nodo
                    {std::cout << "Error en el proceso"<<std::endl;}
                }
            }
            else // No ha sido localizada la clave
            {
                EliminarRegistro (C1,Raiz->Ramas->arregloRamas[K],Encontrado);
                // Las llamadas recursivas retornan el control a este punto,
                // se comprueba que el nodo hijo mantenga un numero
                // claves igual o mayor que el minimo necesario
                if (Raiz->Ramas->ObtenerRama(K) !=NULL){

                    if (Raiz->Ramas->ObtenerRama(K)->cuenta<5){

                        Restablecer(Raiz,K);
                    }
                }
            }
        }
    }
}



//recibe la direccion del nodo y la posicion de la clave a eliminar.
//Elimina la clave junto con la rama que le corresponde
void ArbolClientes::Quitar(ApuntadorPagina & P, int& K)
{
    int J; //entero
    //With P

    {
        for (J= K+1;J <= P->cuenta; J++)
        {
            //	P->Claves->ObtenerApuntadorClave(J) = P->Claves->ObtenerApuntadorClave(J-1);

            //P->Claves[J-1] = P->Claves[J];
            //P->Claves[J-1].ObtenerClave(0);
            //	P->Ramas[J-1] =  P->Ramas[J];

//	cout<<	"DAAAAAAAAAAAAAAAAH: "<<P->Claves->ObtenerApuntadorClave(J)->valorCl->getCedula()<<endl;


            //	nodo* temp = P->Claves->ObtenerApuntadorClave(J);
            P->Claves->arregloClaves[J-1] = P->Claves->ObtenerApuntadorClave(J);
            //	nodo* temp2 = P->Claves->ObtenerApuntadorClave(J-1);
            //   temp2 = temp;   //Desplaza una posicion a la izquierda, con ello elimina la clave}

            //    cout<<temp2->valorCl->getCedula()<<endl;
            //delete (temp);

            P->Ramas->arregloRamas[J-1] = P->Ramas->ObtenerRama(J);
            //   ApuntadorPagina temp3 = P->Ramas->ObtenerRama(J);
            //     ApuntadorPagina temp4 = P->Ramas->ObtenerRama(J-1);
            //   temp4 = temp3;

        }
        P->cuenta=(P->cuenta)-1;
    }

}


//Busca la clave inmediatamente sucesor de la clave k y reemplaza la clave K
void ArbolClientes::Sucesor(ApuntadorPagina P, int& K)
{
    ApuntadorPagina Q;

    Q = P->Ramas->ObtenerRama(K);

    while (Q->Ramas->ObtenerRama(0) != NULL){
        Q = Q->Ramas->ObtenerRama(0);
    }

    P->Claves[K] = Q->Claves[1];
}



//Este realiza las acciones mas complejas del proceso. Restaura el nodo P.Ramas[K]
//el cual ha quedado con un numero menor de claves, menos que el minimo
void ArbolClientes::Restablecer (ApuntadorPagina P, int& K)
{
    if (K>0)   //Tiene hermano izquierdo
    {
        if (P->Ramas->ObtenerRama(K-1)->cuenta > 5) //Tiene mas claves que el minimo y por tanto puede desplazarse una clave
        {
            MoverDerecha(P,K);
        }
        else
        {
            Combina(P,K);
        }
    }
    else
    {//solo tiene hermano derecho
        if (P->Ramas->ObtenerRama(1)->cuenta > 5)
        {
            //Tiene mas claves que el minimo
            int int_temp = 1;
            MoverIzquierda(P, int_temp);
        }
        else{
            int int_temp = 1;
            Combina(P, int_temp);
        }
    }
}




//Mueve una clave del nodo antecedente(P) al nodo que se esta restaurando
//Asciende la clave mayor del hermano izquierdo al nodo antecedente
void ArbolClientes::MoverDerecha(ApuntadorPagina P, int& K)
//En este metodo se deja hueco en el nodo P.Ramas[K] que es el nodo que tiene menos claves que elminimo
//necesario, inserta la clave k del nodo antecedente y a su vez asciende la clave mayor ( la mas a la derecha)
//del hermano izquierdo
{
    int J;
    //with P.Ramas[K]
    {
        for (J= P->Ramas->ObtenerRama(K)->cuenta; J>=1; J--)
        {
            P->Ramas->ObtenerRama(K)->Claves[J+1]= P->Ramas->ObtenerRama(K)->Claves[J];
            P->Ramas->ObtenerRama(K)->Ramas[J+1]=P->Ramas->ObtenerRama(K)->Ramas[J];
        }
        P->Ramas->ObtenerRama(K)->cuenta=J= P->Ramas->ObtenerRama(K)->cuenta+1;
        P->Ramas->ObtenerRama(K)->Ramas[1] = P->Ramas->ObtenerRama(K)->Ramas[0];
        P->Ramas->ObtenerRama(K)->Claves[1] = P->Claves[K]; // baja la clave del nodo padre
    }
    //Ahora sube la clave desde el hermano izquierdo al nodo padre, para reemplazar la que bajo
    //with P.Ramas[K-1] // hermano izquierdo
    {
        P->Claves[K]=P->Ramas->ObtenerRama(K-1)->Claves[P->Ramas->ObtenerRama(K-1)->cuenta];
        P->Ramas->ObtenerRama(K)->Ramas[0] = P->Ramas->ObtenerRama(K-1)->Ramas[P->Ramas->ObtenerRama(K-1)->cuenta];
        P->Ramas->ObtenerRama(K-1)->cuenta = P->Ramas->ObtenerRama(K-1)->cuenta-1;
    }
}




//Ahora la clave que asciende al nodo antecedente es la clave menor(izquierda) del nodo a restaurar
void ArbolClientes::MoverIzquierda (ApuntadorPagina P, int& K)
{
    int J;
    //with P.Ramas[K-1]// es el nodo con menos claves que el minimo
    {
        P->Ramas->ObtenerRama(K-1)->cuenta=P->Ramas->ObtenerRama(K-1)->cuenta+1;
        P->Ramas->ObtenerRama(K-1)->Claves[P->Ramas->ObtenerRama(K-1)->cuenta]=P->Claves[K];
        P->Ramas->ObtenerRama(K-1)->Ramas[P->Ramas->ObtenerRama(K-1)->cuenta]=P->Ramas->ObtenerRama(K)->Ramas[0];
        // baja la clave del nodo padre
    }
    //with P.Ramas[K] // hermano derecho
    {
        P->Claves[K]=P->Ramas->ObtenerRama(K)->Claves[1];   //sube al nodo padre de la clave 1 del hermano derecho, sustituye a la que bajo
        P->Ramas[0]=P->Ramas->ObtenerRama(K)->Ramas[1];
        P->Ramas->ObtenerRama(K)->cuenta=P->Ramas->ObtenerRama(K)->cuenta-1;

        for (J=1; J<=P->Ramas->ObtenerRama(K)->cuenta; J++)
        {
            P->Ramas->ObtenerRama(K)->Claves[J]= P->Ramas->ObtenerRama(K)->Claves[J+1];
            P->Ramas->ObtenerRama(K)->Ramas[J] = P->Ramas->ObtenerRama(K)->Ramas[J+1];
        }
    }
}



//Este metodo forma un solo nodo
//Combina el nodo que esta en la rama K con el que esta en la rama k-1 y la clave mediana de ambos
// que se encuentra en el nodo ascendente.
void ArbolClientes::Combina(ApuntadorPagina P, int& K)
//forma un nuevo nodo con el hermano izquierdo la mediana ente el nodo problema y el hermano izquierdo
//situado en el nodo padre y las claves del nodo problema.
{
    int J;
    ApuntadorPagina Q;
    Q = P->Ramas->ObtenerRama(K);

    //with P.Ramas[K-1]//hermano izquierdo
    {
        P->Ramas->ObtenerRama(K-1)->cuenta = P->Ramas->ObtenerRama(K-1)->cuenta+1;
        P->Ramas->ObtenerRama(K-1)->Claves[P->Ramas->ObtenerRama(K-1)->cuenta]=P->Claves[K];// baja clave mediana desde el nodo padre
        P->Ramas->ObtenerRama(K-1)->Ramas[P->Ramas->ObtenerRama(K-1)->cuenta] = Q->Ramas[0];

        for (J=1; J<= Q->cuenta; J++)
        {
            P->Ramas->ObtenerRama(K-1)->cuenta = P->Ramas->ObtenerRama(K-1)->cuenta+1;
            P->Ramas->ObtenerRama(K-1)->Claves[P->Ramas->ObtenerRama(K-1)->cuenta] = Q->Claves[J];
            P->Ramas->ObtenerRama(K-1)->Ramas[P->Ramas->ObtenerRama(K-1)->cuenta] = Q->Ramas[J];
        }
    }
    //Reajustadas las claves y ramas del nodo padre debido a que antes ascendio la clave K
    //with P

    for (J=K; J<= P->Ramas->ObtenerRama(K-1)->cuenta-1; J++)
    {
        P->Claves[J]=P->Claves[J+1];
        P->Ramas[J]=P->Ramas[J+1];
    }
    P->cuenta=P->cuenta-1;

    delete(Q);
}
