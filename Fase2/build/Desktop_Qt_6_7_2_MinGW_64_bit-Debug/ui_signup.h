/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton_aceptar;
    QLineEdit *lineEdit_nombre;
    QLineEdit *lineEdit_2_apellido;
    QLineEdit *lineEdit_3_correo;
    QLineEdit *lineEdit_4_password;
    QDateEdit *dateEdit_fechaNac;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(481, 595);
        centralwidget = new QWidget(SignUp);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(90, -10, 431, 91));
        QFont font;
        font.setFamilies({QString::fromUtf8("Cascadia Mono SemiBold")});
        font.setPointSize(28);
        font.setBold(true);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(170, 40, 241, 91));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Cascadia Mono SemiBold")});
        font1.setPointSize(18);
        font1.setBold(true);
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 110, 81, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans MT")});
        font2.setPointSize(14);
        label_3->setFont(font2);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 200, 81, 31));
        label_4->setFont(font2);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 290, 81, 31));
        label_5->setFont(font2);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(50, 380, 111, 31));
        label_6->setFont(font2);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(50, 470, 211, 31));
        label_7->setFont(font2);
        pushButton_aceptar = new QPushButton(centralwidget);
        pushButton_aceptar->setObjectName("pushButton_aceptar");
        pushButton_aceptar->setGeometry(QRect(160, 530, 201, 31));
        QFont font3;
        font3.setPointSize(11);
        pushButton_aceptar->setFont(font3);
        lineEdit_nombre = new QLineEdit(centralwidget);
        lineEdit_nombre->setObjectName("lineEdit_nombre");
        lineEdit_nombre->setGeometry(QRect(50, 140, 391, 41));
        QFont font4;
        font4.setPointSize(14);
        lineEdit_nombre->setFont(font4);
        lineEdit_2_apellido = new QLineEdit(centralwidget);
        lineEdit_2_apellido->setObjectName("lineEdit_2_apellido");
        lineEdit_2_apellido->setGeometry(QRect(50, 230, 391, 41));
        lineEdit_2_apellido->setFont(font4);
        lineEdit_3_correo = new QLineEdit(centralwidget);
        lineEdit_3_correo->setObjectName("lineEdit_3_correo");
        lineEdit_3_correo->setGeometry(QRect(50, 320, 391, 41));
        lineEdit_3_correo->setFont(font4);
        lineEdit_4_password = new QLineEdit(centralwidget);
        lineEdit_4_password->setObjectName("lineEdit_4_password");
        lineEdit_4_password->setGeometry(QRect(50, 410, 391, 41));
        lineEdit_4_password->setFont(font4);
        lineEdit_4_password->setAutoFillBackground(false);
        lineEdit_4_password->setInputMethodHints(Qt::InputMethodHint::ImhHiddenText|Qt::InputMethodHint::ImhNoAutoUppercase|Qt::InputMethodHint::ImhNoPredictiveText|Qt::InputMethodHint::ImhSensitiveData);
        dateEdit_fechaNac = new QDateEdit(centralwidget);
        dateEdit_fechaNac->setObjectName("dateEdit_fechaNac");
        dateEdit_fechaNac->setGeometry(QRect(280, 470, 161, 31));
        QFont font5;
        font5.setPointSize(12);
        dateEdit_fechaNac->setFont(font5);
        SignUp->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SignUp);
        statusbar->setObjectName("statusbar");
        SignUp->setStatusBar(statusbar);

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QMainWindow *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "Registro", nullptr));
        label->setText(QCoreApplication::translate("SignUp", "SocialStructure", nullptr));
        label_2->setText(QCoreApplication::translate("SignUp", "-Reg\303\255strate-", nullptr));
        label_3->setText(QCoreApplication::translate("SignUp", "Nombre", nullptr));
        label_4->setText(QCoreApplication::translate("SignUp", "Apellido", nullptr));
        label_5->setText(QCoreApplication::translate("SignUp", "Correo", nullptr));
        label_6->setText(QCoreApplication::translate("SignUp", "Contrase\303\261a", nullptr));
        label_7->setText(QCoreApplication::translate("SignUp", "Fecha de Nacimiento", nullptr));
        pushButton_aceptar->setText(QCoreApplication::translate("SignUp", "Aceptar", nullptr));
        lineEdit_nombre->setText(QString());
        lineEdit_2_apellido->setText(QString());
        lineEdit_3_correo->setText(QString());
        lineEdit_4_password->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
