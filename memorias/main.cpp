#include "cachegui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cachegui w;
    w.show();

    return a.exec();
}
