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
        void inverter();

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

void Pilha::inverter() {
    Pilha p2;
    Pilha p3;
    int valor;
    Noh* aux = NULL;

    while(topo != NULL) {
        aux = topo->prox;
        valor = topo->dado;
        delete topo;
        topo = aux;
        p2.empilharNoh(valor);
    }

    while(p2.topo != NULL) {
        aux = p2.topo->prox;
        valor = p2.topo->dado;
        delete p2.topo;
        p2.topo = aux;
        p3.empilharNoh(valor);
    }

    while(p3.topo != NULL) {
        aux = p3.topo->prox;
        valor = p3.topo->dado;
        delete p3.topo;
        p3.topo = aux;
        empilharNoh(valor);
    }
}

//Funcao principal
int main(){
    Pilha p1;
    
    int tam;
    cin >> tam;

    int valor;

    for (int i = 0; i < tam; ++i) {
        cin >> valor;
        p1.empilharNoh(valor);
    }
    
    p1.inverter();
    for (int i = 0; i < tam; ++i)
    {
        cout << p1.desempilharNoh();
    }

    return 0;
}
