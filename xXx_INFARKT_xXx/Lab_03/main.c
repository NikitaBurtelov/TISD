#include "typesRoutines.h"

// для работы с данным представлением матрицы нужно релизовать две подпрограммы:
//  1) получение адреса значения или значения элемента матрицы из упакованного представления по двум индексам (строка, столбец)
//  2) для записи значения элемента матрицы в его упакованном представлении по двум индексам

intMatrix_t* genMatrix(int dencity, int strings, int colums)
{
    if(dencity < 0 || dencity > 100)
        return NULL;

    int elemNumber = (((strings * colums * dencity)) / 100);

    intMatrix_t *res = malloc(sizeof (intMatrix_t));
    res->columns = colums;
    res->strings = strings;
    initMatrix(res);

    srand((unsigned)time(NULL));

    for(int i = 0; i < strings; i++)
        for(int j = 0; j < colums; j++)
            res->data[i][j] = 0;

    while(elemNumber > 0)
    {
        int string = rand() % strings, colum = rand() % colums;
        if(res->data[string][colum] == 0)
        {
            res->data[string][colum] = rand() % 9 + 1;
            elemNumber--;
        }
    }
    return res;
}
int main()
{

    int choose;
    printf("1 - Standart\n"
           "2 - 1x1000 on 1000x1000 with dencity\n"
           "choose:");
    if(scanf("%d", &choose) != 1)
    {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }

    switch (choose) {

    case 2:
    {
        packedMatrix_t pMtxL, pMtxR, *resPMtx;
        intMatrix_t *mtxL, *mtxR, *resMtx;
        time_t simpleMul = 0, packedMul = 0, start = 0, end = 0;
        unsigned long dencity;

        unsigned long a = 1,b = 1000, c = 1000;
        printf("Input dencity in percents:");
        if(scanf("%d", (unsigned*)&dencity) != 1)
        {
            printf("Wrong input!\n");
            return EXIT_FAILURE;
        }
        if(dencity < 1 || dencity > 100)
        {
            printf("Wrong value of dencity!\n");
            return EXIT_FAILURE;
        }
        mtxL = genMatrix((int)dencity, (int)a, (int)b);
        formPackedMatrix(&pMtxL, mtxL);
        mtxR = genMatrix((int)dencity, (int)b, (int)c);
        formPackedMatrix(&pMtxR, mtxR);

        // замер времени для перемножения обыкновенных матриц
        start = end = 0;
        start = clock();
        resMtx = mulMatrix(mtxL, mtxR);
        end = clock();
        simpleMul = end - start;

        printf("\nSimple matrix:\n");
        printf("\n");
        printf("TIME = %lf\n", (((double)simpleMul)/CLOCKS_PER_SEC));
        unsigned long memL = a*b*sizeof (int) + sizeof (int*)*a + sizeof (intMatrix_t);
        unsigned long memR = b*c*sizeof (int) + sizeof (int*)*b + sizeof (intMatrix_t);
        unsigned long memRes = a*c*sizeof (int) + sizeof (int*)*a + sizeof (intMatrix_t);
        printf("Memory = %lu\n", memL+memR+memRes);

        // замер времени для перемножения упакованных матриц
        start = clock();
        resPMtx = mulPackedMtxOnPackedMtx1(&pMtxL, &pMtxR);
        end = clock();
        packedMul = end - start;

        printf("\nPacked matrix:\n");
        printf("\n");
        double time = (((double)packedMul)/CLOCKS_PER_SEC);
        printf("TIME = %lf\n", time);
        //unsigned long memLp = (sizeof (int) * (unsigned long)pMtxL.A.size * 2 + sizeof (node_t) * (unsigned long)pMtxL.IA.len + sizeof (packedMatrix_t));
        //unsigned long memRp = (sizeof (int) * (unsigned long)pMtxL.A.size * 2 + sizeof (node_t) * (unsigned long)pMtxR.IA.len + sizeof (packedMatrix_t));
        //unsigned long memResp = (sizeof (int) * (unsigned long)resPMtx->A.size * 2 + sizeof (node_t) * (unsigned long)resPMtx->IA.len + sizeof (packedMatrix_t));
        //unsigned long memResp = (sizeof (int) )
        //printf("Memory = %lu\n", memLp*memRp+memResp);

        destMatrix(&(mtxL->data), mtxL->strings);
        destPackedMatrix(&pMtxL);
        destMatrix(&(mtxR->data), mtxR->strings);
        destPackedMatrix(&pMtxR);
        destPackedMatrix(resPMtx);
        destMatrix(&(resMtx->data), resMtx->strings);
        free(resMtx);
        free(resPMtx);
        break;
    }
    case 1:
    {
        packedMatrix_t pMtxL, pMtxR, *resPMtx;
        intMatrix_t mtxL, mtxR, *resMtx;
        time_t simpleMul = 0, packedMul = 0, start = 0, end = 0;

        mtxL.strings = 1;
        printf("Input Number of columns!\n");
        if(scanf("%d", &mtxL.columns) != 1)
        {
            printf("Wrong input!\n");
            exit(1);
        }

        if(mtxL.strings < 1 || mtxL.columns < 1)
        {
            printf("Wrong number of columns!\n");
            exit(1);
        }
        initMatrix(&mtxL);

        printf("Input elements of matrix\n");
        for(int i = 0; i < mtxL.strings; i++)
            for(int j = 0; j < mtxL.columns; j++)
                if(scanf("%d", &(mtxL.data[i][j])) != 1)
                {
                    printf("Wrong Elements input!\n");
                    exit(1);
                }


        formPackedMatrix(&pMtxL, &mtxL);

        printf("Input Number of strings & columns!\n");
        if(scanf("%d %d", &mtxR.strings, &mtxR.columns) != 2)
        {
            printf("Wrong input!\n");
            exit(1);
        }

        if(mtxR.strings != mtxL.columns)
        {
            printf("Number of columns of left matrix doesn't equal to number of strings of right matrix! Multiplication is impossible!\n");
            return EXIT_FAILURE;
        }
        if(mtxR.strings < 1 || mtxR.columns < 1)
        {
            printf("Wrong number of strings or columns!\n");
            exit(1);
        }
        initMatrix(&mtxR);

        printf("Input elements of matrix\n");
        for(int i = 0; i < mtxR.strings; i++)
            for(int j = 0; j < mtxR.columns; j++)
                if(scanf("%d", &(mtxR.data[i][j])) != 1)
                {
                    printf("Wrong elements input!\n");
                    exit(1);
                }
        formPackedMatrix(&pMtxR, &mtxR);

        // замер времени для перемножения обыкновенных матриц
        start = end = 0;
        start = clock();
        resMtx = mulMatrix(&mtxL, &mtxR);
        end = clock();
        simpleMul = end - start;

        // замер времени для перемножения упакованных матриц
        start = clock();
        resPMtx = mulPackedMtxOnPackedMtx1(&pMtxL, &pMtxR);
        end = clock();
        packedMul = end - start;

        printf("\nSimple matrix:\n");
        intMatrixOutput(resMtx);
        printf("\n");
        printf("TIME = %lf\n", (((double)simpleMul)/CLOCKS_PER_SEC));

        printf("\nPacked matrix:\n");
        printPackedMtx(resPMtx);

        printPackedMtxf(*resPMtx);
        printf("\n");
        printf("TIME = %lf\n", (((double)packedMul)/CLOCKS_PER_SEC));

        destMatrix(&(mtxL.data), mtxL.strings);
        destPackedMatrix(&pMtxL);
        destMatrix(&(mtxR.data), mtxR.strings);
        destPackedMatrix(&pMtxR);
        destPackedMatrix(resPMtx);
        destMatrix(&(resMtx->data), resMtx->strings);
        free(resMtx);
        free(resPMtx);
    }
        break;
    default:
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
/*

1 1 1 1 1

1 3
1 1 1
3 3
-1 0 -1
0 0 -1
0 1 0


1 1
1 1 1 1 1

5 5
1 0 0 4 0
0 0 0 0 0
2 6 9 0 5
5 7 0 0 0
0 0 0 0 8

5 100 (500)
1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0
5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0
0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8
1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0 2 6 9 0 0
5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0 5 7 0 0 0
0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8 0 0 0 0 8

1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0 1 0 0 4 0
*/
