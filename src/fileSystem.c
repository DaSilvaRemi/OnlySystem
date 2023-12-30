#include "fileSystem.h"

void fileSystem_ls(Node* currentDir){
    ListNode* current = currentDir->childrens->head;

    while (current != NULL)
    {
        printf("%s ", ((Node*) current->node)->data.key);
        current = current->next;
    }
}

void fileSystem_cd(Node** currentDir, char* dirName){
    Node* newDir;
    
    if (strcmp(dirName, "..") == 0)
    {
       if(!node_hasParent(*currentDir)){
            printf("You are on root directory can't process to this operation !");
            return;
       }

        newDir = (*currentDir)->parent;
    } else {
        newDir = node_findChildrenWithKey(*currentDir, dirName);
    }
    
    if (newDir == NULL || newDir->data.nodeType != DIRECTORY_T)
    {
        printf("The directory don't exist");
        return;
    }

    *currentDir = newDir;
}

void fileSystem_rm(Tree* fileSystem, Node* currentDir, char* fileName){
    Node* fileToRemove;

    fileToRemove = node_findChildrenWithKey(currentDir, fileName);

    if (fileToRemove == NULL || fileToRemove->data.nodeType != FILE_T)
    {
        printf("File not found !");
        return;
    }    

    tree_removeNode(fileSystem, fileToRemove);
}

void fileSystem_mkdir(Tree* fileSystem, Node* currentDir, char* dirName){
    NodeData data;
    data.content = NULL;
    data.contentLength = 0;
    data.key = dirName;
    data.keyLength = strlen(dirName);
    data.nodeType = DIRECTORY_T;

    Node* newNode = node_new(data);
    tree_addNode(fileSystem, currentDir, newNode);
}

void fileSystem_rmdir(Tree* fileSystem, Node* currentDir, char* dirName){
    Node* dirToRemove;

    dirToRemove = node_findChildrenWithKey(currentDir, dirName);

    if (dirToRemove == NULL || dirToRemove->data.nodeType != DIRECTORY_T)
    {
        printf("Directory not found !");
        return;
    }    

    tree_removeNode(fileSystem, dirToRemove);
}

void fileSystem_put(Tree* fileSystem, Node* currentDir, char* fileName){
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
       printf("failed to open file '%s'", fileName); 
       return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* fileContent = (char*)malloc(fileSize + 1);
    
    fread(fileContent, sizeof(char), fileSize, file); 
    fileContent[fileSize] = '\0';
    fclose(file);

    NodeData data;
    data.content = fileContent;
    data.contentLength = fileSize + 1;
    data.key = fileName;
    data.keyLength = strlen(fileName);
    data.nodeType = FILE_T;

    Node* newNode = node_new(data);
    tree_addNode(fileSystem, currentDir, newNode);
}

void fileSystem_cat(Node* currentDir, char* fileName){
    Node* fileToRead;

    fileToRead = node_findChildrenWithKey(currentDir, fileName);

    if (fileToRead == NULL || fileToRead->data.nodeType != FILE_T)
    {
        printf("File not found !");
        return;
    }

    printf("%s", fileToRead->data.content);    
}