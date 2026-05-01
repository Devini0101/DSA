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
    if (*list == NULL || (*list)->line > line || ((*list)->line == line && (*list)->col > col)) {
        item->next = *list;
        *list = item;
        return;
    }

    //ordernar pela menor linhas e dps pela coluna da linha
    Node *aux = *list;

    while (aux->next != NULL && aux->next->line <= line && aux->next->col <= col){
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
        printf("Dado não encontrado na matriz!");
        return;
    }

    printf("Valor (%d) encontrado na linha: %d e coluna: %d", aux->data, aux->line, aux->col);
}

void show(Node** list, int lines, int cols){
    int current_line, current_col;

    for (current_line = 0; current_line < lines; current_line++){
        printf("[ ");

        int line_items[cols];
        memset(line_items, 0, sizeof(line_items)); //fullfill with zeros all the cols values by default

        Node *aux = *list;
        while (aux != NULL) {
            if (aux->line == current_line){
                line_items[aux->col] = aux->data;
            }
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

void free_list(Node** list){

}

int main () {
    int lines,cols,action, data_line, data_col, data;
    Node *list;
    action = 0;

    printf("informe a dimensao da matriz\n");
    printf("linhas: \n");
    scanf("%d",&lines);

    printf("colunas: \n");
    scanf("%d",&cols);

    while (1 == 1) {
        printf("\n--------------------------------------------\n");
        printf("\nAcoes possiveis:\n");
        printf("1) Inserir dado\n");
        printf("2) Busca dado\n");
        printf("3) Ler dados sequenciais (vai inserindo e eu deixo na ordem, inserir tambem 0)\n");
        printf("4) Soma matrizes\n");
        printf("5) Subtrai matrizes\n");
        printf("6) Multiplica matrizes\n");
        printf("7) Gerar matriz transposta\n");
        printf("8) Mostra Matriz (incluindo 0)\n");
        printf("9) Mostra Diagonal Principal (incluindo 0)\n");
        printf("10) Encerrar\n");

        printf("Insira a ação a ser realizada:\n");
        scanf("%d", &action);

        switch (action)
        {
        case 1:
            printf("Insira o valor para insercao:\n");
            scanf("%d", &data);
            printf("Insira a linha:\n");
            scanf("%d", &data_line);
            printf("Insira a coluna:\n");
            scanf("%d", &data_col);
            insert_node(&list, data, data_line, data_col);
            break;
        case 8:
            show(&list, lines, cols);
            break;
        case 9:
            return 0;
            break;
        default:
            break;
        }
    }

    free(list);

    return 0;
}