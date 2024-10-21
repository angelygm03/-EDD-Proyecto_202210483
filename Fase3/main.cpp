#include "mainwindow.h"
#include "avltree.h"
#include "binarysearchtree.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AVLTree *usuariosAVL = new AVLTree();
    BinarySearchTree *bst = new BinarySearchTree();
    DoubleList *publicacionesList = nullptr;
    MainWindow w(nullptr, usuariosAVL, publicacionesList, bst);
    w.show();
    return a.exec();
}
