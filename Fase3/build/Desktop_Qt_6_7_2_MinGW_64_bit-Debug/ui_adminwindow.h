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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
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
    QPushButton *pushButton;
    QTableWidget *tableWidget_usuarios;
    QPushButton *pushButton_2_buscar;
    QLineEdit *lineEdit_correo;
    QComboBox *comboBox_orden;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuCarga_masiva;
    QMenu *menuReportes;
    QMenu *menuBuscar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName("AdminWindow");
        AdminWindow->resize(811, 539);
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
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(670, 20, 121, 31));
        tableWidget_usuarios = new QTableWidget(centralwidget);
        if (tableWidget_usuarios->columnCount() < 4)
            tableWidget_usuarios->setColumnCount(4);
        QFont font;
        font.setFamilies({QString::fromUtf8("Gill Sans MT")});
        font.setPointSize(12);
        font.setBold(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget_usuarios->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget_usuarios->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget_usuarios->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        tableWidget_usuarios->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_usuarios->setObjectName("tableWidget_usuarios");
        tableWidget_usuarios->setGeometry(QRect(120, 140, 631, 331));
        QFont font1;
        font1.setPointSize(12);
        tableWidget_usuarios->setFont(font1);
        tableWidget_usuarios->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        pushButton_2_buscar = new QPushButton(centralwidget);
        pushButton_2_buscar->setObjectName("pushButton_2_buscar");
        pushButton_2_buscar->setGeometry(QRect(162, 90, 111, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans MT")});
        font2.setPointSize(12);
        pushButton_2_buscar->setFont(font2);
        lineEdit_correo = new QLineEdit(centralwidget);
        lineEdit_correo->setObjectName("lineEdit_correo");
        lineEdit_correo->setGeometry(QRect(280, 90, 271, 31));
        lineEdit_correo->setFont(font1);
        comboBox_orden = new QComboBox(centralwidget);
        comboBox_orden->addItem(QString());
        comboBox_orden->addItem(QString());
        comboBox_orden->addItem(QString());
        comboBox_orden->addItem(QString());
        comboBox_orden->setObjectName("comboBox_orden");
        comboBox_orden->setGeometry(QRect(570, 90, 161, 31));
        comboBox_orden->setFont(font2);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 0, 291, 91));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Cascadia Mono SemiBold")});
        font3.setPointSize(20);
        font3.setBold(true);
        label->setFont(font3);
        AdminWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdminWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 811, 25));
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
        pushButton->setText(QCoreApplication::translate("AdminWindow", "Cerrar sesi\303\263n", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_usuarios->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AdminWindow", "Nombres", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_usuarios->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AdminWindow", "Apellidos", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_usuarios->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AdminWindow", "Correo", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_usuarios->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AdminWindow", "Nacimiento", nullptr));
        pushButton_2_buscar->setText(QCoreApplication::translate("AdminWindow", "Buscar", nullptr));
        lineEdit_correo->setText(QString());
        comboBox_orden->setItemText(0, QCoreApplication::translate("AdminWindow", "Ninguno", nullptr));
        comboBox_orden->setItemText(1, QCoreApplication::translate("AdminWindow", "Preorden", nullptr));
        comboBox_orden->setItemText(2, QCoreApplication::translate("AdminWindow", "Inorden", nullptr));
        comboBox_orden->setItemText(3, QCoreApplication::translate("AdminWindow", "Postorden", nullptr));

        label->setText(QCoreApplication::translate("AdminWindow", "SocialStructure", nullptr));
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
