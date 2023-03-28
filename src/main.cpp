#include "pessoa.hpp"
#include "funcoes.hpp"

int main(){    
    int N, nMatrizesArquivo, linhaInicial, colunaInicial;
    ifstream arquivo;
    string ** matriz;
    //Pessoa * p = new Pessoa();

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

    cout << "N = " << N << endl;
    cout << "nMatrizesArquivo = " << nMatrizesArquivo << endl;
    lerMatrizArquivo(matriz, arquivo, N);
    
    linhaInicial = determinarLinhaInicial();
    colunaInicial = determinarColunaInicial();


    //Liberação da matriz
    for(int i = 0; i < N; i++){
        free(matriz[i]);
    }
    free(matriz);

    arquivo.close();
    return 0;
}