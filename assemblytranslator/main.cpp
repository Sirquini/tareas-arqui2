#include "guiarqui2.h"
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <iostream>
#include <string>
//#include <unordered_map>
#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>
#include <utility>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuiArqui2 w;
    w.show();

    return a.exec();
}
