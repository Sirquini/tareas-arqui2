#ifndef CACHEGUI_H
#define CACHEGUI_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <iostream>
#include "qcustomplot.h"

namespace Ui {
class cachegui;
}

class cachegui : public QMainWindow
{
    Q_OBJECT

public:
    explicit cachegui(QWidget *parent = 0);
    ~cachegui();

private slots:
    void on_analisis_clicked();

    void on_Generar_clicked();

private:
    Ui::cachegui *ui;
};

#endif // CACHEGUI_H
