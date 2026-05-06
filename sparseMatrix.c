#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//based on a linear list
typedef struct linearlist
{
    int data;
    int line, col;
    struct linearlist *next;
} Node;

Node * create_node (){
    Node *p;
    p = (Node*)malloc(sizeof(Node));
    if(!p){
        printf("Problema em alocar memória");
        exit(0);
    }
    return p;
}

void insert_node (Node** list, int data, int line, int col) {
    Node* item = create_node();
    item->data = data;
    item->line = line;
    item->col = col;
    item->next = NULL;

    // list is empty or the new node comes before the current head
    if (*list == NULL) {
        item->next = *list;
        *list = item;
        return;
    }

    //ordernar pela menor linhas e dps pela coluna da linha
    Node *aux = *list;

    while (aux->next != NULL){
        //greater than the line
        if (aux->next->line > line){
            break;
        }

        //if the next node is greater than the col we are in
        if (aux->next->line == line && aux->next->col > col){
            break;
        }

        aux = aux->next;
    }
    item->next = aux->next;
    aux->next = item;
}

void show(Node** list, int lines, int cols){
    int current_line, current_col;
    Node *aux = *list;
    for (current_line = 0; current_line < lines; current_line++){
        printf("[ ");

        int line_items[cols];
        memset(line_items, 0, sizeof(line_items)); //fullfill with zeros all the cols values by default

        while (aux != NULL && aux->line == current_line) {
            //overwrite the 0 for the actual value on the col
            line_items[aux->col] = aux->data;
            aux = aux->next;
        }

        for(current_col = 0; current_col < cols; current_col++) {
            printf("%d ", line_items[current_col]);
            if (current_col < cols - 1) {
                printf(", ");
            }
        }
        printf(" ]\n");
    }
}

void insert_sequentially(Node** list, int lines, int cols) {
    int data;
    for(int i = 1; i <= lines; i++){
        for(int j = 1; j <= cols; j++){
            printf("Valor para linha %d e coluna %d: \n", i, j);
            scanf("%d", &data);
            if (data != 0) {
                insert_node(list, data, i - 1, j - 1);
            }
        }
    }
}


void search_data(Node** list, int data){
    Node *aux = *list;
    int found = 0;
    while (aux != NULL ){
        if (aux->data == data){
            found = 1;
            break;
        }
        aux = aux->next;
    }

    if (found != 1){
        printf("Dado nao encontrado na matriz!");
        return;
    }

    printf("Valor (%d) encontrado na linha: %d e coluna: %d", aux->data, aux->line, aux->col);
}

