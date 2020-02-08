#ifndef TYPESROUTINES_H
#define TYPESROUTINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <time.h>

#define LIST_UNDERFLOW -101
#define LIST_OVERFLOW -102
#define ALLOC_ERROR -103
#define OUT_OF_BOUNDS -104


// узел
typedef struct node_t
{
    struct node_t* prev;
    struct node_t* next;
    int A;
    int JA;
    int index;
} node_t;

// Двусвязный список
typedef struct list_t
{
    node_t* head;
    node_t* tail;
    int len;
}list_t;

// динамическая матрица целых чисел
typedef struct
{
    int** data;            // указатель на первую строку матрицы
    int columns;           // количество столбцов
    int strings;           // количество строк
} intMatrix_t;

// динамический массив целых чисел
typedef struct
{
    int size;  // размер массива
    int* data;      // указатель на первый элемент массива
} intVector_t;

// представление разряженной матрицы
typedef struct
{
    int maxColumn;           // количество столбцов в матрице
    intVector_t A;           // вектор A содержит значения ненулевых элементов;
    intVector_t JA;          // вектор JA содержит номера столбцов для элементов вектора A;
    list_t IA;               // связный список IA, в элементе Nk которого находится номер компонент в A и JA, с которых начинается описание строки Nk матрицы A.
} packedMatrix_t;



/*              ФУНКЦИИ ВЕКТОРА                                            */

