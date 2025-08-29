#include <stdbool.h>
#include <stdio.h>

#define TAMANHO 10
#define TAM_PADRAO 3
#define LARGURA_PADRAO 5

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]);
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO], const char* titulo);
bool validarEntrada(int valor, int min, int max, const char* mensagem);
void posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int inicio_i, int inicio_j,
                               int tamanho);
void posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int inicio_i, int inicio_j,
                             int tamanho);
void posicionarNavioDiagonal(int tabuleiro[TAMANHO][TAMANHO], int inicio_i, int inicio_j,
                             int tamanho);
void aplicarPadrao(int areas_afetadas[TAMANHO][TAMANHO], int centro_i, int centro_j,
                   int padrao[TAM_PADRAO][LARGURA_PADRAO], const char* nomePadrao);

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0};
    int areas_afetadas[TAMANHO][TAMANHO] = {0};

    int cone[TAM_PADRAO][LARGURA_PADRAO] = {{0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {1, 1, 1, 1, 1}};
    int cruz[TAM_PADRAO][LARGURA_PADRAO] = {{0, 0, 1, 0, 0}, {1, 1, 1, 1, 1}, {0, 0, 1, 0, 0}};
    int octaedro[TAM_PADRAO][LARGURA_PADRAO] = {{0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}};

    int horizontal_inicio_i, horizontal_inicio_j;
    int vertical_inicio_i, vertical_inicio_j;
    int diagonal1_inicio_i, diagonal1_inicio_j;
    int diagonal2_inicio_i, diagonal2_inicio_j;
    int centro_i, centro_j;

    printf("=== BATALHA NAVAL - TODOS OS NÍVEIS ===\n\n");

    printf("=== NÍVEL NOVATO ===\n");
    printf("Posicionamento de Navios Básicos\n\n");

    printf("Navio Horizontal (3 células):\n");
    do {
        printf("Linha inicial (0-9): ");
        scanf("%d", &horizontal_inicio_i);
    } while (!validarEntrada(horizontal_inicio_i, 0, 9, "Linha deve estar entre 0 e 9"));

    do {
        printf("Coluna inicial (0-7): ");
        scanf("%d", &horizontal_inicio_j);
    } while (!validarEntrada(horizontal_inicio_j, 0, 7, "Coluna deve estar entre 0 e 7"));

    printf("\nNavio Vertical (3 células):\n");
    do {
        printf("Linha inicial (0-7): ");
        scanf("%d", &vertical_inicio_i);
    } while (!validarEntrada(vertical_inicio_i, 0, 7, "Linha deve estar entre 0 e 7"));

    do {
        printf("Coluna inicial (0-9): ");
        scanf("%d", &vertical_inicio_j);
    } while (!validarEntrada(vertical_inicio_j, 0, 9, "Coluna deve estar entre 0 e 9"));

    printf("\n=== NÍVEL AVENTUREIRO ===\n");
    printf("Posicionamento de Navios Adicionais\n\n");

    printf("Navio Diagonal 1 (4 células):\n");
    do {
        printf("Linha inicial (0-6): ");
        scanf("%d", &diagonal1_inicio_i);
    } while (!validarEntrada(diagonal1_inicio_i, 0, 6, "Linha deve estar entre 0 e 6"));

    do {
        printf("Coluna inicial (0-6): ");
        scanf("%d", &diagonal1_inicio_j);
    } while (!validarEntrada(diagonal1_inicio_j, 0, 6, "Coluna deve estar entre 0 e 6"));

    printf("\nNavio Diagonal 2 (4 células):\n");
    do {
        printf("Linha inicial (0-6): ");
        scanf("%d", &diagonal2_inicio_i);
    } while (!validarEntrada(diagonal2_inicio_i, 0, 6, "Linha deve estar entre 0 e 6"));

    do {
        printf("Coluna inicial (0-6): ");
        scanf("%d", &diagonal2_inicio_j);
    } while (!validarEntrada(diagonal2_inicio_j, 0, 6, "Coluna deve estar entre 0 e 6"));

    printf("\n=== NÍVEL MESTRE ===\n");
    printf("Centro das Habilidades Especiais\n\n");

    printf("Linha do centro (1-8): ");
    scanf("%d", &centro_i);
    while (!validarEntrada(centro_i, 1, 8, "Linha deve estar entre 1 e 8")) {
        printf("Linha do centro (1-8): ");
        scanf("%d", &centro_i);
    }

    printf("Coluna do centro (2-7): ");
    scanf("%d", &centro_j);
    while (!validarEntrada(centro_j, 2, 7, "Coluna deve estar entre 2 e 7")) {
        printf("Coluna do centro (2-7): ");
        scanf("%d", &centro_j);
    }

    posicionarNavioHorizontal(tabuleiro, horizontal_inicio_i, horizontal_inicio_j, 3);
    posicionarNavioVertical(tabuleiro, vertical_inicio_i, vertical_inicio_j, 3);

    posicionarNavioDiagonal(tabuleiro, diagonal1_inicio_i, diagonal1_inicio_j, 4);
    posicionarNavioDiagonal(tabuleiro, diagonal2_inicio_i, diagonal2_inicio_j, 4);

    exibirTabuleiro(tabuleiro, "TABULEIRO COMPLETO COM NAVIOS (0-ÁGUA, 1-NAVIO)");

    aplicarPadrao(areas_afetadas, centro_i, centro_j, cone, "CONE");
    exibirTabuleiro(areas_afetadas, "ÁREAS AFETADAS PELO CONE (0-NÃO, 1-SIM)");

    aplicarPadrao(areas_afetadas, centro_i, centro_j, cruz, "CRUZ");
    exibirTabuleiro(areas_afetadas, "ÁREAS AFETADAS PELA CRUZ (0-NÃO, 1-SIM)");

    aplicarPadrao(areas_afetadas, centro_i, centro_j, octaedro, "OCTAEDRO");
    exibirTabuleiro(areas_afetadas, "ÁREAS AFETADAS PELO OCTAEDRO (0-NÃO, 1-SIM)");

    return 0;
}

