/********************************************************************************
** Form generated from reading UI file 'userwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWINDOW_H
#define UI_USERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Userwindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_buscar;
    QLabel *label_6;
    QLineEdit *lineEdit_2_nombres;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_2_buscar;
    QLabel *label_5;
    QLineEdit *lineEdit_buscar;
    QLineEdit *lineEdit_4_correo;
    QLineEdit *lineEdit_3_apellidos;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit_5_fechanac;
    QPushButton *pushButton_2_agregar;
    QWidget *tab_2_publicaciones;
    QGroupBox *groupBox;
    QPlainTextEdit *plainTextEdit_contenidoPost;
    QPushButton *pushButton_abrirImg;
    QLabel *label_15;
    QGraphicsView *graphicsView_img;
    QPushButton *pushButton_2_publicar;
    QLabel *label_14;
    QGroupBox *groupBox_3;
    QDateEdit *dateEdit_fechaBST;
    QPushButton *pushButton_AplicarFecha;
    QGroupBox *groupBox_4;
    QComboBox *comboBox_2_recorrido;
    QPushButton *pushButton_3_recorridoAplicar;
    QGroupBox *groupBox_5;
    QPushButton *pushButton_6_verArbol;
    QPushButton *pushButton_4_comentar;
    QListWidget *listWidget_publicaciones;
    QPushButton *pushButton_4_Comments;
    QWidget *tab_3_solicitudes;
    QGroupBox *groupBox_2;
    QTableWidget *tableWidget_recibidas;
    QLabel *label_7;
    QLabel *label_19;
    QWidget *tab_4_reportes;
    QLabel *label_18;
    QGroupBox *groupBox_7;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLineEdit *lineEdit_2_top1fecha;
    QLineEdit *lineEdit_3_top2fecha;
    QLineEdit *lineEdit_4_top3fecha;
    QLabel *label_49;
    QLabel *label_50;
    QLineEdit *lineEdit_9_top2pub;
    QLabel *label_51;
    QLineEdit *lineEdit_10_top1pub;
    QLineEdit *lineEdit_11_top3pub;
    QGroupBox *groupBox_8;
    QGraphicsView *graphicsView_bst;
    QLabel *label_52;
    QPushButton *pushButton_7_reportes;
    QWidget *tab_5_perfil;
    QLineEdit *lineEdit_5_fechanacUsuario;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_3_apellidosUsuario;
    QLineEdit *lineEdit_4_correoUsuario;
    QLineEdit *lineEdit_2_nombreUsuario;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QPushButton *pushButton_2_eliminar;

    void setupUi(QMainWindow *Userwindow)
    {
        if (Userwindow->objectName().isEmpty())
            Userwindow->setObjectName("Userwindow");
        Userwindow->resize(979, 674);
        centralwidget = new QWidget(Userwindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 981, 661));
        tab_buscar = new QWidget();
        tab_buscar->setObjectName("tab_buscar");
        label_6 = new QLabel(tab_buscar);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(290, 10, 431, 91));
        QFont font;
        font.setFamilies({QString::fromUtf8("Cascadia Mono SemiBold")});
        font.setPointSize(24);
        font.setBold(true);
        label_6->setFont(font);
        lineEdit_2_nombres = new QLineEdit(tab_buscar);
        lineEdit_2_nombres->setObjectName("lineEdit_2_nombres");
        lineEdit_2_nombres->setEnabled(true);
        lineEdit_2_nombres->setGeometry(QRect(260, 240, 401, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gill Sans MT")});
        font1.setPointSize(14);
        lineEdit_2_nombres->setFont(font1);
        pushButton = new QPushButton(tab_buscar);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(820, 20, 101, 31));
        label_3 = new QLabel(tab_buscar);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(260, 300, 121, 21));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Cascadia Code SemiBold")});
        font2.setPointSize(14);
        font2.setBold(true);
        label_3->setFont(font2);
        label_4 = new QLabel(tab_buscar);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(260, 390, 121, 21));
        label_4->setFont(font2);
        pushButton_2_buscar = new QPushButton(tab_buscar);
        pushButton_2_buscar->setObjectName("pushButton_2_buscar");
        pushButton_2_buscar->setGeometry(QRect(580, 90, 83, 29));
        QFont font3;
        font3.setPointSize(12);
        pushButton_2_buscar->setFont(font3);
        label_5 = new QLabel(tab_buscar);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(260, 480, 251, 21));
        label_5->setFont(font2);
        lineEdit_buscar = new QLineEdit(tab_buscar);
        lineEdit_buscar->setObjectName("lineEdit_buscar");
        lineEdit_buscar->setGeometry(QRect(260, 90, 311, 31));
        lineEdit_buscar->setFont(font3);
        lineEdit_4_correo = new QLineEdit(tab_buscar);
        lineEdit_4_correo->setObjectName("lineEdit_4_correo");
        lineEdit_4_correo->setGeometry(QRect(260, 420, 401, 41));
        lineEdit_4_correo->setFont(font1);
        lineEdit_3_apellidos = new QLineEdit(tab_buscar);
        lineEdit_3_apellidos->setObjectName("lineEdit_3_apellidos");
        lineEdit_3_apellidos->setGeometry(QRect(260, 330, 401, 41));
        lineEdit_3_apellidos->setFont(font1);
        label_2 = new QLabel(tab_buscar);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 210, 121, 21));
        label_2->setFont(font2);
        label = new QLabel(tab_buscar);
        label->setObjectName("label");
        label->setGeometry(QRect(180, 160, 271, 21));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Cascadia Code SemiBold")});
        font4.setPointSize(16);
        font4.setBold(true);
        label->setFont(font4);
        lineEdit_5_fechanac = new QLineEdit(tab_buscar);
        lineEdit_5_fechanac->setObjectName("lineEdit_5_fechanac");
        lineEdit_5_fechanac->setGeometry(QRect(260, 510, 401, 41));
        lineEdit_5_fechanac->setFont(font1);
        pushButton_2_agregar = new QPushButton(tab_buscar);
        pushButton_2_agregar->setObjectName("pushButton_2_agregar");
        pushButton_2_agregar->setGeometry(QRect(260, 570, 401, 41));
        pushButton_2_agregar->setFont(font3);
        tabWidget->addTab(tab_buscar, QString());
        tab_2_publicaciones = new QWidget();
        tab_2_publicaciones->setObjectName("tab_2_publicaciones");
        groupBox = new QGroupBox(tab_2_publicaciones);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 70, 331, 391));
        groupBox->setFont(font3);
        plainTextEdit_contenidoPost = new QPlainTextEdit(groupBox);
        plainTextEdit_contenidoPost->setObjectName("plainTextEdit_contenidoPost");
        plainTextEdit_contenidoPost->setGeometry(QRect(20, 50, 291, 151));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe UI")});
        font5.setPointSize(12);
        plainTextEdit_contenidoPost->setFont(font5);
        pushButton_abrirImg = new QPushButton(groupBox);
        pushButton_abrirImg->setObjectName("pushButton_abrirImg");
        pushButton_abrirImg->setGeometry(QRect(200, 220, 111, 29));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Segoe UI")});
        font6.setPointSize(9);
        pushButton_abrirImg->setFont(font6);
        label_15 = new QLabel(groupBox);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(20, 210, 161, 51));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Cascadia Code SemiBold")});
        font7.setPointSize(9);
        font7.setBold(true);
        label_15->setFont(font7);
        graphicsView_img = new QGraphicsView(groupBox);
        graphicsView_img->setObjectName("graphicsView_img");
        graphicsView_img->setGeometry(QRect(20, 260, 171, 111));
        pushButton_2_publicar = new QPushButton(groupBox);
        pushButton_2_publicar->setObjectName("pushButton_2_publicar");
        pushButton_2_publicar->setGeometry(QRect(200, 260, 111, 31));
        pushButton_2_publicar->setFont(font6);
        label_14 = new QLabel(tab_2_publicaciones);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(320, -10, 311, 91));
        label_14->setFont(font);
        groupBox_3 = new QGroupBox(tab_2_publicaciones);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(30, 470, 151, 141));
        groupBox_3->setFont(font3);
        dateEdit_fechaBST = new QDateEdit(groupBox_3);
        dateEdit_fechaBST->setObjectName("dateEdit_fechaBST");
        dateEdit_fechaBST->setGeometry(QRect(10, 40, 131, 29));
        QFont font8;
        font8.setPointSize(10);
        dateEdit_fechaBST->setFont(font8);
        pushButton_AplicarFecha = new QPushButton(groupBox_3);
        pushButton_AplicarFecha->setObjectName("pushButton_AplicarFecha");
        pushButton_AplicarFecha->setGeometry(QRect(10, 90, 131, 29));
        QFont font9;
        font9.setPointSize(9);
        pushButton_AplicarFecha->setFont(font9);
        groupBox_4 = new QGroupBox(tab_2_publicaciones);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(210, 470, 151, 141));
        groupBox_4->setFont(font3);
        comboBox_2_recorrido = new QComboBox(groupBox_4);
        comboBox_2_recorrido->addItem(QString());
        comboBox_2_recorrido->addItem(QString());
        comboBox_2_recorrido->addItem(QString());
        comboBox_2_recorrido->addItem(QString());
        comboBox_2_recorrido->setObjectName("comboBox_2_recorrido");
        comboBox_2_recorrido->setGeometry(QRect(10, 40, 131, 28));
        comboBox_2_recorrido->setFont(font8);
        pushButton_3_recorridoAplicar = new QPushButton(groupBox_4);
        pushButton_3_recorridoAplicar->setObjectName("pushButton_3_recorridoAplicar");
        pushButton_3_recorridoAplicar->setGeometry(QRect(10, 90, 131, 29));
        pushButton_3_recorridoAplicar->setFont(font9);
        groupBox_5 = new QGroupBox(tab_2_publicaciones);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(400, 70, 551, 541));
        groupBox_5->setFont(font3);
        pushButton_6_verArbol = new QPushButton(groupBox_5);
        pushButton_6_verArbol->setObjectName("pushButton_6_verArbol");
        pushButton_6_verArbol->setGeometry(QRect(330, 480, 191, 31));
        pushButton_6_verArbol->setFont(font9);
        pushButton_4_comentar = new QPushButton(groupBox_5);
        pushButton_4_comentar->setObjectName("pushButton_4_comentar");
        pushButton_4_comentar->setGeometry(QRect(40, 480, 131, 31));
        pushButton_4_comentar->setFont(font9);
        listWidget_publicaciones = new QListWidget(groupBox_5);
        listWidget_publicaciones->setObjectName("listWidget_publicaciones");
        listWidget_publicaciones->setGeometry(QRect(40, 60, 481, 391));
        pushButton_4_Comments = new QPushButton(groupBox_5);
        pushButton_4_Comments->setObjectName("pushButton_4_Comments");
        pushButton_4_Comments->setGeometry(QRect(180, 480, 141, 31));
        pushButton_4_Comments->setFont(font9);
        tabWidget->addTab(tab_2_publicaciones, QString());
        tab_3_solicitudes = new QWidget();
        tab_3_solicitudes->setObjectName("tab_3_solicitudes");
        groupBox_2 = new QGroupBox(tab_3_solicitudes);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(210, 190, 551, 221));
        groupBox_2->setFont(font3);
        tableWidget_recibidas = new QTableWidget(groupBox_2);
        if (tableWidget_recibidas->columnCount() < 4)
            tableWidget_recibidas->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_recibidas->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_recibidas->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_recibidas->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_recibidas->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_recibidas->setObjectName("tableWidget_recibidas");
        tableWidget_recibidas->setGeometry(QRect(20, 40, 501, 171));
        label_7 = new QLabel(tab_3_solicitudes);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(330, 0, 351, 91));
        label_7->setFont(font);
        label_19 = new QLabel(tab_3_solicitudes);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(120, 60, 931, 91));
        label_19->setFont(font);
        tabWidget->addTab(tab_3_solicitudes, QString());
        tab_4_reportes = new QWidget();
        tab_4_reportes->setObjectName("tab_4_reportes");
        label_18 = new QLabel(tab_4_reportes);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(400, 0, 201, 91));
        label_18->setFont(font);
        groupBox_7 = new QGroupBox(tab_4_reportes);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(20, 180, 381, 431));
        groupBox_7->setFont(font8);
        label_20 = new QLabel(groupBox_7);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(10, 40, 281, 20));
        label_21 = new QLabel(groupBox_7);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 240, 281, 20));
        label_22 = new QLabel(groupBox_7);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 80, 21, 31));
        QFont font10;
        font10.setPointSize(15);
        label_22->setFont(font10);
        label_23 = new QLabel(groupBox_7);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 130, 21, 31));
        label_23->setFont(font10);
        label_24 = new QLabel(groupBox_7);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 180, 21, 31));
        label_24->setFont(font10);
        lineEdit_2_top1fecha = new QLineEdit(groupBox_7);
        lineEdit_2_top1fecha->setObjectName("lineEdit_2_top1fecha");
        lineEdit_2_top1fecha->setGeometry(QRect(40, 80, 301, 31));
        QFont font11;
        font11.setPointSize(11);
        lineEdit_2_top1fecha->setFont(font11);
        lineEdit_3_top2fecha = new QLineEdit(groupBox_7);
        lineEdit_3_top2fecha->setObjectName("lineEdit_3_top2fecha");
        lineEdit_3_top2fecha->setGeometry(QRect(40, 130, 301, 31));
        lineEdit_3_top2fecha->setFont(font11);
        lineEdit_4_top3fecha = new QLineEdit(groupBox_7);
        lineEdit_4_top3fecha->setObjectName("lineEdit_4_top3fecha");
        lineEdit_4_top3fecha->setGeometry(QRect(40, 180, 301, 31));
        lineEdit_4_top3fecha->setFont(font11);
        label_49 = new QLabel(groupBox_7);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(10, 380, 21, 31));
        label_49->setFont(font10);
        label_50 = new QLabel(groupBox_7);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(10, 280, 21, 31));
        label_50->setFont(font10);
        lineEdit_9_top2pub = new QLineEdit(groupBox_7);
        lineEdit_9_top2pub->setObjectName("lineEdit_9_top2pub");
        lineEdit_9_top2pub->setGeometry(QRect(40, 330, 301, 31));
        lineEdit_9_top2pub->setFont(font11);
        label_51 = new QLabel(groupBox_7);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(10, 330, 21, 31));
        label_51->setFont(font10);
        lineEdit_10_top1pub = new QLineEdit(groupBox_7);
        lineEdit_10_top1pub->setObjectName("lineEdit_10_top1pub");
        lineEdit_10_top1pub->setGeometry(QRect(40, 280, 301, 31));
        lineEdit_10_top1pub->setFont(font11);
        lineEdit_11_top3pub = new QLineEdit(groupBox_7);
        lineEdit_11_top3pub->setObjectName("lineEdit_11_top3pub");
        lineEdit_11_top3pub->setGeometry(QRect(40, 380, 301, 31));
        lineEdit_11_top3pub->setFont(font11);
        groupBox_8 = new QGroupBox(tab_4_reportes);
        groupBox_8->setObjectName("groupBox_8");
        groupBox_8->setGeometry(QRect(410, 180, 551, 431));
        groupBox_8->setFont(font8);
        graphicsView_bst = new QGraphicsView(groupBox_8);
        graphicsView_bst->setObjectName("graphicsView_bst");
        graphicsView_bst->setGeometry(QRect(10, 30, 531, 391));
        label_52 = new QLabel(tab_4_reportes);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(170, 70, 711, 41));
        QFont font12;
        font12.setFamilies({QString::fromUtf8("Cascadia Code")});
        font12.setPointSize(15);
        label_52->setFont(font12);
        pushButton_7_reportes = new QPushButton(tab_4_reportes);
        pushButton_7_reportes->setObjectName("pushButton_7_reportes");
        pushButton_7_reportes->setGeometry(QRect(380, 120, 181, 31));
        pushButton_7_reportes->setFont(font11);
        tabWidget->addTab(tab_4_reportes, QString());
        tab_5_perfil = new QWidget();
        tab_5_perfil->setObjectName("tab_5_perfil");
        lineEdit_5_fechanacUsuario = new QLineEdit(tab_5_perfil);
        lineEdit_5_fechanacUsuario->setObjectName("lineEdit_5_fechanacUsuario");
        lineEdit_5_fechanacUsuario->setGeometry(QRect(260, 480, 401, 41));
        lineEdit_5_fechanacUsuario->setFont(font1);
        label_8 = new QLabel(tab_5_perfil);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(260, 270, 121, 21));
        label_8->setFont(font2);
        label_9 = new QLabel(tab_5_perfil);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(180, 130, 271, 21));
        label_9->setFont(font4);
        label_10 = new QLabel(tab_5_perfil);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(260, 180, 121, 21));
        label_10->setFont(font2);
        lineEdit_3_apellidosUsuario = new QLineEdit(tab_5_perfil);
        lineEdit_3_apellidosUsuario->setObjectName("lineEdit_3_apellidosUsuario");
        lineEdit_3_apellidosUsuario->setGeometry(QRect(260, 300, 401, 41));
        lineEdit_3_apellidosUsuario->setFont(font1);
        lineEdit_4_correoUsuario = new QLineEdit(tab_5_perfil);
        lineEdit_4_correoUsuario->setObjectName("lineEdit_4_correoUsuario");
        lineEdit_4_correoUsuario->setGeometry(QRect(260, 390, 401, 41));
        lineEdit_4_correoUsuario->setFont(font1);
        lineEdit_2_nombreUsuario = new QLineEdit(tab_5_perfil);
        lineEdit_2_nombreUsuario->setObjectName("lineEdit_2_nombreUsuario");
        lineEdit_2_nombreUsuario->setEnabled(true);
        lineEdit_2_nombreUsuario->setGeometry(QRect(260, 210, 401, 41));
        lineEdit_2_nombreUsuario->setFont(font1);
        label_11 = new QLabel(tab_5_perfil);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(260, 360, 121, 21));
        label_11->setFont(font2);
        label_12 = new QLabel(tab_5_perfil);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(260, 450, 251, 21));
        label_12->setFont(font2);
        label_13 = new QLabel(tab_5_perfil);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(340, 10, 251, 91));
        label_13->setFont(font);
        pushButton_2_eliminar = new QPushButton(tab_5_perfil);
        pushButton_2_eliminar->setObjectName("pushButton_2_eliminar");
        pushButton_2_eliminar->setGeometry(QRect(260, 540, 401, 41));
        pushButton_2_eliminar->setFont(font3);
        tabWidget->addTab(tab_5_perfil, QString());
        Userwindow->setCentralWidget(centralwidget);

        retranslateUi(Userwindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Userwindow);
    } // setupUi

    void retranslateUi(QMainWindow *Userwindow)
    {
        Userwindow->setWindowTitle(QCoreApplication::translate("Userwindow", "SocialStructure", nullptr));
        label_6->setText(QCoreApplication::translate("Userwindow", "SocialStructure", nullptr));
        lineEdit_2_nombres->setText(QString());
        pushButton->setText(QCoreApplication::translate("Userwindow", "Cerrar sesi\303\263n", nullptr));
        label_3->setText(QCoreApplication::translate("Userwindow", "Apellidos", nullptr));
        label_4->setText(QCoreApplication::translate("Userwindow", "Correo", nullptr));
        pushButton_2_buscar->setText(QCoreApplication::translate("Userwindow", "Buscar", nullptr));
        label_5->setText(QCoreApplication::translate("Userwindow", "Fecha de nacimiento", nullptr));
        lineEdit_buscar->setText(QString());
        label_2->setText(QCoreApplication::translate("Userwindow", "Nombres", nullptr));
        label->setText(QCoreApplication::translate("Userwindow", "Datos del usuario", nullptr));
        pushButton_2_agregar->setText(QCoreApplication::translate("Userwindow", "Agregar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_buscar), QCoreApplication::translate("Userwindow", "Buscar", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Userwindow", "Nueva publicaci\303\263n", nullptr));
        plainTextEdit_contenidoPost->setPlainText(QString());
        pushButton_abrirImg->setText(QCoreApplication::translate("Userwindow", "Abrir", nullptr));
        label_15->setText(QCoreApplication::translate("Userwindow", "Agrega una imagen", nullptr));
        pushButton_2_publicar->setText(QCoreApplication::translate("Userwindow", "Publicar", nullptr));
        label_14->setText(QCoreApplication::translate("Userwindow", "Publicaciones", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Userwindow", "Fecha", nullptr));
        pushButton_AplicarFecha->setText(QCoreApplication::translate("Userwindow", "Aplicar", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("Userwindow", "Recorrido", nullptr));
        comboBox_2_recorrido->setItemText(0, QCoreApplication::translate("Userwindow", "Ninguno", nullptr));
        comboBox_2_recorrido->setItemText(1, QCoreApplication::translate("Userwindow", "Preorden", nullptr));
        comboBox_2_recorrido->setItemText(2, QCoreApplication::translate("Userwindow", "Inorden", nullptr));
        comboBox_2_recorrido->setItemText(3, QCoreApplication::translate("Userwindow", "Postorden", nullptr));

        pushButton_3_recorridoAplicar->setText(QCoreApplication::translate("Userwindow", "Aplicar", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("Userwindow", "Feed", nullptr));
        pushButton_6_verArbol->setText(QCoreApplication::translate("Userwindow", "Ver \303\241rbol de comentarios ", nullptr));
        pushButton_4_comentar->setText(QCoreApplication::translate("Userwindow", "Comentar", nullptr));
        pushButton_4_Comments->setText(QCoreApplication::translate("Userwindow", "Ver comentarios", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2_publicaciones), QCoreApplication::translate("Userwindow", "Publicaciones", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Userwindow", "Solicitudes recibidas", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_recibidas->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Userwindow", "Emisor", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_recibidas->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Userwindow", "Estado", nullptr));
        label_7->setText(QCoreApplication::translate("Userwindow", "SocialStructure", nullptr));
        label_19->setText(QCoreApplication::translate("Userwindow", "\302\241Haz nuevos amigos y comparte con ellos!", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3_solicitudes), QCoreApplication::translate("Userwindow", "Solicitudes", nullptr));
        label_18->setText(QCoreApplication::translate("Userwindow", "Reportes", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("Userwindow", "Top 3", nullptr));
        label_20->setText(QCoreApplication::translate("Userwindow", "Fechas con m\303\241s publicaciones", nullptr));
        label_21->setText(QCoreApplication::translate("Userwindow", "Publicaciones con m\303\241s comentarios", nullptr));
        label_22->setText(QCoreApplication::translate("Userwindow", "1.", nullptr));
        label_23->setText(QCoreApplication::translate("Userwindow", "2.", nullptr));
        label_24->setText(QCoreApplication::translate("Userwindow", "3.", nullptr));
        lineEdit_2_top1fecha->setText(QString());
        lineEdit_3_top2fecha->setText(QString());
        lineEdit_4_top3fecha->setText(QString());
        label_49->setText(QCoreApplication::translate("Userwindow", "3.", nullptr));
        label_50->setText(QCoreApplication::translate("Userwindow", "1.", nullptr));
        lineEdit_9_top2pub->setText(QString());
        label_51->setText(QCoreApplication::translate("Userwindow", "2.", nullptr));
        lineEdit_10_top1pub->setText(QString());
        lineEdit_11_top3pub->setText(QString());
        groupBox_8->setTitle(QCoreApplication::translate("Userwindow", "\303\201rbol BST", nullptr));
        label_52->setText(QCoreApplication::translate("Userwindow", "Observa los reportes y estad\303\255sticas del sistema", nullptr));
        pushButton_7_reportes->setText(QCoreApplication::translate("Userwindow", "Generar reportes", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4_reportes), QCoreApplication::translate("Userwindow", "Reportes", nullptr));
        label_8->setText(QCoreApplication::translate("Userwindow", "Apellidos", nullptr));
        label_9->setText(QCoreApplication::translate("Userwindow", "Datos del usuario", nullptr));
        label_10->setText(QCoreApplication::translate("Userwindow", "Nombres", nullptr));
        lineEdit_2_nombreUsuario->setText(QString());
        label_11->setText(QCoreApplication::translate("Userwindow", "Correo", nullptr));
        label_12->setText(QCoreApplication::translate("Userwindow", "Fecha de nacimiento", nullptr));
        label_13->setText(QCoreApplication::translate("Userwindow", "Mi Perfil", nullptr));
        pushButton_2_eliminar->setText(QCoreApplication::translate("Userwindow", "Eliminar Perfil", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5_perfil), QCoreApplication::translate("Userwindow", "Perfil", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Userwindow: public Ui_Userwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWINDOW_H
