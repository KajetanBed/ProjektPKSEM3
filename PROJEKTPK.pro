QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    ARX.cpp \
    GWZ.cpp \
    PID.cpp \
    UAR.cpp \
    WarstwaU.cpp \
    qcustomplot.cpp \
    main.cpp \
    mainwindow.cpp \
    ustawieniaarx.cpp

HEADERS += \
    ARX.h \
    GWZ.h \
    PID.h \
    UAR.h \
    WarstwaU.h \
    qcustomplot.h \
    mainwindow.h \
    ustawieniaarx.h

FORMS += \
    mainwindow.ui \
    ustawieniaarx.ui
