#include "pessoa.hpp"
#include "funcoes.hpp"
#include "posicoesAndadas.hpp"

int main(){    
    int N, nMatrizesArquivo, linhaInicial, colunaInicial, matrizAtual = 1;
    ifstream arquivo;
    string ** matriz;
    Pessoa * p = new Pessoa();

    //Retirada de informações do arquivo
    arquivo.open("dataset/input.data", ios::in);
    N = lerPrimeiraLinha(arquivo);
    nMatrizesArquivo = contarLinhasVazias(arquivo);
    arquivo.close();//Fechei aqui pois na função de contar linhas vazias, percorro todo o arquivo.
    arquivo.open("dataset/input.data", ios::in);

    //Alocação da matriz
    matriz = (string**)malloc(N * sizeof(string*));
    for(int i = 0; i < N; i++){
        matriz[i] = (string*)malloc(N * sizeof(string));
    }

    cout << "Tamanho das matrizes = " << N << endl;
    cout << "Quantidade de matrizes = " << nMatrizesArquivo << endl;

    linhaInicial = determinarLinhaInicial();
    colunaInicial = determinarColunaInicial();
    PosicoesAndadas * posicoes = new PosicoesAndadas(nMatrizesArquivo);

    for(int i = 0; i < nMatrizesArquivo; i++){
        lerMatrizArquivo(matriz, arquivo, N);
        criaArquivoEimprimeMatrizNoArquivo(nMatrizesArquivo, matriz, matrizAtual, N);
    }
    
    andar(p, linhaInicial, colunaInicial, N, nMatrizesArquivo, posicoes);

    cout << "\nCasas percorridas ao todo = " << p->casasPercorridas << endl;
    cout << "\nSoma de itens consumidos = " << p->valorTotal << endl;
    posicoesNaoVisitadas(posicoes, nMatrizesArquivo, N);
    cout << "\nPerigos enfrentados, no total = " << p->perigosVisitados << endl;

    //Liberação da matriz
    for(int i = 0; i < N; i++){
        free(matriz[i]);
    }
    free(matriz);

    arquivo.close();
    return 0;
}