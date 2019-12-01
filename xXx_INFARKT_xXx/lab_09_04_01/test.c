#include "headers/math.h"
#include "headers/includes.h"
#include "headers/matrix_routines.h"
#include <time.h>

int main(void)
{
    matrix_t A, B, C;
    matrix_t A1, B1, C1;
    matrix_t A2, B2, C2;
    int ro = 2, gm = 3;
    int ro1 = 1, gm1 = 5;
    int ro2 = 0, gm2 = 1;

    initMatrix(&A, 5, 3);
    initMatrix(&B, 3, 5);

    initMatrix(&A1, 6, 7);
    initMatrix(&B1, 7, 6);

    initMatrix(&A2, 4, 10);
    initMatrix(&B2, 10, 4);

    srand((unsigned)time(NULL));

    for(int i = 0; i < A.strings; i++)
        for(int j = 0; j < A.columns; j++)
            A.dataP[i][j] = rand() % 2 + i;

    for(int i = 0; i < B.strings; i++)
        for(int j = 0; j < B.columns; j++)
            B.dataP[i][j] = rand() % 2 + i;


    for(int i = 0; i < A1.strings; i++)
        for(int j = 0; j < A1.columns; j++)
            A1.dataP[i][j] = rand() % 2 + i;

    for(int i = 0; i < B1.strings; i++)
        for(int j = 0; j < B1.columns; j++)
            B1.dataP[i][j] = rand() % 2 + i;


    for(int i = 0; i < A2.strings; i++)
        for(int j = 0; j < A2.columns; j++)
            A2.dataP[i][j] = rand() % 2 + i;

    for(int i = 0; i < B2.strings; i++)
        for(int j = 0; j < B2.columns; j++)
            B2.dataP[i][j] = rand() % 2 + i;

    create1stMatrix(&A);
    create1stMatrix(&A1);
    create1stMatrix(&A2);
    create1stMatrix(&B);
    create1stMatrix(&B1);
    create1stMatrix(&B2);

    create2ndMatrix(&A, &B);
    create2ndMatrix(&A1, &B1);
    create2ndMatrix(&A2, &B2);

    create3rdMatrix(&A, &B, &C, ro, gm);
    create3rdMatrix(&A1, &B1, &C1, ro1, gm1);
    create3rdMatrix(&A2, &B2, &C2, ro2, gm2);

    addColumn(&A);
    addColumn(&A1);
    addColumn(&A2);
    deleteColumn(&A);
    deleteColumn(&A1);
    deleteColumn(&A2);
    addString(&A);
    addString(&A1);
    addString(&A2);
    deleteString(&A);
    deleteString(&A1);
    deleteString(&A2);

    addColumn(&B);
    addColumn(&B1);
    addColumn(&B2);
    deleteColumn(&B);
    deleteColumn(&B1);
    deleteColumn(&B2);
    addString(&B);
    addString(&B1);
    addString(&B2);
    deleteString(&B);
    deleteString(&B1);
    deleteString(&B2);

    addColumn(&C);
    addColumn(&C1);
    addColumn(&C2);
    deleteColumn(&C);
    deleteColumn(&C1);
    deleteColumn(&C2);
    addString(&C);
    addString(&C1);
    addString(&C2);
    deleteString(&C);
    deleteString(&C1);
    deleteString(&C2);


    matrixOutput(A);
    matrixOutput(B);
    matrixOutput(C);

    matrixOutput(A1);
    matrixOutput(B1);
    matrixOutput(C1);

    matrixOutput(A1);
    matrixOutput(B1);
    matrixOutput(C1);

    destMatrix(&A);
    destMatrix(&A1);
    destMatrix(&A2);
    destMatrix(&B);
    destMatrix(&B1);
    destMatrix(&B2);
    destMatrix(&C);
    destMatrix(&C1);
    destMatrix(&C2);

    return EXIT_SUCCESS;
}
// 2 3 4 7 1 3 2 7 5 3 0 2 9 1 2 2 3 3 3 8 8 2 1 8 3 2 3
// ColumnsA StringsA
// (ColumnsA*StringsA number of values)
// ColumnsB StringsB
// (ColumnsB*StringsB number of values)
// ro value
// gamma value
