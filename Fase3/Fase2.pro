QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adjacencylist.cpp \
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
    huffman.cpp \
    imagewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    neighbor.cpp \
    node.cpp \
    nodebst.cpp \
    nodedoublelist.cpp \
    nodelist.cpp \
    signup.cpp \
    simplelist.cpp \
    solicitudlist.cpp \
    stack.cpp \
    stacknode.cpp \
    usernode.cpp \
    userwindow.cpp

HEADERS += \
    adjacencylist.h \
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
    huffman.h \
    huffmannode.h \
    imagewindow.h \
    mainwindow.h \
    neighbor.h \
    node.h \
    nodebst.h \
    nodedoublelist.h \
    nodelist.h \
    signup.h \
    simplelist.h \
    solicitudlist.h \
    stack.h \
    stacknode.h \
    usernode.h \
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
