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
        void empilharNoh();
        void imprimirPilha();
};

//Construtor do noh
Pilha::Pilha(){
    topo = NULL;
    tam = 0;
}

//Funcao principal
int main(){
    Pilha pilhanoh;
    char op = 'a';
    int valor = 0;

    while(op != 'q'){
        cout << "\nOperacao: ";
        cin >> op;

        switch(op)
    }
    return 0;
}