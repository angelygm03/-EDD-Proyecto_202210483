#ifndef USERWINDOW_H
#define USERWINDOW_H
#include "avltree.h"

#include <QMainWindow>

namespace Ui {
class Userwindow;
}

class Userwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Userwindow(QWidget *parent = nullptr, AVLTree *usuariosAVL = nullptr);
    ~Userwindow();

private slots:
    void on_actionIr_a_publicaciones_triggered();

    void on_pushButton_2_buscar_clicked();

private:
    Ui::Userwindow *ui;
    AVLTree* usuariosAVL;
};

#endif // USERWINDOW_H
