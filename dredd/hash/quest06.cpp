#include <iostream>
#include <algorithm>

using namespace std;

class minHeap{
    private:
        int* vetDados;
        int size;
    public:
        minHeap(int array[], int tam);
        ~minHeap();
        int pai(int i){ return ((i - 1)/2); }
        int esquerdo(int i){ return (2*i + 1); }
        int direito(int i){ return (2*i + 2); }
        void corrigeDescendo(int i, int n);
};


minHeap::minHeap(int array[], int tam){
    vetDados = new int[tam];
    vetDados = array;
    size = tam;
}

minHeap::~minHeap() {
    delete[] vetDados;
}

void minHeap::corrigeDescendo(int i, int n){
    int esq = esquerdo(i);
    int dir = direito(i);
    int menor = i;
    int valor = i;
    bool trocou = false;
    
    if(dir < size and vetDados[dir] < vetDados[menor]){
        menor = dir;
    }
    
    if(esq < size and vetDados[esq] < vetDados[menor]){
        menor = esq;
    }
    
    if(menor != i){
        swap(vetDados[i], vetDados[menor]);
        trocou = true;
        corrigeDescendo(menor, n);
    }
    
    if(valor == n and trocou == true) {
        cout << valor << ": ";
        for (int i = 0; i < size; i++) {
            cout << vetDados[i] << " ";
        }
        cout << endl;
    }
}

int main(){
    int t;
    cin >> t;
    
    int *vetao;
    vetao = new int[t];
    for (int i = 0; i < t; i++){
        cin >> vetao[i];
    }
    
    
    minHeap meuheap(vetao, t);
    for (int i = (t-1)/2; i >= 0; i--){
        int n = i;
        meuheap.corrigeDescendo(i, n);
    }
    
    return 0;
}
