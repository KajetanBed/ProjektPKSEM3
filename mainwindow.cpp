#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ustawieniaarx.h"
#include "UAR.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- 1. BACKEND ---
    vector<double> A = {-0.4, 0.1, -0.05};
    vector<double> B = {0.6, 0.2, 0.1};
    int k = 1;

    ARX model(A, B, k);
    PID regulator(1.0, 50.0, 0.1);
    GeneratorWartosciZadanej gen(1.0, 10.0, 0.0, 0.5, 200, TypSygnalu::SygnalProstokatny);

    symulatorUAR = new UAR(model, regulator, gen);

    symulatorUAR->getARX().ustawLimitWejscia(-10.0, 10.0); // Wymuś zakres sterowania
    symulatorUAR->getARX().ustawLimitWyjscia(-10.0, 10.0); // Wymuś zakres wyjścia
    symulatorUAR->getARX().przelaczLimity(true);           // Wymuś włączenie

    timerSymulacji = new QTimer(this);
    connect(timerSymulacji, &QTimer::timeout, this, &MainWindow::aktualizujSymulacje);
    aktualnyCzas = 0.0;
    y_prev = 0.0;

    // --- 2. KONFIGURACJA WYKRESÓW ---

    // Wykres 1: Główny (2 linie: Zadana i Wyjście)
    setupPlot(ui->chartWykres1, "Regulacja", "Wartość");
    ui->chartWykres1->addGraph(); // Graph 0: Zadana
    ui->chartWykres1->graph(0)->setPen(QPen(Qt::red));
    ui->chartWykres1->graph(0)->setName("Zadana");

    ui->chartWykres1->addGraph(); // Graph 1: Wyjście
    ui->chartWykres1->graph(1)->setPen(QPen(Qt::blue));
    ui->chartWykres1->graph(1)->setName("Wyjście");

    // Legenda tylko na głównym
    ui->chartWykres1->legend->setVisible(true);

    // Wykres 2: Uchyb (1 linia)
    setupPlot(ui->chartWykres2, "Uchyb", "e");
    ui->chartWykres2->addGraph();
    ui->chartWykres2->graph(0)->setPen(QPen(Qt::black));

    // Wykres 3: Sterowanie (1 linia)
    setupPlot(ui->chartwykres3, "Sterowanie", "u");
    ui->chartwykres3->addGraph();
    ui->chartwykres3->graph(0)->setPen(QPen(Qt::darkGreen));

    // Wykres 4: PID (3 linie: P, I, D)
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


    // --- 3. UI ---
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::on_btnStart_clicked);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::on_btnStop_clicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::on_btnReset_clicked);

}

