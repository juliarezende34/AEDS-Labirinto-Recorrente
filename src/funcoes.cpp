#include "pessoa.hpp"
#include "funcoes.hpp"
#include "posicoesAndadas.hpp"
#include <algorithm>

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

void imprimeMatrizNoArquivo(string ** matriz, ofstream arquivo, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arquivo << matriz[i][j] << " ";
        }
    }
}

void criaArquivoEimprimeMatrizNoArquivo(int nMatrizesArquivo, string ** matriz, int& matrizAtual, int N){
    string path =  "dataset/";
    string nome, nArquivoString;
    int nArquivo;
    stringstream auxiliar;
    
    if(matrizAtual <= nMatrizesArquivo){
        nArquivo = matrizAtual;
        auxiliar << nArquivo;
        nArquivoString = auxiliar.str();
        nome = path + "matriz" + nArquivoString + ".data";
        auxiliar.str("");
        matrizAtual++;
    }
    
    ofstream arquivo2;
    arquivo2.open(nome, ios::out);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arquivo2 << matriz[i][j] << " ";
        }
    }
    arquivo2.close();
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

void lerMatrizArquivoSeparado(string ** matriz, ifstream &arquivo, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arquivo >> matriz[i][j];
        }
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
    int num;
    random_device rd;
    mt19937 gen(rd());
    //srand(time(NULL));
    if(linhaAtual == 0){
        uniform_int_distribution<> dis(0, 1);
        num = dis(gen);
        return num; //Posso descer ou permanecer
    }
    else if(linhaAtual == (N - 1)){
        uniform_int_distribution<> dis(-1, 0);
        num = dis(gen);
        return num; //Posso subir ou permanecer
    }
    else{
        uniform_int_distribution<> dis(-1, 1);
        num = dis(gen);//Posso descer, subir ou permanecer
        return num;
    }
}

int sorteioColuna(int colunaAtual, int N){
    //srand(time(NULL));
    int num;
    random_device rd;
    mt19937 gen(rd());
    if(colunaAtual == 0){
        uniform_int_distribution<> dis(0, 1);
        num = dis(gen);
        return num; //Posso ir para a direita ou permanecer;
    }
    else if(colunaAtual == (N - 1)){
        uniform_int_distribution<> dis(-1, 0);
        num = dis(gen);
        return num; //Posso ir para a esquerda ou permanecer;
    }
    else{
        uniform_int_distribution<> dis(-1, 1);
        num = dis(gen);
        return num;
    }
}

void imprimirMatriz(string ** matriz, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool posicaoFoiVisitada(PosicoesAndadas * posicoes, int nArquivo, int linha, int coluna){
    pair<int,int> par = {linha,coluna};
    if(posicoes->vetorPosicoesAndadas[nArquivo - 1].empty()){
        return false;
    }
    else{
        if((find(posicoes->vetorPosicoesAndadas[nArquivo - 1].begin(), posicoes->vetorPosicoesAndadas[nArquivo - 1].end(), par)) != (posicoes->vetorPosicoesAndadas[nArquivo - 1].end())){
            return true;
        }
        else{
            return false;
        }
    }
}

void escreverMatrizArquivo(string ** matriz, ofstream &arquivo, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arquivo << matriz[i][j] << " ";
        }
        arquivo << "\n";
    }
}

