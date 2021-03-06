#ifndef TMP_H
#define TMP_H

#endif // TMP_H


/*
packedMatrix_t *mulPackedMtxOnPackedMtx(const packedMatrix_t *left, const packedMatrix_t *right)
{
    if(left->maxColumn != right->IA.len)
        return NULL;

    packedMatrix_t *res = (packedMatrix_t *)calloc(sizeof (packedMatrix_t), sizeof (char));
    res->maxColumn = right->maxColumn;
    res->A.size = 0;
    res->JA.size = 0;
    res->A.data = res->JA.data = NULL;
    res->IA.len = 0;
    for(int i = 0; i < left->IA.len; i++)
        add(&(res->IA), -1, -1);

    for(int i = 0; i < left->A.size; i++) // проходим по всем значениям левой матрицы
    {
        int last, first = findString(right, left->JA.data[i], &last); // находим, где начинается и заканчивается строка с индексом столбца i-го элемента левой матрицы правой матрицы
        for(int k = first; k <= last; k++) // проходим по всем элементам правой матрицы в строке с индексом столбца элемента массива A левой матрицы
        {
            int rightC = right->JA.data[k]; // индекс столбца элемента правой матрицы
            int rightV = right->A.data[k]; // значение элемента правой матрицы
            int leftS = peekString(*left, i); // индекс строки элемента левой матрицы
            int leftV = left->A.data[i]; // значение элемента левой матрицы

            int oldResValue;
            takeElem(res, leftS, rightC, &oldResValue); // смотрим старое значение в результатной матрице
            int newResValue = oldResValue + leftV * rightV; // считаем новое значение в результатной матрице
            putElem(res, leftS, rightC, newResValue);
        }
    }
    return res;
}

void reform(packedMatrix_t *matrix)
{
    node_t *curr = matrix->IA.head;
    for(int i = 0; i < matrix->IA.len; i++, curr = curr->next)
        if(curr->A == -1 && i != 0)
        {
            curr->A = curr->prev->A; curr->JA = curr->prev->JA;
        }
        else if(curr->A == -1)
        {
            curr->A = 0; curr->JA = 0;
        }
}
*/

