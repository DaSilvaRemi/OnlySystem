#include "ui.h"
#include "tree.h"

int main(){
    Tree* fileSystem = tree_new();
    Node* root = node_new("./", NULL);

    ui_main_menu();
    
    return 0;
}