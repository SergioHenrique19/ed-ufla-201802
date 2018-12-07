/* 
 * Algoritmo generico de implementacao de pilha encadeada 
 * 
 * Copyright 2018 - Sérgio H. M. Garcia
*/

#include <iostream>

using namespace std;

//Classe de noh a ser "alocado" na pilha
class Noh{
    friend class Pilha;

    private:
        int dado;
        Noh* prox;
    
    public:
        Noh(int valor){
            dado = valor;
            prox = NULL;
        }
};

//Classe de pilha dos nohs
class Pilha{
    private:
        Noh* topo;
        int tam;
    
    public:
        Pilha();
        ~Pilha();
        int empilharNoh(int valor);
        int desempilharNoh();
        int espiaTopo();
        void limparPilha();

};

//Construtor do noh
Pilha::Pilha(){
    topo = NULL;
    tam = 0;
}

//Destrutor da pilha
Pilha::~Pilha(){
    limparPilha();
}

//Empilhar novo noh
int Pilha::empilharNoh(int valor){
    Noh* novo = new Noh(valor);

    if(topo == NULL){
        topo = novo;
    }else{
        novo->prox = topo;
        topo = novo;
    }

    tam++;

    return tam;
}

//Desempilhar topo da pilha
int Pilha::desempilharNoh(){
    if(topo != NULL){
        Noh* aux = topo;
        int result = aux->dado;

        topo = topo->prox;
        delete aux;
        tam--;

        return result;
    }else{
        return -1;
    }
}

//Espia o topo da pilha
int Pilha::espiaTopo(){
    if(topo != NULL){
        return topo->dado;
    }else{
        return -1;
    }
}

//Limpar a pilha -- remover todo os elementos
void Pilha::limparPilha(){
    while(topo != NULL){
        Noh* aux = topo;
        int val = topo->dado;

        topo = topo->prox;
        delete aux;
        tam--;

        cout << val << " ";
    }
}

//Funcao principal
int main(){
    Pilha pilhanoh;
    char op = 'a';
    int valor = 0;

    while(op != 'q'){
        cout << "\nOperacao: ";
        cin >> op;

        switch(op){
            case 'i':
                cout << "Valor: ";
                cin >> valor;
                cout << "Tamanho: " << pilhanoh.empilharNoh(valor);
                break;

            case 'e':
                cout << pilhanoh.espiaTopo();
                break;

            case 'd':
                cout << "Resultado: " << pilhanoh.desempilharNoh();
                break;
            
            case 'l':
                pilhanoh.limparPilha();
                break;
            
            case 'q':
                cout << "Saindo...\n";
                break;
            
            default:
                cout << "\nComando invalido...\n";
                break;
        }
    }
    return 0;
}