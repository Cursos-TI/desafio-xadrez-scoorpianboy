#include <stdio.h>

/* =========================
   "Entradas" definidas no código
   ========================= */
int TORRE_PASSOS_DIREITA   = 5;  /* Torre: 5 casas p/ Direita (recursivo) */
int BISPO_PASSOS_DIAGONAL  = 5;  /* Bispo: 5 casas em Cima Direita (recursivo e loops aninhados) */
int RAINHA_PASSOS_ESQUERDA = 8;  /* Rainha: 8 casas p/ Esquerda (recursivo) */

/* Cavalo (aventureiro) — 2 Baixo, 1 Esquerda (loops aninhados simples) */
int CAVALO_BASICO_BAIXO    = 2;
int CAVALO_BASICO_ESQUERDA = 1;

/* Cavalo (mestre) — 2 Cima, 1 Direita (loops aninhados complexos) */
int CAVALO_TOP_CIMA        = 2;
int CAVALO_TOP_DIREITA     = 1;

/* Strings de direção (padrão do enunciado) */
const char* DIR_CIMA          = "Cima";
const char* DIR_BAIXO         = "Baixo";
const char* DIR_ESQUERDA      = "Esquerda";
const char* DIR_DIREITA       = "Direita";
const char* DIR_CIMA_DIREITA  = "Cima Direita";

/* =========================
   TORRE (recursivo) — Direita
   ========================= */
void torre_direita_rec(int passos) {
    if (passos <= 0) return;              /* caso base */
    printf("%s\n", DIR_DIREITA);          /* imprime uma casa */
    torre_direita_rec(passos - 1);        /* próximo passo */
}

/* =========================
   BISPO (recursivo) — Cima Direita
   ========================= */
void bispo_cima_direita_rec(int passos) {
    if (passos <= 0) return;
    printf("%s\n", DIR_CIMA_DIREITA);
    bispo_cima_direita_rec(passos - 1);
}

/* =========================
   BISPO (loops aninhados)
   - externo: componente vertical (cima)
   - interno: componente horizontal (direita)
   - imprime exatamente 1 passo diagonal por iteração externa
   ========================= */
void bispo_cima_direita_loops(int passos_verticais, int passos_horizontais) {
    for (int v = 0; v < passos_verticais; v++) {  /* vertical (externo) */
        for (int h = 0; h < passos_horizontais; h++) {  /* horizontal (interno) */
            if (h == v) {                       /* sincroniza 1× horizontal p/ cada vertical */
                printf("%s\n", DIR_CIMA_DIREITA);
                break;                           /* evita múltiplas impressões por passo */
            }
        }
    }
}

/* =========================
   RAINHA (recursivo) — Esquerda
   ========================= */
void rainha_esquerda_rec(int passos) {
    if (passos <= 0) return;
    printf("%s\n", DIR_ESQUERDA);
    rainha_esquerda_rec(passos - 1);
}

/* =========================
   CAVALO (aventureiro)
   2× Baixo e 1× Esquerda
   - loops aninhados: for (baixo) + while (esquerda)
   - separado por linha em branco dos anteriores (feito no main)
   ========================= */
void cavalo_basico() {
    /* segmento vertical: 2 casas p/ baixo (for) */
    for (int i = 0; i < CAVALO_BASICO_BAIXO; i++) {
        printf("%s\n", DIR_BAIXO);
    }
    /* segmento horizontal: 1 casa p/ esquerda (while) */
    int rest = CAVALO_BASICO_ESQUERDA;
    while (rest > 0) {
        printf("%s\n", DIR_ESQUERDA);
        rest--;
    }
}

/* =========================
   CAVALO (mestre)
   2× Cima e 1× Direita
   - loops aninhados com múltiplas variáveis/condições
   - uso de continue e break p/ controle de fluxo
   ========================= */
void cavalo_avancado() {
    int impressos = 0;  /* segurança para manter 3 saídas: 2 Cima + 1 Direita */

    /* segmento 0 = vertical (2× Cima), segmento 1 = horizontal (1× Direita) */
    for (int seg = 0; seg < 2; seg++) {
        int alvo = (seg == 0) ? CAVALO_TOP_CIMA : CAVALO_TOP_DIREITA;
        int feito = 0;

        /* exemplo de condição “inútil” apenas para demonstrar continue com critério */
        if (alvo == 0) {
            continue;  /* pularia segmento vazio (não é o caso aqui) */
        }

        /* do-while interno executando as casas do segmento atual */
        do {
            /* proteção extra: não imprimir além de 3 linhas desse cavalo */
            if (impressos >= 3) {
                break;
            }

            if (seg == 0) {
                printf("%s\n", DIR_CIMA);
            } else {
                printf("%s\n", DIR_DIREITA);
            }

            feito++;
            impressos++;

            /* se, por qualquer motivo, ultrapassar o alvo, encerra cedo */
            if (feito > alvo) {
                break;
            }

        } while (feito < alvo);

        if (impressos >= 3) break;  /* encerra o laço externo ao completar o L */
    }
}

/* =========================
   MAIN — organiza a saída
   - cada peça identificada
   - linha em branco entre blocos
   ========================= */
int main(void) {
    /* Torre (recursivo) */
    printf("Torre:\n");
    torre_direita_rec(TORRE_PASSOS_DIREITA);
    printf("\n");

    /* Bispo (recursivo) */
    printf("Bispo (recursivo):\n");
    bispo_cima_direita_rec(BISPO_PASSOS_DIAGONAL);
    printf("\n");

    /* Bispo (loops aninhados) */
    printf("Bispo (loops aninhados):\n");
    bispo_cima_direita_loops(BISPO_PASSOS_DIAGONAL, BISPO_PASSOS_DIAGONAL);
    printf("\n");

    /* Rainha (recursivo) */
    printf("Rainha:\n");
    rainha_esquerda_rec(RAINHA_PASSOS_ESQUERDA);
    printf("\n");

    /* Cavalo — aventureiro */
    printf("Cavalo (basico):\n");
    cavalo_basico();
    printf("\n");

    /* Cavalo — mestre */
    printf("Cavalo (avancado):\n");
    cavalo_avancado();
    printf("\n");

    return 0;
}
