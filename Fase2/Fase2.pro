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
    comentario.cpp \
    doublelist.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    nodedoublelist.cpp \
    solicitudlist.cpp \
    stack.cpp \
    stacknode.cpp \
    userwindow.cpp

HEADERS += \
    adminwindow.h \
    arbolb.h \
    avltree.h \
    comentario.h \
    doublelist.h \
    mainwindow.h \
    node.h \
    nodedoublelist.h \
    solicitudlist.h \
    stack.h \
    stacknode.h \
    userwindow.h

FORMS += \
    adminwindow.ui \
    mainwindow.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
