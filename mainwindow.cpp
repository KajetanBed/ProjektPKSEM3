#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ustawieniaarx.h"
#include "UAR.h"
#include "WarstwaU.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vector<double> A = {-0.4, 0.1, -0.05};
    vector<double> B = {0.6, 0.2, 0.1};
    int k = 1;

    ARX model(A, B, k);
    PID regulator(1.0, 50.0, 0.1);
    GeneratorWartosciZadanej gen(1.0, 10.0, 0.0, 0.5, 200, TypSygnalu::SygnalProstokatny);

    symulatorUAR = new UAR(model, regulator, gen);
    warstwaUslug = new WarstwaU();

    warstwaUslug->setArxLimits(symulatorUAR, -10.0, 10.0, -10.0, 10.0);
    warstwaUslug->toggleArxLimits(symulatorUAR, true);

    timerSymulacji = new QTimer(this);
    connect(timerSymulacji, &QTimer::timeout, this, &MainWindow::aktualizujSymulacje);
    aktualnyCzas = 0.0;
    y_prev = 0.0;

    // Wykres 1: Główny
    setupPlot(ui->chartWykres1, "Regulacja", "Wartość");
    ui->chartWykres1->addGraph(); // Zadana
    ui->chartWykres1->graph(0)->setPen(QPen(Qt::red));
    ui->chartWykres1->graph(0)->setName("Zadana");

    ui->chartWykres1->addGraph(); // Wyjście
    ui->chartWykres1->graph(1)->setPen(QPen(Qt::blue));
    ui->chartWykres1->graph(1)->setName("Wyjście");
    ui->chartWykres1->legend->setVisible(true);

    // Wykres 2: Uchyb
    setupPlot(ui->chartWykres2, "Uchyb", "e");
    ui->chartWykres2->addGraph();
    ui->chartWykres2->graph(0)->setPen(QPen(Qt::black));

    // Wykres 3: Sterowanie
    setupPlot(ui->chartwykres3, "Sterowanie", "u");
    ui->chartwykres3->addGraph();
    ui->chartwykres3->graph(0)->setPen(QPen(Qt::darkGreen));

    // Wykres 4: PID
    setupPlot(ui->chartWykres4, "Składowe PID", "Wartość");
    ui->chartWykres4->addGraph(); // P
    ui->chartWykres4->graph(0)->setPen(QPen(Qt::red));
    ui->chartWykres4->graph(0)->setName("P");

    ui->chartWykres4->addGraph(); // I
    ui->chartWykres4->graph(1)->setPen(QPen(Qt::green));
    ui->chartWykres4->graph(1)->setName("I");

    ui->chartWykres4->addGraph(); // D
    ui->chartWykres4->graph(2)->setPen(QPen(Qt::blue));
    ui->chartWykres4->graph(2)->setName("D");
    ui->chartWykres4->legend->setVisible(true);

    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::on_btnStart_clicked);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::on_btnStop_clicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::on_btnReset_clicked);
}

MainWindow::~MainWindow()
{
    delete warstwaUslug;
    delete symulatorUAR;
    delete ui;
}

void MainWindow::setupPlot(QCustomPlot *plot, QString tytul, QString yLabel)
{
    // Tytuł
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, tytul, QFont("sans", 10, QFont::Bold)));

    // Osie
    plot->xAxis->setLabel("Czas [s]");
    plot->yAxis->setLabel(yLabel);

    // Interakcja
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_btnStop_clicked() { timerSymulacji->stop(); }

