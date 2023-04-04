#ifndef POSICOES_ANDADAS_HPP
#define POSICOES_ANDADAS_HPP

#include "pessoa.hpp"
#include "utility"

using namespace std;

class PosicoesAndadas{
    public:
        vector<pair<int, int>> * vetorPosicoesAndadas;
        PosicoesAndadas(int nMatrizesArquivo);
        PosicoesAndadas();
};

#endif