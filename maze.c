#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 30
#define FREE_SPACE 0
#define WALL 1
#define CORNER 2
#define VISITED 3
#define MOUSE 4

typedef struct {
    int row;
    int col;
} Position;


typedef struct Node {
    Position pos;
    struct Node* next;
} Node;

void push(Node** top, Position pos){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        exit(1);
    }
    newNode->pos = pos;
    newNode->next = *top; //points to the old top
    *top = newNode; //is new top
}

Position pop(Node** top) { //like a retrocess, returns last step but removes from the top of stack
    if ( top == NULL || *top == NULL){
        exit(1);
    }
    Node* temp = *top;
    Position newTop = temp->pos;
    *top = temp->next; //top pointer down
    free(temp);
    return newTop;
}

Position search(Node* top){
    return top->pos;
}

int is_empty(Node* top){
    if (top == NULL){ return 1; }
    return 0;
}

void clear_stack(Node** top){
    while(!is_empty(*top)){
        pop(top);
    }
}

void print_maze(Node* top, int maze[SIZE][SIZE]){
    system("cls");
    Position mouse_pos = search(top);

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            unsigned char fillable = 32; //default as white space (ASCII 32)
            if (i == mouse_pos.row && j == mouse_pos.col) {
                fillable = 2; // Mouse symbol
            } else {
                switch ( maze[i][j]) {
                    case WALL:
                        fillable = 219; //solid block
                        break;
                    case CORNER:
                        fillable = 46;  //dot
                        break;
                    case VISITED:
                        fillable = 176; //dotted block
                        break;
                    default:
                        fillable = 32;  //free space
                        break;
                }
            }
            printf("%c", fillable);
        }
        printf("\n");
    }
}

int main() {
    int maze[SIZE][SIZE];
    int i, j;
    Node* top = NULL;

    srand(time(NULL));

    //GERAÇÃO DO LABIRINTO
    for (i = 0; i < SIZE; i++){
        for (j = 0 ; j < SIZE; j++ ){
            if(j == 0 || j == (SIZE - 1) || i == 0 || i == (SIZE - 1)) {
                maze[i][j] = WALL;
            } else if (j == 2 && i == 2){
                maze[i][j] = FREE_SPACE; // Deixamos livre na matriz, o print_maze cuida de desenhar o rato
            } else {
                maze[i][j] = rand() % 3;
            }
        }
    }

    Position initial_pos = {2,2};
    push(&top,initial_pos); //start stack as initial position of the mouse

    maze[SIZE - 2][SIZE - 1] = FREE_SPACE; //saída

    // algoritmo de busca por saída
    while(!is_empty(top)){
        print_maze(top, maze);
        printf("\n");
        Position current_pos = search(top);

        if (current_pos.row == SIZE - 2 && current_pos.col == SIZE - 1){
            printf("O rato achou a saida na posicao linha: %d, coluna: %d  !!", current_pos.row, current_pos.col);
            break;
        }

        int moved = 0;
        Position next_pos;

        //vetores de posição direita, baixo, esquerda, cima
        int direction_row[] = {0, 1, 0, -1};
        int direction_col[] = {1, 0, -1, 0};

        for ( int direction = 0; direction < 4; direction++){
            //moves
            int row = current_pos.row + direction_row[direction];
            int col = current_pos.col + direction_col[direction];

            //dentro dos limites
            if ( (row > 0 && row < SIZE) && (col > 0 && col < SIZE)){
                //se achar um espaço em branco ou beco move para lá
                if ( (maze[row][col] == FREE_SPACE) || ( maze[row][col] == CORNER )  ){
                    next_pos.row = row;
                    next_pos.col = col;
                    moved = 1;
                    break; // sai da escolha de direção
                }
            }
        }

        maze[current_pos.row][current_pos.col] = VISITED; //local passado marcado como visitado

        if (moved) {
            push(&top, next_pos); //avança passo
        } else {
            //entrou num lugar sem saida, vai ter que retroceder e tomar outra decisão
            pop(&top);

            if (is_empty(top)){
                printf("Rato ficou sem saidas");
                break;
            }
        }

    }

    clear_stack(&top); //limpa pilha concluindo ou não o labirinto
    return 0;
}