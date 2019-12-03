#include "headers/includes.h"
#include "headers/types.h"
#include "headers/rec_arr_routines.h"
#include "headers/record_routines.h"

int main()
{
    record_arr_t arr;
    init_arr(&arr);

    printf("Input 'none', to stop input\n");
    if(input_arr(&arr) != EXIT_SUCCESS)
    {
        dest_arr(&arr);
        return EXIT_FAILURE;
    }

    if(b_task(&arr) != EXIT_SUCCESS)
    {
        dest_arr(&arr);
        return EXIT_FAILURE;
    }

    if(c_task(&arr) != EXIT_SUCCESS)
    {
        dest_arr(&arr);
        return EXIT_FAILURE;
    }

    sort_arr(&arr);

    if(arr_to_file(&arr) != EXIT_SUCCESS)
    {
        dest_arr(&arr);
        return EXIT_FAILURE;
    }

    dest_arr(&arr);
    return EXIT_SUCCESS;
}
