#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


int ler_elementos(char *nome, int linhas, int colunas, int matriz[linhas][colunas]){
    FILE *txt;

    txt = fopen(nome, "r");
    if(txt==NULL){
        printf("Erro ao ler o arquivo de texto\n");
        return -1;
    }

    for (int i = 0; i < linhas; i++) {
        for(int j = 0; j< colunas; j++ ) {
            if (fscanf(txt, "%d", &matriz[i][j]) != 1){
                printf("Erro ao ler o arquivo\n");
                fclose(txt);
            }   
        }
    }

    return 0;
}


void explorar_ilha(int i, int j, int linhas, int colunas, int matriz[linhas][colunas]){
    if (i < 0 || j < 0 || i >= linhas || j >= colunas || matriz[i][j] == 0)
        return;

    matriz[i][j] = 0;

    explorar_ilha(i-1, j, linhas, colunas, matriz);
    explorar_ilha(i+1, j, linhas, colunas, matriz);
    explorar_ilha(i, j-1, linhas, colunas, matriz);
    explorar_ilha(i, j+1, linhas, colunas, matriz);
}


int n_ilhas(int linhas, int colunas, int matrizcopia[linhas][colunas]){
    int ilhas = 0;

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            if(matrizcopia[i][j] != 0){
                ilhas++;
                explorar_ilha(i, j, linhas, colunas, matrizcopia);
            }
        } 
    }

    return ilhas;
}


int somar_ilha(int i, int j, int linhas, int colunas, int matriz[linhas][colunas]){

    if (i < 0 || j < 0 || i >= linhas || j >= colunas || matriz[i][j] == 0)
        return 0;

    int soma = matriz[i][j];
    matriz[i][j] = 0; 

    soma += somar_ilha(i-1, j, linhas, colunas, matriz);
    soma += somar_ilha(i+1, j, linhas, colunas, matriz);
    soma += somar_ilha(i, j-1, linhas, colunas, matriz);
    soma += somar_ilha(i, j+1, linhas, colunas, matriz);

    return soma;
}


int encontrar_somas(int linhas, int colunas, int matriz[linhas][colunas]){
    int somatotal = 0;

    for(int i = 0; i<linhas; i++){
        for(int j = 0; j<colunas; j++){
            somatotal += somar_ilha(i, j, linhas, colunas, matriz);
        }
    }

    return somatotal;
 }


int profundidades_das_ilhas(int linhas, int colunas, int matriz[linhas][colunas], int valores_ilhas[]){ 
    int copia[linhas][colunas];

    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            copia[i][j] = matriz[i][j];

    int qtd_ilhas = 0;

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            if (copia[i][j] != 0){
                valores_ilhas[qtd_ilhas] = somar_ilha(i, j, linhas, colunas, copia);
                qtd_ilhas++;
            }
        }
    }

    return qtd_ilhas;
}


bool encontrar_combinacoes_rec(int profundidades[], int n, int indice, int alvo, int combinacao[], int tamanho_atual, int soma_atual){
    
    if (soma_atual == alvo) {
        for (int i = 0; i < tamanho_atual; i++)
            printf("%d ", combinacao[i]);
        return true; 
    }
    
    if (indice == n || soma_atual > alvo)
        return false;


    combinacao[tamanho_atual] = profundidades[indice];
    if (encontrar_combinacoes_rec(profundidades, n, indice + 1, alvo,
                                  combinacao, tamanho_atual + 1, soma_atual + profundidades[indice]))
        return true; 

    
    if (encontrar_combinacoes_rec(profundidades, n, indice + 1, alvo,
                                  combinacao, tamanho_atual, soma_atual))
        return true; 

    return false; 
}


void calcular_profundidades(int qtd_somas, int valores_ilhas[], int profundidades[]){
    for (int i = 0; i < qtd_somas; ++i) {
        int p = valores_ilhas[i] / 6;   
        if (p < 1) p = 1;               
        profundidades[i] = p;
    }
}


int achar_combinacao(int conprofundidade, int profundidades[], int qtd_ilhas){
    int soma_total = 0;
    for (int i = 0; i < qtd_ilhas; ++i) soma_total += profundidades[i];

    if (soma_total < conprofundidade) {
        printf("Nao ha resposta valida! \n");
        return 0;
    }

    int combinacao[qtd_ilhas];
    bool achou = encontrar_combinacoes_rec(profundidades, qtd_ilhas, 0, conprofundidade, combinacao, 0, 0);

    if (!achou)
        printf("Nao ha resposta valida! \n");

    return 0;
}


int main(int argc, char *argv[]){
    if(argc != 5){
        printf("A entrada deve estar no modelo: <profundidade_container> <linhas_da_matriz> <colunas_da_matriz> exemplo.txt \n");
        return 1;
    }

    int conprofundidade = atoi(argv[1]);
    int linhas = atoi(argv[2]);
    int colunas = atoi(argv[3]);
    int matriz[linhas][colunas];
    int matrizcopia[linhas][colunas];
    int valores_ilhas[linhas*colunas];
    char * nome = argv[4];

    ler_elementos(nome, linhas, colunas, matriz);

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            matrizcopia[i][j] = matriz[i][j];
        }
    }

    int nilhas = n_ilhas(linhas, colunas, matrizcopia);

    int funduras = profundidades_das_ilhas(linhas, colunas, matriz, valores_ilhas);

    printf("%d \n", nilhas);

    int profundidades[funduras];
    calcular_profundidades(funduras, valores_ilhas, profundidades);

    for (int i = 0; i < funduras; i++) {
        int profundidades = valores_ilhas[i]/6;
        if(profundidades>=1){
        printf("%d ", profundidades);
        }
        else
            printf("1 ");
        
    }

    printf("\n");
    
    int mochila = achar_combinacao(conprofundidade, profundidades, funduras);

    printf("\n");

    return 0;
}