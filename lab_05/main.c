#include "headers/header.h"
#include "headers/output.h"
#include "headers/delete.h"
#include "headers/insert.h"
#include "headers/push.h"


int main() {
    arr_queue frst_arr;
    list_queue *frst_list = NULL;

    init_list_queue(&frst_list);
    push_li(&frst_list);

    printf("%d %d", frst_list->rear, frst_list->frnt);

    return EXIT_SUCCESS;
}