/*
int putElem(packedMatrix_t* pMtx, const int str, const int col, const int elem)
{
    node_t *currstr = pMtx->IA.head;
    node_t *rightBorderNode;
    int rightBorder, leftBorder;

    if(str >= pMtx->IA.len || str < 0 || col < 0 || col >= pMtx->maxColumn)
        return OUT_OF_BOUNDS;
    while(currstr->index != str) // находим текущую строку в списке строк
        currstr = currstr->next;

    int currentItem; // если текущий элемент и элемент по индексам равен нулю
    takeElem(pMtx, str, col, &currentItem); // то выходим из подпрограммы
    if(!currentItem && !elem)
        return EXIT_SUCCESS;

    if(currstr->JA > -1) // если строка не пуста, мы можем определить начальный и конечный индексы
    {
        leftBorder = currstr->JA; // определяем левую границу обхода как индекс элемента массива JA с которого начинается текущая строка

        if(!currstr->next) // если строка последняя
            rightBorder = pMtx->JA.size; // определяем правую границу как конец длина массива JA
        else // иначе нужно найти границу обхода, или определить, что она совпадает с pMtx->JA.size
        {
            rightBorderNode = currstr->next;                              // обходим все узлы списка слева направо с текущего до первого описывающего не пустую строку
            while(rightBorderNode->JA < 0 && rightBorderNode->next)
                rightBorderNode = rightBorderNode->next;

            if(rightBorderNode->JA < 0) // если последний узел содержал отрицательное значение, значит граница обхода совпадает с pMtx->JA.size
                rightBorder = pMtx->JA.size;
            else
                rightBorder = rightBorderNode->JA; // иначе узел rightBorderNode является реальной правой границей текущей строки

        }

        for(int i = leftBorder; i < rightBorder; i++) // можно попытаться найти ненулевой элемент и заменить его значение
            {
                if(pMtx->JA.data[i] == col) // если в строке находится элемент, у которого индекс столбца совпадает с аргументом, мы можем заменить значение
                {
                    if(!elem) // если значение равно 0
                    {
                        if(i + 1 >= rightBorder && currstr->A == i) // какое-то условие которое я забыл что делает блять потому что нельзя ходить гулять посреди работы
                            currstr->A = currstr->JA = -1; // в строке не остается ненулевых элементов => меняем значение узла

                        delete(&(pMtx->JA), i);
                        delete(&(pMtx->A), i);
                        node_t *tmp = currstr->next; // сдвигаем индексы элементов начала строк в списке
                        while(tmp)
                        {
                            if(tmp->JA > -1)
                            {
                                tmp->JA--;
                                tmp->A--;
                            }
                            tmp = tmp->next;
                        }
                        return EXIT_SUCCESS;
                    }
                    pMtx->A.data[i] = elem;
                    return EXIT_SUCCESS;
                }
            }

        for(int i = leftBorder; i < rightBorder - 1; i++) // пробегаем по всем элементам строки, кроме последнего
        {
            if(pMtx->JA.data[i] < col && pMtx->JA.data[i+1] > col) // если индекс столбца записываемого элемента не нарушает возрастание индексов в подстроке, мы добавляем элемент в подстроку
            {
                insert(&(pMtx->JA), i + 1, col); // добавляем элемент в подстроку
                insert(&(pMtx->A), i + 1, elem);

                node_t *tmp = currstr->next; // сдвигаем индексы элементов начала строк в списке
                while(tmp)
                {
                    if(tmp->JA > -1)
                    {
                        tmp->JA++;
                        tmp->A++;
                    }
                    tmp = tmp->next;
                }
                return EXIT_SUCCESS;
            }
        }

        // мы рассмотрели случаи, когда элемент добавляется в середину, начало подстроки или заменяет собой ненулевой элемент
        // значит у нас остался единственный случай, когда элемент добавляется в конец строки (является крайним правым в подстроке)

        if(1)
        {
            insert(&(pMtx->JA), rightBorder, col); // добавляем элемент в конец подстроки
            insert(&(pMtx->A), rightBorder, elem);

            node_t *tmp = currstr->next; // сдвигаем индексы элементов начала строк в списке
            while(tmp)
            {
                if(tmp->JA > 0)
                {
                    tmp->JA++;
                    tmp->A++;
                }
                tmp = tmp->next;
            }
        }
    }
    else // здесь рассмотрим добавление элемента в строку полностью состоящую из нулей
    {
        // для начала нам нужно поиском определить границы

        // поиск правой границы
        rightBorderNode = currstr->next;

        if(!currstr->next) // если строка последняя
            rightBorder = pMtx->JA.size; // определяем правую границу как конец длина массива JA
        else // иначе нужно найти границу обхода, или определить, что она совпадает с pMtx->JA.size
        {
            rightBorderNode = currstr->next;                              // обходим все узлы списка слева направо с текущего до первого описывающего не пустую строку
            while(rightBorderNode->JA < 0 && rightBorderNode->next)
                rightBorderNode = rightBorderNode->next;

            if(rightBorderNode->JA < 0) // если последний узел содержал отрицательное значение, значит граница обхода совпадает с pMtx->JA.size
                rightBorder = pMtx->JA.size;
            else
                rightBorder = rightBorderNode->JA; // иначе узел rightBorderNode является реальной правой границей текущей строки
        }

        // так как строка не содержит ненулевых элементов => подстрока пуста, следовательно первый левый элемент после правой границы будет левой границей подстроки
        // подстрока пуста => длина ноль => правая и левая границы совпадают
        insert(&(pMtx->JA), rightBorder, col);
        insert(&(pMtx->A), rightBorder, elem);
        currstr->A = rightBorder;
        currstr->JA = rightBorder;

        node_t *tmp = currstr->next; // сдвигаем индексы элементов начала строк в списке
        while(tmp)
        {
            if(tmp->JA > -1)
            {
                tmp->JA++;
                tmp->A++;
            }
            tmp = tmp->next;
        }
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
*/
