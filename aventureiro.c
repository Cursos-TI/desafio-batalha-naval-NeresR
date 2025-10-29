#include <stdio.h>

#define TAM 10        // Tamanho fixo do tabuleiro (10x10)
#define NAVIO 3       // Tamanho dos navios (3 posições)
#define AGUA 0        // Valor que representa água
#define NAVIO_VAL 3   // Valor que representa um navio

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // === 1. Inicializar o tabuleiro com 0 (água) ===
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // === 2. Definir coordenadas iniciais para os navios ===
    // Navio 1: horizontal (linha 1, coluna 2)
    int linhaN1 = 1, colunaN1 = 2;

    // Navio 2: vertical (linha 5, coluna 7)
    int linhaN2 = 5, colunaN2 = 7;

    // Navio 3: diagonal principal (↘) começando em (0,0)
    int linhaN3 = 0, colunaN3 = 0;

    // Navio 4: diagonal secundária (↙) começando em (0, 9)
    int linhaN4 = 0, colunaN4 = 9;

    // === 3. Posicionar o Navio 1 (horizontal) ===
    if (colunaN1 + NAVIO <= TAM) {
        for (j = colunaN1; j < colunaN1 + NAVIO; j++) {
            if (tabuleiro[linhaN1][j] == NAVIO_VAL) {
                printf("Erro: sobreposição detectada no Navio 1.\n");
                return 1;
            }
            tabuleiro[linhaN1][j] = NAVIO_VAL;
        }
    } else {
        printf("Erro: Navio 1 fora dos limites do tabuleiro.\n");
        return 1;
    }

    // === 4. Posicionar o Navio 2 (vertical) ===
    if (linhaN2 + NAVIO <= TAM) {
        for (i = linhaN2; i < linhaN2 + NAVIO; i++) {
            if (tabuleiro[i][colunaN2] == NAVIO_VAL) {
                printf("Erro: sobreposição detectada no Navio 2.\n");
                return 1;
            }
            tabuleiro[i][colunaN2] = NAVIO_VAL;
        }
    } else {
        printf("Erro: Navio 2 fora dos limites do tabuleiro.\n");
        return 1;
    }

    // === 5. Posicionar o Navio 3 (diagonal principal ↘) ===
    if (linhaN3 + NAVIO <= TAM && colunaN3 + NAVIO <= TAM) {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaN3 + i][colunaN3 + i] == NAVIO_VAL) {
                printf("Erro: sobreposição detectada no Navio 3.\n");
                return 1;
            }
            tabuleiro[linhaN3 + i][colunaN3 + i] = NAVIO_VAL;
        }
    } else {
        printf("Erro: Navio 3 fora dos limites do tabuleiro.\n");
        return 1;
    }

    // === 6. Posicionar o Navio 4 (diagonal secundária ↙) ===
    if (linhaN4 + NAVIO <= TAM && colunaN4 - (NAVIO - 1) >= 0) {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaN4 + i][colunaN4 - i] == NAVIO_VAL) {
                printf("Erro: sobreposição detectada no Navio 4.\n");
                return 1;
            }
            tabuleiro[linhaN4 + i][colunaN4 - i] = NAVIO_VAL;
        }
    } else {
        printf("Erro: Navio 4 fora dos limites do tabuleiro.\n");
        return 1;
    }

    // === 7. Exibir o tabuleiro ===
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n");

    return 0;
}
