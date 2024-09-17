#include "crearpublicacion.h"
#include "ui_crearpublicacion.h"
#include <QFileDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QMessageBox>

CrearPublicacion::CrearPublicacion(QWidget *parent, const std::string &correoUsuario, DoubleList *list)
    : QMainWindow(parent),
    ui(new Ui::CrearPublicacion),
    publicacionesList(list),
    usuarioCorreo(correoUsuario)
{
    ui->setupUi(this);
}

CrearPublicacion::~CrearPublicacion()
{
    delete ui;
}

void CrearPublicacion::on_plainTextEdit_contenidoPost_textChanged()
{
    QString texto = ui->plainTextEdit_contenidoPost->toPlainText();
}


void CrearPublicacion::on_pushButton_abrirImg_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Abrir Imagen"), "", tr("Imágenes (*.png *.xpm *.jpg)"));
    if (!filePath.isEmpty())
    {
        QPixmap imagen(filePath);  // Cargar la imagen

        // Crear una escena para mostrar la imagen
        QGraphicsScene* scene = new QGraphicsScene(this);
        scene->addPixmap(imagen.scaled(ui->graphicsView_img->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        // Asignar la escena a la vista gráfica
        ui->graphicsView_img->setScene(scene);
    }
}


void CrearPublicacion::on_pushButton_2_postear_clicked()
{
    QString contenido = ui->plainTextEdit_contenidoPost->toPlainText();
    QString imagenPath;

    // Si hay una imagen seleccionada
    if (!ui->graphicsView_img->scene()->items().isEmpty()) {
        imagenPath = QFileDialog::getOpenFileName(this, tr("Seleccionar Imagen"), "", tr("Images (*.png *.jpeg *.jpg)"));
    }

    // Capturando la fecha y hora actuales
    QDateTime now = QDateTime::currentDateTime();
    QString fecha = now.toString("dd-MM-yyyy");
    QString hora = now.toString("hh:mm:ss");

    // Verificación de contenido no vacío
    if (contenido.isEmpty()) {
        QMessageBox::warning(this, "Error", "El contenido no puede estar vacío.");
        return;
    }

    // Se inserta en la lista de publicaciones
    publicacionesList->insertAtEnd(usuarioCorreo, contenido.toStdString(), fecha.toStdString(), hora.toStdString(), imagenPath.toStdString());

    QMessageBox::information(this, "Éxito", "Publicación creada exitosamente.");
    publicacionesList->print();
    this->close();
}

