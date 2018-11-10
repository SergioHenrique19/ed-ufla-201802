// Tabela Hash com tratamento de colisão por endereçamento aberto
#include <iostream>
#include <exception>

typedef int TValor; // tipo do valor armazenado

class InfoHash {
    friend class Hash; // essa classe só deve ser usada na classe Hash
    InfoHash();
    InfoHash(const std::string& chave, const TValor& valor);
    std::string mChave;
    TValor mValor;
};

class Hash {
    public:
        Hash(unsigned capacidade = 50);
        ~Hash();
        void EscreverEstrutura(std::ostream& saida) const;   // Mostra todos as posições de armazenamento da hash.
        void Inserir(const std::string& chave, const TValor& valor);   // Insere uma cópia do valor. Não permite inserção de chave repetida.
        void Remover(const std::string& chave);   // Remove um item da hash associado com a chave dada.
        TValor Valor(const std::string& chave) const;   // Retorna o valor associado a uma chave.
    protected:
        unsigned Buscar(const std::string& chave) const;   // Retorna a posicao em que uma chave está armazenada na estrutura.
        unsigned Posicao(const std::string& chave) const;   // Retorna a posicao em que uma chave deveria ficar na estrutura.
        InfoHash** mVetPtDados;
        InfoHash* REMOVIDO; // ponteiro especial a ser usado para marcar posições de elemento removido
        unsigned mCapacidade;
        unsigned mTamanho;
};

using namespace std;

InfoHash::InfoHash()
    : mChave(), mValor() {
}

InfoHash::InfoHash(const std::string& chave, const TValor& valor)
    : mChave(chave), mValor(valor) {
}

Hash::Hash(unsigned capacidade) // capacidade tem valor default
    : mVetPtDados(new InfoHash*[capacidade]), REMOVIDO(new InfoHash()), mCapacidade(capacidade), mTamanho(0) {
    for(unsigned i = 0; i < capacidade; i++){
        mVetPtDados[i] = NULL;
    }
}

Hash::~Hash() {
    // desalocar memória de cada item (InfoHash) armazenado
    for(unsigned i = 0; i < mTamanho; i++){
        //if(mVetPmVetPtDados[i] != REMOVIDO)
        mVetPtDados[i] = NULL;
    }
    
    // desalocar o ponteiro especial REMOVIDO
    delete REMOVIDO;
    
    // desalocar o vetor de ponteiros
    delete[] mVetPtDados;
}

unsigned Hash::Buscar(const std::string& chave) const {
    // Retorna a posicao em que uma chave está armazenada na estrutura. Protegido.
    unsigned pos = Posicao(chave);
    unsigned cont = 0;
    bool achou = false;
    
    while(cont < mCapacidade and achou == false){
        if(mVetPtDados[pos] != NULL and mVetPtDados[pos] != NULL){
            if(mVetPtDados[pos]->mChave == chave){
                achou = true;
            }else{
                if(pos + 1 == mCapacidade){
                    pos = 0;
                }else{
                    pos++;
                }
                
                cont++;
            }
        }else{
            if(pos + 1 == mCapacidade){
                pos = 0;
            }else{
                pos++;
            }
            
            cont++;
        }
    }
    
    if(mVetPtDados[pos] != NULL and mVetPtDados[pos]->mChave == chave){
        return pos;
    }else{
        throw invalid_argument("chave nao encontrada");
    }
}

void Hash::EscreverEstrutura(std::ostream& saida) const {
    // Mostra todos as posições de armazenamento da hash. Ajuda a debugar.
    for (unsigned i = 0; i < mCapacidade; ++i) {
        saida << '[' << i;
        if (mVetPtDados[i] != NULL) {
            if (mVetPtDados[i] == REMOVIDO)
                saida << "/removido";
            else
                saida << '/' << mVetPtDados[i]->mChave << '/' << mVetPtDados[i]->mValor;
        }
        saida << "] ";
    }
}

void Hash::Inserir(const string& chave, const TValor& valor) {
    // Insere uma cópia do valor. Não permite inserção de chave repetida.
    if(mTamanho < mCapacidade){
        InfoHash* novo = new InfoHash(chave, valor);
        unsigned pos = Posicao(chave);
        
        while(mVetPtDados[pos] != NULL and mVetPtDados[pos] != REMOVIDO and mVetPtDados[pos]->mChave != chave){
            pos++;
            pos %= mCapacidade;
        }
        
        if(mVetPtDados[pos] == NULL or mVetPtDados[pos] == REMOVIDO){
            mTamanho++;
            mVetPtDados[pos] = novo;
        }else{
            throw invalid_argument("chave repetida");
        }
    }else{
        throw runtime_error("tabela hash lotada");
    }
}

unsigned Hash::Posicao(const string& chave) const {
    // Retorna a posição de armazenamento de uma chave, 0 <= posicao < mCapacidade. Protegido.
    unsigned pos = 1;
    unsigned tamanho = unsigned(chave.length());
    for (unsigned i = 0; i < tamanho; ++i)
        pos = 7 * pos + chave[i];
    return pos % mCapacidade;
}

void Hash::Remover(const std::string& chave) {
    // Remove um item da hash associado com a chave dada.
    unsigned pos = Buscar(chave);
    delete mVetPtDados[pos];
    mVetPtDados[pos] = REMOVIDO;
    mTamanho--;
}

TValor Hash::Valor(const std::string& chave) const {
    // Retorna o valor associado a uma chave.
    unsigned pos = Buscar(chave);
    
    return mVetPtDados[pos]->mValor;
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Hash tabela(capacidade);
    char operacao;
    string chave;
    TValor valor;
    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // inserir
                    cin >> chave >> valor;
                    tabela.Inserir(chave, valor);
                    break;
                case 'r': // remover
                    cin >> chave;
                    tabela.Remover(chave);
                    break;
                case 'c': // consultar
                    cin >> chave;
                    valor = tabela.Valor(chave);
                    cout << valor << endl;
                    break;
                case 'd': // debug (mostrar estrutura)
                    tabela.EscreverEstrutura(cout);
                    cout << endl;
                    break;
                case 'f': // finalizar
                    // vai testar depois
                    break;
                default:
                    cerr << "operação inválida\n";
            }
        }
        catch (exception& e) {
            // ignorar a mensagem que explica o erro e só escrever ERRO.
            cout << "ERRO" << endl;
        }
    } while (operacao != 'f');
    return 0;
}
