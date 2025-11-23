#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// -----------------------------
//      STRUCT DA PEÇA
// -----------------------------
typedef struct {
    char nome;
    int id;
} Peca;

// -----------------------------
//    VARIÁVEIS GLOBAIS
// -----------------------------
Peca fila[TAM_FILA];
int frente = 0;
int tras = 0;
int qtdFila = 0;

Peca pilha[TAM_PILHA];
int topo = -1;

int ultimoID = 0;

// -----------------------------
//      GERA UMA NOVA PEÇA
// -----------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = ultimoID++;
    return nova;
}

// -----------------------------
//      ENQUEUE NA FILA
// -----------------------------
void enqueue() {
    if (qtdFila == TAM_FILA) {
        printf("\n[FILA CHEIA - ERRO GRAVE]\n");
        return;
    }

    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAM_FILA;
    qtdFila++;
}

// -----------------------------
//      DEQUEUE NA FILA
// -----------------------------
Peca dequeue() {
    Peca removida = {'?', -1};

    if (qtdFila == 0) {
        printf("\n⚠️  A fila está vazia! Não há peças.\n");
        return removida;
    }

    removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    qtdFila--;

    return removida;
}

// -----------------------------
//        PUSH NA PILHA
// -----------------------------
void push(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("\n⚠️  A pilha está cheia! Não é possível reservar mais peças.\n");
        return;
    }

    pilha[++topo] = p;
    printf("\nPeça reservada: [%c %d]\n", p.nome, p.id);
}

// -----------------------------
//        POP NA PILHA
// -----------------------------
Peca pop() {
    Peca removida = {'?', -1};

    if (topo == -1) {
        printf("\n⚠️  A pilha está vazia! Nenhuma peça reservada.\n");
        return removida;
    }

    removida = pilha[topo--];
    printf("\nPeça usada da reserva: [%c %d]\n", removida.nome, removida.id);
    return removida;
}

// -----------------------------
//      EXIBE A FILA E A PILHA
// -----------------------------
void exibirEstado() {
    printf("\n==============================\n");
    printf("      ESTADO ATUAL\n");
    printf("==============================\n");

    // Fila
    printf("Fila de Peças: ");
    if (qtdFila == 0) {
        printf("(vazia)");
    } else {
        int i = frente;
        for (int c = 0; c < qtdFila; c++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }

    // Pilha
    printf("\nPilha de Reserva (Topo -> Base): ");
    if (topo == -1) {
        printf("(vazia)");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n==============================\n");
}

// -----------------------------
//              MENU
// -----------------------------
void menu() {
    printf("\nOpções:\n");
    printf("1 - Jogar peça\n");
    printf("2 - Reservar peça\n");
    printf("3 - Usar peça reservada\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// -----------------------------
//       FUNÇÃO PRINCIPAL
// -----------------------------
int main() {
    srand(time(NULL));

    // Inicializa fila cheia
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        exibirEstado();
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Jogar peça
                Peca jogada = dequeue();
                if (jogada.id != -1) {
                    printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                    enqueue(); // Sempre gerar nova peça
                }
                break;
            }

            case 2: {
                // Reservar peça (fila -> pilha)
                if (qtdFila > 0 && topo < TAM_PILHA - 1) {
                    Peca p = dequeue();
                    push(p);
                    enqueue(); // repõe uma peça gerada
                } else {
                    printf("\n⚠️  Não foi possível reservar.\n");
                }
                break;
            }

            case 3: {
                // Usar peça reservada
                if (topo >= 0) {
                    pop();
                    enqueue(); // nova peça entra na fila
                } else {
                    printf("\n⚠️  Nenhuma peça na reserva.\n");
                }
                break;
            }

            case 0:
                printf("\nEncerrando jogo...\n");
                break;

            default:
                printf("\n⚠️  Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
