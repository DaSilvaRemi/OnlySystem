#include "ui.h"

int main(){
    Tree* fileSystem = tree_new();
    Node* root = node_new("./", NULL);

    ui_mainMenu(fileSystem);
    
    return 0;
}