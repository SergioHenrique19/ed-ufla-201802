#include <iostream>

using namespace std;

typedef string Texto;

class noh {
    friend class lista;
    private:
        const Texto palavra;
        noh* proximo;
    public:
        noh(Texto p);
};

noh::noh(Texto p) : palavra(p) {
    proximo = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        lista(const lista& umaLista);
        lista& operator=(const lista& umaLista);
        lista operator+(const lista& umaLista) const;
        ~lista();
        void insereInicio(Texto palavra);
        void insereFinal(Texto palavra);
        void resetar();
        void imprime() const;
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

// insere no inicio da lista
void lista::insereInicio(Texto palavra) {
    noh* novo = new noh(palavra);
    novo->proximo = primeiro;
    primeiro = novo;
    if (tamanho == 0)
        ultimo = novo;
    ++tamanho;
}

// insere no final da lista
void lista::insereFinal(Texto palavra){
	noh* novo = new noh(palavra);
	
	if(tamanho == 0){
		primeiro = novo;
		ultimo = novo;
	}else{
		ultimo->proximo = novo;
		ultimo = novo;
	}
	
	++tamanho;
}

// método básico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() const {
    noh* iter = primeiro;
    while (iter != NULL) {
        cout << iter->palavra << " ";
        iter = iter->proximo;
    }
    cout << endl;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
    // IMPLEMENTAR
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    noh* aux = umaLista.primeiro;
    
    while(aux != NULL){
		insereFinal(aux->palavra);
		aux = aux->proximo;
	}
}

// limpar a lista
void lista::resetar(){
    noh* anterior;
    noh* atual = primeiro;
    
    while (atual != NULL){
        anterior = atual;
        atual = atual->proximo;
        delete anterior;
    }  
    
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// sobrecarga do operador de atribuição - retorna a própria lista
lista& lista::operator=(const lista& umaLista) {
    // IMPLEMENTAR
    resetar();
    
    noh* aux = umaLista.primeiro;
    
    while(aux != NULL){
		insereFinal(aux->palavra);
		aux = aux->proximo;
	}
	
	return *this;
}

// concatenacao de listas
lista lista::operator+(const lista& umaLista) const {
    // IMPLEMENTAR
    lista lTemp;
    noh* aux = primeiro;
    
    while(aux != NULL){
		lTemp.insereFinal(aux->palavra);
		aux = aux->proximo;
	}
	
	aux = umaLista.primeiro;
	
	while(aux != NULL){
		lTemp.insereFinal(aux->palavra);
		aux = aux->proximo;
	}
	
	return lTemp;
}

int main() { // NÃO MODIFIQUE!
    lista listaA;
    lista listaB;
    string opcao;
    string palavra;
    char idLista;
    do {
        cin >> opcao;
        if (opcao == "i") {
            cin >> idLista >> palavra;
            if (idLista == 'a')
                listaA.insereInicio(palavra);
            else
                listaB.insereInicio(palavra);
        }
        else if (opcao == "a=b") {
            listaA = listaB;
        }
        else if (opcao == "b=a") {
            listaB = listaA;
        }
        else if (opcao == "s") {
            lista soma = listaA + listaB;
            soma.imprime();
        }
        else if (opcao == "e") {
            // escreve _uma copia_ da lista indicada
            cin >> idLista;
            lista* ptLista = (idLista == 'a') ? &listaA : &listaB;
            lista copiaDaLista(*ptLista);
            copiaDaLista.imprime();
        }
    } while (opcao != "t");
    return 0;
}

