#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "fileSystem.h"

typedef enum cmdChoice {
    LS,
    CD,
    RM,
    MKDIR,
    RMDIR,
    PUT,
    GET,
    CAT,
    STATUS,
    HELP,
    EXIT
} CMDChoice;

void ui_mainMenu();
int ui_getMenuChoice();
int ui_getPartitionSize();
void ui_help();

void ui_cmdMenu(FileSystem* fileSystem);
void ui_displayCurrentPath(Node* currentDir);
int ui_getCmdChoice();

#endif