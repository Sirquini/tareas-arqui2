/********************************************************************************
** Form generated from reading UI file 'guiarqui2.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIARQUI2_H
#define UI_GUIARQUI2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiArqui2
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tab_text;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QPlainTextEdit *text_in;
    QPushButton *Traduction;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *text_out;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *GuiArqui2)
    {
        if (GuiArqui2->objectName().isEmpty())
            GuiArqui2->setObjectName(QString::fromUtf8("GuiArqui2"));
        GuiArqui2->resize(466, 587);
        centralWidget = new QWidget(GuiArqui2);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tab_text = new QTabWidget(centralWidget);
        tab_text->setObjectName(QString::fromUtf8("tab_text"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);

        verticalLayout->addWidget(spinBox);

        text_in = new QPlainTextEdit(tab);
        text_in->setObjectName(QString::fromUtf8("text_in"));

        verticalLayout->addWidget(text_in);

        Traduction = new QPushButton(tab);
        Traduction->setObjectName(QString::fromUtf8("Traduction"));
        Traduction->setAutoDefault(false);

        verticalLayout->addWidget(Traduction);

        tab_text->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        text_out = new QTextBrowser(tab_2);
        text_out->setObjectName(QString::fromUtf8("text_out"));

        verticalLayout_3->addWidget(text_out);

        tab_text->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tab_text);

        GuiArqui2->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(GuiArqui2);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GuiArqui2->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(GuiArqui2);

        tab_text->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GuiArqui2);
    } // setupUi

    void retranslateUi(QMainWindow *GuiArqui2)
    {
        GuiArqui2->setWindowTitle(QApplication::translate("GuiArqui2", "Traductor Arqui 2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tab_text->setToolTip(QApplication::translate("GuiArqui2", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("GuiArqui2", "Linea de inicio del programa:", 0, QApplication::UnicodeUTF8));
        text_in->setPlainText(QApplication::translate("GuiArqui2", "Enter your code here", 0, QApplication::UnicodeUTF8));
        Traduction->setText(QApplication::translate("GuiArqui2", "Traducir", 0, QApplication::UnicodeUTF8));
        tab_text->setTabText(tab_text->indexOf(tab), QApplication::translate("GuiArqui2", "Input", 0, QApplication::UnicodeUTF8));
        tab_text->setTabText(tab_text->indexOf(tab_2), QApplication::translate("GuiArqui2", "Output", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GuiArqui2: public Ui_GuiArqui2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIARQUI2_H
