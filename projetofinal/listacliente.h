#ifndef LISTACLIENTE_H
#define LISTACLIENTE_H
#include "nohcliente.h"

class ListaCliente{
    private:
        NohCliente* primeiro;
        NohCliente* ultimo;
    
    public:
        ListaCliente();
        ~ListaCliente();
        void inserirCliente();
};

#endif