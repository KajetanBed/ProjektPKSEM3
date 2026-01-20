#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ustawieniaarx.h"
#include "WarstwaU.h" // Tylko WarstwaU, brak UAR.h
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

    // Inicjalizacja parametrów ARX/PID została przeniesiona do konstruktora WarstwaU
    // symulatorUAR = new UAR(...); <-- USUNIĘTE

    warstwaUslug = new WarstwaU(); // WarstwaU tworzy sobie UAR wewnątrz

    timerSymulacji = new QTimer(this);
    connect(timerSymulacji, &QTimer::timeout, this, &MainWindow::aktualizujSymulacje);
    aktualnyCzas = 0.0;
    y_prev = 0.0;

    // --- Konfiguracja wykresów (bez zmian) ---
    setupPlot(ui->chartWykres1, "Regulacja", "Wartość");
    ui->chartWykres1->addGraph();
    ui->chartWykres1->graph(0)->setPen(QPen(Qt::red));
    ui->chartWykres1->graph(0)->setName("Zadana");

    ui->chartWykres1->addGraph();
    ui->chartWykres1->graph(1)->setPen(QPen(Qt::blue));
    ui->chartWykres1->graph(1)->setName("Wyjście");
    ui->chartWykres1->legend->setVisible(true);

    setupPlot(ui->chartWykres2, "Uchyb", "e");
    ui->chartWykres2->addGraph();
    ui->chartWykres2->graph(0)->setPen(QPen(Qt::black));

    setupPlot(ui->chartwykres3, "Sterowanie", "u");
    ui->chartwykres3->addGraph();
    ui->chartwykres3->graph(0)->setPen(QPen(Qt::darkGreen));

    setupPlot(ui->chartWykres4, "Składowe PID", "Wartość");
    ui->chartWykres4->addGraph();
    ui->chartWykres4->graph(0)->setPen(QPen(Qt::red)); ui->chartWykres4->graph(0)->setName("P");
    ui->chartWykres4->addGraph();
    ui->chartWykres4->graph(1)->setPen(QPen(Qt::green)); ui->chartWykres4->graph(1)->setName("I");
    ui->chartWykres4->addGraph();
    ui->chartWykres4->graph(2)->setPen(QPen(Qt::blue)); ui->chartWykres4->graph(2)->setName("D");
    ui->chartWykres4->legend->setVisible(true);

    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::on_btnStart_clicked);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::on_btnStop_clicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::on_btnReset_clicked);
}

MainWindow::~MainWindow()
{
    delete warstwaUslug;
    // delete symulatorUAR; <-- USUNIĘTE (WarstwaU posprząta)
    delete ui;
}

void MainWindow::setupPlot(QCustomPlot *plot, QString tytul, QString yLabel)
{
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, tytul, QFont("sans", 10, QFont::Bold)));
    plot->xAxis->setLabel("Czas [s]");
    plot->yAxis->setLabel(yLabel);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_btnStop_clicked() { timerSymulacji->stop(); }

void MainWindow::aktualizujSymulacje()
{
    // 1. Pobieranie parametrów (bez zmian)
    warstwaUslug->setPidK(ui->spinKp->value());
    warstwaUslug->setPidTI(ui->spinTi->value());
    warstwaUslug->setPidTD(ui->spinTd->value());

    warstwaUslug->setGwzAmplitude(ui->spinAmp->value());
    warstwaUslug->setGwzPeriod(ui->spinOkres->value());
    warstwaUslug->setGwzWypelnienie(ui->spinWypelnienie->value());
    warstwaUslug->setGwzStala(ui->spinStala->value());

    if (ui->comboTyp->currentIndex() == 0)
        warstwaUslug->setGwzType(TypSygnalu::SygnalProstokatny);
    else
        warstwaUslug->setGwzType(TypSygnalu::Sinusoida);

    if (ui->boxRozniczka->currentIndex() == 0)
        warstwaUslug->setPidMode(PID::trybCalki::wew);
    else
        warstwaUslug->setPidMode(PID::trybCalki::zew);

    warstwaUslug->setGwzTT(timerSymulacji->interval());
    int nowyInterwal = ui->spinInterwal->value();
    if (nowyInterwal >= 10 && timerSymulacji->interval() != nowyInterwal)
    {
        timerSymulacji->setInterval(nowyInterwal);
    }

    // 2. Obliczenia (bez zmian)
    double w = warstwaUslug->generateGwz();
    double e = w - y_prev;
    double dt = timerSymulacji->interval() / 1000.0;
    double u = warstwaUslug->calculatePID(e, dt);

    double valP = warstwaUslug->PIDgetP();
    double valI = warstwaUslug->PIDgetI();
    double valD = warstwaUslug->PIDgetD();

    double y = warstwaUslug->calculateARX(u);
    y_prev = y;

    // 3. Dodawanie danych (bez zmian)
    ui->chartWykres1->graph(0)->addData(aktualnyCzas, w);
    ui->chartWykres1->graph(1)->addData(aktualnyCzas, y);
    ui->chartWykres2->graph(0)->addData(aktualnyCzas, e);
    ui->chartwykres3->graph(0)->addData(aktualnyCzas, u);
    ui->chartWykres4->graph(0)->addData(aktualnyCzas, valP);
    ui->chartWykres4->graph(1)->addData(aktualnyCzas, valI);
    ui->chartWykres4->graph(2)->addData(aktualnyCzas, valD);

    // 4. Przesuwanie osi X
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

    // 5. SKALOWANIE OSI Y - TERAZ UŻYWAMY NOWEJ FUNKCJI
    skalujWykres(ui->chartWykres1);
    skalujWykres(ui->chartWykres2);
    skalujWykres(ui->chartwykres3);

    if (ui->chartWykres4)
        skalujWykres(ui->chartWykres4);

    // 6. Aktualizacja czasu
    aktualnyCzas += dt;
    ui->lblCzas->setText(QString("Czas: %1 s").arg(QString::number(aktualnyCzas, 'f', 2)));
}

