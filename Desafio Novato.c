#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
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
    int contador_id; 
} FilaPecas;

void inicializarFila(FilaPecas *fila);
int filaVazia(FilaPecas *fila);
int filaCheia(FilaPecas *fila);
void enqueue(FilaPecas *fila, Peca peca);
Peca dequeue(FilaPecas *fila);
Peca gerarPeca(FilaPecas *fila);
void exibirFila(FilaPecas *fila);
void exibirMenu();

int main() {
    FilaPecas fila;
    int opcao;
    
    srand(time(NULL));
    
    inicializarFila(&fila);
    
    printf("=== Tetris Stack - Fila de Pecas Futuras ===\n\n");
    
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca(&fila);
        enqueue(&fila, novaPeca);
    }
    
    do {
        printf("\nEstado atual da fila:\n");
        exibirFila(&fila);
        
        exibirMenu();
        
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca pecaRemovida = dequeue(&fila);
                    printf("\n>>> Peça jogada: [%c %d]\n", pecaRemovida.nome, pecaRemovida.id);
                    
                    if (!filaCheia(&fila)) {
                        Peca novaPeca = gerarPeca(&fila);
                        enqueue(&fila, novaPeca);
                        printf(">>> Nova peça adicionada: [%c %d]\n", novaPeca.nome, novaPeca.id);
                    }
                } else {
                    printf("\n>>> Erro: Fila vazia! Nenhuma peça para jogar.\n");
                }
                break;
                
            case 2:
                if (!filaCheia(&fila)) {
                    Peca novaPeca = gerarPeca(&fila);
                    enqueue(&fila, novaPeca);
                    printf("\n>>> Nova peça adicionada: [%c %d]\n", novaPeca.nome, novaPeca.id);
                } else {
                    printf("\n>>> Erro: Fila cheia! Não é possível adicionar mais peças.\n");
                }
                break;
                
            case 0: 
                printf("\n>>> Obrigado por jogar Tetris Stack! Saindo...\n");
                break;
                
            default:
                printf("\n>>> Opção inválida! Por favor, escolha 0, 1 ou 2.\n");
                break;
        }
        
    } while (opcao != 0);
    
    return 0;
}

void inicializarFila(FilaPecas *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
    fila->contador_id = 0;
}

 */
int filaVazia(FilaPecas *fila) {
    return fila->tamanho == 0;
}

 */
int filaCheia(FilaPecas *fila) {
    return fila->tamanho == TAMANHO_FILA;
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

Peca gerarPeca(FilaPecas *fila) {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};

    int indiceTipo = rand() % NUM_TIPOS_PECAS;
    novaPeca.nome = tipos[indiceTipo];

    novaPeca.id = fila->contador_id;
    fila->contador_id++;
    
    return novaPeca;
}

void exibirFila(FilaPecas *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("Fila de peças: ");
    
    int indice = fila->frente;
    for (int i = 0; i < fila->tamanho; i++) {
        printf("[%c %d] ", fila->pecas[indice].nome, fila->pecas[indice].id);
        indice = (indice + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

void exibirMenu() {
    printf("\n=== Opcoes de Acao ===\n");
    printf("1 - Jogar peça (dequeue)\n");
    printf("2 - Inserir nova peça (enqueue)\n");
    printf("0 - Sair\n");
}