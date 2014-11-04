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
