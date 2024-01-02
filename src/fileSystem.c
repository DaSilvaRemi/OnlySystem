#include "fileSystem.h"

Tree* fileSystem_init(){
    Tree* fileSystem;
    NodeData data;
    Node* root;

    fileSystem = tree_new();

    if (fileSystem == NULL)
    {
        return NULL;
    }
    
    data.key = "";
    data.keyLength = 0;
    data.content = NULL;
    data.contentLength = 0;
    data.nodeType = DIRECTORY_T;

    root = node_new(data);

    if (root == NULL)
    {
        return NULL;
    }

    tree_addNode(fileSystem, NULL, root);
    utils_createDir(PARTITION_DIR_NAME);

    return fileSystem;
}

void fileSystem_ls(Node *currentDir)
{
    ListNode *current = currentDir->childrens->head;

    while (current != NULL)
    {
        printf("%s ", ((Node *)current->node)->data.key);
        current = current->next;
    }
}

void fileSystem_cd(Node **currentDir, char *dirName)
{
    Node *newDir;

    if (strcmp(dirName, "..") == 0)
    {
        if (!node_hasParent(*currentDir))
        {
            printf("You are on root directory can't process to this operation !");
            return;
        }

        newDir = (*currentDir)->parent;
    }
    else
    {
        newDir = node_findChildrenWithKey(*currentDir, dirName);
    }

    if (newDir == NULL || newDir->data.nodeType != DIRECTORY_T)
    {
        printf("The directory don't exist");
        return;
    }

    *currentDir = newDir;
}

void fileSystem_rm(Tree *fileSystem, Node *currentDir, char *fileName)
{
    Node *fileToRemove;

    fileToRemove = node_findChildrenWithKey(currentDir, fileName);

    if (fileToRemove == NULL || fileToRemove->data.nodeType != FILE_T)
    {
        printf("File %s not found !", fileName);
        return;
    }

    char *fullPath = fileSystem_getFullRealPathOfANode(fileToRemove);

    if (fullPath == NULL)
    {
        printf("Error by generating the full path of the file");
        return;
    }

    if (utils_deleteFile(fullPath) == 0)
    {
        printf("Can't remove the file on your system !");
        free(fullPath);
        return;
    }

    free(fullPath);
    tree_removeNode(fileSystem, fileToRemove);
}

void fileSystem_mkdir(Tree *fileSystem, Node *currentDir, char *dirName)
{
    if(node_findChildrenWithKey(currentDir, dirName) != NULL){
        printf("Directory already exist in this dir can't put it in memory !");
        return;
    }

    NodeData data;
    data.content = NULL;
    data.contentLength = 0;
    data.key = dirName;
    data.keyLength = strlen(dirName);
    data.nodeType = DIRECTORY_T;

    Node *newNode = node_new(data);
    tree_addNode(fileSystem, currentDir, newNode);

    char *fullPath = fileSystem_getFullRealPathOfANode(newNode);

    if (fullPath == NULL)
    {
        printf("Error by generating the full path of the file");
        return;
    }

    if (utils_createDir(fullPath) == 0)
    {
        printf("Failed to create the directory on your computer !");
    }
}

void fileSystem_rmdir(Tree *fileSystem, Node *currentDir, char *dirName)
{
    Node *dirToRemove;
    ListNode* current;
    char* fullPath;

    dirToRemove = node_findChildrenWithKey(currentDir, dirName);

    if (dirToRemove == NULL || dirToRemove->data.nodeType != DIRECTORY_T)
    {
        printf("parent : %s \n", currentDir->data.key);
        printf("Directory %s not found !\n", dirName);
        return;
    }

    current = dirToRemove->childrens->head;
    
    while (current != NULL)
    {
        if (((Node*) current->node)->data.nodeType == DIRECTORY_T)
        {
            fileSystem_rmdir(fileSystem, dirToRemove, ((Node*) current->node)->data.key);
        }
        else
        {
            fileSystem_rm(fileSystem, dirToRemove, ((Node*) current->node)->data.key);
        }

        current = current->next;
    }
    
    fullPath = fileSystem_getFullRealPathOfANode(dirToRemove);
    
    if (utils_removeEmptyDir(fullPath) == 0)
    {
        printf("Can't delete this dir !");
        return;
    }
    
    free(fullPath);
    tree_removeNode(fileSystem, dirToRemove);
}

void fileSystem_put(Tree *fileSystem, Node *currentDir, char *fileName)
{
    char* fileContent;
    int fileSize;

    if(node_findChildrenWithKey(currentDir, fileName) != NULL){
        printf("File already exist in this dir can't put it in memory !");
        return;
    }

    fileSize = utils_readContentOfAFile(fileName, &fileContent);

    if (fileSize == -1)
    {
        printf("File not found !");
        return;
    }
    
    NodeData data;
    data.content = fileContent;
    data.contentLength = fileSize + 1;
    data.key = fileName;
    data.keyLength = strlen(fileName);
    data.nodeType = FILE_T;

    Node *newNode = node_new(data);
    tree_addNode(fileSystem, currentDir, newNode);

    char *fullPath = fileSystem_getFullRealPathOfANode(newNode);

    if (fullPath == NULL)
    {
        printf("Error by generating the full path of the file");
        return;
    }

    if (utils_writeFile(fullPath, fileContent) == 0)
    {
        printf("Failed to write this file on your computer !");
    }
}

void fileSystem_cat(Node *currentDir, char *fileName)
{
    Node *fileToRead;

    fileToRead = node_findChildrenWithKey(currentDir, fileName);

    if (fileToRead == NULL || fileToRead->data.nodeType != FILE_T)
    {
        printf("File not found !");
        return;
    }

    printf("%s", fileToRead->data.content);
}

char *fileSystem_getFullRealPathOfANode(Node *node)
{
    LinkedList *reversePreorder;
    ListNode *current;
    char *fullPath;
    char *tmp1;
    char *tmp2;

    reversePreorder = tree_getReversePreorder(node);
    linkedList_reverse(reversePreorder);

    current = reversePreorder->head;
    fullPath = DUMP_DIR_NAME;

    while (current != NULL)
    {
        tmp1 = NULL;
        tmp2 = NULL;

        if (((Node *)current->node)->data.nodeType == DIRECTORY_T)
        {
            tmp2 = fullPath;

            tmp1 = utils_concatSTR(((Node *)current->node)->data.key, "/");
            fullPath = utils_concatSTR(tmp2, tmp1);
        }
        else
        {
            tmp1 = fullPath;
            fullPath = utils_concatSTR(tmp1, ((Node *)current->node)->data.key);
        }

        if (tmp1 != NULL)
        {
            free(tmp1);
        }

        current = current->next;
    }

    linkedList_free(reversePreorder);
    return fullPath;
}