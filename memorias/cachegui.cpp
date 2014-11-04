#include "cachegui.h"
#include "ui_cachegui.h"

cachegui::cachegui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cachegui)
{
    ui->setupUi(this);
}

cachegui::~cachegui()
{
    delete ui;
}



void cachegui::on_analisis_clicked()
{
    int bloquescache = ui->cacheblocks->value();
    int numerovias = ui->nvias->value();
    int numeromemp = ui->nmemp->value();
    int tampagina = ui->tampag->value();
    int tambloque = ui->tambloq->value();


}

void cachegui::on_Generar_clicked()
{
    int bloquescache = ui->cacheblocks->value();
    int numerovias = ui->nvias->value();
    int numeromemp = ui->nmemp->value();
    int tampagina = ui->tampag->value();
    int tambloque = ui->tambloq->value();
    if(tampagina > 32)
        QMessageBox::information(0, QString("Error"),QString("El tamaño de pagina no puede superar los 32 bytes") , QMessageBox::Ok);
    if(bloquescache % numerovias != 0)
        QMessageBox::information(0, QString("Error"),QString("El número de bloques debe ser divisible por el número de vías") , QMessageBox::Ok);
    if(1024 % tampagina != 0)
        QMessageBox::information(0, QString("Error"),QString("El tamaño de pagina debe dividir al tamaño de la memoria principal que es un 1KB") , QMessageBox::Ok);
    int fallospor = 20;
    QString fallospagvir;
    fallospagvir = QString("La tasa de fallos es de: ")+ QString::number(fallospor)+QString("%");
    QMessageBox::information(0, QString("Fallos Pagina Virtual"), fallospagvir, QMessageBox::Ok);
}
