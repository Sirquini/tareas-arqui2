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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QSpinBox *spinBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QDoubleSpinBox *Multi;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QDoubleSpinBox *Mono;
    QLabel *label_7;
    QPlainTextEdit *text_in;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Calcular;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *tcalc;
    QSpacerItem *horizontalSpacer;
    QPushButton *Traduction;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QTextBrowser *text_out;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLCDNumber *Multidsp;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLCDNumber *Monodsp;
    QLabel *label_10;
    QToolBar *mainToolBar;

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
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_5->addWidget(label);

        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);

        verticalLayout_5->addWidget(spinBox);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        Multi = new QDoubleSpinBox(tab);
        Multi->setObjectName(QStringLiteral("Multi"));

        horizontalLayout->addWidget(Multi);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout->addWidget(label_8);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        Mono = new QDoubleSpinBox(tab);
        Mono->setObjectName(QStringLiteral("Mono"));

        horizontalLayout_3->addWidget(Mono);

        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_3->addWidget(label_7);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(verticalLayout);

        text_in = new QPlainTextEdit(tab);
        text_in->setObjectName(QStringLiteral("text_in"));

        verticalLayout_5->addWidget(text_in);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Calcular = new QPushButton(tab);
        Calcular->setObjectName(QStringLiteral("Calcular"));

        horizontalLayout_2->addWidget(Calcular);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        tcalc = new QPushButton(tab);
        tcalc->setObjectName(QStringLiteral("tcalc"));

        horizontalLayout_2->addWidget(tcalc);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        Traduction = new QPushButton(tab);
        Traduction->setObjectName(QStringLiteral("Traduction"));
        Traduction->setAutoDefault(false);

        horizontalLayout_2->addWidget(Traduction);


        verticalLayout_5->addLayout(horizontalLayout_2);

        tab_text->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_3->addWidget(label_6);

        text_out = new QTextBrowser(tab_2);
        text_out->setObjectName(QStringLiteral("text_out"));

        verticalLayout_3->addWidget(text_out);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        Multidsp = new QLCDNumber(tab_2);
        Multidsp->setObjectName(QStringLiteral("Multidsp"));

        horizontalLayout_4->addWidget(Multidsp);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_4->addWidget(label_9);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        Monodsp = new QLCDNumber(tab_2);
        Monodsp->setObjectName(QStringLiteral("Monodsp"));

        horizontalLayout_5->addWidget(Monodsp);

        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_5->addWidget(label_10);


        horizontalLayout_6->addLayout(horizontalLayout_5);


        verticalLayout_4->addLayout(horizontalLayout_6);

        tab_text->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tab_text);

        GuiArqui2->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(GuiArqui2);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GuiArqui2->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(GuiArqui2);

        tab_text->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GuiArqui2);
    } // setupUi

    void retranslateUi(QMainWindow *GuiArqui2)
    {
        GuiArqui2->setWindowTitle(QApplication::translate("GuiArqui2", "Traductor Arqui 2", 0));
#ifndef QT_NO_TOOLTIP
        tab_text->setToolTip(QApplication::translate("GuiArqui2", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("GuiArqui2", "Linea de inicio del programa:", 0));
        label_3->setText(QApplication::translate("GuiArqui2", "Frecuencia Multiciclo:", 0));
        label_8->setText(QApplication::translate("GuiArqui2", "GHz", 0));
        label_2->setText(QApplication::translate("GuiArqui2", "Frecuencia Monociclo:", 0));
        label_7->setText(QApplication::translate("GuiArqui2", "GHz", 0));
        text_in->setPlainText(QApplication::translate("GuiArqui2", "Enter your code here", 0));
        Calcular->setText(QApplication::translate("GuiArqui2", "Calcular", 0));
        tcalc->setText(QApplication::translate("GuiArqui2", "Traducir y calcular", 0));
        Traduction->setText(QApplication::translate("GuiArqui2", "Traducir", 0));
        tab_text->setTabText(tab_text->indexOf(tab), QApplication::translate("GuiArqui2", "Input", 0));
        label_6->setText(QApplication::translate("GuiArqui2", "Codigo Traducido", 0));
        label_4->setText(QApplication::translate("GuiArqui2", "Tiempo Multiciclo", 0));
        label_9->setText(QApplication::translate("GuiArqui2", "ns", 0));
        label_5->setText(QApplication::translate("GuiArqui2", "Tiempo Monociclo", 0));
        label_10->setText(QApplication::translate("GuiArqui2", "ns", 0));
        tab_text->setTabText(tab_text->indexOf(tab_2), QApplication::translate("GuiArqui2", "Output", 0));
    } // retranslateUi

};

namespace Ui {
    class GuiArqui2: public Ui_GuiArqui2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIARQUI2_H
