#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

class ImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageWindow(const QString &imagePath, QWidget *parent = nullptr);
    ~ImageWindow();

private:
    QGraphicsView *graphicsView;  // Para mostrar la imagen
    QGraphicsScene *scene; // Escena de gráficos
};

#endif // IMAGEWINDOW_H
