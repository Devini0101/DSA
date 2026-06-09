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

typedef struct Node {
    int pos_int;
    struct Node* next;
} Node;

void push(Node** top, int row, int col){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        exit(1);
    }
    newNode->pos_int = (row * 100) + col; // if row is 2 and col is 3, pos_int will be 203
    newNode->next = *top; //points to the old top
    *top = newNode; //is new top
}

int pop(Node** top) { //like a retrocess, returns last step but removes from the top of stack
    if ( top == NULL || *top == NULL){
        exit(1);
    }
    Node* temp = *top;
    int newTop = temp->pos_int;
    *top = temp->next; //top pointer down
    free(temp);
    return newTop;
}

int search(Node* top){
    return top->pos_int;
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
    int mouse_pos = search(top);

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            unsigned char fillable = 32; //default as white space (ASCII 32)
            if (i == mouse_pos/100 && j == mouse_pos%100) {
                fillable = 2; // Mouse symbol
            } else {
                switch ( maze[i][j]) {
                    case WALL:
                        fillable = 219; //solid block
                        break;
                    case CORNER:
                        fillable = 176;  //dotted block
                        break;
                    case VISITED:
                        fillable = 46; //dot
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

    //Maze generation
    for (i = 0; i < SIZE; i++){
        for (j = 0 ; j < SIZE; j++ ){
            if(j == 0 || j == (SIZE - 1) || i == 0 || i == (SIZE - 1)) {
                maze[i][j] = WALL; //external walls
            } else if (j == 2 && i == 2){
                maze[i][j] = FREE_SPACE; //mouse pos
            } else {
                maze[i][j] = (rand() % 3 == 0) ? WALL : FREE_SPACE; //1 in 3 possibilities will be wall
            }
        }
    }

    int initial_pos = (2 * 100) + 2;
    push(&top, 2, 2); //start stack as initial position of the mouse

    maze[SIZE - 2][SIZE - 1] = FREE_SPACE; // exit of maze

    //algorithm for the exit
    while(!is_empty(top)){
        print_maze(top, maze);
        printf("\n");
        int current_pos = search(top);
        int current_row = current_pos / 100;
        int current_col = current_pos % 100;

        if (current_row == SIZE - 2 && current_col == SIZE - 1){
            printf("O rato achou a saida na posicao linha: %d, coluna: %d  !!", current_row, current_col);
            break;
        }

        int moved = 0;
        int next_pos;
        int next_row, next_col;

        //vectors of position right, down, left, up
        int direction_row[] = {0, 1, 0, -1};
        int direction_col[] = {1, 0, -1, 0};

        for ( int direction = 0; direction < 4; direction++){
            //moves
            int row = current_row + direction_row[direction];
            int col = current_col + direction_col[direction];

            //inside of walls
            if ( (row > 0 && row < SIZE) && (col > 0 && col < SIZE)){
                if ( (maze[row][col] == FREE_SPACE) ){
                    next_pos = (row * 100) + col;
                    next_row = row;
                    next_col = col;
                    moved = 1;
                    break; // sai da escolha de direção
                }
            }
        }

        if (moved) {
            maze[current_row][current_col] = VISITED; //where was is VISITED
            push(&top, next_row, next_col); //next step
        } else {
            //no exit, CORNER and traceback on stack
            maze[current_row][current_col] = CORNER;
            pop(&top);

            if (is_empty(top)){
                printf("Rato ficou sem saidas");
                break;
            }
        }

    }

    clear_stack(&top); //clear stack
    return 0;
}