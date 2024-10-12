#include "imagewindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

ImageWindow::ImageWindow(const QString &imagePath, QWidget *parent) :
    QMainWindow(parent),
    graphicsView(new QGraphicsView(this)),
    scene(new QGraphicsScene(this))
{
    graphicsView->setScene(scene);

    QPixmap image(imagePath);

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(image);
    scene->addItem(item);

    graphicsView->setFixedSize(800, 600);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    graphicsView->setAlignment(Qt::AlignCenter);

    setCentralWidget(graphicsView);
}

ImageWindow::~ImageWindow()
{
    delete graphicsView;
}
