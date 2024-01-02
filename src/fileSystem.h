#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <string.h>
#include "utils.h"
#include "tree.h"

#define DUMP_DIR_NAME "dump"
#define PARTITION_DIR_NAME "partition"

typedef struct fileSystem
{
    Tree* treeFileSystem;
    int partitionSize;
    int usedCapacity;
} FileSystem;

FileSystem* fileSystem_new(int partitionSize);
void fileSystem_free(FileSystem* fileSystem);
void fileSystem_ls(Node* currentDir);
void fileSystem_cd(Node** currentDir, char* dirName);
void fileSystem_rm(FileSystem* fileSystem, Node* currentDir, char* fileName);
void fileSystem_mkdir(FileSystem* fileSystem, Node* currentDir, char* dirName);
void fileSystem_rmdir(FileSystem* fileSystem, Node* currentDir, char* dirName);
void fileSystem_put(FileSystem* fileSystem, Node* currentDir, char* fileName);
void fileSystem_get(Node *currentDir, char *fileName);
void fileSystem_cat(Node* currentDir, char* fileName);
void fileSystem_status(FileSystem* fileSystem);
void fileSystem_exit(FileSystem* fileSystem);
void filesystem_writeNodeToFile(FILE* file, Node* node);
FileSystem* fileSystem_readFile(const char* fileName);
Node* fileSystem_readNodeFromFile(FILE* file);
char* fileSystem_getFullRealPathOfANode(Node* node);

#endif