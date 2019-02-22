#include <iostream>

typedef int Dado;

using namespace std;

class Noh{
    friend class ABB;
    private:
        Noh* mEsquerdo;
        Noh* mDireito;
        Noh* mPai;
        Dado valor;
    public:
        Noh(Dado d);
};

Noh::Noh(Dado d){
    //Construtor
    mEsquerdo = NULL;
    mDireito = NULL;
    mPai = NULL;
    valor = d;
};

class ABB{
    private:
        Noh* mRaiz;
    public:
        ABB();
        ~ABB();
        void insere(Dado d);
        Noh* buscaAux(Noh* atual);
        void transplanta(Noh* antigo, Noh* novo);
        void remove(Dado d);
        Noh* minimoAux(Noh* atual);
        int nivel(Dado d);
        void imprimeOrdem(){ imprimeOrdem(mRaiz);}
        void imprimeOrdem(Noh* atual);
        void imprimePre(){ imprimePre(mRaiz);}
        void imprimePre(Noh* atual);
        void posOrdem(){ posOrdem(mRaiz);}
        void posOrdem(Noh* atual);
};

ABB::ABB(){
    //Contructor
    mRaiz = NULL;
};

ABB::~ABB(){
    //Destructor
   Noh* atual = mRaiz;
   if(atual != NULL){
       posOrdem(atual -> mEsquerdo);
       posOrdem(atual -> mDireito);
       delete atual;
   } 
};

void ABB::insere(Dado d){
    //Insere interativamente
    Noh* novo = new Noh(d);
    
    if(mRaiz == NULL){
        mRaiz = novo;
    }
    else{
        Noh* atual = mRaiz;
        Noh* ant = NULL;
        
        while(atual != NULL){
            ant = atual;
            if(atual -> valor > d){
                atual = atual -> mEsquerdo;
            }
            else{
                atual = atual -> mDireito;
            }
        }
        novo -> mPai = ant;
        if(ant -> valor > novo -> valor){
            ant -> mEsquerdo = novo;
        }
        else{
            ant -> mDireito = novo;
        }
    }
}

Noh* ABB::buscaAux(Noh* aux){
    //Faz a busca na estrutura e retorna
    Noh* atual = mRaiz;
    while(atual != NULL){
        if(atual -> valor == aux -> valor){
            return atual;
        }
        else if(atual -> valor > aux -> valor){
            atual = atual -> mEsquerdo;
        }
        else{
            atual = atual -> mDireito;
        }
    }
    return atual;
}

void ABB::transplanta(Noh* antigo, Noh* novo){
    //Troca dois nos
    if(mRaiz == antigo){
        mRaiz = novo;
    }
    else if(antigo == antigo -> mPai -> mEsquerdo){
        antigo -> mPai -> mEsquerdo = novo;
    }
    else{
        antigo -> mPai -> mDireito = novo;
    }
    if(novo != NULL){
        novo -> mPai = antigo -> mPai;
    }
}

void ABB::remove(Dado d){
    //Remove um elemento (noh) da arvore
    Noh* aux = new Noh(d);
    Noh* remover = buscaAux(aux);
    
    if(remover == NULL){
        cout << "ERRO" << endl;
    }
    else{
        if(remover -> mEsquerdo == NULL){
            transplanta(remover, remover -> mDireito);
        }
        else if(remover -> mDireito == NULL){
            transplanta(remover, remover -> mEsquerdo);
        }
        else{
            Noh* sucessor = minimoAux(remover -> mDireito);
            if(sucessor -> mPai != remover){
                transplanta(sucessor, sucessor -> mDireito);
                sucessor -> mDireito = remover -> mDireito;
                sucessor -> mDireito -> mPai = sucessor;
            }
            transplanta(remover, sucessor);
            sucessor -> mEsquerdo = remover -> mEsquerdo;
            sucessor -> mEsquerdo -> mPai = sucessor;
        }
        delete remover;
    }
}

Noh* ABB::minimoAux(Noh* atual){
    //Retorna o minimo da arvore
    while(atual -> mEsquerdo != NULL){
        atual = atual -> mEsquerdo;
    }
        return atual;
}

int ABB::nivel(Dado d){
    Noh* atual = mRaiz;
    int cont = 0;
    while ((atual != NULL) and (atual->valor != d)){
        cont++;
        if(atual->valor > d){
            atual = atual->mEsquerdo;
        } else {
            atual = atual->mDireito;
        }
    }
    return cont;
}
            
    

void ABB::imprimeOrdem(Noh* atual){
    if(atual != NULL){
        imprimeOrdem(atual -> mEsquerdo);
        cout << atual -> valor << "/" << nivel(atual->valor) << " ";
        imprimeOrdem(atual -> mDireito);
    }
}

void ABB::imprimePre(Noh* atual){
    if(atual != NULL){
        cout << atual -> valor << "/" << nivel(atual->valor) << " ";
        imprimePre(atual -> mEsquerdo);
        imprimePre(atual -> mDireito);
    }
}

void ABB::posOrdem(Noh* atual){
    if(atual != NULL){
        posOrdem(atual -> mEsquerdo);
        posOrdem(atual -> mDireito);
        cout << atual -> valor << "/" << nivel(atual->valor) << " ";
    }
}

int main()
{
    ABB minhaArvore;
    char escolha;
    cin >> escolha;
    Dado chave;
	do{
        switch(escolha){
            case 'i':
                cin >> chave;
                minhaArvore.insere(chave);
                break;
            case 'r':
                cin >> chave;
                minhaArvore.remove(chave);
                break;
            case 'o':
                minhaArvore.imprimeOrdem();
                break;
            case 'p':
                minhaArvore.imprimePre();
                break;
            case 'q':
                minhaArvore.posOrdem();
                break;
            case 'f':
                break;
            default:
                cout << "Comando Invalido!";
            }
            cin >> escolha;
    }while(escolha != 'f');
    
    
	return 0;
}