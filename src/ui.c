#include "ui.h"

void ui_mainMenu()
{
    Tree *fileSystem;
    Node *root;
    NodeData data;
    int menu_choice;

    fileSystem = tree_new();
    data.key = "";
    data.keyLength = 0;
    data.content = NULL;
    data.contentLength = 0;
    data.nodeType = DIRECTORY_T;
    root = node_new(data);
    tree_addNode(fileSystem, NULL, root);

    menu_choice = ui_getMenuChoice();

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
        int partitionSize;

        partitionSize = ui_getPartitionSize();

        if (partitionSize == -1)
        {
            printf("[Error] partition value is invalid");
            exit(1);
        }

        printf("partition size = %d\n", partitionSize);
        ui_help();
        ui_cmdMenu(fileSystem);
    }
}

int ui_getMenuChoice()
{
    int option;

    printf("options:\n");
    printf("\t1. load from file\n");
    printf("\t2. create new partition in memory\n");
    scanf("%d", &option);

    return option == 1 || option == 2 ? option : -1;
}

int ui_getPartitionSize()
{
    int partitionSize;

    printf("Input size of a new partition (example 102400): ");
    scanf("%d", &partitionSize);
    printf("\n");

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

void ui_cmdMenu(Tree *fileSystem)
{
    Node *currentDir = fileSystem->root;
    LinkedList *currentLinkedListPath;
    int cmdChoice;

    while (1)
    {
        printf("\n");
        ui_displayCurrentPath(currentDir);
        cmdChoice = ui_getCmdChoice();

        if (cmdChoice == -1)
        {
            printf("Command not found !");
            continue;
        }

        if (cmdChoice == LS)
        {
            fileSystem_ls(currentDir);
        }
        else if (cmdChoice == CD)
        {
            char dirName[20];

            scanf("%s", dirName);

            fileSystem_cd(&currentDir, dirName);
        }
        else if (cmdChoice == RM)
        {
            char fileName[20];

            scanf("%s", fileName);

            fileSystem_rm(fileSystem, currentDir, fileName);
        }
        else if (cmdChoice == MKDIR)
        {
            char* dirName = (char*) malloc(sizeof(char) * 20);

            scanf("%s", dirName);

            fileSystem_mkdir(fileSystem, currentDir, dirName);
        }
        else if (cmdChoice == RMDIR)
        {
            char dirName[20];

            scanf("%s", dirName);

            fileSystem_rmdir(fileSystem, currentDir, dirName);
        }
        else if (cmdChoice == PUT)
        {
            char* fileName = (char*) malloc(sizeof(char) * 20);

            scanf("%s", fileName);

            fileSystem_put(fileSystem, currentDir, fileName);
        }
        else if (cmdChoice == GET)
        {
            // DO SOMETHING
        }
        else if (cmdChoice == CAT)
        {
            char fileName[20];

            scanf("%s", fileName);

            fileSystem_cat(currentDir, fileName);
        }
        else if (cmdChoice == STATUS)
        {
            // DO SOMETHING
        }
        else if (cmdChoice == HELP)
        {
            ui_help();
        }
        else if (cmdChoice == EXIT)
        {
            // DO SOMETHING
        }
    }
}

void ui_displayCurrentPath(Node *currentDir)
{
    LinkedList *currentLinkedListPath;

    currentLinkedListPath = tree_getReversePrefix(currentDir);
    linkedList_reverse(currentLinkedListPath);

    ListNode *current = currentLinkedListPath->head;

    while (current != NULL)
    {
        if (((Node *)current->node)->data.nodeType == DIRECTORY_T)
        {
            printf("%s", ((Node *)current->node)->data.key);
            printf("/");
        }

        current = current->next;
    }

    linkedList_free(currentLinkedListPath);
}

int ui_getCmdChoice()
{
    char cmdChoice[20];

    printf(" $ ");
    scanf("%s", cmdChoice);

    if (strcmp(cmdChoice, "ls") == 0)
    {
        return LS;
    }
    else if (strcmp(cmdChoice, "cd") == 0)
    {
        return CD;
    }
    else if (strcmp(cmdChoice, "rm") == 0)
    {
        return RM;
    }
    else if (strcmp(cmdChoice, "mkdir") == 0)
    {
        return MKDIR;
    }
    else if (strcmp(cmdChoice, "rmdir") == 0)
    {
        return RMDIR;
    }
    else if (strcmp(cmdChoice, "put") == 0)
    {
        return PUT;
    }
    else if (strcmp(cmdChoice, "get") == 0)
    {
        return GET;
    }
    else if (strcmp(cmdChoice, "cat") == 0)
    {
        return CAT;
    }
    else if (strcmp(cmdChoice, "status") == 0)
    {
        return STATUS;
    }
    else if (strcmp(cmdChoice, "help") == 0)
    {
        return HELP;
    }
    else if (strcmp(cmdChoice, "exit and store img") == 0)
    {
        return EXIT;
    }
    else
    {
        return -1;
    }
}