#include "includes/types.h"
#include "includes/idents.h"
#include "includes/file_routines.h"
#include "includes/table_routines.h"
#include "includes/sorts.h"

void print_main_menu()
{
    printf("\tMenu:\n"
           "\t1.Load base from file\n"
           "\t2.Print tables\n"
           "\t3.Add record\n"
           "\t4.Delete record(-s)\n"
           "\t5.Sort tables\n"
           "\t6.Shuffle tables\n"
           "\t7.Save base to choosened file\n"
           "\t8.Search record\n"
           "\t0.Exit\n");
}

int load_base(key *key_list, int *key_list_len, car *car_list, int *car_list_len, flags *flag)
{
    FILE *fp;
    char rc;
    if(flag->chages_flag == 1 || flag->base_flag == 1)
    {
        printf("If you load new base, current one will be lost. Continue?y/n : ");
        scanf("%c", &rc);
        if (rc == 'n')
        {
            printf("Operation aborted!\n");
            return EXIT_FAILURE;
        }
        else if (rc != 'y')
        {
            printf("Wrong input!\n");
            return EXIT_FAILURE;
        }
        clear();
    }
    if(my_fopen(&fp, &rc) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if(read_file(fp, car_list, car_list_len) == EXIT_FAILURE && rc != 'w')
    {
        fclose(fp);
        return EXIT_FAILURE;
    }
    fclose(fp);
    fill_keys(key_list, car_list, car_list_len, key_list_len);
    if (*car_list_len > 0)
        printf("Base successfully loaded!\n");
    flag->base_flag = 1;
    return EXIT_SUCCESS;
}

int print_tables(car *car_list, int car_list_len, key *key_list, int key_list_len, flags flag)
{
    int mode = 0;
    if(flag.base_flag == 0 || car_list_len == 0)
    {
        printf("Empty base, you have nothing to print!\n");
        return EXIT_FAILURE;
    }
    printf("1.Print key list\n"
           "2.Print car list\n"
           "3.Print car list by sorted key_list\n"
           "4.Back to menu\n");
    printf("Input: ");
    scanf("%d", &mode);
    switch (mode)
    {
        case 1:
            print_keys(key_list, key_list_len);
            break;
        case 2:
            print_cars(car_list);
            break;
        case 3:
            if(flag.car_flag == 1)
            {
                char ch;
                printf("Car list is sorted, do you want to continue?y/n : ");
                scanf("%c", &ch);
                clear();
                if(ch == 'n')
                    return EXIT_FAILURE;
                else if (ch != 'y')
                {
                    printf("Wrong input!\n");
                    return EXIT_FAILURE;
                }
            }
            else if(flag.keys_flag == 0)
            {
                printf("Can not print table by keys, becouse key list is not sorted!\n");
                return EXIT_FAILURE;
            }
            print_table_by_keys(car_list, car_list_len, key_list, key_list_len);
            break;
        case 4:
        break;
        default:
            printf("Wrong input!\n");
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int sort_tables(car *car_list, int car_list_len, key *key_list, int key_list_len, flags *flag)
{
    char mode = 0;
    if(flag->base_flag == 0 || car_list_len == 0)
    {
        printf("Empty base, you have nothing to sort!\n");
        return EXIT_FAILURE;
    }
    printf("1.Sort keys with buble sort\n"
           "2.Sort keys with Shell sort\n"
           "3.Sort cars with buble sort\n"
           "4.Sort cars with Shell sort\n"
           "5.Create time estimation (current base will be shuffled and resorted)\n"
           "6.Go back to menu\n");
    printf("Input: ");
    scanf("%c", &mode);
    clear();
    switch (mode)
    {
    case '1':
        if(flag->keys_flag == 1)
        {
            printf("Key list already sorted, resort?y/n : ");
            scanf("%c", &mode);
            clear();
            if(mode == 'n' || mode != 'y')
                return EXIT_FAILURE;
        }
        buble_key_sort(key_list_len, key_list);
        flag->keys_flag = 1;
        printf("List successfully sotrted!\n");
        break;
    case '2':
        if(flag->keys_flag == 1)
        {
            printf("Key list already sorted, resort?y/n : ");
            scanf("%c", &mode);
            clear();
            if(mode == 'n' || mode != 'y')
                return EXIT_FAILURE;
        }
        shell_key_sort(key_list_len, key_list);
        flag->keys_flag = 1;
        printf("List successfully sotrted!\n");
        break;
    case '3':
        if(flag->car_flag == 1)
        {
            printf("Car list already sorted, resort?y/n : ");
            scanf("%c", &mode);
            clear();
            if(mode == 'n' || mode != 'y')
                return EXIT_FAILURE;
        }
        buble_car_sort(car_list_len, car_list);
        flag->car_flag = 1;
        printf("List successfully sotrted!\n");
        break;
    case '4':
        if(flag->car_flag == 1)
        {
            printf("Car list already sorted, resort?y/n : ");
            scanf("%c", &mode);
            clear();
            if(mode == 'n' || mode != 'y')
                return EXIT_FAILURE;
        }
        shell_car_sort(car_list_len, car_list);
        flag->car_flag = 1;
        printf("List successfully sotrted!\n");
        break;
    case '5':
        {
        double buble_keys, buble_cars, shell_keys, shell_cars;

        if(flag->car_flag == 1)
            shuffle_car_list(car_list, car_list_len);
        if(flag->keys_flag == 1)
            shuffle_key_list(key_list, key_list_len);

        buble_cars = buble_car_sort(car_list_len, car_list);
        buble_keys = buble_key_sort(key_list_len, key_list);
        shuffle_car_list(car_list, car_list_len);
        shuffle_key_list(key_list, key_list_len);
        shell_cars = shell_car_sort(car_list_len, car_list);
        shell_keys = shell_key_sort(key_list_len, key_list);

        flag->car_flag = 1;
        flag->keys_flag = 1;

        printf("Time in seconds\n");
        printf("┌──────┬─────────┬─────────┐\n");
        printf("│      │  Buble  │  Shell  │\n");
        printf("│──────├─────────┼─────────┤\n");
        printf("│ Keys │%.6lf │%.6lf │\n", buble_keys, shell_keys);
        printf("│──────├─────────┼─────────┤\n");
        printf("│ Cars │%.6lf │%.6lf │\n", buble_cars, shell_cars);
        printf("└──────┴─────────┴─────────┘\n");
        }
        break;
    case '6':
        break;
    default:
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int shuffle_tables(car *car_list, int car_list_len, key *key_list, int key_list_len, flags *flag)
{
    if(flag->base_flag == 0 || car_list_len == 0)
    {
        printf("Empty base, you have nothing to shuffle!\n");
        return EXIT_FAILURE;
    }
    if(flag->car_flag == 1)
    {
        shuffle_car_list(car_list, car_list_len);
        flag->car_flag = 0;
    }
    if(flag->keys_flag == 1)
    {
        shuffle_key_list(key_list, key_list_len);
        flag->keys_flag = 0;
    }
    printf("Sorted lists are shuffled!\n");
    return EXIT_SUCCESS;
}

int add_record(car *car_list, int *car_list_len, key *key_list, int *key_list_len, flags *flag)
{
    add_rec(car_list, flag, car_list_len);
    fill_keys(key_list, car_list, car_list_len, key_list_len);
    flag->keys_flag = 0;
    flag->base_flag = 1;
    return EXIT_SUCCESS;
}

int delete_record(car *car_list, key *key_list, int *car_list_len, int *key_list_len)
{
    if(*car_list_len == 0)
    {
        printf("Empty base!\n");
        return EXIT_FAILURE;
    }
    if (delete_procedure(key_list, car_list, car_list_len, key_list_len) != EXIT_SUCCESS)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int main()
{
    int car_list_len = 0;
    int key_list_len = 0;
    int menu_choose = 1;
    car car_list[LISTLEN];
    key key_list[LISTLEN];
    flags flag;
    ident_list(car_list);
    ident_flags(&flag);
    ident_key_list(key_list);


    while(menu_choose)
    {
        print_main_menu();
        printf("Input:");
        if(scanf("%d", &menu_choose) == 1)
        {
            clear();
            printf("\n");
            switch (menu_choose)
            {
            case 1:
                load_base(key_list, &key_list_len, car_list, &car_list_len, &flag);
                break;
            case 2:
                print_tables(car_list, car_list_len, key_list, key_list_len, flag);
                break;
            case 3:
                if (add_record(car_list, &car_list_len, key_list, &key_list_len, &flag) == EXIT_SUCCESS)
                    flag.chages_flag = 1;
                break;
            case 4:
                if (delete_record(car_list, key_list, &car_list_len, &key_list_len) == EXIT_SUCCESS)
                    flag.chages_flag = 1;
                break;
            case 5:
                if (sort_tables(car_list, car_list_len, key_list, car_list_len, &flag) == EXIT_SUCCESS)
                    flag.chages_flag = 1;
                break;
            case 6:
                if (shuffle_tables(car_list, car_list_len, key_list, key_list_len, &flag) == EXIT_SUCCESS)
                    flag.chages_flag = 1;
                break;
            case 7:
                save_changes(car_list, car_list_len, flag);
                break;
            case 8:
                search_rec(car_list, car_list_len, &flag);
                break;
            case 0:
                if(car_list_len != 0 && flag.chages_flag == 1)
                    save_changes(car_list, car_list_len, flag);
                break;
            default:
                printf("Wrong input!\n");
            }
            printf("\n");
        }
        else
        {
            clear();
            printf("Wrong input!\n");
        }
    }

    return EXIT_SUCCESS;
}
