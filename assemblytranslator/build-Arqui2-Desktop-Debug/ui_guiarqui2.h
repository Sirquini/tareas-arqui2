/********************************************************************************
** Form generated from reading UI file 'guiarqui2.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIARQUI2_H
#define UI_GUIARQUI2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiArqui2
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tab_text;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *text_in;
    QPushButton *Traduction;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *text_out;
    QMenuBar *menuBar;
    QMenu *menuTraductor;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GuiArqui2)
    {
        if (GuiArqui2->objectName().isEmpty())
            GuiArqui2->setObjectName(QStringLiteral("GuiArqui2"));
        GuiArqui2->resize(466, 587);
        centralWidget = new QWidget(GuiArqui2);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tab_text = new QTabWidget(centralWidget);
        tab_text->setObjectName(QStringLiteral("tab_text"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        text_in = new QPlainTextEdit(tab);
        text_in->setObjectName(QStringLiteral("text_in"));

        verticalLayout->addWidget(text_in);

        Traduction = new QPushButton(tab);
        Traduction->setObjectName(QStringLiteral("Traduction"));
        Traduction->setAutoDefault(false);

        verticalLayout->addWidget(Traduction);

        tab_text->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        text_out = new QTextBrowser(tab_2);
        text_out->setObjectName(QStringLiteral("text_out"));

        verticalLayout_3->addWidget(text_out);

        tab_text->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tab_text);

        GuiArqui2->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GuiArqui2);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 466, 25));
        menuTraductor = new QMenu(menuBar);
        menuTraductor->setObjectName(QStringLiteral("menuTraductor"));
        GuiArqui2->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GuiArqui2);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GuiArqui2->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GuiArqui2);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GuiArqui2->setStatusBar(statusBar);

        menuBar->addAction(menuTraductor->menuAction());

        retranslateUi(GuiArqui2);

        tab_text->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GuiArqui2);
    } // setupUi

    void retranslateUi(QMainWindow *GuiArqui2)
    {
        GuiArqui2->setWindowTitle(QApplication::translate("GuiArqui2", "GuiArqui2", 0));
#ifndef QT_NO_TOOLTIP
        tab_text->setToolTip(QApplication::translate("GuiArqui2", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        text_in->setPlainText(QApplication::translate("GuiArqui2", "Enter your code here", 0));
        Traduction->setText(QApplication::translate("GuiArqui2", "Traducir", 0));
        tab_text->setTabText(tab_text->indexOf(tab), QApplication::translate("GuiArqui2", "Tab 1", 0));
        tab_text->setTabText(tab_text->indexOf(tab_2), QApplication::translate("GuiArqui2", "Tab 2", 0));
        menuTraductor->setTitle(QApplication::translate("GuiArqui2", "Traductor", 0));
    } // retranslateUi

};

namespace Ui {
    class GuiArqui2: public Ui_GuiArqui2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIARQUI2_H
