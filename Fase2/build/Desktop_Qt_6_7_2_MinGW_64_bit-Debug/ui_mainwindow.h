/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_Usuario;
    QLineEdit *lineEdit_2_Password;
    QPushButton *pushButton_Login;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(606, 357);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 10, 431, 91));
        QFont font;
        font.setFamilies({QString::fromUtf8("Cascadia Mono SemiBold")});
        font.setPointSize(28);
        font.setBold(true);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 120, 151, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gill Sans MT")});
        font1.setPointSize(18);
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 210, 151, 51));
        label_3->setFont(font1);
        lineEdit_Usuario = new QLineEdit(centralwidget);
        lineEdit_Usuario->setObjectName("lineEdit_Usuario");
        lineEdit_Usuario->setGeometry(QRect(200, 130, 341, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans MT")});
        font2.setPointSize(16);
        lineEdit_Usuario->setFont(font2);
        lineEdit_2_Password = new QLineEdit(centralwidget);
        lineEdit_2_Password->setObjectName("lineEdit_2_Password");
        lineEdit_2_Password->setGeometry(QRect(200, 210, 341, 41));
        lineEdit_2_Password->setFont(font2);
        lineEdit_2_Password->setEchoMode(QLineEdit::EchoMode::Password);
        pushButton_Login = new QPushButton(centralwidget);
        pushButton_Login->setObjectName("pushButton_Login");
        pushButton_Login->setGeometry(QRect(290, 290, 151, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Gill Sans MT")});
        font3.setPointSize(12);
        pushButton_Login->setFont(font3);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Bienvenido", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "SocialStructure", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Usuario", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Contrase\303\261a", nullptr));
        pushButton_Login->setText(QCoreApplication::translate("MainWindow", "Ingresar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
