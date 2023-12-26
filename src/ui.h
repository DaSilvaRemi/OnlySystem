#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void ui_mainMenu(Tree* tree);
int ui_getMenuChoice();
int ui_getPartitionSize();
void ui_help();

void ui_cmdMenu(Tree* tree);

#endif