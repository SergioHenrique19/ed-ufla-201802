#include <iostream>

using namespace std;

//Classe operacao
class NohOperacao{
    friend class PilhaOp;
    private:
        bool op;   //true: debitar(sub), false: creditar(add)
        int valor;
        NohOperacao* proximo;

    public:
        NohOperacao(){
            op = false;
            valor = 0;
            proximo = NULL;
        }
};

//Classe-pilha de operacoes feitas por um cliente
class PilhaOp{
    private:
        NohOperacao* topo;
        int tamanho;

    public:
        PilhaOp();
        ~PilhaOp();
        void empilhar(bool oper, int preco);
        void imprimir();
};

//Construtor da pilha de operacoes
PilhaOp::PilhaOp(){
    topo = NULL;
    tamanho = 0;
}

//Destrutor da pilha de operacoes
PilhaOp::~PilhaOp(){
    NohOperacao* aux = topo;
    NohOperacao* prox = NULL;

    while(aux != NULL){
        prox = aux->proximo;
        delete aux;
        aux = prox;
    }
}

void PilhaOp::empilhar(bool oper, int preco){
    NohOperacao* novo = new NohOperacao();
    novo->op = oper;
    novo->valor = preco;

    if(novo){
        novo->proximo = topo;
        topo = novo;
        tamanho++;
    }
}

void PilhaOp::imprimir(){
    NohOperacao* aux = topo;
    int saldo = 0;

    while(aux != NULL){
        if(aux->op == true){
            saldo-=aux->valor;
            cout << "OPERACAO: DEBITO";
        }else{
            saldo+=aux->valor;
            cout << "OPERACAO: CREDITO";
        }

        cout << endl << "VALOR: " << aux->valor << endl;
        aux = aux->proximo;
    }

    cout << "SALDO: " << saldo << endl;
}

int main(){
    PilhaOp pilhaop;
    bool oper;
    int preco;
    char op = 'a';

    while(op != 'q'){
        cout << "\nOperacao: ";
        cin >> op;

        switch(op){
            case 'i':
                cout << "\nCategoria: ";
                cin >> oper;
                cout << "Valor: ";
                cin >> preco;
                pilhaop.empilhar(oper, preco);
                break;
            
            case 'p':
                pilhaop.imprimir();
                break;

            case 'q':
                cout << "Saindo..." << endl;
                break;
            
            default:
                cout << "Comando invalido" << endl;
                break;
        }
    }

    return 0;
}
