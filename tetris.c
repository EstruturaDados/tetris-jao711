//NIVEL NOVATO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Definições e Estruturas ---

// Define o tamanho máximo da fila de peças.
#define TAMANHO_FILA 5

/**
 * @struct Peca
 * @brief Representa uma única peça do jogo Tetris.
 *
 * Cada peça tem um tipo (nome) e um identificador único (id).
 */
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

/**
 * @struct Fila
 * @brief Estrutura de dados para uma fila circular de peças.
 *
 * Gerencia um array de peças, controlando o início, o fim e o número
 * de elementos presentes.
 */
typedef struct {
    Peca itens[TAMANHO_FILA]; // Array que armazena as peças
    int inicio;               // Índice do primeiro elemento da fila
    int fim;                  // Índice do último elemento da fila
    int contador;             // Número de elementos na fila
} Fila;

// --- Protótipos das Funções ---

void inicializarFila(Fila *f);
int estaCheia(Fila *f);
int estaVazia(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
Peca gerarPeca();
void exibirFila(Fila *f);
void exibirMenu();

// --- Função Principal (main) ---

int main() {
    Fila filaDePecas;
    int opcao;

    // Inicializa o gerador de números aleatórios para criar peças variadas.
    srand(time(NULL));

    // Prepara a fila para ser utilizada.
    inicializarFila(&filaDePecas);

    // Preenche a fila inicial com o número definido de peças.
    printf("Inicializando o jogo com %d pecas...\n", TAMANHO_FILA);
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(&filaDePecas, gerarPeca());
    }

    // Loop principal do jogo, continua até o jogador escolher a opção 0.
    do {
        exibirFila(&filaDePecas);
        exibirMenu();
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Jogar peça (dequeue)
                if (!estaVazia(&filaDePecas)) {
                    Peca pecaJogada = dequeue(&filaDePecas);
                    printf("\n>> Peca '%c' (ID: %d) foi jogada.\n", pecaJogada.nome, pecaJogada.id);
                } else {
                    printf("\n>> A fila de pecas esta vazia! Nao e possivel jogar.\n");
                }
                break;
            case 2: // Inserir nova peça (enqueue)
                if (!estaCheia(&filaDePecas)) {
                    Peca novaPeca = gerarPeca();
                    enqueue(&filaDePecas, novaPeca);
                    printf("\n>> Nova peca '%c' (ID: %d) inserida no final da fila.\n", novaPeca.nome, novaPeca.id);
                } else {
                    printf("\n>> A fila de pecas esta cheia! Jogue uma peca para adicionar outra.\n");
                }
                break;
            case 0: // Sair
                printf("\nSaindo do Tetris Stack. Ate a proxima!\n");
                break;
            default:
                printf("\n>> Opcao invalida! Tente novamente.\n");
                // Limpa o buffer de entrada para evitar loops infinitos caso o usuário digite um caractere.
                while (getchar() != '\n');
                break;
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Gera uma nova peça com ID único e tipo aleatório.
 * @return A nova peça criada.
 */
Peca gerarPeca() {
    static int proximoId = 0; // Contador estático para garantir um ID único sequencial.
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indiceTipo = rand() % 4; // Gera um índice aleatório de 0 a 3.

    novaPeca.nome = tipos[indiceTipo];
    novaPeca.id = proximoId++;
    return novaPeca;
}

/**
 * @brief Inicializa uma fila, definindo seus valores padrão.
 * @param f Ponteiro para a fila a ser inicializada.
 */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->contador = 0;
}

/**
 * @brief Verifica se a fila está cheia.
 * @param f Ponteiro para a fila.
 * @return 1 se a fila está cheia, 0 caso contrário.
 */
int estaCheia(Fila *f) { return f->contador == TAMANHO_FILA; }

/**
 * @brief Verifica se a fila está vazia.
 * @param f Ponteiro para a fila.
 * @return 1 se a fila está vazia, 0 caso contrário.
 */
int estaVazia(Fila *f) { return f->contador == 0; }

/**
 * @brief Adiciona uma peça ao final da fila (enqueue).
 * @param f Ponteiro para a fila.
 * @param p A peça a ser adicionada.
 */
void enqueue(Fila *f, Peca p) {
    if (!estaCheia(f)) {
        f->fim = (f->fim + 1) % TAMANHO_FILA; // Avança o 'fim' de forma circular.
        f->itens[f->fim] = p;
        f->contador++;
    }
}

/**
 * @brief Remove e retorna a peça do início da fila (dequeue).
 * @param f Ponteiro para a fila.
 * @return A peça removida.
 */
Peca dequeue(Fila *f) {
    Peca p = { ' ', -1 }; // Peça padrão para retorno em caso de fila vazia.
    if (!estaVazia(f)) {
        p = f->itens[f->inicio];
        f->inicio = (f->inicio + 1) % TAMANHO_FILA; // Avança o 'início' de forma circular.
        f->contador--;
    }
    return p;
}

/**
 * @brief Exibe o estado atual da fila de peças.
 * @param f Ponteiro para a fila.
 */
void exibirFila(Fila *f) {
    printf("\n\nConfira a seguir seu estado:\n\n");
    printf("Fila de pecas\n");
    if (estaVazia(f)) {
        printf("[Fila vazia]\n");
    } else {
        int i = f->inicio;
        for (int c = 0; c < f->contador; c++) {
            printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
            i = (i + 1) % TAMANHO_FILA;
        }
        printf("\n");
    }
    printf("Tabela: Visualizacao a fila de pecas.\n");
    printf("Curadoria de TI.\n");
}

/**
 * @brief Exibe o menu de ações disponíveis para o jogador.
 */
void exibirMenu() {
    printf("\nOpcoes de acao:\n\n");
    printf("Codigo\tAcao\n");
    printf("1\tJogar peca \n");
    printf("2\tInserir nova peca\n");
    printf("0\tSair\n");
    printf("Tabela: Comandos disponiveis para manipular a fila de pecas.\n");
    
}

