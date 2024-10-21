#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include <QMessageBox>
#include "avltree.h"

namespace Ui {
class SignUp;
}

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr, AVLTree *usuariosAVL = nullptr, QMainWindow *mainWindow = nullptr); // Agregar el puntero a la ventana principal
    ~SignUp();

private slots:
    void on_pushButton_aceptar_clicked();

private:
    Ui::SignUp *ui;
    AVLTree *usuariosAVL;
    QMainWindow *mainWindow; // Puntero a la ventana principal
};

#endif // SIGNUP_H
