#include <iostream>

using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo
 
// pilha implementada em arranjo 
class pilhav {
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posTopo;
    public:
        pilhav(int cap = 20);
        ~pilhav();
        void empilha(Dado valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
        void info();  // imprime informações da pilha (tamanho e  posição do topo)
};

pilhav::pilhav(int cap) : capacidade(cap), dados(NULL),
                          tamanho(-1), posTopo(0) { 
    if(capacidade > 0) {
        dados = new Dado[capacidade];
    }
}

pilhav::~pilhav() {
    delete[] dados;
}

void pilhav::empilha(Dado valor) {
    tamanho++;
    dados[tamanho] = valor;
    posTopo = tamanho;
}

Dado pilhav::desempilha() {
    Dado Retorna = dados[tamanho];
    tamanho--;
    posTopo = tamanho;
    return Retorna;
}

Dado pilhav::espia() {
     return dados[tamanho];
}

void pilhav::depura() {
    for (int i = 0; i <= tamanho; i++) {
        cout << dados[i] << " ";
    }
    cout << endl;
}

void pilhav::info() {
    cout << tamanho+1 << " " << posTopo << endl;
}

int main() {
    Dado cap = 20;
    pilhav v1(cap);
    for (unsigned i = 0; i < 5; i++) {
        Dado valor;
        cin >> valor;
        v1.empilha(valor);
    }
    for (unsigned i = 0; i < 3; i++) {
        cout << v1.desempilha();
        cout << " ";
    }
    cout << endl;
    for (unsigned i = 0; i < 4; i++) {
        Dado valor;
        cin >> valor;
        v1.empilha(valor);
    }
    for (unsigned i = 0; i < 3; i++) {
        cout << v1.desempilha();
        cout << " ";
    }
    cout << endl;
    cout << v1.espia() << endl;
    v1.depura();
    v1.info();
    
    return 0;
}
