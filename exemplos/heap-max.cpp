#include <iostream>
#include <algorithm>

using namespace std;

class maxHeap{
  private:
    int *vetDados;
    int size;
    int capacity;

  public:
    maxHeap();
    ~maxHeap();
    int pai(int i) { return ((i - 1) / 2); }
    int esquerdo(int i) { return (2 * i + 1); }
    int direito(int i) { return (2 * i + 2); }
    void corrigeDescendo(int i);
    void insere(int valor);
    void imprime();
    void imprimeReverso();
    void corrigeSubindo(int i);
    void remove();
};

maxHeap::maxHeap(){
    capacity = 20;
    size = 0;
    vetDados = new int[20];
}

maxHeap::~maxHeap(){
    delete[] vetDados;
}

void maxHeap::corrigeDescendo(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;

    if (esq < size and vetDados[esq] > vetDados[maior]){
        maior = esq;
    }

    if (dir < size and vetDados[dir] > vetDados[maior]){
        maior = dir;
    }

    if (maior != i){
        swap(vetDados[i], vetDados[maior]);
        corrigeDescendo(maior);
    }
}

void maxHeap::insere(int valor){
    vetDados[size] = valor;
    size++;
}

void maxHeap::imprime(){
    for (int i = 0; i < size; i++){
        cout << vetDados[i] << " ";
    }
}

void maxHeap::remove(){
    swap(vetDados[0], vetDados[size - 1]);
    size--;
    corrigeDescendo(0);
}

void maxHeap::corrigeSubindo(int i){
    int p = pai(i);
    if (i > 0 and vetDados[i] > vetDados[p]){
        swap(vetDados[i], vetDados[p]);
        corrigeSubindo(p);
    }
}

void maxHeap::imprimeReverso(){
    for (int i = capacity - 1; i >= 0; i--){
        cout << vetDados[i] << " ";
    }
    cout << endl;
}

int main(){
    int cont = 0;
    maxHeap meuheap;
    int valor;

    for (int i = 0; i < 15; i++){
        cont++;
        cin >> valor;
        meuheap.insere(valor);
    }

    for (int i = (15 - 1) / 2; i >= 0; i--){
        meuheap.corrigeDescendo(i);
    }
    meuheap.imprime();
    cout << endl;

    for (int i = 0; i < 5; i++){
        cont++;
        cin >> valor;
        meuheap.insere(valor);
        meuheap.corrigeSubindo(cont - 1);
    }
    meuheap.imprime();
    cout << endl;
    for (int i = cont; i > 0; i--){
        meuheap.remove();
    }
    meuheap.imprimeReverso();

    return 0;
}