#ifndef NOHCLIENTE_H
#define NOHCLIENTE_H
#include <string.h>
#include "pilhaoperacao.h"

//Estrutura de dados do cliente
struct DadosCli{
    string cpf;
    string nome;
};

//Classe do noh-cliente
class NohCliente{
    friend class ListaCliente;

    private:
        DadosCli cliente;
        NohCliente* proximo;
        PilhaOperacao* operacao;
        PilhaOperacao operacoes;
    
    public:
        NohCliente();
};

#endif