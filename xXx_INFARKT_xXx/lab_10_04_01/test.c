#include "headers/includes.h"
#include "headers/rec_arr_routines.h"
#include "headers/record_routines.h"
#include "headers/types.h"

int main()
{
    record_arr_t arr;
    init_arr(&arr);

    dest_arr(&arr);
    return EXIT_SUCCESS;
}
