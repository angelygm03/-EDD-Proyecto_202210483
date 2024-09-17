#include "publicacioneswindow.h"
#include "ui_publicacioneswindow.h"
#include "crearpublicacion.h"

Publicarwindow::Publicarwindow(QWidget *parent, const string &usuarioCorreo)
    : QMainWindow(parent)
    , ui(new Ui::Publicarwindow)
    , usuarioCorreo(usuarioCorreo)
    , publicacionesList(new DoubleList())
{
    ui->setupUi(this);
}

Publicarwindow::~Publicarwindow()
{
    delete ui;
}

void Publicarwindow::on_pushButton_2_crearPost_clicked()
{
    CrearPublicacion *crearpublicacion = new CrearPublicacion(this, usuarioCorreo, publicacionesList);
    crearpublicacion->show();
    this->hide();
}



