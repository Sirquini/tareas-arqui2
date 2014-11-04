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

    if(tampagina > 32)
        QMessageBox::critical(0, QString("Error"),QString("El tamaño de pagina no puede superar los 32 bytes") , QMessageBox::Ok);
    if(numerovias > 0 && (bloquescache % numerovias) != 0)
        QMessageBox::critical(0, QString("Error"),QString("El número de bloques debe ser divisible por el número de vías") , QMessageBox::Ok);
    if(tampagina > 0 && (1024 % tampagina) != 0)
        QMessageBox::critical(0, QString("Error"),QString("El tamaño de pagina debe dividir al tamaño de la memoria principal que es un 1KB") , QMessageBox::Ok);
    else if(bloquescache == 0 || numerovias == 0 || numeromemp == 0 || tampagina == 0 || tambloque == 0)
        QMessageBox::critical(0, QString("Error"),QString("Le falta ingresar uno o más datos") , QMessageBox::Ok);
    else
    {
        // generate some data:
        QVector<double> x(101), y(101); // initialize with entries 0..100
        for (int i=0; i<101; ++i)
        {
          x[i] = i/50.0 - 1; // x goes from -1 to 1
          y[i] = x[i]*x[i]; // let's plot a quadratic function
        }
        // create graph and assign data to it:
        ui->plot1->addGraph();
        ui->plot1->graph(0)->setData(x, y);
        // give the axes some labels:
        ui->plot1->xAxis->setLabel("Tamaño del bloque");
        ui->plot1->yAxis->setLabel("Tamaño de la cache");
        // set axes ranges, so we see all data:
        ui->plot1->xAxis->setRange(-1, 1);
        ui->plot1->yAxis->setRange(0, 1);
        ui->plot1->replot();
    
        // create graph and assign data to it:
        ui->plot2->addGraph();
        ui->plot2->graph(0)->setData(x, y);
        // give the axes some labels:
        ui->plot2->xAxis->setLabel("Número de vías");
        ui->plot2->yAxis->setLabel("Tamaño de la cache");
        // set axes ranges, so we see all data:
        ui->plot2->xAxis->setRange(-1, 1);
        ui->plot2->yAxis->setRange(0, 1);
    
        ui->plot2->replot();
    }
}

void cachegui::on_Generar_clicked()
{
    int bloquescache = ui->cacheblocks->value();
    int numerovias = ui->nvias->value();
    int numeromemp = ui->nmemp->value();
    int tampagina = ui->tampag->value();
    int tambloque = ui->tambloq->value();
    if(tampagina > 32)
        QMessageBox::critical(0, QString("Error"),QString("El tamaño de pagina no puede superar los 32 bytes") , QMessageBox::Ok);
    if(numerovias > 0 && (bloquescache % numerovias) != 0)
        QMessageBox::critical(0, QString("Error"),QString("El número de bloques debe ser divisible por el número de vías") , QMessageBox::Ok);
    if(tampagina > 0 && (1024 % tampagina) != 0)
        QMessageBox::critical(0, QString("Error"),QString("El tamaño de pagina debe dividir al tamaño de la memoria principal que es un 1KB") , QMessageBox::Ok);
    else if(bloquescache == 0 || numerovias == 0 || numeromemp == 0 || tampagina == 0 || tambloque == 0)
        QMessageBox::critical(0, QString("Error"),QString("Le falta ingresar uno o más datos") , QMessageBox::Ok);
    else
    {
        int fallospor = 20;
        QString fallospagvir;
        fallospagvir = QString("La tasa de fallos es de: ")+ QString::number(fallospor)+QString("%");
        QMessageBox::information(0, QString("Fallos Pagina Virtual"), fallospagvir, QMessageBox::Ok);
    }
}

