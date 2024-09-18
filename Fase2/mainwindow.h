#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <adminwindow.h>
#include <userwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, AVLTree *usuariosAVL = nullptr, DoubleList* publicacionesList = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Login_clicked();

private:
    Ui::MainWindow *ui;
    AdminWindow *adminwindow;
    Userwindow *userwindow;
    AVLTree *usuariosAVL;
    DoubleList *publicacionesList;
};
#endif // MAINWINDOW_H
