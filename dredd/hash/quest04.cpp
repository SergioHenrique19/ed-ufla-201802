#include <iostream>
#include <string>

using namespace std;

int funcaoHash(string c) {
    int tam = c.size();
    return tam%23;  
}


class noh {
    friend class tabelaHash;
    private:
        string chave;
        string valor;
        noh* proximo = NULL;
    public:
        noh(string c, string v) {
            chave = c;
            valor = v;
        }
};

class tabelaHash {
    private:
        // vetor de ponteiros de nÃ³s
        noh** elementos;
        int capacidade;
    public:
        // construtor padrÃ£o
        tabelaHash(int cap = 23);
        // destrutor
        ~tabelaHash();
        // insere um valor v com chave c
        void insere(string palavra, string significado);
        // recupera um valor associado a uma dada chave
        void recupera(string c);
        // altera o valor associado a uma chave
};

// construtor padrÃ£o
tabelaHash::tabelaHash(int cap) {
    elementos = new noh*[cap];
    capacidade = cap;
    for (int i = 0; i < cap; i++)
        elementos[i] = NULL;
}

// destrutor
tabelaHash::~tabelaHash() {
    for (int i=0; i < capacidade; i++) {
        noh* atual = elementos[i];
        // percorre a lista removendo todos os nÃ³s
        while (atual != NULL) {
            noh* aux = atual;
            atual = atual-> proximo;
            delete aux;
        }
    }
    delete[] elementos;
}

// Insere um valor v com chave c.
void tabelaHash::insere(string c, string v) {
    //  CODIGO A SER DESENVOLVIDO
    int posicao = funcaoHash(c);
    if(elementos[posicao] == NULL) {
        noh* novo = new noh(c, v);
        elementos[posicao] = novo;
    } else {
        if(elementos[posicao]->proximo == NULL) {
            noh* novo = new noh(c,v);
            noh* atual = elementos[posicao];
            novo->proximo = atual;
            elementos[posicao] = novo;
            atual->proximo = NULL;
        } else {
            noh* novo = new noh(c,v);
            noh* atual = elementos[posicao];
            novo->proximo = atual;
            elementos[posicao] = novo;
        }
    }
}

// recupera um valor associado a uma dada chave 
void tabelaHash::recupera(string c) {
    int posicao = funcaoHash(c);
    string retorna = "NULL";
    bool encontrou = false;
    if(elementos[posicao] != NULL) {
        if(elementos[posicao]->chave == c) {
            retorna = elementos[posicao]->valor;
        } else {
            noh* atual = elementos[posicao];
            while(encontrou == false and atual != NULL) {
                if(atual->chave == c) {
                    retorna = atual->valor;
                    encontrou = true;
                }
                atual = atual->proximo;
            }
        }
    }
    cout << "[" << c << "]" << " => " << retorna << endl;
}

int main() {
    
    tabelaHash th(23);
    int quant;
    cin >> quant;
    string palavra;
    string significado;
    cin >> palavra;
    cin.ignore();
    getline(cin,significado);
    th.insere(palavra, significado);
    for (int i = 1; i < quant; i++) {
        cin >> palavra;
        getline(cin,significado);
        th.insere(palavra, significado);
    }
    
    string procura;
    while(procura != "-1") {
        cin >> procura;
        if(procura != "-1") {
            th.recupera(procura);
        }
    }

   return 0;
}