MainWindow::~MainWindow()
{
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

    // Interakcja (przesuwanie i przybliżanie)
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_btnStop_clicked() { timerSymulacji->stop(); }

void MainWindow::aktualizujSymulacje()
{
    // --- 1. Aktualizacja parametrów z UI (Live) ---
    // Pobieramy wartości z okienek i wysyłamy do Backendu

    // PID
    symulatorUAR->getPID().setK(ui->spinKp->value());
    symulatorUAR->getPID().setTI(ui->spinTi->value());
    symulatorUAR->getPID().setTD(ui->spinTd->value());

    // Generator
    symulatorUAR->getGWZ().setAmplituda(ui->spinAmp->value());
    symulatorUAR->getGWZ().setTRZ(ui->spinOkres->value()); // To jest T_rzeczywiste
    symulatorUAR->getGWZ().setWypelnienie(ui->spinWypelnienie->value());
    symulatorUAR->getGWZ().setStala(ui->spinStala->value());

    // Typ sygnału (0 - Prostokąt, 1 - Sinusoida - zależy jak dodałeś w ComboBox)
    if(ui->comboTyp->currentIndex() == 0)
        symulatorUAR->getGWZ().setTyp(TypSygnalu::SygnalProstokatny);
    else
        symulatorUAR->getGWZ().setTyp(TypSygnalu::Sinusoida);

    // Aktualizacja interwału generatora (musi wiedzieć jaki jest krok czasu)
    symulatorUAR->getGWZ().setTT(timerSymulacji->interval());


    // --- 2. Obliczenia Symulacji (To co było) ---
    double w = symulatorUAR->getGWZ().obliczSygnal();
    double e = w - y_prev;
    double dt = timerSymulacji->interval() / 1000.0; // ms na sekundy
    double u = symulatorUAR->getPID().oblicz(e,dt);

    double valP = symulatorUAR->getPID().getP();
    double valI = symulatorUAR->getPID().getI();
    double valD = symulatorUAR->getPID().getD();

    double y = symulatorUAR->getARX().symuluj(u);
    y_prev = y;

    // --- 3. Aktualizacja Wykresów (QCustomPlot) ---
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

    ui->chartWykres1->yAxis->rescale();
    ui->chartWykres2->yAxis->rescale();
    ui->chartwykres3->yAxis->rescale();
    ui->chartWykres4->yAxis->rescale();

    ui->chartWykres1->replot();
    ui->chartWykres2->replot();
    ui->chartwykres3->replot();
    ui->chartWykres4->replot();

    // --- 4. Status i Czas ---
    aktualnyCzas += (timerSymulacji->interval() / 1000.0); // Przeliczenie ms na sekundy
    ui->lblCzas->setText(QString("Czas: %1 s").arg(QString::number(aktualnyCzas, 'f', 2)));
}

// Obsługa przycisku START (zmienia interwał wg ustawień)
void MainWindow::on_btnStart_clicked()
{
    int interwal = ui->spinInterwal->value();
    if(interwal < 10) interwal = 10; // Zabezpieczenie
    timerSymulacji->start(interwal);
}

// Obsługa przycisku RESET CAŁKI (Zgodnie z instrukcją)
void MainWindow::on_btnResetCalki_clicked()
{
    symulatorUAR->getPID().resetujSumeUchybu();
}
void MainWindow::on_btnReset_clicked()
{
    timerSymulacji->stop();

    // Reset backendu
    if(symulatorUAR) {
        symulatorUAR->getGWZ().reset();
        symulatorUAR->getPID().resetujSumeUchybu();
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

    // 2. Wypełniamy je aktualnymi danymi (żeby użytkownik wiedział co edytuje)
    // UWAGA: Tu potrzebujesz getterów, które dodaliśmy w Kroku 1
    okno.setWielomianA(symulatorUAR->getARX().getA());
    okno.setWielomianB(symulatorUAR->getARX().getB());
    okno.setK(symulatorUAR->getARX().getK());
    // okno.setSzum(...) // jeśli masz getter do szumu

    // 3. Wyświetlamy okno (funkcja exec() zatrzymuje interakcję, ale timer działa w tle!)
    if(okno.exec() == QDialog::Accepted)
    {
        // 4. Jeśli użytkownik kliknął Zatwierdź -> pobieramy dane i ustawiamy w modelu

        // Zgodnie z instrukcją: zmiany wprowadzamy po zamknięciu okna
        symulatorUAR->getARX().ustawA(okno.getA());
        symulatorUAR->getARX().ustawB(okno.getB());
        symulatorUAR->getARX().ustawOpoznienie(okno.getK());
        symulatorUAR->getARX().przelaczSzum(okno.getSzum() > 0.0);
        // symulatorUAR->getARX().ustawOdchylenie(okno.getSzum()); // jeśli masz taką metodę
        double uMin = okno.getUmin();
        double uMax = okno.getUmax();
        if (!okno.getLimityAktywne()) {
                    uMin = -999999.0;
                    uMax = 999999.0;
        }
        // Limity
        symulatorUAR->getARX().ustawLimitWejscia(okno.getUmin(), okno.getUmax());
        symulatorUAR->getARX().przelaczLimity(okno.getLimityAktywne());
    }
}
void MainWindow::on_btnZapisz_clicked()
{
    // 1. Otwórz okno dialogowe zapisu
    QString nazwaPliku = QFileDialog::getSaveFileName(this, "Zapisz konfigurację", "", "Pliki JSON (*.json)");
    if (nazwaPliku.isEmpty()) return;

    // 2. Stwórz główny obiekt JSON
    QJsonObject root;

    // --- SEKCJA PID (Pobieramy z UI, bo tam są aktualne nastawy) ---
    QJsonObject jsonPID;
    jsonPID["Kp"] = ui->spinKp->value();
    jsonPID["Ti"] = ui->spinTi->value();
    jsonPID["Td"] = ui->spinTd->value();
    root["PID"] = jsonPID;

    // --- SEKCJA GENERATOR ---
    QJsonObject jsonGEN;
    jsonGEN["Amplituda"] = ui->spinAmp->value();
    jsonGEN["Okres"] = ui->spinOkres->value();
    jsonGEN["Wypelnienie"] = ui->spinWypelnienie->value();
    jsonGEN["Stala"] = ui->spinStala->value();
    jsonGEN["Typ"] = ui->comboTyp->currentIndex();
    root["Generator"] = jsonGEN;

    // --- SEKCJA ARX (Pobieramy z backendu, bo to skomplikowane wektory) ---
    QJsonObject jsonARX;

    // Zapisujemy wektor A
    QJsonArray arrayA;
    for (double val : symulatorUAR->getARX().getA()) {
        arrayA.append(val);
    }
    jsonARX["A"] = arrayA;

    // Zapisujemy wektor B
    QJsonArray arrayB;
    for (double val : symulatorUAR->getARX().getB()) {
        arrayB.append(val);
    }
    jsonARX["B"] = arrayB;

    jsonARX["k"] = symulatorUAR->getARX().getK();
    // Jeśli masz metodę getSzum() w ARX, odkomentuj:
    // jsonARX["szum"] = symulatorUAR->getARX().getSzum();

    root["ARX"] = jsonARX;

    // --- SEKCJA SYMULACJI ---
    root["Interwal"] = ui->spinInterwal->value();


    // 3. Zapisz do pliku
    QFile file(nazwaPliku);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Błąd", "Nie można zapisać pliku!");
        return;
    }

    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();

    // Wyświetl info na pasku statusu (opcjonalnie)
    ui->statusbar->showMessage("Zapisano konfigurację!", 3000);
}
void MainWindow::on_btnWczytaj_clicked()
{
    // 1. Otwórz okno dialogowe
    QString nazwaPliku = QFileDialog::getOpenFileName(this, "Wczytaj konfigurację", "", "Pliki JSON (*.json)");
    if (nazwaPliku.isEmpty()) return;

    // 2. Otwórz i przeczytaj plik
    QFile file(nazwaPliku);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Błąd", "Nie można otworzyć pliku!");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    // 3. Parsuj JSON
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        QMessageBox::critical(this, "Błąd", "Błędny format pliku!");
        return;
    }
    QJsonObject root = doc.object();

    // --- WCZYTANIE PID (Ustawiamy UI, pętla symulacji sama zaktualizuje backend) ---
    if (root.contains("PID")) {
        QJsonObject jsonPID = root["PID"].toObject();
        ui->spinKp->setValue(jsonPID["Kp"].toDouble());
        ui->spinTi->setValue(jsonPID["Ti"].toDouble());
        ui->spinTd->setValue(jsonPID["Td"].toDouble());
    }

    // --- WCZYTANIE GENERATORA ---
    if (root.contains("Generator")) {
        QJsonObject jsonGEN = root["Generator"].toObject();
        ui->spinAmp->setValue(jsonGEN["Amplituda"].toDouble());
        ui->spinOkres->setValue(jsonGEN["Okres"].toDouble());
        ui->spinWypelnienie->setValue(jsonGEN["Wypelnienie"].toDouble());
        if(jsonGEN.contains("Stala")) {
                     ui->spinStala->setValue(jsonGEN["Stala"].toDouble());
                }
        ui->comboTyp->setCurrentIndex(jsonGEN["Typ"].toInt());
    }

    // --- WCZYTANIE ARX (To najważniejsze - musimy ręcznie wgrać do modelu) ---
    if (root.contains("ARX")) {
        QJsonObject jsonARX = root["ARX"].toObject();

        // Czytamy wektor A
        std::vector<double> newA;
        QJsonArray arrA = jsonARX["A"].toArray();
        for (const auto &val : arrA) newA.push_back(val.toDouble());

        // Czytamy wektor B
        std::vector<double> newB;
        QJsonArray arrB = jsonARX["B"].toArray();
        for (const auto &val : arrB) newB.push_back(val.toDouble());

        int newK = jsonARX["k"].toInt();

        // Ustawiamy w backendzie
        symulatorUAR->getARX().ustawA(newA);
        symulatorUAR->getARX().ustawB(newB);
        symulatorUAR->getARX().ustawOpoznienie(newK);

        // Opcjonalnie szum:
        // if(jsonARX.contains("szum")) ...
    }

    // --- WCZYTANIE INTERWAŁU ---
    if (root.contains("Interwal")) {
        ui->spinInterwal->setValue(root["Interwal"].toInt());
    }

    // 4. Reset po wczytaniu (Dobra praktyka)
    on_btnReset_clicked();

    QMessageBox::information(this, "Sukces", "Wczytano konfigurację pomyślnie.");
}
