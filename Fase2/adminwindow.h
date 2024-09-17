#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "avltree.h"
#include "doublelist.h"
#include "arbolb.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();
    AVLTree* usuariosAVL;
    DoubleList* publicacionesList;
    ArbolB* comentariosTree;

private slots:
    void on_actionCargar_usuarios_triggered();

    void on_actionCargar_solicitudes_triggered();

    void on_actionCargarPublicaciones_triggered();

    void on_pushButton_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
