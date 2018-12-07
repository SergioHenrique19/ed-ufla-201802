/* 
 * Algoritmo generico de implementacao de fila encadeada 
 * 
 * Copyright 2018 - Sérgio H. M. Garcia
*/

#include <iostream>

using namespace std;

//Classe noh a ser inserido na fila
class Noh{
    friend class Fila;

    private:
        int dado;
        Noh* prox;
    
    public:
        Noh(int valor){
            dado = valor;
            prox = NULL;
        }
};

//Classe da fila
class Fila{
    private:
        Noh* primeiro;
        Noh* ultimo;
        int tam;

    public:
        Fila();
        ~Fila();
        int enfilerar(int valor);
        int desenfilerar();
        void limparFila();
};

//Construtor da fila
Fila::Fila(){
    primeiro = NULL;
    ultimo = NULL;
    tam = 0;
}

//Destrutor da fila
Fila::~Fila(){
    limparFila();
}

//Enfilerar -- inserir elemento no final da fila
int Fila::enfilerar(int valor){
    Noh* novo = new Noh(valor);

    if((primeiro == NULL) and (ultimo == NULL)){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->prox = novo;
        ultimo = novo;
    }

    tam++;

    return tam;
}

//Desenfilerar -- retirar primeiro elemento da fila
int Fila::desenfilerar(){
    if(primeiro != NULL){
        Noh* aux = primeiro;

        primeiro = primeiro->prox;
        delete aux;
        tam--;

        if(tam == 0){
            ultimo = NULL;
        }

        return tam;
    }else{
        return tam;
    }
}

//Limpar toda a fila
void Fila::limparFila(){
    while(primeiro != NULL){
        Noh* aux = primeiro;
        int result = aux->dado;

        primeiro = primeiro->prox;
        delete aux;
        tam--;

        if(tam == 0){
            ultimo = NULL;
        }

        cout << result << " ";
    }

    cout << endl;
}

//Funcao principal
int main(){
    Fila filanoh;
    char op = 'a';
    int valor = 0;

    while(op != 'q'){
        cout << "\nOperacao: ";
        cin >> op;

        switch(op){
            case 'i':
                cout << "Valor: ";
                cin >> valor;
                cout << "Tamanho: " << filanoh.enfilerar(valor) << endl;
                break;
            
            case 'd':
                cout << "Tamanho: " << filanoh.desenfilerar() << endl;
                break;
            
            case 'l':
                filanoh.limparFila();
                break;
            
            case 'q':
                cout << "Saindo...\n";
                filanoh.limparFila();
                break;
            
            default:
                cout << "Comando invalido\n";
                break;
        }
    }
    return 0;
}
