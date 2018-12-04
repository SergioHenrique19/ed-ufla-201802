#include <iostream>
#include <string.h>

using namespace std;

//Classe cliente
class NohCliente{
    friend class ListaCliente;
    private:
        string cpf;
        string nome;
        int saldo;
        NohCliente* proximo;

    public:
        NohCliente(){   //Construtor da classe Cliente
            cpf = " ";
            nome = " ";
            saldo = 0;
            proximo = NULL;
        }
};

//Classe-lista de clientes cadastrados
class ListaCliente{
    private:
        NohCliente* primeiroCli;
        NohCliente* ultimoCli;
        int tamanho;
    
    public:
        ListaCliente();
        ~ListaCliente();
        void inserir(string id, string nome);
        int buscar(string id);
        void deletar(string id);
        void imprimir();        
};

//Construtor da lista de clientes
ListaCliente::ListaCliente(){
    primeiroCli = NULL;
    ultimoCli = NULL;
    tamanho = 0;
}

//Destrutor da lista de clientes
ListaCliente::~ListaCliente(){
    NohCliente* aux = primeiroCli;
    NohCliente* prox;

    while(aux != NULL){
        prox = aux->proximo;
        delete aux;
        aux = prox;
    }
}

//Inserir cliente na lista
void ListaCliente::inserir(string id, string nome){
    NohCliente* novo = new NohCliente();
    novo->cpf = id;
    novo->nome = nome;

    if(novo){
        if(primeiroCli == NULL){
            primeiroCli = novo;
            ultimoCli = novo;
        }else{
            ultimoCli->proximo = novo;
            ultimoCli = novo;
        }
        tamanho++;
    }
}

//Buscar cliente na lista
int ListaCliente::buscar(string id){
    NohCliente* aux = primeiroCli;
    int cont = 0;

    while(aux != NULL){
        if(aux->cpf == id){
            return cont;
        }else{
            aux = aux->proximo;
        }
        cont++;
    }

    return -1;
}

//Deletar cliente da lista
void ListaCliente::deletar(string id){
    int pos = buscar(id);

    if(pos == -1){
        cout << "Cliente nao cadastrado...";
    }else{
        NohCliente* aux = primeiroCli;
        NohCliente* ant = NULL;
        int cont = 0;

        while(cont != pos){
            ant = aux;
            aux = aux->proximo;
            cont++;
        }

        if(cont > 0 and aux != ultimoCli){
            ant->proximo = aux->proximo;
            delete aux;
        }else if(cont > 0 and aux == ultimoCli){
            ultimoCli = ant;
            ant->proximo = NULL;
            delete aux;
        }else if(cont == 0 and primeiroCli == ultimoCli){
            ant = aux;
            aux = aux->proximo;
            primeiroCli = NULL;
            ultimoCli = NULL;
            delete ant;
        }else if(cont == 0 and primeiroCli != ultimoCli){
            ant = aux;
            aux = aux->proximo;
            primeiroCli = aux;
            delete ant;
        }

        tamanho--;
    }
}

//Imprimir lista de clientes
void ListaCliente::imprimir(){
    NohCliente* aux = primeiroCli;
    
    while(aux != NULL){
        cout << "\nCPF: " << aux->cpf << endl;
        cout << "Nome: " << aux->nome << endl;
        cout << "Saldo: " << aux->saldo << endl;

        aux = aux->proximo;
    }
}

//Bagaca acontecendo
int main(){
    ListaCliente listacliente;
    char op = 'a';
    string id;
    string nome;

    while(op != 'q'){
        cout << "\nOperacao: ";
        cin >> op;

        switch(op){
            case 'i':   //inserir cliente na lista -> FUNCIONANDO
                cin.ignore();
                cout << "CPF: ";
                getline(cin, id);
                cout << "Nome: ";
                getline(cin, nome);
                listacliente.inserir(id, nome);
                break;
            
            case 'b':   //buscar cliente na lista -> FUNCIONANDO
                cin.ignore();
                cout << "CPF: ";
                getline(cin, id);
                listacliente.buscar(id);
                break;
            
            case 'd':   //deletar cliente na lista -> FUNCIONANDO                
                cin.ignore();
                cout << "CPF: ";
                getline(cin, id);
                listacliente.deletar(id);
                break;

            case 'p':   //imprimir lista de cliente -> FUNCIONANDO
                listacliente.imprimir();
                break;
            
            case 'q':
                cout << "Saindo...\n";
                break;
            
            default:
                cout << "Comando invalido";
                break;
        }
    }

    return 0;
}