bool validarEntrada(int valor, int min, int max, const char* mensagem) {
    if (valor < min || valor > max) {
        printf("Entrada inválida! %s\n", mensagem);
        return false;
    }
    return true;
}

void posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int inicio_i, int inicio_j,
                               int tamanho) {
    for (int j = inicio_j; j < inicio_j + tamanho; j++) {
        if (j < TAMANHO) {
            tabuleiro[inicio_i][j] = 1;
        }
    }
}

void posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int inicio_i, int inicio_j,
                             int tamanho) {
    for (int i = inicio_i; i < inicio_i + tamanho; i++) {
        if (i < TAMANHO) {
            tabuleiro[i][inicio_j] = 1;
        }
    }
}

void posicionarNavioDiagonal(int tabuleiro[TAMANHO][TAMANHO], int inicio_i, int inicio_j,
                             int tamanho) {
    for (int d = 0; d < tamanho; d++) {
        int i = inicio_i + d;
        int j = inicio_j + d;
        if (i < TAMANHO && j < TAMANHO) {
            tabuleiro[i][j] = 1;
        }
    }
}

void aplicarPadrao(int areas_afetadas[TAMANHO][TAMANHO], int centro_i, int centro_j,
                   int padrao[TAM_PADRAO][LARGURA_PADRAO], const char* nomePadrao) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            areas_afetadas[i][j] = 0;
        }
    }

    for (int i = 0; i < TAM_PADRAO; i++) {
        for (int j = 0; j < LARGURA_PADRAO; j++) {
            int x = centro_i - 1 + i;
            int y = centro_j - 2 + j;
            if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO) {
                areas_afetadas[x][y] = padrao[i][j];
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO], const char* titulo) {
    printf("\n=== %s ===\n", titulo);
    printf("   0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}