#include "posicoesAndadas.hpp"
#include <algorithm>

int lerPrimeiraLinha(ifstream &arquivo);//

int contarLinhasVazias(ifstream& arquivo);//

void imprimeMatrizNoArquivo(string ** matriz, ofstream arquivo, int N);//

void criaArquivoEimprimeMatrizNoArquivo(int nMatrizesArquivo, string ** matriz, int& matrizAtual, int N);//

void lerMatrizArquivo(string ** matrizTexto, ifstream &arquivo, int N);//

void lerMatrizArquivoSeparado(string ** matriz, ifstream &arquivo, int N);//

int determinarLinhaInicial();//

int determinarColunaInicial();//

int sorteioLinha(int linhaAtual, int N);//

int sorteioColuna(int colunaAtual, int N);//

void imprimirMatriz(string ** matriz, int N);//

bool posicaoFoiVisitada(PosicoesAndadas * posicoes, int nArquivo, int linha, int coluna);//

void escreverMatrizArquivo(string ** matriz, ofstream &arquivo, int N);//

bool paredeAoRedor(string ** matriz, int linha, int coluna, int N);//

void andar(Pessoa * p, int linhaInicial, int colunaInicial, int N, int nMatrizesArquivo, PosicoesAndadas * posicoes);//

void posicoesRelatorio(PosicoesAndadas * posicoes, int nMatrizesArquivo, int N);//

void arquivoOutput(ofstream &arquivo, int nMatrizesArquivo, int N);//

int verificarCondicaoTroca(string ** matriz, int N);//

void apagarArquivosSeparados(int nMatrizesArquivo);//