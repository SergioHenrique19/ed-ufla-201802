#include <iostream>

using namespace std;

typedef string Dado;

class noh {
    private:    
        friend class lista;
        Dado palavra;
        noh* proximo;
        noh* anterior;
    public:
        noh(Dado comando);
};

noh::noh(Dado comando) {
    palavra = comando;
    proximo = NULL;
    anterior = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        ~lista();
        void insereInicio(Dado comando, int tam);
        Dado removeInicio(int tam);
        void insereFim(Dado comando, int tam);
        Dado removeFim(int tam);
};

// constrói uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::~lista() {
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

// método básico que *percorre* a lista, imprimindo seus elementos
// insere por padrão no final da lista
void lista::insereInicio(Dado comando,int tam) {
    // Implemente aqui
    noh* novo = new noh(comando);
    noh* aux = NULL;
    if(novo) {
        aux = primeiro;
        primeiro = novo;
        primeiro->proximo = aux;
        aux->anterior = primeiro;
        tamanho++;
    }
}   

void lista::insereFim(Dado comando, int tam) {
    noh* novo = new noh(comando);
    noh* aux = NULL;
    if(tamanho == 0) {
        ultimo = novo;
        primeiro = novo;
        tamanho++;
    } else if(tamanho >= 1) {
        aux = ultimo;
        ultimo->proximo = novo;
        ultimo = novo;
        ultimo->anterior = aux;
        tamanho++;
    }
}

Dado lista::removeInicio(int tam) {
    noh* aux = NULL;
    Dado retorna;
    if(tamanho == 0) {
        cerr << "ERRO" << endl;
    } else {
        if(tamanho == 1) {
            retorna = primeiro->palavra;
            primeiro = NULL;
            ultimo = NULL;
            tamanho--;
        } else if(tamanho > 1) {
            aux = primeiro;
            retorna = aux->palavra;
            primeiro = aux->proximo;
            primeiro->anterior = NULL;
            delete aux;
            tamanho--;
        }
    }
    return retorna;
}

Dado lista::removeFim(int tam) {
    Dado retorna;
    if(tamanho == 0) {
        cerr << "ERRO" << endl;
    } else {
        if(tamanho == 1) {
            retorna = primeiro->palavra;
            ultimo = NULL;
            primeiro = NULL;
            tamanho--;
        } else if(tamanho > 1) {
            noh* aux = NULL;
            aux = ultimo;
            retorna = aux->palavra;
            ultimo = aux->anterior;
            ultimo->proximo = NULL;
            delete aux;
            tamanho--;
        }
    }
    return retorna;
}


int main() { // NÃO MODIFIQUE!
    lista minhaLista;
    Dado comando;
    int tam;
    cin >> tam;
    int cont = 0;
    cin.ignore();
    getline(cin, comando);
    while(comando != "sair") {
        if(comando == "undo") {
            if(cont == 0) {
                cout << "ERRO" << endl;
            } else if(cont > 0) {
                cout << "desfazer: " << minhaLista.removeFim(tam) << endl;
                cont--;
            }
        } else {
            if(cont < tam) {
                minhaLista.insereFim(comando, tam);
                cont++;
            } else if(cont == tam) {
                cout << "esqueci: " << minhaLista.removeInicio(tam) << endl;
                minhaLista.insereFim(comando, tam);
            }
        }
        getline(cin, comando);
    }
    cout << endl;
    
    return 0;
}
