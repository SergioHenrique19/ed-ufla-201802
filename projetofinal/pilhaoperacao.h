#ifndef PILHAOPERACAO_H
#define PILHAOPERACAO_H
#include "nohoperacao.h"

//Classe com as operacoes feitas pelo cliente
class PilhaOperacao{
    friend class ListaCliente;

    private:
        NohOperacao* topo;
        int saldo;
    public:
        PilhaOperacao();
        ~PilhaOperacao();
        void empilharOperacao(bool oper, int preco);
        void imprimirOperacoes();
};

#endif