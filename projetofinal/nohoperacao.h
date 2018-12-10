#ifndef NOHOPERACAO_H
#define NOHOPERACAO_H

//Estrutura de dados da operacao
struct DadosOp{
    bool op;   //credito-add(0), debito-sub(1)
    int valor;
};

//Classe do noh-operacao
class NohOperacao{
    friend class PilhaOperacao;

    private:
        DadosOp oper;
        NohOperacao* proximo;
    
    public:
        NohOperacao();
};

#endif