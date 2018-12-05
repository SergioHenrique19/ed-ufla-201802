/*
 * Trabalho de Estrutura de Dados
 * 
 * Sistema de cadastro e pagamento com Arduino
 *  e uso das estruturas de dados lista e pilha
 * 
 * Copyright 2018 by João Victor Teófilo Salgado,
 *  Layse Cristina Silva Garcia e Sérgio Henrique Menta Garcia
 * 
 * Arquivo principal
*/

#include <iostream>

using namespace std;

//Estrutura com os dados do cliente
struct DadosCli{
    string cpf;
    string nome;
};

//Estrutura com os dados da operacao
struct DadosOp{
    string ident;
    bool op;   //true: debitar(sub), false: creditar(add)
    int valor;
};

//Classe NohOp para cadastrar as operacoes do cliente
class NohOp{
    friend class PilhaOp;

    private:
        DadosOp oper;
        NohOp* prox;
    public:
        NohOp(){   //Construtor do NohOp
            oper.ident = " ";
            oper.op = 0;
            oper.valor = 0;
        }
};

//Classe PilhaOp - todas as operacoes feitas pelo cliente
class PilhaOp{
    friend class ListaCliente;

    private:
        NohOp* topo;
        int tam;
        int saldo;
    public:
        PilhaOp();
        ~PilhaOp();
        void empilharOperacao(bool oper, int preco, string id);
        void limparOperacao();
        void imprimirOperacoes();
};

//Classe NohCliente para cadastrar clientes
class NohCliente{
    friend class ListaCliente;

    private:
        DadosCli cliente;
        NohCliente* prox;
        PilhaOp* operacao;
    public:
        NohCliente(){   //Construtor do NohCliente
            cliente.cpf = " ";
            cliente.nome = " ";
        }
};

//Classe ListaCliente - relacao dos clientes cadastrados
class ListaCliente{
    private:
        NohCliente* primeiro;
        NohCliente* ultimo;
        int tam;
    public:
        ListaCliente();
        ~ListaCliente();
        void inserirCliente(string id, string nome);
        int buscarCliente(string id);
        void deletarCliente(string id);
        void imprimirCliente();
};
 
/*====================== IMPLEMENTACAO DO CLIENTE =====================================*/

//Construtor da lista de clientes
ListaCliente::ListaCliente(){
    primeiro = NULL;
    ultimo = NULL;
    tam = 0;
}

//Destrutor da lista de clientes
ListaCliente::~ListaCliente(){
    NohCliente* aux = primeiro;
    NohCliente* prox;

    while(aux != NULL){
        prox = aux->prox;
        delete aux;
        tam--;
        aux = prox;
    }
}

//Inserir novo clinte na lista de clientes
void ListaCliente::inserirCliente(string id, string nome){
    NohCliente* novo = new NohCliente();
    novo->cliente.cpf = id;
    novo->cliente.nome = nome;

    if(novo){
        if(primeiro == NULL){
            primeiro = novo;
            ultimo = novo;
        }else{
            ultimo->prox = novo;
            ultimo = novo;
        }
        tam++;
    }
}

//Buscar cliente na lista de clientes
int ListaCliente::buscarCliente(string id){
    NohCliente* aux = primeiro;
    int cont = 0;

    while(aux != NULL){
        if(aux->cliente.cpf == id){
            cout << "Saldo: " << aux->operacao->saldo << endl;
            return cont;
        }else{
            aux = aux->prox;
        }
        cont++;
    }

    return -1;
}

/*====================== IMPLEMENTACAO DA OPERACAO =====================================*/

//Construtor da pilha de operacoes do cliente
PilhaOp::PilhaOp(){
    topo = NULL;
    tam = 0;
    saldo = 0;
}

//Destrutor da pilha de operacoes do cliente
PilhaOp::~PilhaOp(){
    NohOp* aux = topo;
    NohOp* prox = NULL;

    while(aux != NULL){
        prox = aux->prox;
        delete aux;
        tam--;
        aux = prox;
    }

    saldo = 0;
}

//Empilhar/cadastrar nova operacao do cliente
void PilhaOp::empilharOperacao(bool oper, int preco, string id){
    NohOp* novo = new NohOp();
    novo->oper.ident = id;
    novo->oper.op = oper;
    novo->oper.valor = preco;

    if(novo){
        novo->prox = topo;
        topo = novo;
        tam++;
        if(novo->oper.op == 0){
            saldo+=novo->oper.valor;
        }else{
            saldo-=novo->oper.valor;
        }
    }
}

//Excluir as operacoes
void PilhaOp::limparOperacao(){
    
}

//Programa principal
int main(){
    return 0;
}