void sum_matrixes(Node** first_list, Node** second_list, int lines, int cols){
    int current_line, current_col;
    Node *aux_first = *first_list;
    Node *aux_second = *second_list;

    printf("Resultado da soma das matrizes:\n");

    for (current_line = 0; current_line < lines; current_line ++){
        int first_list_items[cols];
        int second_list_items[cols];
        memset(first_list_items, 0, sizeof(first_list_items));
        memset(second_list_items, 0, sizeof(second_list_items));

        while (aux_first != NULL && aux_first->line == current_line){
            first_list_items[aux_first->col] = aux_first->data;
            aux_first = aux_first->next;
        }

        while (aux_second != NULL && aux_second->line == current_line){
            second_list_items[aux_second->col] = aux_second->data;
            aux_second = aux_second->next;
        }

        printf("[ ");
        for( current_col = 0; current_col < cols; current_col++){
            int sum = first_list_items[current_col] + second_list_items[current_col];
            printf("%d ", sum);
            if (current_col < cols - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

}

void subtract_matrixes(Node** first_list, Node** second_list, int lines, int cols){
    int current_line, current_col;
    Node *aux_first = *first_list;
    Node *aux_second = *second_list;

    printf("Resultado da subtracao das matrizes:\n");
    for (current_line = 0; current_line < lines; current_line++){
        int first_list_items[cols];
        int second_list_items[cols];

        memset(first_list_items, 0, sizeof(first_list_items));
        memset(second_list_items, 0, sizeof(second_list_items));

        while (aux_first != NULL && aux_first->line == current_line){
            first_list_items[aux_first->col] = aux_first->data;
            aux_first = aux_first->next;
        }

        while (aux_second != NULL && aux_second->line == current_line){
            second_list_items[aux_second->col] = aux_second->data;
            aux_second = aux_second->next;
        }

        printf("[ ");
        for ( current_col = 0; current_col < cols; current_col++)
        {
            int sub = first_list_items[current_col] - second_list_items[current_col];
            printf("%d",sub);
            if (current_col < cols - 1){
                printf(", ");
            }
        }
        printf(" ]\n");
    }
}

void multiply_matrixes(Node** first_list, Node** second_list, int lines, int cols){
    Node *aux_first = *first_list;

    int current_line, current_col;
    printf("Resultado da multiplicacao das matrizes:\n");

    for (current_line = 0; current_line < lines; current_line++){
        int first_list_line[cols];
        memset(first_list_line, 0, sizeof(first_list_line));

        //first matriz line
        while (aux_first != NULL && aux_first->line == current_line){
            first_list_line[aux_first->col] = aux_first->data;
            aux_first = aux_first->next;
        }

        printf("[ ");
        //second matrix for each column
        for (current_col = 0; current_col < cols; current_col ++){
            Node *aux_second = *second_list; // restart pointer for every column

            int second_list_col[lines];
            memset(second_list_col, 0, sizeof(second_list_col));

            while(aux_second != NULL){
                if (aux_second->col == current_col){
                    second_list_col[aux_second->line] = aux_second->data;
                }
                aux_second = aux_second->next;
            }

            int sum = 0;
            //iterate through the line multiplying the value from the col from the second matrix and summing the total
            for (int i = 0; i < cols; i++){
                sum += first_list_line[i] * second_list_col[i];
            }

            printf("%d", sum);
            if (current_col < cols - 1){
                printf(", ");
            }

        }
        printf(" ]\n");
    }
}

// Shows the main diagonal including zeros
// Iterates from 0 to min(lines, cols) — for each index i, searches for a node
// where line == i && col == i. If not found in the list, it's a stored zero.
void show_main_diagonal(Node** list, int lines, int cols) {
    int size = lines < cols ? lines : cols;

    printf("Diagonal principal:\n[ ");
    for (int i = 0; i < size; i++) {
        int found = 0;
        Node *aux = *list;

        while (aux != NULL) {
            // only non-zero values are stored, so finding the node means it's non-zero
            if (aux->line == i && aux->col == i) {
                printf("%d", aux->data);
                found = 1;
                break;
            }
            aux = aux->next;
        }

        // not in the list = was zero (sparse matrix only stores non-zeros)
        if (!found) printf("0");
        if (i < size - 1) printf(", ");
    }
    printf(" ]\n");
}

// Generates and displays the transposed matrix
// Transpose: rows <-> cols. To build row i of the transposed matrix,
// we look for nodes where col == i (they were in column i of the original),
// and place their data at position [line] in the new row.
void generate_transpose(Node** list, int lines, int cols) {
    Node *transposed = NULL;
    Node *aux = *list;

    // swap line <-> col for each node when inserting into the new list
    while (aux != NULL) {
        insert_node(&transposed, aux->data, aux->col, aux->line);
        aux = aux->next;
    }

   
    printf("Matriz transposta (%dx%d):\n", cols, lines);
    show(&transposed, cols, lines);

    free_list(&transposed);
}

void free_list(Node** list){
    Node *aux, *previous;
    aux = *list;

    while (aux != NULL){
        previous = aux;
        aux = previous->next;
        free(previous);
    }
}

int main () {
    int lines,cols,action, data_line, data_col, data;
    Node *list, *second_list;
    list = NULL;
    second_list = NULL;
    action = 0;

    printf("informe a dimensao da matriz:\n");
    printf("--------------------------------------------\n");
    printf("linhas: \n");
    scanf("%d",&lines);

    printf("colunas: \n");
    scanf("%d",&cols);

    while (action != 9){
        printf("\n--------------------------------------------\n");
        printf("\nAcoes possiveis:\n");
        printf("1) Inserir dado\n");
        printf("2) Busca dado\n");
        printf("3) Soma matrizes\n");
        printf("4) Subtrai matrizes\n");
        printf("5) Multiplica matrizes\n");
        printf("6) Mostra Matriz\n");
        printf("7) Gerar matriz transposta\n");
        printf("8) Mostra Diagonal Principal (incluindo 0s)\n");
        printf("9) Encerrar\n");
        printf("--------------------------------------------\n");

        printf("Insira a acao a ser realizada:\n");
        scanf("%d", &action);

        switch (action)
        {
            case 1:
                printf("Insira dados sequenciais:\n");
                insert_sequentially(&list, lines, cols);
                break;
            case 2:
                printf("Insira o valor para busca\n");
                scanf("%d", &data);
                search_data(&list, data);
                break;
            case 3:
                if (second_list == NULL){
                    printf("Inicialize uma segunda matriz para realizar a soma:\n");
                    insert_sequentially(&second_list, lines, cols);
                }
                sum_matrixes(&list, &second_list, lines, cols);
                break;
            case 4:
                if (second_list == NULL){
                    printf("Inicialize uma segunda matriz para realizar a subtracao:\n");
                    insert_sequentially(&second_list, lines, cols);
                }
                subtract_matrixes(&list,&second_list,lines,cols);
                break;
            case 5:
                if (second_list == NULL){
                    printf("Inicialize uma segunda matriz para realizar a multiplicacao:\n");
                    insert_sequentially(&second_list, lines, cols);
                }
                multiply_matrixes(&list, &second_list, lines, cols);
                break;
            case 6:
                show(&list, lines, cols);
                break;
            case 7:
                generate_transpose(&list, lines, cols);
                break;
            case 8:
                show_main_diagonal(&list, lines, cols);
                break;
            case 9:
                free_list(&list);
                free_list(&second_list);
                return 0;
            default:
                break;
        }
    }

    return 0;
}
