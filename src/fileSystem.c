#include "fileSystem.h"

FileSystem* fileSystem_new(int partitionSize){
    FileSystem* fileSystem;
    NodeData data;
    Node* root;

    fileSystem = (FileSystem*) malloc(sizeof(FileSystem));

    if (fileSystem == NULL)
    {
        printf("Failed to init the file system");
        return NULL;
    }

    fileSystem->treeFileSystem = tree_new();

    if (fileSystem->treeFileSystem == NULL)
    {
        printf("Failed to init the tree file system");
        return NULL;
    }
    
    data.key = (char*) malloc(sizeof(char));
    data.keyLength = 0;
    data.content = NULL;
    data.contentLength = 0;
    data.nodeType = DIRECTORY_T;

    root = node_new(data);

    if (root == NULL)
    {
        printf("Failed to init the root !");
        return NULL;
    }

    tree_addNode(fileSystem->treeFileSystem, NULL, root);
    // utils_createDir(PARTITION_DIR_NAME);
    utils_createDir(DUMP_DIR_NAME);

    fileSystem->partitionSize = partitionSize;
    fileSystem->usedCapacity = 0;

    return fileSystem;
}

void fileSystem_free(FileSystem* fileSystem){
    if (fileSystem == NULL)
    {
        return;
    }
    
    tree_free(fileSystem->treeFileSystem);
    free(fileSystem);
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

void fileSystem_rm(FileSystem* fileSystem, Node *currentDir, char *fileName)
{
    Node *fileToRemove;

    fileToRemove = node_findChildrenWithKey(currentDir, fileName);

    if (fileToRemove == NULL || fileToRemove->data.nodeType != FILE_T)
    {
        printf("File %s not found !", fileName);
        return;
    }

    // char *fullPath = fileSystem_getFullRealPathOfANode(fileToRemove);

    // if (fullPath == NULL)
    // {
    //     printf("Error by generating the full path of the file");
    //     return;
    // }

    // if (utils_deleteFile(fullPath) == 0)
    // {
    //     printf("Can't remove the file on your system !");
    //     free(fullPath);
    //     return;
    // }

    // free(fullPath);
    fileSystem->usedCapacity -= fileToRemove->data.contentLength;
    tree_removeNode(fileSystem->treeFileSystem, fileToRemove);
}

void fileSystem_mkdir(FileSystem* fileSystem, Node *currentDir, char *dirName)
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
    tree_addNode(fileSystem->treeFileSystem, currentDir, newNode);

    // char *fullPath = fileSystem_getFullRealPathOfANode(newNode);

    // if (fullPath == NULL)
    // {
    //     printf("Error by generating the full path of the file");
    //     return;
    // }

    // if (utils_createDir(fullPath) == 0)
    // {
    //     printf("Failed to create the directory on your computer !");
    // }
}

void fileSystem_rmdir(FileSystem* fileSystem, Node *currentDir, char *dirName)
{
    Node *dirToRemove;
    ListNode* current;
    char* fullPath;

    dirToRemove = node_findChildrenWithKey(currentDir, dirName);

    if (dirToRemove == NULL || dirToRemove->data.nodeType != DIRECTORY_T)
    {
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
    
    // fullPath = fileSystem_getFullRealPathOfANode(dirToRemove);
    
    // if (utils_removeEmptyDir(fullPath) == 0)
    // {
    //     printf("Can't delete this dir !");
    //     return;
    // }
    
    // free(fullPath);
    tree_removeNode(fileSystem->treeFileSystem, dirToRemove);
}

void fileSystem_put(FileSystem* fileSystem, Node *currentDir, char *fileName)
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

    if (fileSystem->usedCapacity + data.contentLength > fileSystem->partitionSize)
    {
        printf("You have used all the capacity");
        return;
    }

    Node *newNode = node_new(data);
    tree_addNode(fileSystem->treeFileSystem, currentDir, newNode);
    fileSystem->usedCapacity += newNode->data.contentLength;

    // char *fullPath = fileSystem_getFullRealPathOfANode(newNode);

    // if (fullPath == NULL)
    // {
    //     printf("Error by generating the full path of the file");
    //     return;
    // }

    // if (utils_writeFile(fullPath, fileContent) == 0)
    // {
    //     printf("Failed to write this file on your computer !");
    // }
}

