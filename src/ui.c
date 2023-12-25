#include "ui.h"

void ui_main_menu()
{
    int menu_choice = ui_get_menu_choice();

    if (menu_choice == -1)
    {
        printf("[Error] no such option");
        exit(1);
    }

    if (menu_choice == 1)
    {
        /* code */
    }
    else if (menu_choice == 2)
    {
        int partitionSize = ui_get_partition_size();

        if (partitionSize == -1)
        {
            printf("[Error] partition value is invalid");
            exit(1);
        }

        printf("partition size = %d", partitionSize);
        ui_help();
    }
}

int ui_get_menu_choice()
{
    int option;

    printf("options:\n");
    printf("\t1. load from file");
    printf("\t2. create new partition in memory");
    scanf("%d", option);

    return option == 1 || option == 2 ? option : -1;
}

int ui_get_partition_size()
{
    int partitionSize;

    printf("Input size of a new partition (example 102400): ");
    scanf("%d", partitionSize);

    return partitionSize > 0 ? partitionSize : -1;
}

void ui_help()
{
    printf("List of commands\n");
    printf("'ls' list directory \n");
    printf("'cd' change directory \n");
    printf("'rm' remove \n");
    printf("'mkdir' make directory \n");
    printf("'rmdir' remove directory \n");
    printf("'put' put file into the space \n");
    printf("'get' get file from the space \n");
    printf("'cat' show content \n");
    printf("'status' show status of the space \n");
    printf("'help' \n");
    printf("'exit and store img' \n");
}