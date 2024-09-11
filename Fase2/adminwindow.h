#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "mylist.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_actionCargar_usuarios_triggered();

    void on_actionCargar_solicitudes_triggered();

    void on_actionCargarPublicaciones_triggered();

private:
    Ui::AdminWindow *ui;
    MyList lista;
};

#endif // ADMINWINDOW_H
