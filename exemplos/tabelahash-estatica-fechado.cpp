/*
 * Algoritmo de tabela hash estatica com encadeamento fechado
 * 
 * Copyright 2018 - Sérgio H. M. Garcia
*/

#include <iostream>
#include <string>

using namespace std;

const int UMPRIMO = 39;

//Funcao que calcula hash a partir de uma chave
int funcaoHash(string c, int t){
    int h = 0;
    for(unsigned i = 0; i < c.length(); i++){
        h = (UMPRIMO * h + c[i]) % t;
    }
    return h;
}

//Classe noh que armazena chave e valor na tabela hash
class Noh{
    friend class TabelaHash;

    private:
        string chave;
        string valor;
        Noh* prox;

    public:
        Noh(string c, string v){
            chave = c;
            valor = v;
            prox = NULL;
        }
};

//Classe da tabela hash
class TabelaHash{
    private:
        Noh** elementos;   //Vetor de ponteiros
        int cap;

    public:
        TabelaHash(int tam = 100);
        ~TabelaHash();
        void inserir(string c, string v);
        string recuperarValor(string c);
        void alterarValor(string c, string v);
        void removerValor(string c);
        void percorrer();
};

//Construtor da tabela hash
TabelaHash::TabelaHash(int tam){
    elementos = new Noh*[tam];
    cap = tam;
    for(int i = 0; i < tam; i++){
        elementos[i] = NULL;
    }
}

//Destrutor da tabela hash
TabelaHash::~TabelaHash(){
    for(int i = 0; i < cap; i++){
        Noh* atual = elementos[i];

        while(atual != NULL){
            Noh* aux = atual;
            atual = atual->prox;
            delete aux;
        }
    }
    delete[] elementos;
}

//Inserir um valor v com uma chave c
void TabelaHash::inserir(string c, string v){
    Noh* novo = new Noh(c, v);
    int j = funcaoHash(c, cap);

    if(recuperarValor(c) == "NAO ENCONTRADO"){
        if(elementos[j] == NULL){
            elementos[j] = novo;
        }else{
            Noh* aux = elementos[j];

            while(aux->prox != NULL){
                aux = aux->prox;
            }

            aux->prox = novo;
        }
    }
}

//Recuperar um valor associado a uma chave
string TabelaHash::recuperarValor(string c){
    int j = funcaoHash(c, cap);

    if((elementos[j] != NULL) and (elementos[j]->chave == c)){
        return elementos[j]->valor;
    }else{
        Noh* atual = elementos[j];

        while((atual != NULL) and (atual->chave != c)){
            atual = atual->prox;
        }

        if((atual != NULL) and (atual->chave == c)){
            return atual->valor;
        }else{
            return "NAO ENCONTRADO";
        }
    }
}

//Alterar um valor associado a uma chave
void TabelaHash::alterarValor(string c, string v){
    int j = funcaoHash(c, cap);

    if(recuperarValor(c) == "NAO ENCONTRADO"){
        cout << "Erro na alteracao...\n";
    }else{
        if((elementos[j] != NULL) and (elementos[j]->chave == c)){
            elementos[j]->valor = v;
        }else{
            Noh* aux = elementos[j];

            while((aux != NULL) and (aux->chave != c)){
                aux = aux->prox;
            }

            if((aux != NULL) and (aux->chave == c)){
                aux->valor = v;
            }
        }
    }
}

//Remover um valor associado a uma chave
void TabelaHash::removerValor(string c){
    if(recuperarValor(c) == "NAO ENCONTRADO"){
        cout << "Erro na remocao...\n";
    }else{
        int j = funcaoHash(c, cap);

        if((elementos[j] != NULL) and (elementos[j]->chave == c)){
            Noh* removido = elementos[j];
            elementos[j] = elementos[j]->prox;
            delete removido;
        }else{
            Noh* atual = elementos[j];
            Noh* ant;

            while((atual != NULL) and (atual->chave != c)){
                ant = atual;
                atual = atual->prox;
            }

            if((atual != NULL) and (atual->chave == c)){
                Noh* removido = atual;
                ant->prox = atual->prox;
                delete removido;
            }
        }
    }
}

//Percorrer a tabela hash
void TabelaHash::percorrer(){
    Noh* atual;

    for(int i = 0; i < cap; i++){
        cout << i << ":";
        atual = elementos[i];
        while(atual != NULL){
            cout << "[" << atual->chave << "/" << atual->valor << "]->";
            atual = atual->prox;
        }
        cout << "NULL   ";
    }
}

//Funcao principal
int main(){
    TabelaHash th(10);
    int qtd;
    string indice, atrib;

    //Insercao na tabela
    cout << "Quantidade: ";
    cin >> qtd;
    for(int i = 0; i < qtd; i++){
        cout << "Chave: ";
        cin >> indice;
        cout << "Valor: ";
        cin >> atrib;
        th.inserir(indice, atrib);
    }

    //Altera valores
    cout << "\nQuantidade: ";
    cin >> qtd;
    for(int i = 0; i < qtd; i++){
        cout << "Chave: ";
        cin >> indice;
        cout << "Valor: ";
        cin >> atrib;
        th.alterarValor(indice, atrib);
    }

    //Remove valores
    cout << "\nQuantidade: ";
    cin >> qtd;
    for(int i = 0; i < qtd; i++){
        cout << "Chave: ";
        cin >> indice;
        th.removerValor(indice);
    }

    //Recupera valores
    cout << "\nQuantidade: ";
    cin >> qtd;
    for(int i = 0; i < qtd; i++){
        cout << "Chave: ";
        cin >> indice;
        th.recuperarValor(indice);
    }

    //Percorre tabela
    cout << endl;
    th.percorrer();
    cout << endl;

    return 0;
}