bool paredeAoRedor(string ** matriz, int linha, int coluna, int N){
    bool retorno = false;
    if(linha == 0){
        if(coluna == 0){
            if((matriz[linha + 1][coluna] == "#") && (matriz[linha + 1][coluna + 1] == "#") && (matriz[linha][coluna + 1] == "#")){
                retorno = true;
            }
        }
        else if(coluna == (N - 1)){
            if((matriz[linha + 1][coluna] == "#") && (matriz[linha + 1][coluna - 1] == "#") && (matriz[linha][coluna - 1] == "#")){
                retorno = true;
            }
        }
        else{
            if((matriz[linha + 1][coluna] == "#") && (matriz[linha + 1][coluna + 1] == "#") && (matriz[linha][coluna + 1] == "#") && (matriz[linha + 1][coluna - 1] == "#") && (matriz[linha][coluna - 1] == "#")){
                retorno = true;
            }
        }
    }
    else if(linha == (N - 1)){
        if(coluna == 0){
            if((matriz[linha - 1][coluna] == "#") && (matriz[linha - 1][coluna + 1] == "#") && (matriz[linha][coluna + 1] == "#")){
                retorno = true;
            }
        }
        else if(coluna == (N-1)){
            if((matriz[linha - 1][coluna] == "#") && (matriz[linha - 1][coluna - 1] == "#") && (matriz[linha][coluna - 1] == "#")){
                retorno = true;
            }
        }
        else{
            if((matriz[linha - 1][coluna] == "#") && (matriz[linha - 1][coluna - 1] == "#") && (matriz[linha - 1][coluna + 1] == "#") && (matriz[linha][coluna - 1] == "#") && (matriz[linha][coluna + 1] == "#")){
                retorno = true;
            }
        }
    }
    else{
        if((matriz[linha + 1][coluna] == "#") && (matriz[linha - 1][coluna] == "#") && (matriz[linha][coluna + 1] == "#") && (matriz[linha][coluna - 1] == "#") && (matriz[linha + 1][coluna + 1] == "#") && (matriz[linha + 1][coluna - 1] == "#") && (matriz[linha - 1][coluna + 1] == "#") && (matriz[linha - 1][coluna - 1] == "#")){
            retorno = true;
        }
    }
    return retorno;
}

void andar(Pessoa * p, int linhaInicial, int colunaInicial, int N, int nMatrizesArquivo, PosicoesAndadas * posicoes){
    string ** matriz;
    int linha = linhaInicial, coluna = colunaInicial, valorAtual, acrescimoLinha, acrescimoColuna, contadorDeRodadas = 0, sacolaAnterior, vidaAnterior;
    bool estado = false;
    stringstream s;
    ifstream arquivoLeitura;
    ofstream arquivoEscrita;

    string path =  "dataset/";
    string nome, nArquivoString, nomeEscrita;
    int nArquivo = 1;
    stringstream auxiliar;

    matriz = new string * [N];
    for(int i = 0; i < N; i++){
        matriz[i] = new string[N];
    }

    while(p->vida > 0){
        auxiliar << nArquivo;
        nArquivoString = auxiliar.str();

        nome = path + "matriz" + nArquivoString + ".data";

        cout << "\nARQUIVO: " << nome << endl;
        
        arquivoLeitura.open(nome, ios::in);
        lerMatrizArquivoSeparado(matriz, arquivoLeitura, N);
        arquivoLeitura.close();
        //imprimirMatriz(matriz, N);

        if(contadorDeRodadas > 0){//Atualizar posição inicial quando troca de matriz
            if(matriz[0][0] != "#"){
                linha = 0;
                coluna = 0;
            }
            else{
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < (N-1); j++){//Ignorando a última coluna devido à minha condição de troca
                        if(matriz[i][j] != "#"){
                            linha = i;
                            coluna = j;
                            cout << "\nA posição inicial após a troca foi " << linha << " " << coluna << endl;
                            break;
                        }
                    }
                }
            }
            if(estado && (linha == linhaInicial) && (coluna == colunaInicial) && (vidaAnterior == p->vida) && (sacolaAnterior == p->sacola)){
                cout << "\nCAMINHO ZERADO!\n";
                break;
            }
        }
        else{//Estou na primeira rodada, linha == linhaInicial e coluna == colunaInicial
            if(matriz[linha][coluna] == "#"){
                for(int i = linha; i < N; i++){
                    for(int j = coluna; j < (N-1); j++){//Ignorando a última coluna devido à minha condição de troca
                        if(matriz[i][j] != "#"){
                            linha = i;
                            coluna = j;
                            cout << "\nA posição inicial foi " << linha << " " << coluna << endl;
                            break;
                        }
                    }
                }
            }
        }

        if(paredeAoRedor(matriz, linha, coluna, N)){
            cout << "\nVocê está preso entre paredes, não há como andar. :(\n";
            break;
        }

        while((coluna != (N-1)) && (p->vida > 0)){
            cout << "Posição atual: " << linha << " " << coluna << " " << matriz[linha][coluna] << "\n";

            if(matriz[linha][coluna] != "#"){
                if((matriz[linha][coluna] != "*")){
                    cout << "Posição com número.\n";
                    valorAtual = atoi(matriz[linha][coluna].c_str());
                    if(valorAtual > 0){
                        p->sacola++;
                        p->valorTotal++;
                        valorAtual--;
                        s << valorAtual;
                        matriz[linha][coluna] = s.str();
                        s.str("");
                        if(p->sacola == 4){
                            if(p->vida < 10){
                                vidaAnterior = p->vida;
                                sacolaAnterior = p->sacola;
                                p->vida++;
                                estado = true;
                            }
                            p->sacola = 0;
                        }
                    }    
                    if(!posicaoFoiVisitada(posicoes, nArquivo, linha, coluna)){ 
                        posicoes->vetorPosicoesAndadas[nArquivo - 1].push_back({linha,coluna});   
                    }           
                }

                else if(matriz[linha][coluna] == "*"){
                    p->vida--;
                    cout << "\nVocê perdeu uma vida.\n";
                    if(!posicaoFoiVisitada(posicoes, nArquivo, linha, coluna)){ 
                        posicoes->vetorPosicoesAndadas[nArquivo - 1].push_back({linha,coluna});   
                    }
                    p->perigosVisitados++;
                }
                p->casasPercorridas++;
            }

            acrescimoLinha = sorteioLinha(linha, N);
            acrescimoColuna = sorteioColuna(coluna, N);

            if(matriz[linha + acrescimoLinha][coluna + acrescimoColuna] != "#"){
                linha += acrescimoLinha;
                coluna += acrescimoColuna;
            }
            else{
                cout << "A posição sorteada foi uma parede. Vamos sortear de novo.\n";
            }
            
            //imprimirMatriz(matriz, N); 

            if(p->vida == 0){
                cout << "Suas vidas acabaram. :(\n ";
                break;
            }       
        }
        
        arquivoEscrita.open(nome, ios::out);
        escreverMatrizArquivo(matriz, arquivoEscrita, N);
        arquivoEscrita.close();

        nome.clear();
        nArquivoString.clear();
        auxiliar.str("");
        nArquivo++;
        if(nArquivo > nMatrizesArquivo){
            nArquivo = 1;
        }
        contadorDeRodadas++;
    }
}

