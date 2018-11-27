#include <iostream>

using namespace std;

//Classe operacao
class NohOperacao{
    private:
        bool op;    //true: debitar(sub), false: creditar(add)
        float valor;
        NohOperacao* proximo;
    
    public:
        NohOperacao(){
            op = false;
            valor = 0.0;
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
        void Desempilhar();
        void Empilhar();
        void LimparTudo();
        unsigned Tamanho() { return tamanho; }
        void Topo();
};

int main(){
    return 0;
}
