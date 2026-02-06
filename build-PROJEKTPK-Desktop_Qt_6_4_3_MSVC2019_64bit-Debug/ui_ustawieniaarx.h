/********************************************************************************
** Form generated from reading UI file 'ustawieniaarx.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USTAWIENIAARX_H
#define UI_USTAWIENIAARX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UstawieniaARX
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *leA;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *leB;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpinBox *spinK;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QDoubleSpinBox *spinSzum;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *checkSzum;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QCheckBox *checkLimity;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QDoubleSpinBox *spinUmin;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QDoubleSpinBox *spinUmax;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QDoubleSpinBox *spinYmin;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QDoubleSpinBox *spinYmax;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btnZatwierdz;
    QPushButton *btnAnuluj;

    void setupUi(QDialog *UstawieniaARX)
    {
        if (UstawieniaARX->objectName().isEmpty())
            UstawieniaARX->setObjectName("UstawieniaARX");
        UstawieniaARX->resize(400, 475);
        UstawieniaARX->setMinimumSize(QSize(400, 475));
        UstawieniaARX->setMaximumSize(QSize(400, 475));
        UstawieniaARX->setStyleSheet(QString::fromUtf8("/* --- G\305\201\303\223WNE T\305\201O --- */\n"
"QDialog {\n"
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
"    color: #4da6ff; \n"
"    background-color: transparent;\n"
"}\n"
"\n"
"/* --- POLA EDYCJI I ETYKIETY --- */\n"
"QLabel {\n"
"    color: #dddddd;\n"
"    background-color: transparent; /* \305\273eby nie mia\305\202y t\305\202a rodzica */\n"
"    border: none;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    color: #dddddd;\n"
"    font-size: 11px;\n"
"    background-color: transparent; /* \305\273eby nie mia\305\202y t\305\202a rodzica */\n"
"    border: none;\n"
"}\n"
"\n"
"QCheckBox{\n"
"color: #dddddd\n"
"}\n"
"\n"
"QDou"
                        "bleSpinBox, QSpinBox, QComboBox {\n"
"    background-color: #454545;\n"
"    border: 1px solid #666666;\n"
"    border-radius: 3px;\n"
"    padding: 4px;\n"
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
"QPushButton#btnStart:hover { background-color: #388e3c"
                        "; }\n"
