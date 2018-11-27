#include <iostream>

using namespace std;

//Classe cliente
class NohCliente{
    friend class ListaCliente;
    private:
        int cpf;
        string nome;
        float saldo;
        NohCliente* proximo;
        NohCliente* anterior;
    
    public:
        NohCliente(){   //Construtor da classe Cliente
            cpf = 0;
            nome = "";
            saldo = 0.0;
            proximo = NULL;
            anterior = NULL;
        }
};

//Classe-lista de clientes cadastrados
class ListaCliente{
    private:
        NohCliente* primeiroCli;
        NohCliente* ultimoCli;
        int tamanho;
    
    private:
        ListaCliente();
        ~ListaCliente();
};

int main(){
    return 0;
}
