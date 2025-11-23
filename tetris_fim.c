#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // tamanho fixo da fila

// -----------------------------
//       STRUCT DA PEÇA
// -----------------------------
typedef struct {
    char nome; // tipo da peça ('I', 'O', 'T', 'L')
    int id;    // identificador único
} Peca;

// -----------------------------
//        VARIÁVEIS GLOBAIS
// -----------------------------
Peca fila[TAM_FILA];
int frente = 0;      
int tras = 0;
int qtd = 0;
int ultimoID = 0;

// -----------------------------
//   GERA UMA NOVA PEÇA
// -----------------------------
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = ultimoID++;
    return nova;
}

// -----------------------------
//      INSERE NA FILA
// -----------------------------
void enqueue() {
    if (qtd == TAM_FILA) {
        printf("\n⚠️  A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAM_FILA;
    qtd++;

    printf("\nPeça inserida com sucesso!\n");
}

// -----------------------------
//    REMOVE DA FILA (DEQUEUE)
// -----------------------------
void dequeue() {
    if (qtd == 0) {
        printf("\n⚠️  A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca p = fila[frente];

    printf("\nPeça jogada: [%c %d]\n", p.nome, p.id);

    frente = (frente + 1) % TAM_FILA;
    qtd--;
}

// -----------------------------
//   MOSTRA TODA A FILA
// -----------------------------
void exibirFila() {
    printf("\n=== Fila de Peças ===\n");

    if (qtd == 0) {
        printf("(vazia)\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < qtd; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

// -----------------------------
//           MENU
// -----------------------------
void menu() {
    printf("\n\nOpções:\n");
    printf("1 - Jogar peça (dequeue)\n");
    printf("2 - Inserir nova peça (enqueue)\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// -----------------------------
//       PROGRAMA PRINCIPAL
// -----------------------------
int main() {
    srand(time(NULL));

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        exibirFila();
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
