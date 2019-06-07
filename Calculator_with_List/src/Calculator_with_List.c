/*
 ============================================================================
 Name        : Queue.c
 Author      : AndrewVorotyntsev
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Задаем функцию факториал
float factorial(float n)
{
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

/* Определяем элемент очереди */
typedef struct list_node {
    struct list_node *next;
    int type;
    int oper;
    float *A;
    float *B;
} list_node_t;

/* Определяем саму очередь */
typedef struct list {

    int size;
    /* начало списка */
    list_node_t *head;
    /* конец списка */
    list_node_t *tail;
} list_t;

/* Инициализация массива */
list_t * create_list(void)
{
    list_t *lt = malloc(sizeof(list_t));

    lt->size = 0;
    lt->head = NULL;
    lt->tail = lt->head;

    return lt;
}


//функция заполнения данными элементов списка
void list_push_back(list_t *lt, int type, int oper,float *A,float *B)
{
    list_node_t * node = malloc(sizeof(list_node_t));
    node->type=type;
    node->oper=oper;
    node->A=A;
    node->B=B;
    if(lt->tail != NULL)
        lt->tail->next = node;
    else {
        lt->head = node;
    }

    lt->tail = node;
    lt->size += 1;
}



void * list_pop(list_t *lt)
{
    if(lt->size == 0){
        /* Список пуст */
        return NULL;
    }

    list_node_t *node = lt->head;


    lt->size -= 1;
    //lt->head = node->next;

    free(node);

    if(lt->size == 0){
        /* Это был последний элемент */
        lt->head = NULL;
        lt->tail = NULL;
    }

    //return lt->head;
    lt->head = node->next;
    return lt->head;
}

//struct element* getElement();

//Список результатов
typedef struct nodeResult
{
  float C; // значения
  struct nodeResult *next; // указатель на следующий элемент
}nodeResult;


typedef struct listResult
{
    nodeResult* head;
    nodeResult* tail;
}listResult;




listResult * initializelistResult(void)
{
    listResult* lt = malloc(sizeof(list_t));
    lt->head = NULL;
    lt->tail = lt->head;

    return lt;
}

void putResult(listResult* lst ,float C)
{
    nodeResult* t = (nodeResult*) malloc(sizeof(nodeResult));
    t->C=C;
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


void printResult(const listResult* const lst)
{
    FILE *result ;
    result = fopen("Result.txt" , "w");
    float p;
    for(nodeResult* tmp = lst->head; tmp; tmp = tmp->next){
        p = tmp->C;
        fprintf(result,"%f\n",p);
    }
}


int main(void) {
    //Инициализируем список для данных , открываем файл с данными
    list_t *list = create_list();
    FILE *write ;
    write = fopen("Data.txt", "r");
    int t,o,r,k;
    float *A,*B,e,*C;
    r = 1;
    k = 0;
    //Заполняем узлы списка данными
    while(r == 1)
    {
        fscanf(write ,"%i" , &t);
        A = malloc(t*sizeof(float));
        B = malloc(t*sizeof(float));
        fscanf(write ,"%i" , &o);
        for (int y=0;y<t;y++){
            fscanf(write,"%f", &A[y]);
        }
        for (int l=0;l<t;l++){
            fscanf(write,"%f", &B[l]);
        //if ((t == 1) || ((t > 1) && (o != 2)))
        //    k = k + t;
        }
        if (t == 1)
            k = k + 1;
        if (t > 1)
        {
            if (o != 2)
                k = k + t;
            if (o == 2)
                k = k + 1;
        }
        fscanf(write ,"%i" , &r);
        list_push_back(list,t,o,A,B);
    }
    fclose(write);
    C = malloc(k*sizeof(float));
    int j;
    j = 0;
    //Производим вычисления , проходя через все элементы списка
    for(list_node_t* node = list->head; node; node = node->next)
    {
        if (node->type==1)
        {
            switch (node->oper)
            {
                case 0:
                    C[j] = node->A[0]+node->B[0];
                    j = j + 1;
                    break;
                case 1:
                    C[j] = node->A[0]-node->B[0];
                    j = j + 1;
                    break ;
                case 2:
                    C[j] = node->A[0]*node->B[0];
                    j = j + 1;
                    break ;
                case 3:
                    C[j] = node->A[0]/node->B[0];
                    j = j + 1;
                    break;
                case 4:
                    C[j] = pow(node->A[0],node->B[0]);
                    j = j + 1;
                    break;
                case 5:
                    C[j] = factorial(node->A[0]);
                    j = j + 1;
                    break;
            }
        }
        else
        {
            switch (node->oper)
                {
                case 0:
                    for (int h=0;h<node->type;h++)
                    {
                        C[j] = node->A[h]+node->B[h];
                        j = j + 1;
                    }
                    break;
                case 1:
                    for (int u=0;u<node->type;u++)
                    {
                        C[j] = node->A[u]-node->B[u];
                        j = j + 1;
                    }
                    break;
                case 2:
                    e=0;
                    for (int s=0;s<node->type;s++)
                    {
                        float d;
                        d=node->A[s]*node->B[s];
                        e=e+d;
                    }
                    C[j] = e;
                    j = j + 1;
                    break;
                }
        }
    if (j == k)
        break;
    }
    //Открываем лист результатов и вводим туда данные ,затем печатаем в файл
    listResult *answer = initializelistResult();
    for (int w=0;w<j;w++)
    {
        putResult(answer ,C[w]);
    }
    printResult(answer);
    puts("That's all!");
}


