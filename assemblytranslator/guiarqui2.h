#ifndef GUIARQUI2_H
#define GUIARQUI2_H

#include <QMainWindow>
 #include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>
#include <utility>

namespace Ui {
class GuiArqui2;
}

class GuiArqui2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiArqui2(QWidget *parent = 0);
    ~GuiArqui2();

private slots:
    void on_Traduction_clicked();


    //void on_text_in_textChanged();

private:
    Ui::GuiArqui2 *ui;
};

#endif // GUIARQUI2_H
