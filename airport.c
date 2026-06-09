#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Plane {
    char name[50];
    int id;
    char from[50];
    char to[50];
    int passengers;
    struct Plane *next;
} Plane;

typedef struct Queue {
    Plane *start;
    Plane *end;
    int size;
} Queue;


void start_queue( Queue *queue) {
    queue->start = NULL;
    queue->end = NULL;
    queue->size = 0;
}

Plane* create_plane (int id) {
    Plane *p = (Plane *)malloc(sizeof(Plane));

    if (p == NULL) {
        return NULL;
    }
    p->id = id;
    printf("Informe o nome do aviao (Nao deve conter espacos):");
    scanf("%s",p->name);

    printf("\nOrigem: ");
    scanf("%s", p->from);

    printf("\nDestino:");
    scanf("%s", p->to);

    while (strcmp(p->to, p->from) == 0) {
        printf("O destino deve ser diferente da origem\n");
        printf("Informe o destino: ");
        scanf("%s", p->to);
    }

    printf("\nQtde de Passageiros: ");
    scanf("%d", &p->passengers);

    while (p->passengers < 1) {
        printf("O aviao deve ter no minimo 1 passageiro\n");
        printf("Informe a quantidade de passageiros: ");
        scanf("%d", &p->passengers);
    }

    p->next = NULL;
    return p;
}

void enqueue (Queue *queue, Plane *pl) {
    if (pl == NULL) {
        return;
    }
    if (queue->start == NULL) {
        queue->start = pl;
        queue->end = pl;
    } else {
        queue->end->next = pl;
        queue->end = pl;
    }
    queue->size++;
}

void dequeue (Queue *queue) {
    if (queue->start == NULL){
        printf("A fila esta vazia\n");
        return;
    }

    Plane *to_remove = queue->start;
    queue->start = to_remove->next;
    //was last node
    if (queue->start == NULL) {
        queue->end = NULL;
    }

    printf("\nAviao %s de ID: %d com destino a: %s autorizado\n", to_remove->name, to_remove->id, to_remove->to);
    free(to_remove);
    queue->size--;
}

void list_queue (Queue *queue) {
    if (queue->start == NULL) {
        printf("A fila esta vazia\n");
        return;
    }

    Plane *temp = queue->start;

    while ( temp != NULL) {
        printf("\n----------------------------------------------------------------------------\n");
        printf(" ID: %d  -  Nome: '%s' -  Destino: %s  -  Origem: %s - Qtde passageiros: %d\n",temp->id, temp->name, temp->to, temp->from, temp->passengers);
        temp = temp->next;
    }
}

void first_plane (Queue *queue) {
    if (queue->start == NULL) {
        printf("A fila esta vazia\n");
        return;
    }

    Plane *temp = queue->start;
    printf("\n----------------------------------------------------------------------------\n");
    printf(" ID: %d  -  Nome: '%s' -  Destino: %s  -  Origem: %s - Qtde passageiros: %d\n",temp->id, temp->name, temp->to, temp->from, temp->passengers);
}

void free_queue (Queue *queue) {
    if (queue->start != NULL) {
        Plane *node = queue->start;
        while (node != NULL){
            Plane *temp = node;
            node = node->next;
            free(temp);
        }
    }
}

int main () {
    Queue takeoff, landing;
    start_queue(&takeoff);
    start_queue(&landing);

    int id_takeoff_planes = 1;
    int id_landing_planes = 1;
    int option;

    do {
        printf("\n=== CONTROLE DE AEROPORTO ===\n");
        printf("1. Adicionar aviao decolagem\n");
        printf("2. Adicionar aviao pouso\n");
        printf("3. Listar decolagem\n");
        printf("4. Listar pouso\n");
        printf("5. Num avioes decolagem\n");
        printf("6. Num avioes pouso\n");
        printf("7. Autorizar decolagem\n");
        printf("8. Autorizar pouso\n");
        printf("9. Ver primeiro decolagem\n");
        printf("10. Ver primeiro pouso\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option){

        case 0 :
            break;
        case 1:{
            Plane* new_takeoff = create_plane(id_takeoff_planes++);
            enqueue(&takeoff, new_takeoff);
            break;
        }
        case 2:{
            Plane* new_landing = create_plane(id_landing_planes++);
            enqueue(&landing, new_landing);
            break;
        }
        case 3:{
            list_queue(&takeoff);
            break;
        }
        case 4:{
            list_queue(&landing);
            break;
        }
        case 5:{
            if (takeoff.size == 0) {
                printf("A fila de decolagem esta vazia\n");
            } else {
                printf("A fila de decolagem tem %d avioes aguardando autorizacao\n", takeoff.size);
            }
            break;
        }
        case 6:{
            if (landing.size == 0) {
                printf("A fila de pouso esta vazia\n");
            } else {
                printf("A fila de pouso tem %d avioes aguardando autorizacao\n", landing.size);
            }
            break;
        }
        case 7:{
            dequeue(&takeoff);
            break;
        }
        case 8:{
            dequeue(&landing);
            break;
        }
        case 9:{
            first_plane(&takeoff);
            break;
        }
        case 10:{
            first_plane(&landing);
            break;
        }
        }

    } while (option != 0);

    free_queue(&takeoff);
    free_queue(&landing);
    printf("Saindo.");
    return 0;
}