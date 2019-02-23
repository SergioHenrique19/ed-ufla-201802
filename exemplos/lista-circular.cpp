#include <iostream>

using namespace std;

typedef int Dado;

class noh{
    friend class lista;
	private:
        const Dado dado;
        noh* proximo;
    public:
        noh(Dado d = 0);    
};

//construtor do noh
noh::noh(Dado d) : dado(d) {
    proximo = NULL;
};

class lista{
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        ~lista();
        void insereFim(Dado val);
        void josephus(Dado var);
        inline bool vazia();
};

//construtor da lista
lista::lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

//destrutor da lista
lista::~lista(){
    noh* aux = primeiro;
    noh* proximo = NULL;
    
    while(aux->proximo != ultimo){
        proximo = aux->proximo;
        delete aux;
        aux = proximo;
    }
    
    aux = ultimo;    
    delete aux;
    
    //cout << "\nFinalizado\n";
}

//inserir nohs no final da lista
void lista::insereFim(Dado val){
    noh* novo = new noh(val);
    
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
        novo->proximo = primeiro;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
        novo->proximo = primeiro;
    }
    
    tamanho++;
}

//problema de josephus
void lista::josephus(Dado var){
    noh* aux = primeiro;
    noh* ant = NULL;
    Dado salva = 0;
    
    if(vazia()){
        cerr << "Operacao invalida\n";
    }else{
        if(tamanho == 1){
            salva = aux->dado;
        }else{
            while(tamanho != 1){
                for(int i = 0; i < var; i++){
                    ant = aux;
                    aux = aux->proximo;
                }
            
                ant->proximo = aux->proximo;
                delete aux;
                aux = ant->proximo; 
                primeiro = aux;
                ultimo = aux;           
                salva = aux->dado;
            
                tamanho--;
            }
        }
        
        cout << salva;
    }
}

//verifica lista vazia
inline bool lista::vazia(){
    if(primeiro == NULL and ultimo == NULL){
        return true;
    }else{
        return false;
    }
}

//funcao principal
int main(){
    lista lCircular;
    
    Dado n, m;
    
    cin >> n >> m;
    
    if(n > 0){
        for(int i = 1; i <= n; i++){
            lCircular.insereFim(i);
        }
        
        lCircular.josephus(m);
    }else{
        cout << "Operacao invalida\n";
    }
    
    return 0;
}
