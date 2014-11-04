#ifndef CACHEGUI_H
#define CACHEGUI_H

#include <QMainWindow>

namespace Ui {
class cachegui;
}

class cachegui : public QMainWindow
{
    Q_OBJECT

public:
    explicit cachegui(QWidget *parent = 0);
    ~cachegui();

private:
    Ui::cachegui *ui;
};

#endif // CACHEGUI_H
