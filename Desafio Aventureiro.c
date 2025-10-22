#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3
#define NUM_TIPOS_PECAS 4

typedef struct {
    char nome;  
    int id;     
} Peca;

typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int tamanho;
} FilaPecas;

typedef struct {
    Peca pecas[TAMANHO_PILHA];
    int topo;
    int tamanho;
} PilhaReserva;

void inicializarFila(FilaPecas *fila);
void inicializarPilha(PilhaReserva *pilha);
int filaVazia(FilaPecas *fila);
int filaCheia(FilaPecas *fila);
int pilhaVazia(PilhaReserva *pilha);
int pilhaCheia(PilhaReserva *pilha);
void enqueue(FilaPecas *fila, Peca peca);
Peca dequeue(FilaPecas *fila);
void push(PilhaReserva *pilha, Peca peca);
Peca pop(PilhaReserva *pilha);
Peca gerarPeca(int *contador_id);
void exibirEstado(FilaPecas *fila, PilhaReserva *pilha);
void exibirMenu();

int main() {
    FilaPecas fila;
    PilhaReserva pilha;
    int opcao;
    int contador_id = 0; 
    
    srand(time(NULL));
    
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    printf("=== Tetris Stack - Gerenciamento de Pecas ===\n");
    printf("Fila: %d peças | Pilha de Reserva: %d peças\n\n", TAMANHO_FILA, TAMANHO_PILHA);
    
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca(&contador_id);
        enqueue(&fila, novaPeca);
    }
    
    do {
        exibirEstado(&fila, &pilha);
        
        exibirMenu();
        
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: 
                if (!filaVazia(&fila)) {
                    Peca pecaRemovida = dequeue(&fila);
                    printf("\n>>> Peça jogada: [%c %d]\n", pecaRemovida.nome, pecaRemovida.id);
                    
                    Peca novaPeca = gerarPeca(&contador_id);
                    enqueue(&fila, novaPeca);
                    printf(">>> Nova peça adicionada à fila: [%c %d]\n", novaPeca.nome, novaPeca.id);
                } else {
                    printf("\n>>> Erro: Fila vazia! Nenhuma peça para jogar.\n");
                }
                break;
                
            case 2: 
                if (!filaVazia(&fila)) {
                    if (!pilhaCheia(&pilha)) {
                        Peca pecaReservada = dequeue(&fila);
                        push(&pilha, pecaReservada);
                        printf("\n>>> Peça reservada: [%c %d]\n", pecaReservada.nome, pecaReservada.id);
                        
                        Peca novaPeca = gerarPeca(&contador_id);
                        enqueue(&fila, novaPeca);
                        printf(">>> Nova peça adicionada à fila: [%c %d]\n", novaPeca.nome, novaPeca.id);
                    } else {
                        printf("\n>>> Erro: Pilha de reserva cheia! Não é possível reservar mais peças.\n");
                    }
                } else {
                    printf("\n>>> Erro: Fila vazia! Nenhuma peça para reservar.\n");
                }
                break;
                
            case 3:
                if (!pilhaVazia(&pilha)) {
                    Peca pecaUsada = pop(&pilha);
                    printf("\n>>> Peça reservada usada: [%c %d]\n", pecaUsada.nome, pecaUsada.id);
                } else {
                    printf("\n>>> Erro: Pilha de reserva vazia! Nenhuma peça para usar.\n");
                }
                break;
                
            case 0: 
                printf("\n>>> Obrigado por jogar Tetris Stack! Saindo...\n");
                break;
                
            default:
                printf("\n>>> Opção inválida! Por favor, escolha 0, 1, 2 ou 3.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar(); 
            getchar(); 
        }
        
    } while (opcao != 0);
    
    return 0;
}

void inicializarFila(FilaPecas *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

void inicializarPilha(PilhaReserva *pilha) {
    pilha->topo = -1;
    pilha->tamanho = 0;
}

int filaVazia(FilaPecas *fila) {
    return fila->tamanho == 0;
}

int filaCheia(FilaPecas *fila) {
    return fila->tamanho == TAMANHO_FILA;
}

int pilhaVazia(PilhaReserva *pilha) {
    return pilha->tamanho == 0;
}

int pilhaCheia(PilhaReserva *pilha) {
    return pilha->tamanho == TAMANHO_PILHA;
}

void enqueue(FilaPecas *fila, Peca peca) {
    if (!filaCheia(fila)) {
        fila->tras = (fila->tras + 1) % TAMANHO_FILA;
        fila->pecas[fila->tras] = peca;
        fila->tamanho++;
    }
}

Peca dequeue(FilaPecas *fila) {
    Peca pecaRemovida;
    
    if (!filaVazia(fila)) {
        pecaRemovida = fila->pecas[fila->frente];
        fila->frente = (fila->frente + 1) % TAMANHO_FILA;
        fila->tamanho--;
    }
    
    return pecaRemovida;
}

void push(PilhaReserva *pilha, Peca peca) {
    if (!pilhaCheia(pilha)) {
        pilha->topo++;
        pilha->pecas[pilha->topo] = peca;
        pilha->tamanho++;
    }
}

Peca pop(PilhaReserva *pilha) {
    Peca pecaRemovida;
    
    if (!pilhaVazia(pilha)) {
        pecaRemovida = pilha->pecas[pilha->topo];
        pilha->topo--;
        pilha->tamanho--;
    }
    
    return pecaRemovida;
}

Peca gerarPeca(int *contador_id) {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};

    int indiceTipo = rand() % NUM_TIPOS_PECAS;
    novaPeca.nome = tipos[indiceTipo];
    
    novaPeca.id = *contador_id;
    (*contador_id)++;
    
    return novaPeca;
}

void exibirEstado(FilaPecas *fila, PilhaReserva *pilha) {
    printf("\n=== ESTADO ATUAL ===\n");
    
    printf("Fila de peças:\t\t");
    if (filaVazia(fila)) {
        printf("Vazia");
    } else {
        int indice = fila->frente;
        for (int i = 0; i < fila->tamanho; i++) {
            printf("[%c %d] ", fila->pecas[indice].nome, fila->pecas[indice].id);
            indice = (indice + 1) % TAMANHO_FILA;
        }
    }
    printf("\n");
    
    printf("Pilha de reserva\t(Topo -> Base): ");
    if (pilhaVazia(pilha)) {
        printf("Vazia");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->pecas[i].nome, pilha->pecas[i].id);
        }
    }
    printf("\n");
}

void exibirMenu() {
    printf("\n=== OPCOES DE ACAO ===\n");
    printf("1 - Jogar peça (remover da fila)\n");
    printf("2 - Reservar peça (mover da fila para a pilha)\n");
    printf("3 - Usar peça reservada (remover da pilha)\n");
    printf("0 - Sair\n");
}