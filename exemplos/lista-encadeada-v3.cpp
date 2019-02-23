#include <iostream>

using namespace std;

typedef int Dado;

class noh
{
    private:
        friend class aluno;
        noh* anterior;
        noh* proximo;
        Dado Matricula;
        string nomeAluno;
    public:
        noh(Dado matricula, string nome);
};
        
noh::noh(Dado matricula, string nome)
{
    Matricula = matricula;
    nomeAluno = nome;
    anterior = NULL;
    proximo = NULL;
}

class aluno
{
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        aluno();
        ~aluno();
        void insere(Dado matricula, string nome);
        void remove(Dado remove);
        void imprimeDireto();
        void imprimeReverso();
};

aluno::aluno() 
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

aluno::~aluno()
{
    noh* iter = primeiro;
    
    while (iter != NULL) 
    {
        delete iter;
        iter = iter->proximo;
    }
}

void aluno::insere(Dado matricula, string nome)
{
    noh* novo = new noh(matricula, nome);
    
    if(novo)
    {
        if(primeiro == NULL)
        {
            primeiro = novo;
            ultimo = novo;
        }
        else
        {
           novo -> proximo = primeiro;
           primeiro->anterior = novo;
           primeiro = novo;
        }
        tamanho++;
    }
    else
    {
        cerr << "noh nao foi criado" << endl;
    }
}

void aluno::remove(Dado remove)
{  
    bool achou = false;
    Dado cont = 1;
    if(remove < 0 or tamanho == 0) {
       cout << "ERRO" << endl;
    } else {
       noh* aux = ultimo;
       noh* ant = aux->anterior;
       noh* pos = aux->proximo;
       while(cont <= tamanho and achou == false) {
           if(aux->Matricula == remove) {
               if(aux != ultimo and aux != primeiro) {
                   ant->proximo = aux->proximo;
                   pos->anterior = aux->anterior;
                   delete aux;
                   achou = true;
                   tamanho--;
               } else if(aux == ultimo and tamanho > 1) {
                   ultimo = aux->anterior;
                   delete aux;
                   achou = true;
                   tamanho--;
               } else if(aux == primeiro and tamanho > 1) {
                   primeiro = aux->proximo;
                   delete aux;
                   achou = true;
                   tamanho--;
               } else if(tamanho == 1) {
                   delete aux;
                   primeiro = NULL;
                   achou = true;
                   ultimo = NULL;
                   tamanho--;
               }
           }
           if(achou == false and cont != tamanho) {
               aux = aux->anterior;
               ant = aux->anterior;
               pos = aux->proximo;
           }
           cont++;
       }
       if(achou == false) {
           cout << "ERRO" << endl;
       }
   }
}

void aluno::imprimeReverso()
{
    noh* aux = ultimo;
    
    while(aux != primeiro)
    {
        if(tamanho > 0) {
            cout << aux -> Matricula << " " << aux -> nomeAluno << " ";
            aux = aux -> anterior;
        }
    }
    if(aux == primeiro) {
        if(tamanho > 0) {
            cout << aux -> Matricula << " " << aux -> nomeAluno;
        }
    }
    cout << endl;
}

void aluno::imprimeDireto()
{
    noh* aux = primeiro;
    
    while(aux != ultimo)
    {
        if(tamanho > 0) {
            cout << aux -> Matricula << " " << aux -> nomeAluno << " ";
            aux = aux -> proximo;
        }
    }
    if(aux == ultimo) {
        if(tamanho > 0) {
            cout << aux -> Matricula << " " << aux -> nomeAluno;
        }
    }
    cout << endl;
}

int main()
{
    aluno alunos;
    Dado matricula, remover;
    string nome;
    
    string escolha;
    cin >> escolha;
    
    while(escolha != "t")
    {
        if(escolha == "i")
        {
            cin >> matricula;
            cin >> nome;
            alunos.insere(matricula, nome);
        }
        if(escolha == "r")
        {
            cin >> remover;
            alunos.remove(remover);
        }
        if(escolha == "ed")
        {
            alunos.imprimeDireto();
        }
        if(escolha == "er")
        {
            alunos.imprimeReverso();
        }
        
        cin >> escolha;
    }
                	
	return 0;
}