void MainWindow::on_btnStart_clicked()
{
    int interwal = ui->spinInterwal->value();
    if (interwal < 10) interwal = 10;
    timerSymulacji->start(interwal);
}

void MainWindow::on_btnResetCalki_clicked()
{
    warstwaUslug->resetPid();
}

void MainWindow::on_btnReset_clicked()
{
    timerSymulacji->stop();
    if (warstwaUslug)
    {
        warstwaUslug->resetGwz();
        warstwaUslug->resetPid();
    }
    aktualnyCzas = 0.0;
    y_prev = 0.0;
    ui->lblCzas->setText("Czas: 0.00 s");

    // Czyszczenie danych na wykresach
    ui->chartWykres1->graph(0)->data()->clear();
    ui->chartWykres1->graph(1)->data()->clear();
    ui->chartWykres2->graph(0)->data()->clear();
    ui->chartwykres3->graph(0)->data()->clear();
    ui->chartWykres4->graph(0)->data()->clear();
    ui->chartWykres4->graph(1)->data()->clear();
    ui->chartWykres4->graph(2)->data()->clear();

    ui->chartWykres1->replot();
    ui->chartWykres2->replot();
    ui->chartwykres3->replot();
    ui->chartWykres4->replot();
}

void MainWindow::on_btnUstawieniaARX_clicked()
{
    UstawieniaARX okno(this);

    // Pobieramy dane przez WarstwaU (bez UAR w argumencie)
    okno.setWielomianA(warstwaUslug->getArxA());
    okno.setWielomianB(warstwaUslug->getArxB());
    okno.setK(warstwaUslug->getArxK());
    okno.setSzum(warstwaUslug->getArxNoise());

    if (okno.exec() == QDialog::Accepted)
    {
        warstwaUslug->setArxA(okno.getA());
        warstwaUslug->setArxB(okno.getB());
        warstwaUslug->setArxDelay(okno.getK());
        warstwaUslug->toggleArxNoise(okno.getSzum() > 0.0);
        // Uwaga: ARX ma generator szumu wewnatrz, tutaj przekazujesz tylko bool,
        // ale w ARX.h widać distribution(0, 0.01). Jeśli chcesz zmieniać amplitudę szumu,
        // musiałbyś dodać metodę setSzumAmplituda w ARX i WarstwieU.

        double uMin = okno.getUmin();
        double uMax = okno.getUmax();
        if (!okno.getLimityAktywne())
        {
            uMin = -999999.0;
            uMax = 999999.0;
        }

        warstwaUslug->setArxInputLimit(okno.getUmin(), okno.getUmax());
        warstwaUslug->setArxOutputLimit(okno.getYmin(), okno.getYmax());
        warstwaUslug->toggleArxLimits(okno.getLimityAktywne());
    }
}

