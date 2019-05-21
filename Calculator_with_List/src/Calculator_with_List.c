/*
 ============================================================================
 Name        : Simple_List.c
 Author      : Andrew Vorotyntsev
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>

float factorial(float n)
{
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

struct node {
    int type;
    int oper;
    float *A;
    float *B;
    int v;
    struct node *next;
};

typedef struct node Node;

struct list
{
    Node* head;
    Node* tail;
};

typedef struct list List;



void initializeList(List* lst)
{
    lst->head = 0;
    lst->tail = 0;
}

void filling(List* lst,int type, int oper,float *A,float *B, int v)
{
    Node* t = (Node*) malloc(sizeof(Node));
    t->type = type;
    t->oper = oper;
    t->A=A;
    t->B=B;
    t->v=v;
    t->next = 0;
    if(lst->head == 0)
    {
       lst->head = t;
       lst->tail = t;
       return;
    }
    lst->tail->next = t;
    lst->tail = t;
}

void calculate(const List* const lst)
{
    FILE *result ;
    result = fopen("Result.txt" , "w");
    float *A,*B,e,d;
    for(Node* tmp = lst->head; tmp; tmp = tmp->next)
        {
        if (tmp->type==1)
        {

        switch (tmp->oper)
            {
                case 0:
                    fprintf(result,"_%f", tmp->A[0]+tmp->B[0]);
                    break;
                case 1:
                    fprintf(result,"_%f", tmp->A[0]-tmp->B[0]);
                    break ;
                case 2:
                    fprintf(result,"_%f", tmp->A[0]*tmp->B[0]);
                    break ;
                case 3:
                    fprintf(result,"_%f", tmp->A[0]/tmp->B[0]);
                   break;
                case 4:
                    fprintf(result,"_%f", pow (tmp->A[0], tmp->B[0]));
                    break;
                case 5:
                    fprintf(result,"_%f", factorial(tmp->A[0]));
                    break;
            }
        }
        else
            {
            switch (tmp->oper)
                    {
                    case 0:
                        for (int h=0;h<tmp->type;h++){
                            fprintf(result,"_%f" , tmp->A[h]+tmp->B[h]);
                        }
                            break;
                    case 1:
                        for (int j=0;j<tmp->type;j++)
                        {
                            fprintf(result,"_%f" ,tmp->A[j]-tmp->B[j]);
                        }   break ;
                    case 2:
                        e=0;
                        for (int s=0;s<tmp->type;s++)
                        {
                            d=tmp->A[s]*tmp->B[s];
                            e=e+d;
                        }
                        fprintf(result,"_%f", e);
                        break;
                    }
            }


                }
}

int main(void) {
    List lst;
    initializeList(&lst);
    FILE *write ;
    write = fopen("Data.txt", "r");
    int t,o,r;
    float *A,*B;
    r = 1;
    while(r == 1){
    if (A != NULL) A = malloc(t*sizeof(float));
    if (B != NULL) B = malloc(t*sizeof(float));
    fscanf(write ,"%i" , &t);
    fscanf(write ,"%i" , &o);
    for (int k=0;k<t;k++)
            fscanf(write,"%f", &A[k]);
    for (int l=0;l<t;l++)
            fscanf(write,"%f", &B[l]);
    fscanf(write ,"%i" , &r);
    filling(&lst,t,o,A,B,r);
    }
    calculate(&lst);
    printf("That's all!");
}
