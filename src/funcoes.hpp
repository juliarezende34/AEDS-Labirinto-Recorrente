#include "pessoa.hpp"

int lerPrimeiraLinha(ifstream &arquivo){
    int N;
    string primeiraLinha;
    getline(arquivo, primeiraLinha);
    N = atoi(primeiraLinha.c_str());
    return N;
}

int contarLinhasVazias(ifstream& arquivo){
    string linha;
    bool estado;
    int cont = 0;
    while(!arquivo.eof()){
        getline(arquivo, linha);
        estado = true;
        for(char c : linha){
            if(!isspace(c)){
                estado = false;
            }
        }
        if(estado){
            cont++;
        }
    }
    return cont;
}

void lerMatrizArquivo(string ** matrizTexto, ifstream &arquivo, int N){
    int cont = 0;
    string numeroAtual, linha;
    getline(arquivo, linha);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrizTexto[i][j] = "x";
        }
    }

    if (!arquivo)
    {
        cout << "Erro na abertura do arquivo!!\n";
        exit(-1);
    }
    else
    { 
        for (int x = 0; x < N; x++)
        {
            getline(arquivo, linha);

            for (int i = 0; i <= (int) linha.size(); i++)
            {
                if (linha[i] != '\0')
                {
                    if (linha[i] != ' ')
                    {
                        numeroAtual += linha[i];
                    }
                    else
                    {
                        for (int i = 0; i < N; i++)
                        {
                            if (matrizTexto[cont][i] == "x")
                            {
                                matrizTexto[cont][i] = numeroAtual;
                                break;
                            }
                        }
                        numeroAtual.clear();
                    }
                }
                else
                {
                    break;
                }
            }
            cont++;
            linha.clear();
        }
        cont = 0;
    }
}

int determinarLinhaInicial(){
    int linha;
    cout << "Digite a linha da posição inicial:\n>";
    cin >> linha;
    return linha;
}

int determinarColunaInicial(){
    int coluna;
    cout << "Digite a coluna da posição inicial:\n>";
    cin >> coluna;
    return coluna;
}

int sorteioLinha(int linhaAtual, int N){
    srand(time(NULL));
    int num;
    if(linhaAtual == 0){
        return 1; //Posso somente descer
    }
    else if(linhaAtual == (N - 1)){
        return -1; //Posso somente subir
    }
    else{
        num = rand()%2 - 1;
        return num;
    }
}

int sorteioColuna(int colunaAtual, int N){
    srand(time(NULL));
    int num;
    if(colunaAtual = 0){
        return 1; //Posso somente ir para a direita;
    }
    else if(colunaAtual == (N - 1)){
        return -1; //Posso somente ir para a esquerda;
    }
    else{
        num = rand()%2 - 1;
        return num;
    }
}

void andar(Pessoa * p, int linhaInicial, int colunaInicial, int N, string ** matriz){
    int linha = linhaInicial, coluna = colunaInicial, valorAtual;
    stringstream s;
    while(p->vida > 0){
        if((matriz[linha][coluna] != "*") && (matriz[linha][coluna] != "#")){
            valorAtual = atoi(matriz[linha][coluna].c_str());
            if(valorAtual > 0){
                p->sacola++;
                valorAtual--;
                s << valorAtual;
                s >> matriz[linha][coluna];
            }
        }
    }
}