void MainWindow::on_btnZapisz_clicked()
{
    QString nazwaPliku = QFileDialog::getSaveFileName(this, "Zapisz konfigurację", "", "Pliki JSON (*.json)");
    if (nazwaPliku.isEmpty()) return;

    QJsonObject root;

    // --- 1. ZAPIS PID ---
    QJsonObject jsonPID;
    jsonPID["Kp"] = ui->spinKp->value();
    jsonPID["Ti"] = ui->spinTi->value();
    jsonPID["Td"] = ui->spinTd->value();
    // Zapisujemy tryb całki (0 - wew, 1 - zew)
    jsonPID["Tryb"] = (warstwaUslug->getPidMode() == PID::trybCalki::zew) ? 1 : 0;
    root["PID"] = jsonPID;

    // --- 2. ZAPIS GENERATORA ---
    QJsonObject jsonGEN;
    jsonGEN["Amplituda"] = ui->spinAmp->value();
    jsonGEN["Okres"] = ui->spinOkres->value();
    jsonGEN["Wypelnienie"] = ui->spinWypelnienie->value();
    jsonGEN["Stala"] = ui->spinStala->value();
    jsonGEN["Typ"] = ui->comboTyp->currentIndex();
    root["Generator"] = jsonGEN;

    // --- 3. ZAPIS ARX ---
    QJsonObject jsonARX;

    // Wielomiany
    QJsonArray arrayA;
    for (double val : warstwaUslug->getArxA()) arrayA.append(val);
    jsonARX["A"] = arrayA;

    QJsonArray arrayB;
    for (double val : warstwaUslug->getArxB()) arrayB.append(val);
    jsonARX["B"] = arrayB;

    jsonARX["k"] = warstwaUslug->getArxK();

    // Szum
    jsonARX["SzumAktywny"] = warstwaUslug->getArxNoiseActive();
    jsonARX["SzumAmplituda"] = warstwaUslug->getArxNoise();

    // Limity
    QJsonObject jsonLimity;
    jsonLimity["Aktywne"] = warstwaUslug->getArxLimitsActive();
    jsonLimity["U_min"] = warstwaUslug->getArxUMin();
    jsonLimity["U_max"] = warstwaUslug->getArxUMax();
    jsonLimity["Y_min"] = warstwaUslug->getArxYMin();
    jsonLimity["Y_max"] = warstwaUslug->getArxYMax();
    jsonARX["Limity"] = jsonLimity;

    root["ARX"] = jsonARX;

    // --- 4. POZOSTAŁE ---
    root["Interwal"] = ui->spinInterwal->value();

    // Zapis do pliku
    QFile file(nazwaPliku);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Błąd", "Nie można zapisać pliku!");
        return;
    }
    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();

    ui->statusbar->showMessage("Zapisano pełną konfigurację!", 3000);
}
void MainWindow::on_btnWczytaj_clicked()
{
    QString nazwaPliku = QFileDialog::getOpenFileName(this, "Wczytaj konfigurację", "", "Pliki JSON (*.json)");
    if (nazwaPliku.isEmpty()) return;

    QFile file(nazwaPliku);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Błąd", "Nie można otworzyć pliku!");
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) return;
    QJsonObject root = doc.object();

    // --- 1. WCZYTANIE PID ---
    if (root.contains("PID")) {
        QJsonObject jsonPID = root["PID"].toObject();
        ui->spinKp->setValue(jsonPID["Kp"].toDouble());
        ui->spinTi->setValue(jsonPID["Ti"].toDouble());
        ui->spinTd->setValue(jsonPID["Td"].toDouble());

        // Ustawienie ComboBoxa trybu (0 - stała pod całką, 1 - stała przed całką)
        if (jsonPID.contains("Tryb")) {
            int trybIndex = jsonPID["Tryb"].toInt();
            ui->boxRozniczka->setCurrentIndex(trybIndex); // Zakładam, że 0=Wew, 1=Zew w UI

            // Od razu ustawiamy w logice
            warstwaUslug->setPidMode(trybIndex == 1 ? PID::trybCalki::zew : PID::trybCalki::wew);
        }
    }

    // --- 2. WCZYTANIE GENERATORA ---
    if (root.contains("Generator")) {
        QJsonObject jsonGEN = root["Generator"].toObject();
        ui->spinAmp->setValue(jsonGEN["Amplituda"].toDouble());
        ui->spinOkres->setValue(jsonGEN["Okres"].toDouble());
        ui->spinWypelnienie->setValue(jsonGEN["Wypelnienie"].toDouble());
        if (jsonGEN.contains("Stala")) ui->spinStala->setValue(jsonGEN["Stala"].toDouble());
        ui->comboTyp->setCurrentIndex(jsonGEN["Typ"].toInt());
    }

    // --- 3. WCZYTANIE ARX ---
    if (root.contains("ARX")) {
        QJsonObject jsonARX = root["ARX"].toObject();

        // Wielomiany
        std::vector<double> newA, newB;
        QJsonArray arrA = jsonARX["A"].toArray();
        for (const auto &val : arrA) newA.push_back(val.toDouble());
        QJsonArray arrB = jsonARX["B"].toArray();
        for (const auto &val : arrB) newB.push_back(val.toDouble());

        warstwaUslug->setArxA(newA);
        warstwaUslug->setArxB(newB);
        warstwaUslug->setArxK(jsonARX["k"].toInt());

        // Szum
        if (jsonARX.contains("SzumAktywny")) {
            warstwaUslug->toggleArxNoise(jsonARX["SzumAktywny"].toBool());
        }

        // Limity
        if (jsonARX.contains("Limity")) {
            QJsonObject jsonLimity = jsonARX["Limity"].toObject();

            double uMin = jsonLimity["U_min"].toDouble();
            double uMax = jsonLimity["U_max"].toDouble();
            double yMin = jsonLimity["Y_min"].toDouble();
            double yMax = jsonLimity["Y_max"].toDouble();
            bool aktywne = jsonLimity["Aktywne"].toBool();

            warstwaUslug->setArxInputLimit(uMin, uMax);
            warstwaUslug->setArxOutputLimit(yMin, yMax);
            warstwaUslug->toggleArxLimits(aktywne);
        }
    }

    // --- 4. POZOSTAŁE ---
    if (root.contains("Interwal")) {
        ui->spinInterwal->setValue(root["Interwal"].toInt());
    }

    // Reset i odświeżenie symulacji
    on_btnReset_clicked();

    // Ważne: Wymuszamy aktualizację WarstwyU danymi z interfejsu (na wszelki wypadek)
    aktualizujSymulacje();

    QMessageBox::information(this, "Sukces", "Wczytano pełną konfigurację.");
}
void MainWindow::skalujWykres(QCustomPlot *p, double minSpan)
{
    if (!p) return;
    if (p->graphCount() == 0) return; // Zabezpieczenie przed pustym wykresem

    bool found = false;
    // Pobieramy zakres pierwszego wykresu
    QCPRange range = p->graph(0)->getValueRange(found);

    // Jeśli na jednym wykresie (QCustomPlot) jest więcej linii (np. zadana i wyjście),
    // musimy uwzględnić zakresy ich wszystkich.
    for (int i = 1; i < p->graphCount(); ++i)
    {
        bool f;
        QCPRange r = p->graph(i)->getValueRange(f);
        if (f)
            range.expand(r); // Rozszerzamy zakres o kolejne linie
    }

    if (!found || range.size() < 0.001)
    {
        // Jeśli sygnał jest płaski (stała wartość) lub brak danych -> sztywne ramy
        // Centrujemy wokół wartości (jeśli jest), lub wokół 0
        double center = (found) ? range.center() : 0.0;
        p->yAxis->setRange(center - minSpan / 2.0, center + minSpan / 2.0);
    }
    else
    {
        // Jeśli sygnał się zmienia -> dodaj margines 15% góra/dół
        double margin = range.size() * 0.15;
        p->yAxis->setRange(range.lower - margin, range.upper + margin);
    }

    // Ostateczne odświeżenie (rysowanie)
    p->replot();
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    // 1. Wywołujemy oryginalną obsługę zdarzenia (żeby układ okna się przeliczył)
    QMainWindow::resizeEvent(event);

    // 2. Obliczamy nowy rozmiar czcionki
    // Możemy bazować na szerokości (width()) lub wysokości (height()) okna.
    // Dzielnik (np. 60) dobieramy eksperymentalnie, żeby wyglądało dobrze.
    // Im mniejszy dzielnik, tym większa czcionka.

    int nowyRozmiar = this->width() / 60;

    // Zabezpieczenie: nie chcemy czcionki mniejszej niż np. 8 punktów
    if (nowyRozmiar < 8) nowyRozmiar = 8;
    // Opcjonalnie: nie większa niż np. 24 (jeśli nie chcesz gigantycznej)
    if (nowyRozmiar > 30) nowyRozmiar = 30;

    // 3. Pobieramy obecną czcionkę labela, zmieniamy rozmiar i ustawiamy z powrotem
    QFont czcionka = ui->lblCzas->font();
    czcionka.setPointSize(nowyRozmiar);
    // Opcjonalnie pogrubienie:
    czcionka.setBold(true);

    ui->lblCzas->setFont(czcionka);
    ui->label->setFont(czcionka);
    ui->labelRozniczka->setFont(czcionka);
    ui->label_2->setFont(czcionka);
    ui->label_3->setFont(czcionka);
    ui->label_4->setFont(czcionka);
    ui->label_5->setFont(czcionka);
    ui->label_6->setFont(czcionka);
    ui->label_7->setFont(czcionka);
    ui->label_8->setFont(czcionka);
    ui->label_9->setFont(czcionka);

    // Jeśli masz inne labele, które chcesz skalować, zrób to samo dla nich tutaj:
    // ui->innyLabel->setFont(czcionka);
}
