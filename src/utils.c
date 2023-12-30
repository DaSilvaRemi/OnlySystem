#include "utils.h"

char* utils_concatSTR(const char* str1, const char* str2) {
    char* result = malloc(strlen(str1) + strlen(str2) + 1);

    if (result) {
        strcpy(result, str1);
        strcat(result, str2);
    }

    return result;
}

int utils_readContentOfAFile(char* fileName, char** fileContent){
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    *fileContent = (char *)malloc(fileSize + 1);

    fread(*fileContent, sizeof(char), fileSize, file);
    fileContent[fileSize] = '\0';
    fclose(file);

    return fileSize;
}

int utils_writeFile(const char* fileName, const char* content) {
    FILE* file = fopen(fileName, "w");

    if (file == NULL) {
        printf("Can't write into the file !");
        return 0;
    }

    fprintf(file, "%s", content);
    fclose(file);
    return 1;
}

int utils_deleteFile(const char* fileName){
    return remove(fileName) == -1 ? 0 : 1; 
}


int utils_createDir(const char* directoryName){
    return mkdir(directoryName, S_IRWXU) == 0 ? 1 : 0; 
}

int utils_removeEmptyDir(const char* directoryName){
    return rmdir(directoryName) == 0 ? 1 : 0;
}
