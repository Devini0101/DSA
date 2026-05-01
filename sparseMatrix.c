#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//based on a linear list
typedef struct linearlist
{
    int data;
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




int main () {
    return 0;
}