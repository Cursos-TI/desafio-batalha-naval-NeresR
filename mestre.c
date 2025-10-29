#include <stdio.h>
#include <stdlib.h>  // <-- necessário para abs()

#define TAM 10        // Tamanho do tabuleiro
#define NAVIO 3       // Valor que representa o navio
#define AGUA 0        // Valor que representa a água
#define HABILIDADE 5  // Valor que representa área de efeito

// -----------------------------
// Função para inicializar o tabuleiro
// -----------------------------
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// -----------------------------
// Função para exibir o tabuleiro formatado
// -----------------------------
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Habilidade\n");
}

// -----------------------------
// Função para posicionar manualmente alguns navios
// -----------------------------
void posicionarNavios(int tabuleiro[TAM][TAM]) {
    // Navio horizontal
    for (int j = 2; j < 2 + NAVIO; j++)
        tabuleiro[1][j] = NAVIO;

    // Navio vertical
    for (int i = 5; i < 5 + NAVIO; i++)
        tabuleiro[i][7] = NAVIO;

    // Diagonal principal ↘
    for (int i = 0; i < NAVIO; i++)
        tabuleiro[i][i] = NAVIO;

    // Diagonal secundária ↙
    for (int i = 0; i < NAVIO; i++)
        tabuleiro[i][9 - i] = NAVIO;
}

// -----------------------------
// Função para construir matriz de habilidade CONE (5x5)
// -----------------------------
void construirCone(int cone[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // Condicional: forma de cone invertido (expande para baixo)
            if (j >= 2 - i && j <= 2 + i && i < 5)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// -----------------------------
// Função para construir matriz de habilidade CRUZ (5x5)
// -----------------------------
void construirCruz(int cruz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // Linhas e colunas centrais formam a cruz
            if (i == 2 || j == 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// -----------------------------
// Função para construir matriz de habilidade OCTAEDRO (5x5)
// -----------------------------
void construirOctaedro(int oct[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // Forma de losango (|i - centro| + |j - centro| <= 2)
            // Usando abs() — certifique-se de ter incluído <stdlib.h>
            if ((abs(i - 2) + abs(j - 2)) <= 2)
                oct[i][j] = 1;
            else
                oct[i][j] = 0;

            /* Alternativa sem abs(), caso prefira:
            int di = (i - 2 >= 0) ? (i - 2) : (2 - i);
            int dj = (j - 2 >= 0) ? (j - 2) : (2 - j);
            if (di + dj <= 2) oct[i][j] = 1; else oct[i][j] = 0;
            */
        }
    }
}

// -----------------------------
// Função para aplicar a habilidade no tabuleiro
// -----------------------------
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[5][5], int origemX, int origemY) {
    int centro = 2; // centro da matriz 5x5

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                // Calcula a posição correspondente no tabuleiro
                int x = origemX + (i - centro);
                int y = origemY + (j - centro);

                // Valida se está dentro dos limites
                if (x >= 0 && x < TAM && y >= 0 && y < TAM) {
                    // Marca área de efeito sem apagar navios
                    if (tabuleiro[x][y] == AGUA)
                        tabuleiro[x][y] = HABILIDADE;
                }
            }
        }
    }
}

// -----------------------------
// Função principal
// -----------------------------
int main() {
    int tabuleiro[TAM][TAM];
    int cone[5][5], cruz[5][5], oct[5][5];

    // 1. Inicializar tabuleiro e navios
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    // 2. Construir as matrizes das habilidades
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(oct);

    // 3. Definir origens das habilidades
    int origemCone[2] = {3, 3};
    int origemCruz[2] = {6, 5};
    int origemOct[2] = {8, 2};

    // 4. Aplicar as habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, origemCone[0], origemCone[1]);
    aplicarHabilidade(tabuleiro, cruz, origemCruz[0], origemCruz[1]);
    aplicarHabilidade(tabuleiro, oct, origemOct[0], origemOct[1]);

    // 5. Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
