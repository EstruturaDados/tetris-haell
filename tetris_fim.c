#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ---------------------------------------
//  STRUCT PEÇA
// ---------------------------------------
typedef struct {
    char nome;
    int id;
} Peca;

// ---------------------------------------
//  VARIÁVEIS GLOBAIS
// ---------------------------------------
Peca fila[TAM_FILA];
int frente = 0, tras = 0, qtdFila = 0;

Peca pilha[TAM_PILHA];
int topo = -1;

int ultimoID = 0;

// ---------------------------------------
//  GERA NOVA PEÇA ALEATÓRIA
// ---------------------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = ultimoID++;
    return p;
}

// ---------------------------------------
//  ENQUEUE (INSERIR NA FILA CIRCULAR)
// ---------------------------------------
void enqueue() {
    if (qtdFila == TAM_FILA) {
        printf("\n[FILA CHEIA - Isto não deveria ocorrer!]\n");
        return;
    }

    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAM_FILA;
    qtdFila++;
}

// ---------------------------------------
//  DEQUEUE (REMOVER DA FILA CIRCULAR)
// ---------------------------------------
Peca dequeue() {
    Peca vazia = {'?', -1};

    if (qtdFila == 0) {
        printf("\n⚠️  Fila vazia! Nada a remover.\n");
        return vazia;
    }

    Peca p = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    qtdFila--;

    return p;
}

// ---------------------------------------
//  PUSH NA PILHA
// ---------------------------------------
void push(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("\n⚠️  Pilha cheia! Não é possível reservar.\n");
        return;
    }

    pilha[++topo] = p;
}

// ---------------------------------------
//  POP DA PILHA
// ---------------------------------------
Peca pop() {
    Peca vazia = {'?', -1};

    if (topo == -1) {
        printf("\n⚠️  Pilha vazia! Nada a usar.\n");
        return vazia;
    }

    return pilha[topo--];
}

// ---------------------------------------
//  TROCA PEÇA FRENTE DA FILA ↔ TOPO DA PILHA
// ---------------------------------------
void trocaUnica() {
    if (qtdFila == 0) {
        printf("\n⚠️  A fila está vazia, não há peça para trocar.\n");
        return;
    }
    if (topo == -1) {
        printf("\n⚠️  A pilha está vazia, não há peça para trocar.\n");
        return;
    }

    Peca temp = fila[frente];
    fila[frente] = pilha[topo];
    pilha[topo] = temp;

    printf("\n🔄 Troca individual realizada!\n");
}

// ---------------------------------------
//  TROCA MÚLTIPLA ENTRE FILA (3 PEÇAS) E PILHA (3 PEÇAS)
// ---------------------------------------
void trocaMultipla() {
    if (qtdFila < 3) {
        printf("\n⚠️  A fila não possui 3 peças para troca.\n");
        return;
    }
    if (topo < 2) {
        printf("\n⚠️  A pilha não possui 3 peças para troca.\n");
        return;
    }

    int idx = frente;

    // Troca as 3 primeiras da fila com as 3 da pilha
    for (int i = 0; i < 3; i++) {
        Peca temp = fila[idx];
        fila[idx] = pilha[topo - i];
        pilha[topo - i] = temp;
        idx = (idx + 1) % TAM_FILA;
    }

    printf("\n🔁 Troca múltipla realizada entre fila e pilha!\n");
}

// ---------------------------------------
//  EXIBIR ESTADO DO SISTEMA
// ---------------------------------------
void exibirEstado() {
    printf("\n=========================================\n");
    printf("         ESTADO ATUAL DO SISTEMA\n");
    printf("=========================================\n");

    printf("Fila de peças: ");
    if (qtdFila == 0) {
        printf("(vazia)");
    } else {
        int i = frente;
        for (int c = 0; c < qtdFila; c++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }

    printf("\nPilha de reserva (Topo → Base): ");
    if (topo == -1) {
        printf("(vazia)");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n=========================================\n");
}

// ---------------------------------------
//  MENU
// ---------------------------------------
void menu() {
    printf("\nAções disponíveis:\n");
    printf("1 - Jogar peça da frente da fila\n");
    printf("2 - Enviar peça da fila para a pilha de reserva\n");
    printf("3 - Usar peça da pilha de reserva\n");
    printf("4 - Trocar peça da fila com o topo da pilha\n");
    printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// ---------------------------------------
//  MAIN
// ---------------------------------------
int main() {
    srand(time(NULL));

    // Inicializa a fila completamente
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
                    enqueue();  // mantém fila cheia
                }
                break;
            }

            case 2: {
                // Reservar peça
                if (topo >= TAM_PILHA - 1) {
                    printf("\n⚠️  Pilha cheia! Não é possível reservar.\n");
                    break;
                }

                Peca p = dequeue();
                if (p.id != -1) {
                    push(p);
                    printf("\nPeça reservada: [%c %d]\n", p.nome, p.id);
                    enqueue();
                }
                break;
            }

            case 3: {
                // Usar peça reservada
                Peca usada = pop();
                if (usada.id != -1) {
                    printf("\nPeça usada da reserva: [%c %d]\n", usada.nome, usada.id);
                    enqueue();
                }
                break;
            }

            case 4:
                trocaUnica();
                break;

            case 5:
                trocaMultipla();
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\n⚠️  Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
