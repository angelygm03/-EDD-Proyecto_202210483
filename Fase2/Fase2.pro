QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    arbolb.cpp \
    avltree.cpp \
    binarysearchtree.cpp \
    comentario.cpp \
    doublelist.cpp \
    fechalist.cpp \
    fechanodo.cpp \
    friendlist.cpp \
    friendnode.cpp \
    imagewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    nodebst.cpp \
    nodedoublelist.cpp \
    signup.cpp \
    solicitudlist.cpp \
    stack.cpp \
    stacknode.cpp \
    userwindow.cpp

HEADERS += \
    adminwindow.h \
    arbolb.h \
    avltree.h \
    binarysearchtree.h \
    comentario.h \
    doublelist.h \
    fechalist.h \
    fechanodo.h \
    friendlist.h \
    friendnode.h \
    imagewindow.h \
    mainwindow.h \
    node.h \
    nodebst.h \
    nodedoublelist.h \
    signup.h \
    solicitudlist.h \
    stack.h \
    stacknode.h \
    userwindow.h

FORMS += \
    adminwindow.ui \
    imagewindow.ui \
    mainwindow.ui \
    signup.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