void MainWindow::aktualizujSymulacje()
{
    // Aktualizacja parametrów z UI

    // PID
    warstwaUslug->setPidK(symulatorUAR, ui->spinKp->value());
    warstwaUslug->setPidTI(symulatorUAR, ui->spinTi->value());
    warstwaUslug->setPidTD(symulatorUAR, ui->spinTd->value());

    // Generator
    warstwaUslug->setGwzAmplitude(symulatorUAR, ui->spinAmp->value());
    warstwaUslug->setGwzPeriod(symulatorUAR, ui->spinOkres->value());
    warstwaUslug->setGwzWypelnienie(symulatorUAR, ui->spinWypelnienie->value());
    warstwaUslug->setGwzStala(symulatorUAR, ui->spinStala->value());

    // Typ sygnału
    if (ui->comboTyp->currentIndex() == 0)
        warstwaUslug->setGwzType(symulatorUAR, TypSygnalu::SygnalProstokatny);
    else
        warstwaUslug->setGwzType(symulatorUAR, TypSygnalu::Sinusoida);

    if (ui->boxRozniczka->currentIndex() == 0)
        warstwaUslug->setPidMode(symulatorUAR, PID::trybCalki::wew);
    else
        warstwaUslug->setPidMode(symulatorUAR, PID::trybCalki::zew);

    // Aktualizacja interwału generatora
    warstwaUslug->setGwzTT(symulatorUAR, timerSymulacji->interval());

    // Obliczenia Symulacji
    double w = warstwaUslug->generateGwz(symulatorUAR);
    double e = w - y_prev;
    double dt = timerSymulacji->interval() / 1000.0;
    double u = warstwaUslug->calculatePID(symulatorUAR, e, dt);

    double valP = warstwaUslug->PIDgetP(symulatorUAR);
    double valI = warstwaUslug->PIDgetI(symulatorUAR);
    double valD = warstwaUslug->PIDgetD(symulatorUAR);

    double y = warstwaUslug->calculateARX(symulatorUAR, u);
    y_prev = y;

    // Aktualizacja Wykresów
    ui->chartWykres1->graph(0)->addData(aktualnyCzas, w);
    ui->chartWykres1->graph(1)->addData(aktualnyCzas, y);
    ui->chartWykres2->graph(0)->addData(aktualnyCzas, e);
    ui->chartwykres3->graph(0)->addData(aktualnyCzas, u);

    ui->chartWykres4->graph(0)->addData(aktualnyCzas, valP);
    ui->chartWykres4->graph(1)->addData(aktualnyCzas, valI);
    ui->chartWykres4->graph(2)->addData(aktualnyCzas, valD);

    // Skalowanie osi
    double okno = 10.0;
    double minX = (aktualnyCzas > okno) ? aktualnyCzas - okno : 0.0;
    double maxX = (aktualnyCzas > okno) ? aktualnyCzas : okno;

    ui->chartWykres1->xAxis->setRange(minX, maxX);
    ui->chartWykres2->xAxis->setRange(minX, maxX);
    ui->chartwykres3->xAxis->setRange(minX, maxX);
    ui->chartWykres4->xAxis->setRange(minX, maxX);

    ui->chartWykres1->graph(0)->data()->removeBefore(minX);
    ui->chartWykres1->graph(1)->data()->removeBefore(minX);

    ui->chartWykres2->graph(0)->data()->removeBefore(minX);

    ui->chartwykres3->graph(0)->data()->removeBefore(minX);

    ui->chartWykres4->graph(0)->data()->removeBefore(minX);
    ui->chartWykres4->graph(1)->data()->removeBefore(minX);
    ui->chartWykres4->graph(2)->data()->removeBefore(minX);

    auto bezpiecznyRescale = [](QCustomPlot *p, double minSpan = 10.0)
    {
        if (!p)
            return;

        // POBIERAMY dane bezpośrednio, zamiast ufać rescale()
        bool found = false;
        QCPRange range = p->graph(0)->getValueRange(found);

        // Jeśli wykres ma więcej linii (np. zadana i wyjście), uwzględnij obie
        for (int i = 1; i < p->graphCount(); ++i)
        {
            bool f;
            QCPRange r = p->graph(i)->getValueRange(f);
            if (f)
                range.expand(r);
        }

        if (!found || range.size() < 0.001)
        {
            // Jeśli brak danych lub sygnał płaski - trzymaj sztywne +/- 5
            p->yAxis->setRange(-minSpan / 2.0, minSpan / 2.0);
        }
        else
        {
            // Jeśli sygnał żyje - dodaj margines 15% góra/dół RAZ
            double margin = range.size() * 0.15;
            p->yAxis->setRange(range.lower - margin, range.upper + margin);
        }

        // Ostateczna blokada przed błędem numerycznym na osi
        if (!std::isfinite(p->yAxis->range().lower))
            p->yAxis->setRange(-5, 5);

        p->replot();
    };

    bezpiecznyRescale(ui->chartWykres1);
    bezpiecznyRescale(ui->chartWykres2);
    bezpiecznyRescale(ui->chartwykres3);
    if (ui->chartWykres4)
        bezpiecznyRescale(ui->chartWykres4);

    // ui->chartWykres1->yAxis->rescale();
    // ui->chartWykres2->yAxis->rescale();
    // ui->chartwykres3->yAxis->rescale();
    // ui->chartWykres4->yAxis->rescale();

    ui->chartWykres1->replot();
    ui->chartWykres2->replot();
    ui->chartwykres3->replot();
    ui->chartWykres4->replot();

    // Status i Czas
    aktualnyCzas += (timerSymulacji->interval() / 1000.0);
    ui->lblCzas->setText(QString("Czas: %1 s").arg(QString::number(aktualnyCzas, 'f', 2)));
}

