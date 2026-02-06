/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDoubleSpinBox *spinKp;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QDoubleSpinBox *spinTi;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QDoubleSpinBox *spinTd;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelRozniczka;
    QComboBox *boxRozniczka;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QComboBox *comboTyp;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QSpinBox *spinAmp;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QSpinBox *spinOkres;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QDoubleSpinBox *spinWypelnienie;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QSpinBox *spinInterwal;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QDoubleSpinBox *spinStala;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnUstawieniaARX;
    QPushButton *btnResetCalki;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnReset;
    QPushButton *btnZapisz;
    QPushButton *btnWczytaj;
    QGroupBox *STATUS;
    QGridLayout *gridLayout_4;
    QLabel *lblCzas;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_4;
    QCustomPlot *chartWykres1;
    QHBoxLayout *horizontalLayout_12;
    QCustomPlot *chartWykres2;
    QCustomPlot *chartwykres3;
    QCustomPlot *chartWykres4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1300, 800);
        MainWindow->setMinimumSize(QSize(1300, 800));
        MainWindow->setStyleSheet(QString::fromUtf8("/* --- G\305\201\303\223WNE T\305\201O --- */\n"
"QMainWindow, QWidget#centralWidget {\n"
"    background-color: #2b2b2b;\n"
"    color: #f0f0f0;\n"
"}\n"
"\n"
"/* --- LEWY PANEL (Kontenery) --- */\n"
"QGroupBox {\n"
"    background-color: #333333;\n"
"    border: 1px solid #555555;\n"
"    border-radius: 6px;\n"
"    margin-top: 22px; /* Miejsce na tytu\305\202 */\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 5px;\n"
"    color: #4da6ff; /* Niebieski kolor tytu\305\202\303\263w */\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"/* --- POLA EDYCJI I ETYKIETY --- */\n"
"\n"
"QLabel {\n"
"    color: #dddddd;\n"
"    background-color: transparent; /* \305\273eby nie mia\305\202y t\305\202a rodzica */\n"
"    border: none;\n"
"}\n"
"\n"
"\n"
"QDoubleSpinBox, QSpinBox, QComboBox {\n"
"    background-color: #454545;\n"
"    border: 1px solid #666666;\n"
"    border-radius: 3px;\n"
"    padding: 4px;\n"
""
                        "    color: #ffffff;\n"
"    selection-background-color: #4da6ff;\n"
"}\n"
"\n"
"QDoubleSpinBox:hover, QSpinBox:hover, QComboBox:hover {\n"
"    border: 1px solid #4da6ff;\n"
"}\n"
"\n"
"/* --- PRZYCISKI (D\303\263\305\202 ekranu) --- */\n"
"QPushButton {\n"
"    background-color: #404040;\n"
"    border: 1px solid #555555;\n"
"    border-radius: 4px;\n"
"    color: white;\n"
"    padding: 6px 12px;\n"
"    min-height: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #505050;\n"
"    border: 1px solid #4da6ff;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #2a2a2a;\n"
"}\n"
"\n"
"/* Specjalne kolory dla wa\305\274nych przycisk\303\263w (po ObjectName) */\n"
"QPushButton#btnStart {\n"
"    background-color: #2e7d32; /* Zielony */\n"
"    border-color: #4caf50;\n"
"}\n"
"QPushButton#btnStart:hover { background-color: #388e3c; }\n"
"\n"
"QPushButton#btnStop {\n"
"    background-color: #c62828; /* Czerwony */\n"
"    border-color: #ef5350;\n"
"}\n"
"QPushButton#btnStop:hover { back"
                        "ground-color: #d32f2f; }\n"
"\n"
"/* --- Pasek Stanu --- */\n"
"QStatusBar {\n"
"    background-color: #202020;\n"
"    color: #aaaaaa;\n"
"    border-top: 1px solid #444;\n"
"}\n"
"\n"
"/* --- WYKRESY (QCustomPlot) --- */\n"
"/* Wa\305\274ne: QCustomPlot rysuje w\305\202asne t\305\202o w C++. \n"
"   Ustawiamy tu border, \305\274eby wida\304\207 by\305\202o granice widgetu. */\n"
"QCustomPlot {\n"
"    border: 1px solid #555555;\n"
"    border-radius: 4px;\n"
"    background-color: #1e1e1e; \n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(groupBox_3);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label);

        spinKp = new QDoubleSpinBox(groupBox_3);
        spinKp->setObjectName("spinKp");
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinKp->sizePolicy().hasHeightForWidth());
        spinKp->setSizePolicy(sizePolicy2);
        spinKp->setMaximum(100.000000000000000);
        spinKp->setSingleStep(0.100000000000000);

        horizontalLayout_2->addWidget(spinKp);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        spinTi = new QDoubleSpinBox(groupBox_3);
        spinTi->setObjectName("spinTi");
        sizePolicy2.setHeightForWidth(spinTi->sizePolicy().hasHeightForWidth());
        spinTi->setSizePolicy(sizePolicy2);
        spinTi->setMaximum(100.000000000000000);
        spinTi->setSingleStep(0.100000000000000);

        horizontalLayout_3->addWidget(spinTi);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_3);

        spinTd = new QDoubleSpinBox(groupBox_3);
        spinTd->setObjectName("spinTd");
        sizePolicy2.setHeightForWidth(spinTd->sizePolicy().hasHeightForWidth());
        spinTd->setSizePolicy(sizePolicy2);
        spinTd->setSingleStep(0.010000000000000);

        horizontalLayout_4->addWidget(spinTd);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        labelRozniczka = new QLabel(groupBox_3);
        labelRozniczka->setObjectName("labelRozniczka");
        sizePolicy1.setHeightForWidth(labelRozniczka->sizePolicy().hasHeightForWidth());
        labelRozniczka->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(labelRozniczka);

        boxRozniczka = new QComboBox(groupBox_3);
        boxRozniczka->addItem(QString());
        boxRozniczka->addItem(QString());
        boxRozniczka->setObjectName("boxRozniczka");
        sizePolicy1.setHeightForWidth(boxRozniczka->sizePolicy().hasHeightForWidth());
        boxRozniczka->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(boxRozniczka);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(label_4);

        comboTyp = new QComboBox(groupBox_2);
        comboTyp->addItem(QString());
        comboTyp->addItem(QString());
        comboTyp->setObjectName("comboTyp");
        sizePolicy1.setHeightForWidth(comboTyp->sizePolicy().hasHeightForWidth());
        comboTyp->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(comboTyp);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(label_5);

        spinAmp = new QSpinBox(groupBox_2);
        spinAmp->setObjectName("spinAmp");
        sizePolicy2.setHeightForWidth(spinAmp->sizePolicy().hasHeightForWidth());
        spinAmp->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(spinAmp);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(label_6);

        spinOkres = new QSpinBox(groupBox_2);
        spinOkres->setObjectName("spinOkres");
        sizePolicy2.setHeightForWidth(spinOkres->sizePolicy().hasHeightForWidth());
        spinOkres->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(spinOkres);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(label_7);

        spinWypelnienie = new QDoubleSpinBox(groupBox_2);
        spinWypelnienie->setObjectName("spinWypelnienie");
        sizePolicy2.setHeightForWidth(spinWypelnienie->sizePolicy().hasHeightForWidth());
        spinWypelnienie->setSizePolicy(sizePolicy2);
        spinWypelnienie->setMaximum(1.000000000000000);
        spinWypelnienie->setSingleStep(0.100000000000000);

        horizontalLayout_9->addWidget(spinWypelnienie);


        verticalLayout_2->addLayout(horizontalLayout_9);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(label_8);

        spinInterwal = new QSpinBox(groupBox);
        spinInterwal->setObjectName("spinInterwal");
        sizePolicy2.setHeightForWidth(spinInterwal->sizePolicy().hasHeightForWidth());
        spinInterwal->setSizePolicy(sizePolicy2);
        spinInterwal->setMinimum(10);
        spinInterwal->setMaximum(1000);
        spinInterwal->setSingleStep(10);
        spinInterwal->setValue(200);

        horizontalLayout_10->addWidget(spinInterwal);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(label_9);

        spinStala = new QDoubleSpinBox(groupBox);
        spinStala->setObjectName("spinStala");
        sizePolicy2.setHeightForWidth(spinStala->sizePolicy().hasHeightForWidth());
        spinStala->setSizePolicy(sizePolicy2);
        spinStala->setMinimum(-100.000000000000000);
        spinStala->setMaximum(100.000000000000000);

        horizontalLayout_11->addWidget(spinStala);


        verticalLayout_3->addLayout(horizontalLayout_11);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnUstawieniaARX = new QPushButton(centralwidget);
        btnUstawieniaARX->setObjectName("btnUstawieniaARX");

        horizontalLayout->addWidget(btnUstawieniaARX);

        btnResetCalki = new QPushButton(centralwidget);
        btnResetCalki->setObjectName("btnResetCalki");

        horizontalLayout->addWidget(btnResetCalki);

        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName("btnStart");

        horizontalLayout->addWidget(btnStart);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName("btnStop");

        horizontalLayout->addWidget(btnStop);

        btnReset = new QPushButton(centralwidget);
        btnReset->setObjectName("btnReset");

        horizontalLayout->addWidget(btnReset);

        btnZapisz = new QPushButton(centralwidget);
        btnZapisz->setObjectName("btnZapisz");

        horizontalLayout->addWidget(btnZapisz);

        btnWczytaj = new QPushButton(centralwidget);
        btnWczytaj->setObjectName("btnWczytaj");

        horizontalLayout->addWidget(btnWczytaj);


        gridLayout_6->addLayout(horizontalLayout, 4, 0, 1, 2);

        STATUS = new QGroupBox(centralwidget);
        STATUS->setObjectName("STATUS");
        sizePolicy.setHeightForWidth(STATUS->sizePolicy().hasHeightForWidth());
        STATUS->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(STATUS);
        gridLayout_4->setObjectName("gridLayout_4");
        lblCzas = new QLabel(STATUS);
        lblCzas->setObjectName("lblCzas");
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lblCzas->sizePolicy().hasHeightForWidth());
        lblCzas->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(lblCzas, 0, 0, 1, 1);


        gridLayout_6->addWidget(STATUS, 0, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        chartWykres1 = new QCustomPlot(centralwidget);
        chartWykres1->setObjectName("chartWykres1");
        chartWykres1->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(chartWykres1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        chartWykres2 = new QCustomPlot(centralwidget);
        chartWykres2->setObjectName("chartWykres2");
        QFont font;
        font.setBold(false);
        chartWykres2->setFont(font);

        horizontalLayout_12->addWidget(chartWykres2);

        chartwykres3 = new QCustomPlot(centralwidget);
        chartwykres3->setObjectName("chartwykres3");

        horizontalLayout_12->addWidget(chartwykres3);

        chartWykres4 = new QCustomPlot(centralwidget);
        chartWykres4->setObjectName("chartWykres4");

        horizontalLayout_12->addWidget(chartWykres4);


        verticalLayout_4->addLayout(horizontalLayout_12);


        gridLayout_5->addLayout(verticalLayout_4, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 1, 4, 1);

        gridLayout_6->setColumnStretch(0, 2);
        gridLayout_6->setColumnStretch(1, 8);

        verticalLayout_5->addLayout(gridLayout_6);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Symulator UAR", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "PARAMETRY PID", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Kp:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ti:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Td:", nullptr));
        labelRozniczka->setText(QCoreApplication::translate("MainWindow", "Tryb ca\305\202kowania", nullptr));
        boxRozniczka->setItemText(0, QCoreApplication::translate("MainWindow", "Sta\305\202a pod ca\305\202k\304\205", nullptr));
        boxRozniczka->setItemText(1, QCoreApplication::translate("MainWindow", "Sta\305\202a przed ca\305\202k\304\205", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "GENERATOR WARTOSCI ZADANEJ", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "TYP:", nullptr));
        comboTyp->setItemText(0, QCoreApplication::translate("MainWindow", "Prostok\304\205t", nullptr));
        comboTyp->setItemText(1, QCoreApplication::translate("MainWindow", "Sinusoida", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "Amplituda:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Okres:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Wyp\305\202nienie:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "PARAMETRY SYMULACJI:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Interwal:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Sta\305\202a czasowa:", nullptr));
        btnUstawieniaARX->setText(QCoreApplication::translate("MainWindow", "USTAWIENIA ARX", nullptr));
        btnResetCalki->setText(QCoreApplication::translate("MainWindow", "RESET CA\305\201KI", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
        btnZapisz->setText(QCoreApplication::translate("MainWindow", "ZAPISZ", nullptr));
        btnWczytaj->setText(QCoreApplication::translate("MainWindow", "WCZYTAJ", nullptr));
        STATUS->setTitle(QCoreApplication::translate("MainWindow", "STATUS", nullptr));
        lblCzas->setText(QCoreApplication::translate("MainWindow", "Czas: 0.00 s", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
