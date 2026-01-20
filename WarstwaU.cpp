#include "WarstwaU.h"

// ------------------- KONSTRUKTOR I DESTRUKTOR -------------------

WarstwaU::WarstwaU()
{
    // Przenosimy inicjalizację domyślną z MainWindow tutaj
    std::vector<double> A = {-0.4, 0.1, -0.05};
    std::vector<double> B = {0.6, 0.2, 0.1};
    int k = 1;

    ARX model(A, B, k);
    PID regulator(1.0, 50.0, 0.1);
    GeneratorWartosciZadanej gen(1.0, 10.0, 0.0, 0.5, 200, TypSygnalu::SygnalProstokatny);

    // Tworzymy obiekt UAR, który jest teraz własnością tej warstwy
    symulator = new UAR(model, regulator, gen);

    // Ustawienia domyślne limitów
    symulator->getARX().ustawLimitWejscia(-10.0, 10.0);
    symulator->getARX().ustawLimitWyjscia(-10.0, 10.0);
    symulator->getARX().przelaczLimity(true);
}

WarstwaU::~WarstwaU()
{
    if (symulator)
        delete symulator;
}

// ------------------- ARX -------------------

void WarstwaU::setArxA(const std::vector<double> &a) { symulator->getARX().ustawA(a); }
void WarstwaU::setArxB(const std::vector<double> &b) { symulator->getARX().ustawB(b); }
void WarstwaU::setArxDelay(int k) { symulator->getARX().ustawOpoznienie(k); }
void WarstwaU::setArxK(int k) { symulator->getARX().ustawOpoznienie(k); }

void WarstwaU::setArxLimits(double uMin, double uMax, double yMin, double yMax)
{
    symulator->getARX().ustawLimitWejscia(uMin, uMax);
    symulator->getARX().ustawLimitWyjscia(yMin, yMax);
}

void WarstwaU::toggleArxLimits(bool stan) { symulator->getARX().przelaczLimity(stan); }
void WarstwaU::toggleArxNoise(bool stan) { symulator->getARX().przelaczSzum(stan); }
double WarstwaU::calculateARX(double u) { return symulator->getARX().symuluj(u); }
std::vector<double> WarstwaU::getArxA() { return symulator->getARX().getA(); }
std::vector<double> WarstwaU::getArxB() { return symulator->getARX().getB(); }
int WarstwaU::getArxK() { return symulator->getARX().getK(); }
double WarstwaU::getArxNoise() { return symulator->getARX().getSzum(); }

void WarstwaU::setArxInputLimit(double Min, double Max) { symulator->getARX().ustawLimitWejscia(Min, Max); }
void WarstwaU::setArxOutputLimit(double Min, double Max) { symulator->getARX().ustawLimitWyjscia(Min, Max); }

double WarstwaU::getArxUMin() { return symulator->getARX().getUMin(); }
double WarstwaU::getArxUMax() { return symulator->getARX().getUMax(); }
double WarstwaU::getArxYMin() { return symulator->getARX().getYMin(); }
double WarstwaU::getArxYMax() { return symulator->getARX().getYMax(); }
bool WarstwaU::getArxLimitsActive() { return symulator->getARX().getLimityAktywne(); }
bool WarstwaU::getArxNoiseActive() { return symulator->getARX().getSzumAktywny(); }

// ------------------- GWZ ----------------------

void WarstwaU::setGwzAmplitude(double A) { symulator->getGWZ().setAmplituda(A); }
void WarstwaU::setGwzPeriod(double T) { symulator->getGWZ().setTRZ(T); }
void WarstwaU::setGwzStala(double S) { symulator->getGWZ().setStala(S); }
void WarstwaU::setGwzWypelnienie(double p) { symulator->getGWZ().setWypelnienie(p); }
void WarstwaU::setGwzType(TypSygnalu typ) { symulator->getGWZ().setTyp(typ); }
void WarstwaU::setGwzTT(double tt) { symulator->getGWZ().setTT(tt); }
double WarstwaU::generateGwz() { return symulator->getGWZ().obliczSygnal(); }
void WarstwaU::resetGwz() { symulator->getGWZ().reset(); }

// ------------------- PID -------------------

void WarstwaU::setPidK(double k) { symulator->getPID().setK(k); }
void WarstwaU::setPidTI(double TI) { symulator->getPID().setTI(TI); }
void WarstwaU::setPidTD(double TD) { symulator->getPID().setTD(TD); }
void WarstwaU::setPidMode(PID::trybCalki tryb) { symulator->getPID().setTryb(tryb); }
void WarstwaU::resetPid() { symulator->getPID().resetujSumeUchybu(); }
double WarstwaU::calculatePID(double uchyb, double dt) { return symulator->getPID().oblicz(uchyb, dt); }

double WarstwaU::PIDgetP() { return symulator->getPID().getP(); }
double WarstwaU::PIDgetI() { return symulator->getPID().getI(); }
double WarstwaU::PIDgetD() { return symulator->getPID().getD(); }
PID::trybCalki WarstwaU::getPidMode() { return symulator->getPID().getTryb(); }

// ------------------- UAR ----------------------------------------

double WarstwaU::simulateUAR(double zadanie) { return symulator->symuluj(zadanie); }
