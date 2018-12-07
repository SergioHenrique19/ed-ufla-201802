/* 
 * Algoritmo generico de implementacao de lista encadeada 
 * 
 * Copyright 2018 - Sérgio H. M. Garcia
*/

#include <iostream>

using namespace std;

//Classe de noh a ser "alocado" na lista
class Noh{
    friend class Lista;
    private:
        int dado;
        Noh* proximo;
    public:
        Noh(int valor){
            dado = valor;
            proximo = NULL;
        }
};

//Classe de lista dos nohs
class Lista{
    private:
        Noh* primeiro;
        Noh* ultimo;
        int tamanho;
    public:
        Lista();
        ~Lista();
        void inserirNoh(int valor, int pos);
        void inserirNoh(int valor);
        int buscarNoh(int valor);
        void deletarNoh(int pos);
        void imprimirLista();
};

//Construtor da lista
Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

//Destrutor da lista
Lista::~Lista(){
    Noh* aux = primeiro;
    while(aux != NULL){
        delete aux;
        aux = aux->proximo;
        tamanho--;
    }
}

//Inserir novo noh numa posicao especifica da lista -- no inicio, no fim, no meio
void Lista::inserirNoh(int valor, int pos){
    if(tamanho == 0){
        inserirNoh(valor);
    }else{
        if((pos >= 0) and (pos < tamanho)){
            Noh* novo = new Noh(valor);

            if(pos == 0){
                novo->proximo = primeiro;
                primeiro = novo;
            }else if(pos == (tamanho - 1)){
                ultimo->proximo = novo;
                ultimo = novo;
            }else{
                Noh* aux = primeiro;
                int cont = 0;
                while(cont != (pos - 1)){
                    aux = aux->proximo;
                    cont++;
                }

                novo->proximo = aux->proximo;
                aux->proximo = novo;
            }

            tamanho++;
        }else{
            cout << "Posicao invalida..." << endl;
        }
    }
}

//Inserir novo noh no final da lista
void Lista::inserirNoh(int valor){
    Noh* novo = new Noh(valor);

    if((primeiro == NULL) and (ultimo == NULL)){
        primeiro = novo;
        ultimo = novo;
    }else if(ultimo != NULL){
        ultimo->proximo = novo;
        ultimo = novo;
    }

    tamanho++;
}

//Buscar noh pelo valor
int Lista::buscarNoh(int valor){
    Noh* aux = primeiro;
    int cont = 0;
    bool achou = false;

    while((aux != NULL) and (achou != true)){
        if(aux->dado == valor){
            achou = true;
        }else{
            aux = aux->proximo;
            cont++;
        }
    }

    if(achou == true){
        return cont;
    }else{
        return -1;
    }
}

//Deletar noh da lista
void Lista::deletarNoh(int pos){
    if((pos >= 0) and (pos < tamanho)){
        Noh* aux = primeiro;
        Noh* ant = NULL;
        int cont = 0;

        while(cont != pos){
            ant = aux;
            aux = aux->proximo;
            cont++;
        }

        ant->proximo = aux->proximo;
        aux->proximo = NULL;
        delete aux;
        tamanho--;

        cout << "\nNoh removido com sucesso...\n";
    }else{
        cout << "\nEssa posicao não existe...\n";
    }
}

//Imprimir elementos da lista com posicao e valor
void Lista::imprimirLista(){
    Noh* aux = primeiro;
    int cont = 0;

    while(aux != NULL){
        cout << "Posicao: " << cont << " Elemento: " << aux->dado << endl;
        aux = aux->proximo;
        cont++;
    }

    cout << "Tamanho: " << tamanho << endl;
}

//Funcao principal
int main(){
    Lista listanoh;
    char op = 'a';
    int valor = 0;
    int pos = 0;

    while(op != 'q'){
        cout << "\nOperacao: ";
        cin >> op;

        switch(op){
            case 'i':
                cout << "Valor: ";
                cin >> valor;
                listanoh.inserirNoh(valor);
                break;

            case 'j':
                cout << "Posicao: ";
                cin >> pos;
                cout << "Valor: ";
                cin >> valor;
                listanoh.inserirNoh(valor, pos);
                break;
            
            case 'b':
                cout << "Valor: ";
                cin >> valor;
                cout << listanoh.buscarNoh(valor) << endl;
                break;

            case 'd':
                cout << "Posicao: ";
                cin >> pos;
                listanoh.deletarNoh(pos);
                break;

            case 'p':
                listanoh.imprimirLista();
                break;
            
            case 'q':
                cout << "Saindo..." << endl;
                break;

            default:
                cout << "\nComando invalido..." << endl;
                break;
        }
    }

    return 0;
}