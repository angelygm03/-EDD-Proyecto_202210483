/********************************************************************************
** Form generated from reading UI file 'adminwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWINDOW_H
#define UI_ADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminWindow
{
public:
    QAction *actionCargar_usuarios;
    QAction *actionCargar_solicitudes;
    QAction *actionCargarPublicaciones;
    QAction *actionUsuarios;
    QAction *actionPublicaciones;
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuCarga_masiva;
    QMenu *menuReportes;
    QMenu *menuBuscar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName("AdminWindow");
        AdminWindow->resize(800, 600);
        actionCargar_usuarios = new QAction(AdminWindow);
        actionCargar_usuarios->setObjectName("actionCargar_usuarios");
        actionCargar_solicitudes = new QAction(AdminWindow);
        actionCargar_solicitudes->setObjectName("actionCargar_solicitudes");
        actionCargarPublicaciones = new QAction(AdminWindow);
        actionCargarPublicaciones->setObjectName("actionCargarPublicaciones");
        actionUsuarios = new QAction(AdminWindow);
        actionUsuarios->setObjectName("actionUsuarios");
        actionPublicaciones = new QAction(AdminWindow);
        actionPublicaciones->setObjectName("actionPublicaciones");
        centralwidget = new QWidget(AdminWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 160, 291, 61));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(600, 20, 171, 31));
        AdminWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdminWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuCarga_masiva = new QMenu(menubar);
        menuCarga_masiva->setObjectName("menuCarga_masiva");
        menuReportes = new QMenu(menubar);
        menuReportes->setObjectName("menuReportes");
        menuBuscar = new QMenu(menubar);
        menuBuscar->setObjectName("menuBuscar");
        AdminWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AdminWindow);
        statusbar->setObjectName("statusbar");
        AdminWindow->setStatusBar(statusbar);

        menubar->addAction(menuCarga_masiva->menuAction());
        menubar->addAction(menuReportes->menuAction());
        menubar->addAction(menuBuscar->menuAction());
        menuCarga_masiva->addAction(actionCargar_usuarios);
        menuCarga_masiva->addAction(actionCargar_solicitudes);
        menuCarga_masiva->addAction(actionCargarPublicaciones);
        menuReportes->addAction(actionUsuarios);
        menuReportes->addAction(actionPublicaciones);

        retranslateUi(AdminWindow);

        QMetaObject::connectSlotsByName(AdminWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdminWindow)
    {
        AdminWindow->setWindowTitle(QCoreApplication::translate("AdminWindow", "MainWindow", nullptr));
        actionCargar_usuarios->setText(QCoreApplication::translate("AdminWindow", "Cargar usuarios", nullptr));
        actionCargar_solicitudes->setText(QCoreApplication::translate("AdminWindow", "Cargar solicitudes", nullptr));
        actionCargarPublicaciones->setText(QCoreApplication::translate("AdminWindow", "Cargar publicaciones", nullptr));
        actionUsuarios->setText(QCoreApplication::translate("AdminWindow", "Reporte usuarios", nullptr));
        actionPublicaciones->setText(QCoreApplication::translate("AdminWindow", "Reporte publicaciones", nullptr));
        label->setText(QCoreApplication::translate("AdminWindow", "window admin", nullptr));
        pushButton->setText(QCoreApplication::translate("AdminWindow", "Cerrar sesi\303\263n", nullptr));
        menuCarga_masiva->setTitle(QCoreApplication::translate("AdminWindow", "Carga masiva", nullptr));
        menuReportes->setTitle(QCoreApplication::translate("AdminWindow", "Reportes", nullptr));
        menuBuscar->setTitle(QCoreApplication::translate("AdminWindow", "Buscar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminWindow: public Ui_AdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWINDOW_H