"\n"
"QPushButton#btnStop {\n"
"    background-color: #c62828; /* Czerwony */\n"
"    border-color: #ef5350;\n"
"}\n"
"QPushButton#btnStop:hover { background-color: #d32f2f; }\n"
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
        verticalLayout_5 = new QVBoxLayout(UstawieniaARX);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(UstawieniaARX);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8(" color: #4da6ff; /* Niebieski kolor tytu\305\202\303\263w */\n"
"background-color: transparent;\n"
"font-weight: bold;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(UstawieniaARX);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        leA = new QLineEdit(UstawieniaARX);
        leA->setObjectName("leA");

        horizontalLayout->addWidget(leA);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(UstawieniaARX);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        leB = new QLineEdit(UstawieniaARX);
        leB->setObjectName("leB");

        horizontalLayout_2->addWidget(leB);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(UstawieniaARX);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        spinK = new QSpinBox(UstawieniaARX);
        spinK->setObjectName("spinK");
        spinK->setMinimum(1);

        horizontalLayout_3->addWidget(spinK);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(UstawieniaARX);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        spinSzum = new QDoubleSpinBox(UstawieniaARX);
        spinSzum->setObjectName("spinSzum");
        spinSzum->setMaximum(10000.000000000000000);
        spinSzum->setSingleStep(0.010000000000000);

        horizontalLayout_4->addWidget(spinSzum);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        checkSzum = new QCheckBox(UstawieniaARX);
        checkSzum->setObjectName("checkSzum");

        verticalLayout->addWidget(checkSzum);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_6 = new QLabel(UstawieniaARX);
        label_6->setObjectName("label_6");
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        label_6->setFont(font1);
        label_6->setStyleSheet(QString::fromUtf8(" color: #4da6ff; /* Niebieski kolor tytu\305\202\303\263w */\n"
"background-color: transparent;\n"
"font-weight: bold;"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_6);

        checkLimity = new QCheckBox(UstawieniaARX);
        checkLimity->setObjectName("checkLimity");

        verticalLayout_3->addWidget(checkLimity);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_7 = new QLabel(UstawieniaARX);
        label_7->setObjectName("label_7");

        horizontalLayout_5->addWidget(label_7);

        spinUmin = new QDoubleSpinBox(UstawieniaARX);
        spinUmin->setObjectName("spinUmin");
        spinUmin->setMinimum(-100.000000000000000);
        spinUmin->setMaximum(100.000000000000000);
        spinUmin->setSingleStep(1.000000000000000);

        horizontalLayout_5->addWidget(spinUmin);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_8 = new QLabel(UstawieniaARX);
        label_8->setObjectName("label_8");

        horizontalLayout_6->addWidget(label_8);

        spinUmax = new QDoubleSpinBox(UstawieniaARX);
        spinUmax->setObjectName("spinUmax");
        spinUmax->setMinimum(-100.000000000000000);
        spinUmax->setMaximum(100.000000000000000);
        spinUmax->setSingleStep(1.000000000000000);

        horizontalLayout_6->addWidget(spinUmax);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_9 = new QLabel(UstawieniaARX);
        label_9->setObjectName("label_9");

        horizontalLayout_7->addWidget(label_9);

        spinYmin = new QDoubleSpinBox(UstawieniaARX);
        spinYmin->setObjectName("spinYmin");
        spinYmin->setMinimum(-100.000000000000000);
        spinYmin->setMaximum(100.000000000000000);
        spinYmin->setSingleStep(1.000000000000000);

        horizontalLayout_7->addWidget(spinYmin);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_10 = new QLabel(UstawieniaARX);
        label_10->setObjectName("label_10");

        horizontalLayout_8->addWidget(label_10);

        spinYmax = new QDoubleSpinBox(UstawieniaARX);
        spinYmax->setObjectName("spinYmax");
        spinYmax->setMinimum(-100.000000000000000);
        spinYmax->setMaximum(100.000000000000000);
        spinYmax->setSingleStep(1.000000000000000);

        horizontalLayout_8->addWidget(spinYmax);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        btnZatwierdz = new QPushButton(UstawieniaARX);
        btnZatwierdz->setObjectName("btnZatwierdz");

        horizontalLayout_9->addWidget(btnZatwierdz);

        btnAnuluj = new QPushButton(UstawieniaARX);
        btnAnuluj->setObjectName("btnAnuluj");

        horizontalLayout_9->addWidget(btnAnuluj);


        verticalLayout_4->addLayout(horizontalLayout_9);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(UstawieniaARX);

        QMetaObject::connectSlotsByName(UstawieniaARX);
    } // setupUi

    void retranslateUi(QDialog *UstawieniaARX)
    {
        UstawieniaARX->setWindowTitle(QCoreApplication::translate("UstawieniaARX", "Ustawienia ARX", nullptr));
        label->setText(QCoreApplication::translate("UstawieniaARX", "USTAWIENIA ARX", nullptr));
        label_2->setText(QCoreApplication::translate("UstawieniaARX", "Wielomian A:", nullptr));
        label_3->setText(QCoreApplication::translate("UstawieniaARX", "Wielomian B:", nullptr));
        label_4->setText(QCoreApplication::translate("UstawieniaARX", "Op\303\263\305\272nienie:", nullptr));
        label_5->setText(QCoreApplication::translate("UstawieniaARX", "Szum:", nullptr));
        checkSzum->setText(QCoreApplication::translate("UstawieniaARX", "Szum aktywny", nullptr));
        label_6->setText(QCoreApplication::translate("UstawieniaARX", "Limity", nullptr));
        checkLimity->setText(QCoreApplication::translate("UstawieniaARX", "Limity aktywne", nullptr));
        label_7->setText(QCoreApplication::translate("UstawieniaARX", "Umin:", nullptr));
        label_8->setText(QCoreApplication::translate("UstawieniaARX", "Umax", nullptr));
        label_9->setText(QCoreApplication::translate("UstawieniaARX", "Ymin", nullptr));
        label_10->setText(QCoreApplication::translate("UstawieniaARX", "Ymax", nullptr));
        btnZatwierdz->setText(QCoreApplication::translate("UstawieniaARX", "Zatwierd\305\272", nullptr));
        btnAnuluj->setText(QCoreApplication::translate("UstawieniaARX", "Anuluj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UstawieniaARX: public Ui_UstawieniaARX {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USTAWIENIAARX_H