void fileSystem_get(Node *currentDir, char *fileName){
    Node* fileToDump;
    char *fullPath;

    fileToDump = node_findChildrenWithKey(currentDir, fileName);

    if (fileToDump == NULL || fileToDump->data.nodeType != FILE_T)
    {
        printf("File %s not found !\n", fileName);
        return;
    }

    char* tmp = utils_concatSTR(DUMP_DIR_NAME, "/");
    fullPath = utils_concatSTR(tmp, fileToDump->data.key);

    if (fullPath == NULL)
    {
        printf("Error by generating the full path of the file");
        return;
    }

    if (utils_writeFile(fullPath, fileToDump->data.content) == 0)
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

void fileSystem_status(FileSystem* fileSystem){
    printf("partition size: %d\n", fileSystem->partitionSize);
    printf("free space: %d\n", fileSystem->partitionSize - fileSystem->usedCapacity);
}

void filesystem_writeNodeToFile(FILE* file, Node* node) {
    if (node == NULL) {
        return;
    }

    fwrite(&node->data.keyLength, sizeof(int), 1, file);
    fwrite(&node->data.contentLength, sizeof(int), 1, file);
    fwrite(&node->data.nodeType, sizeof(NodeType), 1, file);

    if (node->data.key != NULL) {
        fwrite(node->data.key, sizeof(char), node->data.keyLength, file);
    }

    if (node->data.content != NULL) {
        fwrite(node->data.content, sizeof(char), node->data.contentLength, file);
    }

    fwrite(&node->childrens->counts, sizeof(int), 1, file);

    ListNode* current = node->childrens->head;

    while (current != NULL) {
        filesystem_writeNodeToFile(file, (Node*)current->node);
        current = current->next;
    }
}


void fileSystem_exit(FileSystem* fileSystem){
    FILE* file = fopen("my_fs.dump", "wb");

    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }
    
    fwrite(&fileSystem->partitionSize, sizeof(int), 1, file);
    fwrite(&fileSystem->usedCapacity, sizeof(int), 1, file);
    filesystem_writeNodeToFile(file, fileSystem->treeFileSystem->root);
    fclose(file);

    printf("FileSystem saved to '%s' successfully.\n", "my_fs.dump");
}

FileSystem* fileSystem_readFile(const char* fileName) {
    FileSystem* fileSystem;
    int partitionSize, usedCapacity;
    FILE* binaryDumpFile;

    binaryDumpFile = fopen(fileName, "rb");
    
    if (binaryDumpFile == NULL) {
        printf("Failed to open the file !");
        return NULL;
    }

    fread(&partitionSize, sizeof(int), 1, binaryDumpFile);
    fread(&usedCapacity, sizeof(int), 1, binaryDumpFile);

    fileSystem = fileSystem_new(partitionSize);
    tree_removeNode(fileSystem->treeFileSystem, fileSystem->treeFileSystem->root);

    fileSystem->usedCapacity = usedCapacity;
    tree_addNode(fileSystem->treeFileSystem, NULL, fileSystem_readNodeFromFile(binaryDumpFile)); 
    fclose(binaryDumpFile);

    return fileSystem;
}

Node* fileSystem_readNodeFromFile(FILE* file) {
    NodeType nodeType;
    NodeData nodeData;
    Node* newNode;
    int keyLength, contentLength, childrenCount;

    fread(&keyLength, sizeof(int), 1, file);
    fread(&contentLength, sizeof(int), 1, file);
    fread(&nodeType, sizeof(NodeType), 1, file);

    nodeData.keyLength = keyLength;
    nodeData.contentLength = contentLength;
    nodeData.nodeType = nodeType;
    nodeData.key = (char*) malloc(sizeof(char) * (nodeData.keyLength + 1));
    nodeData.key[nodeData.keyLength] = '\0';

    if (nodeData.keyLength > 0) {
        fread(nodeData.key, sizeof(char), nodeData.keyLength, file);
    }

    if (nodeData.contentLength > 0) {
        nodeData.content = (char*) malloc(sizeof(char) * nodeData.contentLength + 1);
        fread(nodeData.content, sizeof(char), nodeData.contentLength, file);
        nodeData.content[nodeData.contentLength] = '\0';
    } else {
        nodeData.content = NULL;
    }

    newNode = node_new(nodeData);
    fread(&childrenCount, sizeof(int), 1, file);

    for (int i = 0; i < childrenCount; ++i) {
        Node* childNode = fileSystem_readNodeFromFile(file);
        node_addChildren(newNode, childNode);
    }

    return newNode;
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
    fullPath = PARTITION_DIR_NAME;

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