void posicoesNaoVisitadas(PosicoesAndadas * posicoes, int nMatrizesArquivo, int N){
    int qtdPosicoesAndadas, naoAndadas, posicoesSemRepetir=0;
    for(int i = 0; i < nMatrizesArquivo; i++){
        qtdPosicoesAndadas = posicoes->vetorPosicoesAndadas[i].size();
        posicoesSemRepetir += qtdPosicoesAndadas;
        naoAndadas = (N * N) - qtdPosicoesAndadas;
        cout << "\nQuantidade de posições não visitadas na matriz " << i + 1 << " = " << naoAndadas << endl;
    }
    cout << "\nQuantidade de posições andadas sem repetir = "  << posicoesSemRepetir << endl;
}

void arquivoOutput(ofstream &arquivo, int nMatrizesArquivo, int N){
    ifstream arquivoLeitura;
    int nArquivo = 1;
    stringstream auxiliar;
    string path =  "dataset/";
    string nome, nArquivoString;
    string ** matriz;

    matriz = new string * [N];
    for(int i = 0; i < N; i++){
        matriz[i] = new string[N];
    }

    for(int i = 0; i < nMatrizesArquivo; i++){
        auxiliar << nArquivo;
        nArquivoString = auxiliar.str();
        nome = path + "matriz" + nArquivoString + ".data";

        arquivoLeitura.open(nome, ios::in);
        lerMatrizArquivoSeparado(matriz, arquivoLeitura, N);
        arquivoLeitura.close();
        escreverMatrizArquivo(matriz, arquivo, N);
        arquivo << '\n';

        nome.clear();
        nArquivoString.clear();
        auxiliar.str("");
        nArquivo++;
    }
}