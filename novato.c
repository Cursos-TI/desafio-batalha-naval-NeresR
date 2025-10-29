#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Tamanho fixo dos navios
#define AGUA 0        // Valor que representa água
#define NAVIO_VAL 3   // Valor que representa um navio

int main() {
    int tabuleiro[TAM][TAM]; // Matriz 10x10 representando o tabuleiro
    int i, j;

    // ==== 1. Inicializar o tabuleiro com 0 (água) ====
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // ==== 2. Definir coordenadas iniciais dos navios ====
    // Navio 1: horizontal (linha 2, coluna 4)
    int linhaNavio1 = 2;
    int colunaNavio1 = 4;

    // Navio 2: vertical (linha 5, coluna 7)
    int linhaNavio2 = 5;
    int colunaNavio2 = 7;

    // ==== 3. Validar e posicionar o primeiro navio (horizontal) ====
    if (colunaNavio1 + NAVIO <= TAM) {
        for (j = colunaNavio1; j < colunaNavio1 + NAVIO; j++) {
            tabuleiro[linhaNavio1][j] = NAVIO_VAL;
        }
    } else {
        printf("Erro: Navio 1 fora dos limites do tabuleiro.\n");
        return 1;
    }

    // ==== 4. Validar e posicionar o segundo navio (vertical) ====
    if (linhaNavio2 + NAVIO <= TAM) {
        for (i = linhaNavio2; i < linhaNavio2 + NAVIO; i++) {
            // Verifica se há sobreposição com outro navio
            if (tabuleiro[i][colunaNavio2] == NAVIO_VAL) {
                printf("Erro: Navio 2 se sobrepõe ao Navio 1.\n");
                return 1;
            }
            tabuleiro[i][colunaNavio2] = NAVIO_VAL;
        }
    } else {
        printf("Erro: Navio 2 fora dos limites do tabuleiro.\n");
        return 1;
    }

    // ==== 5. Exibir o tabuleiro ====
    printf("\n=== Tabuleiro Batalha Naval ===\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n");

    return 0;
}