int initVector(int** p, int len)
{
    *p = (int *)malloc((unsigned)len * sizeof (int));

    if (!*p)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int destVector(int** p)
{
    if (*p)
    {
        free(*p);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int append(intVector_t* pt, int val)
{
    int* tmp = (int *)realloc(pt->data, sizeof (int) * (unsigned)(pt->size + 1));
    if(!tmp)
        return ALLOC_ERROR;

    pt->size++;
    pt->data = tmp;
    pt->data[pt->size - 1] = val;

    return pt->size - 1;
}

int pop(intVector_t* pt, int* poppedVal)
{
    *poppedVal = pt->data[pt->size - 1];
    int* tmp = (int *)realloc(pt->data, sizeof (int) * (unsigned)(pt->size + 1));
    if(!tmp)
        return ALLOC_ERROR;

    pt->size--;
    pt->data = tmp;

    return EXIT_SUCCESS;
}

int insert(intVector_t* pt, int index, int value)
{
    if(index > pt->size)
        return OUT_OF_BOUNDS;
    else if(index == pt->size)
    {
        append(pt, value);
        return EXIT_SUCCESS;
    }

    pt->size++;
    int* tmp = (int *)realloc(pt->data, sizeof (int) * (unsigned)(pt->size));
    if(!tmp)
        return ALLOC_ERROR;

    pt->data = tmp;

    for(int i = pt->size - 1; i > index; i--)
        pt->data[i] = pt->data[i-1];

    pt->data[index] = value;

    return EXIT_SUCCESS;
}

int delete(intVector_t* pt, int index)
{
    for(int i = index; i < pt->size - 1; i++)
        pt->data[i] = pt->data[i+1];

    int* tmp = (int *)realloc(pt->data, sizeof (int) * (unsigned)(--pt->size));
    if(!tmp)
    {
        if(pt->size == 0)
            pt->data = NULL;
        return ALLOC_ERROR;
    }

    pt->data = tmp;

    return EXIT_SUCCESS;
}



/*               ФУНКЦИИ НЕУПАКОВАННОЙ МАТРИЦЫ                        */

int initMatrix(intMatrix_t *pt)
{
    pt->data = (int **)malloc((unsigned)pt->strings * sizeof (int*));

    if (!pt)
        return EXIT_FAILURE;

    for(int i = 0; i < pt->strings; i++)
    {
        initVector(&(pt->data[i]), (int)pt->columns);
    }
    return EXIT_SUCCESS;
}

int destMatrix(int*** p, int strings)
{
    for(int i = 0; i < strings; i++)
        free((*p)[i]);
    free(*p);
    return EXIT_SUCCESS;
}

int intMatrixInput(intMatrix_t* p)
{
    printf("Input Number of strings & columns!\n");
    if(scanf("%d %d", &p->strings, &p->columns) != 2)
    {
        printf("Wrong Input!\n");
        exit(1);
    }

    if(p->strings < 1 || p->columns < 1)
    {
        printf("Wrong number of strings or columns!\n");
        exit(1);
    }
    initMatrix(p);

    printf("Input elements of matrix\n");
    for(int i = 0; i < p->strings; i++)
        for(int j = 0; j < p->columns; j++)
            if(scanf("%d", &(p->data[i][j])) != 1)
            {
                printf("Wrong Elements input!\n");
                exit(1);
            }

    return EXIT_SUCCESS;
}

void intMatrixOutput(intMatrix_t* p)
{
    for(int i = 0; i < p->strings; i++)
    {
        for(int j = 0; j < p->columns; j++)
            printf("%d ", p->data[i][j]);
        printf("\n");
    }
}

intMatrix_t *mulMatrix(intMatrix_t *left, intMatrix_t *right)
{
    if(left->columns != right->strings)
        return NULL;

    intMatrix_t *res = malloc(sizeof (intMatrix_t));
    res->strings = left->strings;
    res->columns = right->columns;

    res->data = malloc(sizeof (int*) * (unsigned)res->strings);
    for(int i = 0; i < res->strings; i++)
        res->data[i] = malloc(sizeof (int) * (unsigned)res->columns);

    int i,j,k;
    for(i = 0; i < res->strings; i++)
        for(j = 0; j < res->columns; j++)
        {
            res->data[i][j] = 0;
            for(k = 0; k < right->strings; k++)
                res->data[i][j] += left->data[i][k] * right->data[k][j];
        }
    return res;
}



/*              ФУНКЦИИ СПИСКA                                             */

int add(list_t* list, int A, int JA)
{
    if(!list->head)
    {
        node_t *tmp = (node_t*)calloc(sizeof (node_t), sizeof (char));
        if(!tmp)
            return ALLOC_ERROR;

        list->head = tmp;

        list->tail = list->head;
        list->head->next = list->head->prev = NULL;
        list->head->A = A;
        list->head->JA = JA;

        list->len++;
    }
    else
    {
        node_t *tmp = (node_t*)malloc(sizeof (node_t));
        if(!tmp)
            return ALLOC_ERROR;

        list->tail->next = tmp;

        list->tail->next->prev = list->tail;
        list->tail = list->tail->next;
        list->tail->index = 1 + list->tail->prev->index;
        list->tail->A = A;
        list->tail->JA = JA;
        list->tail->next = NULL;

        list->len++;
    }
    return EXIT_SUCCESS;
}

int printList(list_t* list)
{
    node_t* tmp = list->head;
    printf("\n");
    for(int i = 0; i < list->len; i++)
    {
        printf("Index = %d, JA = %d, A = %d\n", tmp->index, tmp->JA, tmp->A);
        if(tmp->next)
            tmp = tmp->next;
        else break;
    }
    return EXIT_SUCCESS;
}

void initList(list_t* list)
{
    list->len = 0;
    list->head = list->tail = NULL;
}

void destList(list_t* list)
{
    node_t* tmp = list->head;
    for(; tmp->next;)
    {
        tmp = tmp->next;
        free(tmp->prev);
    }
    free(tmp);
}



/*                  ФУНКЦИИ УПАКОВАННОЙ МАТРИЦЫ                            */

int formPackedMatrix(packedMatrix_t* packMtx, intMatrix_t* mtx)
{
    packMtx->A.size = packMtx->JA.size = 0;
    packMtx->IA.len = 0;
    packMtx->A.data = packMtx->JA.data = NULL;
    packMtx->IA.head = packMtx->IA.tail = NULL;
    packMtx->maxColumn = mtx->columns;

    int value, string, column, i, j;
    for(i = 0; i < mtx->strings; i++)
    {
        int A = -1, JA = -1;
        for(j = 0; j < mtx->columns; j++)
        {
            value = mtx->data[i][j];
            string = i;
            column = j;
            if(value)
            {
                append(&(packMtx->A), value);
                append(&(packMtx->JA), column);
            }

            if(value && JA < 0)
            {
                A = packMtx->A.size - 1;
                JA = packMtx->JA.size - 1;
            }
        }
        add(&(packMtx->IA), A, JA);
    }

    return packMtx->IA.len;
}

int destPackedMatrix(packedMatrix_t *pMtx)
{
    destList(&(pMtx->IA));
    destVector(&(pMtx->A.data));
    destVector(&(pMtx->JA.data));
    return EXIT_SUCCESS;
}

void printPackedMtx(packedMatrix_t* pt)
{
    printf("\n");
    printf("A arr, size = %d, adress = %p:\n(", pt->A.size, (void*)pt->A.data);
    for(int i = 0; i < pt->A.size; i++)
    {
        if (i == pt->A.size - 1)
            printf("%d", pt->A.data[i]);
        else
            printf("%d;", pt->A.data[i]);
    }
    printf(")\n");

    printf("JA arr, size = %d, adress = %p:\n(", pt->JA.size, (void*)pt->JA.data);
    for(int i = 0; i < pt->JA.size; i++)
    {
        if (i == pt->JA.size - 1)
            printf("%d", pt->JA.data[i]);
        else
            printf("%d;", pt->JA.data[i]);
    }
    printf(")");
    printList(&(pt->IA));
    printf("\n");
}


int takeElem(const packedMatrix_t* pMtx, const int str, const int col, int *elem)
{
    node_t* currstr = pMtx->IA.head;

    if(str >= pMtx->IA.len || str < 0 || col < 0 || col >= pMtx->maxColumn)
        return OUT_OF_BOUNDS;

    while(currstr->index != str)
        currstr = currstr->next;

    if(currstr->A < 0)
        *elem = 0;
    else if(!currstr->next)
    {
        for(int i = currstr->JA; i < pMtx->JA.size; i++)
            if(pMtx->JA.data[i] == col)
            {
                *elem = pMtx->A.data[i];
                return EXIT_SUCCESS;
            }
        *elem = 0;
    }
    else
    {
        node_t* nextstr = currstr->next;
        int i = currstr->A, tmp = nextstr->A;
        while(nextstr->A < 0)
        {
            if(!nextstr->next)
            {
                tmp = pMtx->JA.size;
                break;
            }
            nextstr = nextstr->next;
            tmp = nextstr->A;
        }

        for(; i < tmp; i++)
            if(pMtx->JA.data[i] == col)
            {
                *elem = pMtx->A.data[i];
                return EXIT_SUCCESS;
            }
        *elem = 0;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

void printPackedMtxf(packedMatrix_t mtx)
{
    for(int i = 0; i < mtx.IA.len; i++)
    {
        for(int j = 0; j < mtx.maxColumn; j++)
        {
            int elem;
            takeElem(&mtx, i, j, &elem);
            printf("%d ", elem);
        }
        printf("\n");
    }
}

int peekString(packedMatrix_t mtx, int index)
{
    if(index < 0 || index > mtx.A.size)
        return -1;

    node_t *curr = mtx.IA.head, *next = curr->next;
    for(int i = 0; i < mtx.IA.len; i++)
    {
        if(i < mtx.IA.len - 1)
        {
            while(next->A <= -1)
                next = next->next;
            if(index >= curr->A && index < next->A)
                return curr->index;
            else
            {
                curr = curr->next;
                next = curr->next;
            }
        }
        else
            return curr->index;
    }
    return -2;
}

// ищет начало и конец i-ой строки матрицы в массиве A и возвращает индекс с которого начинается строка в массиве A и записывает индекс последнего элемента в last, -1;-2 если строка пуста
int findString(const packedMatrix_t *mtx, const int index, int *last)
{
    node_t *curr = mtx->IA.head;
    for(int i = 0; i < mtx->IA.len; i++)
        if(i != index) // ищем узел строки index
            curr = curr->next;
        else // если нашли
        {
            node_t *beginNode = curr;
            if(curr->A == -1) // он равен -1 => строка пуста
            {
                *last = -2;
                return -1;
            }

            curr = curr->next;
            if(!curr) // обработка последней строки: если следующего элемента нет, то последним элементом будет элемент с индеком длина массива - 1
            {
                *last = mtx->A.size - 1;
                return beginNode->A;
            }

            while(curr) // иначе ищем первый узел, который указывает на не пустую строку
            {
                if(curr->A != -1) // если нашли
                {
                    *last = curr->A - 1;
                    return beginNode->A;
                }
                curr = curr->next; // иначе идем вперед
            }

            // мы дошли до конца списка, значит текущая строка послдняя значащая
            *last = mtx->A.size - 1;
            return beginNode->A;

        }

    *last = -2; // прошли через весь массив, входные данные некорректны
    return -1;
}

packedMatrix_t *mulPackedMtxOnPackedMtx1(const packedMatrix_t *left, const packedMatrix_t *right)
{
    if(left->maxColumn != right->IA.len)
        return NULL;

    intVector_t *vec = malloc(sizeof (intVector_t));
    vec->size = right->maxColumn;
    vec->data = (int*)calloc(sizeof(int) * vec->size, sizeof (char));

    for(int i = 0; i < left->A.size; i++) // проходим по всем значениям левой матрицы
    {
        int last, first = findString(right, left->JA.data[i], &last); // находим, где начинается и заканчивается строка с индексом столбца i-го элемента левой матрицы правой матрицы
        for(int k = first; k <= last; k++) // проходим по всем элементам правой матрицы в строке с индексом столбца элемента массива A левой матрицы
        {
            int rightC = right->JA.data[k]; // индекс столбца элемента правой матрицы
            int rightV = right->A.data[k]; // значение элемента правой матрицы
            int leftV = left->A.data[i]; // значение элемента левой матрицы

            vec->data[rightC] += leftV * rightV;
        }
    }

    int **a = &(vec->data);
    intMatrix_t res1 = {a, vec->size, 1};
    packedMatrix_t *res = calloc(sizeof (packedMatrix_t), sizeof (char));
    formPackedMatrix(res, &res1);
    return res;
}
#endif // TYPESROUTINES_H
