#include <iostream>

typedef int Dado;

class Fila {
    public:
        Fila(unsigned cap = 80);
        ~Fila();
        // Remove e retorna o prÃ³ximo elemento da fila.
        Dado Desenfileira();
        // Insere um valor na fila. Retorna um booleano que informa se a inserÃ§Ã£o foi realmente
        // realizada.
        bool Enfileirar(const Dado& valor);
        // Escreve todo o conteÃºdo do armazenamento da fila na saÃ­da de dados.
        void EscreverConteudo(std::ostream& saida) const;
        // Retorna tamanho, capacidade, inicio e fim da fila.
        void Info(unsigned* ptTam, unsigned* ptCap, unsigned* ptIni, unsigned* ptFim) const;
        // Retorna o primeiro elemento da fila, sem removÃª-lo.
        Dado Proximo() const;
        // Retorna a quantidade de elementos na fila.
        unsigned Tamanho() const { return mTamanho; }
        // Consulta se a fila estÃ¡ vazia.
        bool Vazia() const ;
    protected:
        unsigned mCapacidade;
        Dado* mDados;
        unsigned mPosInicio; // indica a posicao do primeiro
        unsigned mPosFim;    // indica a posicao do ultimo
        unsigned mTamanho;
};

using namespace std;

Fila::Fila(unsigned cap) : mCapacidade(cap), mDados(NULL), // cap tem valor default
                           mPosInicio(0), mPosFim(0), mTamanho(0) {
    if(mCapacidade > 0) {
        mDados = new Dado[mCapacidade];
    }
    for (unsigned i = 0; i < mCapacidade; i++) {
        mDados[i] = 0;
    }
    
}

Fila::~Fila() {
    delete[] mDados;
}

// Remove e retorna o prÃ³ximo elemento da fila.
Dado Fila::Desenfileira() {
    Dado retorna = 0;
    if(mPosInicio < mPosFim) {
        retorna = mDados[mPosInicio];
        mTamanho--;
        mPosInicio++;
        return retorna;
    } else if(mPosInicio == mPosFim) {
        retorna = mDados[mPosInicio];
        mTamanho--;
        mPosInicio = 0;
        mPosFim = 0;
        return retorna;
    } else if(mPosInicio > mPosFim and mPosInicio != mCapacidade-1) {
        retorna = mDados[mPosInicio];
        mTamanho--;
        mPosInicio++;
        return retorna;
    } else if(mPosInicio > mPosFim and mPosInicio == mCapacidade-1) {
        retorna = mDados[mPosInicio];
        mTamanho--;
        mPosInicio = 0;
        return retorna;
    }
    return retorna;
}

// Insere um valor na fila. Retorna um booleano que informa se a inserÃ§Ã£o foi realmente realizada.
bool Fila::Enfileirar(const Dado& valor) {
    if(mTamanho < mCapacidade) {
        if(mTamanho == 0) {
            mDados[mTamanho] = valor;
            mTamanho++;
        } else if(mTamanho > 0 and mPosFim != mCapacidade-1) {
            mDados[mTamanho] = valor;
            mPosFim = mTamanho;
            mTamanho++;
        } else if(mTamanho > 0 and mPosFim == mCapacidade-1) {
            mPosFim = 0;
            mDados[mPosFim] = valor;
            mTamanho++;
        }
        return true;
    }
    return false;
}

// Escreve todo o conteÃºdo do armazenamento (comeÃ§ando da posiÃ§Ã£o zero) da fila na saÃ­da de dados.
void Fila::EscreverConteudo(ostream& saida) const {

    for (unsigned i = 0; i < mCapacidade; i++)
    {
        cout << mDados[i] << " ";
    }
    cout << endl;
}
    

// Retorna tamanho, capacidade, inicio e fim da fila.
void Fila::Info(unsigned* ptTam, unsigned* ptCap, unsigned* ptIni, unsigned* ptFim) const {
    *ptTam = mTamanho;
    *ptCap = mCapacidade;
    *ptIni = mPosInicio;
    *ptFim = mPosFim;
}

// Retorna o primeiro elemento da fila, sem removÃª-lo.
Dado Fila::Proximo() const {
    return mDados[mPosInicio];
}

// Consulta se a fila estÃ¡ vazia.
bool Fila::Vazia() const {
    if(mTamanho == 0 and mDados[0] == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    unsigned tamanho, capacidade, inicio, fim;
    cin >> capacidade;
    Fila fila(capacidade);
    Dado valor;
    char comando;
    cin >> comando;
    while (comando != 't') {
        switch (comando) {
        case 'e': // enfileirar
            cin >> valor;
            if (not fila.Enfileirar(valor))
                cout << "FILA CHEIA!\n";
            break;
        case 'd': // desenfileirar
            if (fila.Vazia())
                cout << "ERRO\n";
            else {
                valor = fila.Desenfileira();
                cout << valor << endl;
            }
            break;
        case 'p': // proximo
            if (fila.Vazia())
                cout << "ERRO\n";
            else
                cout << fila.Proximo() << endl;
            break;
        case 'i': // informaÃ§Ãµes sobre a fila
            fila.Info(&tamanho, &capacidade, &inicio, &fim);
            cout << "tamanho=" << tamanho << " capacidade=" << capacidade << " inicio=" << inicio
                 << " fim=" << fim << endl;
            fila.EscreverConteudo(cout);
            break;
        case 't':
            // vai testar novamente no while
            break;
        default:
            cout << "comando invalido\n";
        }
        cin >> comando;
    }
    return 0;
}
