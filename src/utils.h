#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

char* utils_concatSTR(const char *s1, const char *s2);
int utils_readContentOfAFile(char* fileName, char** fileContent);
int utils_writeFile(const char* fileName, const char* content);
int utils_deleteFile(const char* fileName);
int utils_createDir(const char* directoryName);
int utils_removeEmptyDir(const char* directoryName);

#endif