// Obsługa przycisku START
void MainWindow::on_btnStart_clicked()
{
    int interwal = ui->spinInterwal->value();
    if (interwal < 10)
        interwal = 10; // Zabezpieczenie
    timerSymulacji->start(interwal);
}

// Obsługa przycisku RESET CAŁKI
void MainWindow::on_btnResetCalki_clicked()
{
    warstwaUslug->resetPid(symulatorUAR);
}
void MainWindow::on_btnReset_clicked()
{
    timerSymulacji->stop();

    // Reset backendu
    if (symulatorUAR)
    {
        warstwaUslug->resetGwz(symulatorUAR);
        warstwaUslug->resetPid(symulatorUAR);
    }
    aktualnyCzas = 0.0;
    y_prev = 0.0;

    // Reset czasu na labelu
    ui->lblCzas->setText("Czas: 0.00 s");

    // Czyszczenie danych na wykresach
    ui->chartWykres1->graph(0)->data()->clear();
    ui->chartWykres1->graph(1)->data()->clear();
    ui->chartWykres2->graph(0)->data()->clear();
    ui->chartwykres3->graph(0)->data()->clear();
    ui->chartWykres4->graph(0)->data()->clear();
    ui->chartWykres4->graph(1)->data()->clear();
    ui->chartWykres4->graph(2)->data()->clear();

    // Odświeżenie
    ui->chartWykres1->replot();
    ui->chartWykres2->replot();
    ui->chartwykres3->replot();
    ui->chartWykres4->replot();
}
void MainWindow::on_btnUstawieniaARX_clicked()
{
    // 1. Tworzymy okno
    UstawieniaARX okno(this);

    // 2. Wypełniamy je aktualnymi danymi
    okno.setWielomianA(warstwaUslug->getArxA(symulatorUAR));
    okno.setWielomianB(warstwaUslug->getArxB(symulatorUAR));
    okno.setK(warstwaUslug->getArxK(symulatorUAR));

    // 3. Wyświetlamy okno
    if (okno.exec() == QDialog::Accepted)
    {
        warstwaUslug->setArxA(symulatorUAR, okno.getA());
        warstwaUslug->setArxB(symulatorUAR, okno.getB());
        warstwaUslug->setArxDelay(symulatorUAR, okno.getK());
        warstwaUslug->toggleArxNoise(symulatorUAR, okno.getSzum() > 0.0);

        double uMin = okno.getUmin();
        double uMax = okno.getUmax();
        if (!okno.getLimityAktywne())
        {
            uMin = -999999.0;
            uMax = 999999.0;
        }

        warstwaUslug->setArxInputLimit(symulatorUAR, okno.getUmin(), okno.getUmax());
        warstwaUslug->setArxOutputLimit(symulatorUAR, okno.getYmin(), okno.getYmax());
        warstwaUslug->toggleArxLimits(symulatorUAR, okno.getLimityAktywne());
    }
}
void MainWindow::on_btnZapisz_clicked()
{
    // 1. Otwórz okno dialogowe zapisu
    QString nazwaPliku = QFileDialog::getSaveFileName(this, "Zapisz konfigurację", "", "Pliki JSON (*.json)");
    if (nazwaPliku.isEmpty())
        return;

    // 2. Stwórz główny obiekt JSON
    QJsonObject root;

    // SEKCJA PID
    QJsonObject jsonPID;
    jsonPID["Kp"] = ui->spinKp->value();
    jsonPID["Ti"] = ui->spinTi->value();
    jsonPID["Td"] = ui->spinTd->value();
    root["PID"] = jsonPID;

    // SEKCJA GENERATOR
    QJsonObject jsonGEN;
    jsonGEN["Amplituda"] = ui->spinAmp->value();
    jsonGEN["Okres"] = ui->spinOkres->value();
    jsonGEN["Wypelnienie"] = ui->spinWypelnienie->value();
    jsonGEN["Stala"] = ui->spinStala->value();
    jsonGEN["Typ"] = ui->comboTyp->currentIndex();
    root["Generator"] = jsonGEN;

    // SEKCJA ARX
    QJsonObject jsonARX;

    // Zapisujemy wektor A
    QJsonArray arrayA;
    for (double val : warstwaUslug->getArxA(symulatorUAR))
    {
        arrayA.append(val);
    }
    jsonARX["A"] = arrayA;

    // Zapisujemy wektor B
    QJsonArray arrayB;
    for (double val : warstwaUslug->getArxB(symulatorUAR))
    {
        arrayB.append(val);
    }
    jsonARX["B"] = arrayB;

    jsonARX["k"] = warstwaUslug->getArxK(symulatorUAR);

    root["ARX"] = jsonARX;

    // SEKCJA SYMULACJI
    root["Interwal"] = ui->spinInterwal->value();

    // 3. Zapisz do pliku
    QFile file(nazwaPliku);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Błąd", "Nie można zapisać pliku!");
        return;
    }

    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();

    ui->statusbar->showMessage("Zapisano konfigurację!", 3000);
}
void MainWindow::on_btnWczytaj_clicked()
{
    // 1. Otwórz okno dialogowe
    QString nazwaPliku = QFileDialog::getOpenFileName(this, "Wczytaj konfigurację", "", "Pliki JSON (*.json)");
    if (nazwaPliku.isEmpty())
        return;

    // 2. Otwórz i przeczytaj plik
    QFile file(nazwaPliku);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Błąd", "Nie można otworzyć pliku!");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    // 3. Parsuj JSON
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull())
    {
        QMessageBox::critical(this, "Błąd", "Błędny format pliku!");
        return;
    }
    QJsonObject root = doc.object();

    // WCZYTANIE PID
    if (root.contains("PID"))
    {
        QJsonObject jsonPID = root["PID"].toObject();
        ui->spinKp->setValue(jsonPID["Kp"].toDouble());
        ui->spinTi->setValue(jsonPID["Ti"].toDouble());
        ui->spinTd->setValue(jsonPID["Td"].toDouble());
    }

    // WCZYTANIE GENERATORA
    if (root.contains("Generator"))
    {
        QJsonObject jsonGEN = root["Generator"].toObject();
        ui->spinAmp->setValue(jsonGEN["Amplituda"].toDouble());
        ui->spinOkres->setValue(jsonGEN["Okres"].toDouble());
        ui->spinWypelnienie->setValue(jsonGEN["Wypelnienie"].toDouble());
        if (jsonGEN.contains("Stala"))
        {
            ui->spinStala->setValue(jsonGEN["Stala"].toDouble());
        }
        ui->comboTyp->setCurrentIndex(jsonGEN["Typ"].toInt());
    }

    // WCZYTANIE ARX
    if (root.contains("ARX"))
    {
        QJsonObject jsonARX = root["ARX"].toObject();

        // Czytamy wektor A
        std::vector<double> newA;
        QJsonArray arrA = jsonARX["A"].toArray();
        for (const auto &val : arrA)
            newA.push_back(val.toDouble());

        // Czytamy wektor B
        std::vector<double> newB;
        QJsonArray arrB = jsonARX["B"].toArray();
        for (const auto &val : arrB)
            newB.push_back(val.toDouble());

        int newK = jsonARX["k"].toInt();

        warstwaUslug->setArxA(symulatorUAR, newA);
        warstwaUslug->setArxB(symulatorUAR, newB);
        warstwaUslug->setArxK(symulatorUAR, newK);
    }

    // WCZYTANIE INTERWAŁU
    if (root.contains("Interwal"))
    {
        ui->spinInterwal->setValue(root["Interwal"].toInt());
    }

    // 4. Reset po wczytaniu (Dobra praktyka)
    on_btnReset_clicked();

    QMessageBox::information(this, "Sukces", "Wczytano konfigurację pomyślnie.");
}
