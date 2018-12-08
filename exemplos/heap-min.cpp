/*
 * Algoritmo generico de minheap
 * 
 * Copyright 2018 - Sérgio H. M. Garcia
*/

#include <iostream>
#include <algorithm>

using namespace std;

//Classe do minheap
class MinHeap{
    private:
        int* vetDados;
        int tam;
    
    public:
        MinHeap(int vetor[], int com);
        ~MinHeap();
        int pai(int i){ return ((i - 1) / 2); }
        int esquerdo(int i){ return (2 * i + 1); }
        int direito(int i){ return (2 * i + 2); }
        void corrigeDescendo(int i, int j);
};

//Construtor do minheap -- heapify
MinHeap::MinHeap(int vetor[], int com){
    vetDados = new int[com];
    vetDados = vetor;
    tam = com;
}

//Destrutor do minheap
MinHeap::~MinHeap(){
    delete[] vetDados;
}

//Corrige descendo -- geralmente utilizado para retirar a raiz
void MinHeap::corrigeDescendo(int i, int j){
    int esq = esquerdo(i);
    int dir = direito(i);
    int menor = i;
    int valor = i;
    bool trocou = false;

    if((dir < tam) and (vetDados[dir] < vetDados[menor])){
        menor = dir;
    }

    if((esq < tam) and (vetDados[esq] < vetDados[menor])){
        menor = esq;
    }

    if(menor != i){
        swap(vetDados[i], vetDados[menor]);
        trocou = true;
        corrigeDescendo(menor, j);
    }

    if((valor == j) and (trocou == true)){
        cout << valor << ": ";
        for(int i = 0; i < tam; i++){
            cout << vetDados[i] << " ";
        }
        cout << endl;
    }
}

//Funcao principal
int main(){
    int t;

    cout << "Tamanho: ";
    cin >> t;

    int* vetor;
    vetor = new int[t];

    for(int i = 0; i < t; i++){
        cout << "Valor: ";
        cin >> vetor[i];
    }
    
    MinHeap minheapi(vetor, t);

    for(int i = (t-1)/2; i >= 0; i--){
        int k = i;
        minheapi.corrigeDescendo(i, k);
    }

    return 0;
}