#include "C:\Users\user\CLionProjects\C_Folder\lab_08\headers\h_array.h"
#include "C:\Users\user\CLionProjects\C_Folder\lab_08\headers\h_includ.h"
#include "C:\Users\user\CLionProjects\C_Folder\lab_08\headers\h_math.h"

#define EPS 1e-10

int test_array_insert()
{
    array_type array;
    short int test_save = 0;
    int len = 2, pos;
    double m2;

    array = (array_type)malloc(len * sizeof(double));

    //Test 1
    pos = 1;
    m2 = -94.558900;

    *array = -199.2478;
    *(array + 1) = 10.13;

    if (array_insert(array, &len, m2, pos) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (*array == -94.558900 && *(array + 1) == -199.247800 &&
            *(array + 2) == -94.558900 && *(array + 3) == 10.130000 && *(array + 4) == -94.558900)
            test_save++;
    }

    //Test 2
    pos = 1;
    m2 = 1068.606500;

    *array = 2451.213;
    *(array + 1) = -314;

    if (array_insert(array, &len, m2, pos) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (*array == 1068.606500 && *(array + 1) == 2451.213000 &&
            *(array + 2) == 1068.606500 && *(array + 3) == -314.000000 && *(array + 4) == 1068.606500)
            test_save++;
    }

    return test_save;
}

int test_m_average_one()
{
    array_type array;
    double m1, m1_test;
    short int test_save = 0;
    int len = 3;

    array = (array_type)malloc(len * sizeof(double));

    //Test 1
    m1 = 0;
    m1_test = 2.571429;

    *array = 1;
    *(array + 1) = 2;
    *(array + 2) = 3;

    if (m_average_one(array, &m1, len) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (m1 == m1_test)
            test_save++;
    }

    //Test 2
    m1 = 0;
    m1_test = 1218.744350;

    *array = 17768.2421;
    *(array + 1) = -199.2478;
    *(array + 2) = 10.13;

    if (m_average_one(array, &m1, len) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (m1 == m1_test)
            test_save++;
    }


    //Test 3
    m1 = 0;
    m1_test = -103719.138571;

    *array = -656.13;
    *(array + 1) = -355146.14;
    *(array + 2) = -3425.25;

    if (m_average_two(array, &m1, len) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (m1 == m1_test)
            test_save++;
    }


    return test_save;
}

int test_m_average_two()
{
    array_type array;
    double m2, m2_test;
    short int test_save = 0;
    int len = 3;

    array = (array_type)malloc(len * sizeof(double));

    //Test 1
    m2 = 0;
    m2_test = -94.558900;

    *array = 17768.2421;
    *(array + 1) = -199.2478;
    *(array + 2) = 10.13;

    if (m_average_two(array, &m2, len) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (m2 == m2_test)
            test_save++;
    }

    //Test 2
    m2 = 0;
    m2_test = 104.500000;

    *array = 17768;
    *(array + 1) = 199;
    *(array + 2) = 10;

    if (m_average_two(array, &m2, len) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (m2 == m2_test)
            test_save++;
    }

    //Test 3
    m2 = 0;
    m2_test = -2040.690000;

    *array = -656.13;
    *(array + 1) = -355146.14;
    *(array + 2) = -3425.25;

    if (m_average_two(array, &m2, len) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (m2 == m2_test)
            test_save++;
    }

    return test_save;
}


// удаляет все элементы массива которые больше mu1
int test_array_del()
{
    array_type array;
    double m1;
    short int test_save = 0;
    int len = 5;

    array = (array_type)malloc(len * sizeof(double));

    //Test 1
    m1 = 4.090909;

    for (int i = 0; i < len; i++)
        *(array + i) = i + 1; //1,2,3,4,5

    if (array_del(&array, &len, m1) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (len == 4)
        {
            if (*array == 1 && *(array + 1) == 2 && *(array + 2) == 3 && *(array + 3) == 4)
                test_save++;
        }
    }

    //Test 2
    m1 = 1.909091;

    for (int i = 0; i < len; i++)
        *(array + i) = 5 - i; //5,4,3,2,1

    if (array_del(&array, &len, m1) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (len == 1)
        {
            if (*array == 1)
                test_save++;
        }
    }

    //Test 3
    m1 = -4.090909;

    for (int i = 0; i < len; i++)
        *(array + i) = -(i + 1); //-1,-2,-3,-4,-5

    if (array_del(&array, &len, m1) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (len == 4)
        {
            if (*array == -1 && *(array + 1) == -2 && *(array + 2) == -3 && *(array + 3) == -4)
                test_save++;
        }
    }

    //Test 4
    m1 = 5.000000;

    for (int i = 0; i < len; i++)
        *(array + i) = -5; //5,5,5,5,5

    if (array_del(&array, &len, m1) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (len == 5)
        {
            if (*array == -5 && *(array + 1) == -5 && *(array + 2) == -5
                && *(array + 3) == -5 && *(array + 4) == -5
                && *(array + 3) == -5)
                test_save++;
        }
    }

    //Test 5
    m1 = 5.000000;

    for (int i = 0; i < len; i++)
        *(array + i) = 5; //5,5,5,5,5

    if (array_del(&array, &len, m1) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (len == 5)
        {
            if (*array == 5 && *(array + 1) == 5 && *(array + 2) == 5
                    && *(array + 3) == 5 && *(array + 4) == 5
                    && *(array + 3) == 5)
                test_save++;
        }
    }

    len = 3;

    array = (array_type)realloc(array, sizeof(double) * (unsigned)(len));

    //Test 6
    m1 = 2.571429;

    for (int i = 0; i < len; i++)
        *(array + i) = i + 1; //1, 2, 3

    if (array_del(&array, &len, m1) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (len == 2)
        {
            if (*array == 1 && *(array + 1) == 2)
                test_save++;
        }
    }
    len = 3;

    //Test 7
    m1 = 1332.428571;

    *array = 17768;
    *(array + 1) = 199;
    *(array + 2) = 10;

    if (array_del(&array, &len, m1) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (len == 2)
        {
            if (*array == 199 && *(array + 1) == 10)
                test_save++;
        }
    }

    //Test 8
    m1 = 1218.744350;

    *array = 17768.2421;
    *(array + 1) = -199.2478;
    *(array + 2) = 10.13;

    if (array_del(&array, &len, m1) == EXIT_FAILURE)
        test_save++;
    else
    {
        if (len == 2)
        {
            if (*array == -199.2478 && *(array + 1) == 10.13)
                test_save++;
        }
    }

    return test_save;
}

int main()
{
    int test_save = 0;

    test_save += test_array_del();

    test_save += test_array_insert();

    test_save += test_m_average_one();

    test_save += test_m_average_two();

    if (test_save == 16)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}
