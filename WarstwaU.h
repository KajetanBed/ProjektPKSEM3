#pragma once
#include <QObject> // <-- Ważne
#include <QTimer>  // <-- Ważne
#include <vector>
#include "ARX.h"
#include "GWZ.h"
#include "PID.h"
#include "UAR.h"

// Dziedziczymy po QObject, aby obsługiwać sygnały i timery
class WarstwaU : public QObject
{
    Q_OBJECT // Makro wymagane dla sygnałów/slotów

private:
    UAR *symulator;
    QTimer *zegarSymulacji; // Timer teraz jest tutaj

public:
    explicit WarstwaU(QObject *parent = nullptr); // Konstruktor z rodzicem Qt
    ~WarstwaU();

    // --- STEROWANIE SYMULACJĄ ---
    void startSymulacji(int interwalMs);
    void stopSymulacji();
    void setInterwalSymulacji(int ms);
    bool czySymulacjaDziala() const;
    double getInterwalSekundy() const; // Pomocnicze dla obliczeń dt

signals:
    // Sygnał wysyłany co tyknięcie zegara -> łapie go MainWindow
    void zadanieOdswiezenia();

public:

    // --- ARX ---
    void setArxA(const std::vector<double> &a);
    void setArxB(const std::vector<double> &b);
    void setArxK(int k);
    void setArxDelay(int k);
    void setArxLimits(double uMin, double uMax, double yMin, double yMax);
    void setArxInputLimit(double Min, double Max);
    void setArxOutputLimit(double Min, double Max);
    void toggleArxLimits(bool stan);
    void toggleArxNoise(bool stan);
    void setArxNoiseAmplitude(double amp);
    double calculateARX(double u);
    std::vector<double> getArxA();
    std::vector<double> getArxB();
    int getArxK();
    double getArxNoise();
    bool getArxLimitsActive();
    bool getArxNoiseActive();
    double getArxUMin();
    double getArxUMax();
    double getArxYMin();
    double getArxYMax();

    // --- GWZ ---
    void setGwzAmplitude(double A);
    void setGwzPeriod(double T);
    void setGwzStala(double S);
    void setGwzWypelnienie(double p);
    void setGwzType(TypSygnalu typ);
    void setGwzTT(double tt);
    double generateGwz();
    void resetGwz();

    // --- PID ---
    void setPidK(double k);
    void setPidTI(double TI);
    void setPidTD(double TD);
    double PIDgetP();
    double PIDgetI();
    double PIDgetD();
    void setPidMode(PID::trybCalki tryb);
    PID::trybCalki getPidMode();
    void resetPid();
    double calculatePID(double uchyb, double dt);

    // --- UAR ---
    double simulateUAR(double zadanie);
};
