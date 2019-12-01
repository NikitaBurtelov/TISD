#include "headers/includes.h"
#include "headers/types.h"
#include "headers/matrix_routines.h"
#include "headers/math.h"

int main()
{
    matrix_t A, B, C;
    int ro, gm;

    if(matrixInput(&A))
        return EXIT_FAILURE;

    if(matrixInput(&B))
    {
        destMatrix(&A);
        return EXIT_FAILURE;
    }

    if(scanf("%d", &ro) != 1 || ro < 0)
    {
        destMatrix(&A);
        destMatrix(&B);
        return EXIT_FAILURE;
    }

    if(scanf("%d", &gm) != 1 || gm < 0)
    {
        destMatrix(&A);
        destMatrix(&B);
        return EXIT_FAILURE;
    }

    create1stMatrix(&A);
    create1stMatrix(&B);

    create2ndMatrix(&A, &B);

    create3rdMatrix(&A, &B, &C, ro, gm);

    matrixOutput(C);

    destMatrix(&C);
    destMatrix(&A);
    destMatrix(&B);
    return 0;
}
