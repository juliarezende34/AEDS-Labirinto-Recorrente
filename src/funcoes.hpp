#include "pessoa.hpp"

vector<string> nomeArquivos;

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
        nomeArquivos.push_back(nome);
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

void andar(Pessoa * p, int linhaInicial, int colunaInicial, int N){
    string ** matriz;
    int linha = linhaInicial, coluna = colunaInicial, valorAtual, acrescimoLinha, acrescimoColuna;
    stringstream s;
    ifstream arquivoLeitura;
    ofstream arquivoEscrita;

    string path =  "dataset/";
    string nome, nArquivoString;
    int nArquivo = 1;
    stringstream auxiliar;

    auxiliar << nArquivo;
    nArquivoString = auxiliar.str();

    nome = path + "matriz" + nArquivoString + ".data";
    
    matriz = new string * [N];
    for(int i = 0; i < N; i++){
        matriz[i] = new string[N];
    }
    
    arquivoLeitura.open("dataset/input.data", ios::in);
    lerMatrizArquivo(matriz, arquivoLeitura, N);
    imprimirMatriz(matriz, N);

    while((p->vida > 0) /* && ((linha != (N -1)) && (coluna != (N-1))) && ((linha != 0)) && (coluna != (N-1)) && ((linha != (N -1)) && (coluna != 0)) */){
        cout << "Posição atual: " << linha << " " << coluna << " " << matriz[linha][coluna] << "\n";
        if(matriz[linha][coluna] != "#"){
            if((matriz[linha][coluna] != "*")){
                cout << "Posição com número.\n";
                valorAtual = atoi(matriz[linha][coluna].c_str());
                if(valorAtual > 0){
                    p->sacola++;
                    valorAtual--;
                    s << valorAtual;
                    matriz[linha][coluna] = s.str();
                    s.str("");
                }
                p->casasPercorridas++;
                
            }

            else if(matriz[linha][coluna] == "*"){
                p->vida--;
                p->casasPercorridas++;
                cout << "\nVocê perdeu uma vida.\n";
            }
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
        
        imprimirMatriz(matriz, N); 

        if(p->vida == 0){
            cout << "Suas vidas acabaram. :(\n ";
        }       
    }
}
