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
#include <string.h>

using namespace std;

//Estrutura com os dados do cliente
struct DadosCli{
    string cpf;
    string nome;
};

//Estrutura com os dados da operacao
struct DadosOp{
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
        void empilharOperacao(bool oper, int preco);
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
        void inserirOper(bool oper, int preco, string id);
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

//Inserir a noh-operacao na pilha do cliente desejado
void ListaCliente::inserirOper(bool oper, int preco, string id){
    NohCliente* aux = primeiro;
    bool achou = false;
    
    while(achou == false or aux != NULL){
        if(aux->cliente.cpf == id){
            achou = true;
            aux->operacao->empilharOperacao(oper, preco);
        }else{
            aux = aux->prox;
        }
    }
}

//Buscar cliente na lista de clientes
int ListaCliente::buscarCliente(string id){
    NohCliente* aux = primeiro;
    int cont = 0;

    while(aux != NULL){
        if(aux->cliente.cpf == id){
            cout << "\nCPF: " << aux->cliente.cpf << endl;
            cout << "Nome: " << aux->cliente.nome << endl;
            aux->operacao->imprimirOperacoes();
            return cont;
        }else{
            aux = aux->prox;
        }
        cont++;
    }

    return -1;
}

//Deletar cliente da lista
void ListaCliente::deletarCliente(string id){
    int pos = buscarCliente(id);

    if(pos == -1){
        cout << "Cliente nao cadastrado...";
    }else{
        NohCliente* aux = primeiro;
        NohCliente* ant = NULL;
        int cont = 0;

        while(cont != pos){
            ant = aux;
            aux = aux->prox;
            cont++;
        }

        if(cont > 0 and aux != ultimo){
            ant->prox = aux->prox;
            aux->operacao->limparOperacao();
            delete aux;
        }else if(cont > 0 and aux == ultimo){
            ultimo = ant;
            ant->prox = NULL;
            aux->operacao->limparOperacao();
            delete aux;
        }else if(cont == 0 and primeiro == ultimo){
            ant = aux;
            aux = aux->prox;
            primeiro = NULL;
            ultimo = NULL;
            ant->operacao->limparOperacao();
            delete ant;
        }else if(cont == 0 and primeiro != ultimo){
            ant = aux;
            aux = aux->prox;
            primeiro = aux;
            ant->operacao->limparOperacao();
            delete ant;
        }

        tam--;
    }
}

//Imprimir lista de clientes com seus respectivos dados
void ListaCliente::imprimirCliente(){
    NohCliente* aux = primeiro;
    
    while(aux != NULL){
        cout << "\nCPF: " << aux->cliente.cpf << endl;
        cout << "Nome: " << aux->cliente.nome << endl;
        cout << "Saldo: " << aux->operacao->saldo << endl;

        aux = aux->prox;
    }
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
void PilhaOp::empilharOperacao(bool oper, int preco){
    NohOp* novo = new NohOp();
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
        
        tam++;
    }
}

//Excluir as operacoes do cliente
void PilhaOp::limparOperacao(){
    while(tam != 0){
        delete topo;
        topo = topo->prox;
        tam--;
    }
}

//Imprimir a pilha de operacoes do cliente
void PilhaOp::imprimirOperacoes(){
    NohOp* aux = topo;

    while(aux != NULL){
        if(aux->oper.op == true){
            cout << "OPERACAO: DEBITO";
        }else{
            cout << "OPERACAO: CREDITO";
        }

        cout << endl << "VALOR: " << aux->oper.valor << endl;
        aux = aux->prox;
    }

    cout << "SALDO: " << saldo << endl;
}

//Programa principal
int main(){
    ListaCliente listacli;
    
    string id, nome;
    bool acao = false;
    int preco = 0;
    char op = 'a';
    
    while(op != 'q'){
        cout << "\nOperacao: ";
        cin >> op;
        cout << endl;
        
        switch(op){
            case 'c':   //inserir cliente  ->  ANDAMENTO
                cin.ignore();
                cout << "CPF: ";
                getline(cin, id);
                cout << "Nome: ";
                getline(cin, nome);
                listacli.inserirCliente(id, nome);
                break;
            
            case 'b':   //buscar cliente  ->  ANDAMENTO
                cin.ignore();
                cout << "CPF: ";
                getline(cin, id);
                listacli.buscarCliente(id);
                break;
                
            case 'p':   //imprimir lista de cliente  ->  ANDAMENTO
                listacli.imprimirCliente();
                break;
                
            case 'd':   //deletar cliente  ->  ANDAMENTO
                cin.ignore();
                cout << "CPF: ";
                getline(cin, id);
                listacli.deletarCliente(id);
                break;
                
            case 'o':   //acrescetar operacao  ->  ANDAMENTO
                cin.ignore();
                cout << "CPF: ";
                getline(cin, id);
                cout << "Categoria: ";
                cin >> acao;
                cout << "Valor: ";
                cin >> preco;
                listacli.inserirOper(acao, preco, id);
                break;
            
            case 'q':   //sair
                cout << "Saindo...\n";
                break;
                
            default:
                cout << "Comando invalido...";
                break;
        }
    }
    
    return 0;
}
