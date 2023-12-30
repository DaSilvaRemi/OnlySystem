#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <string.h>
#include "tree.h"

void fileSystem_ls(Node* currentDir);
void fileSystem_cd(Node** currentDir, char* dirName);
void fileSystem_rm(Tree* fileSystem, Node* currentDir, char* fileName);
void fileSystem_mkdir(Tree* fileSystem, Node* currentDir, char* dirName);
void fileSystem_rmdir(Tree* fileSystem, Node* currentDir, char* dirName);
void fileSystem_put(Tree* fileSystem, Node* currentDir, char* fileName);
void fileSystem_get();
void fileSystem_cat(Node* currentDir, char* fileName);
void fileSystem_exit();

#endif