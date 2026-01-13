#include "WarstwaU.h"

// ------------------- KONSTRUKTOR -------------------

WarstwaU::WarstwaU() = default;

// ------------------- ARX -------------------

void WarstwaU::setArxA(UAR &uar, const std::vector<double> &a)
{
    uar.getARX().ustawA(a);
}

void WarstwaU::setArxB(UAR &uar, const std::vector<double> &b)
{
    uar.getARX().ustawB(b);
}

void WarstwaU::setArxDelay(UAR &uar, int k)
{
    uar.getARX().ustawOpoznienie(k);
}

void WarstwaU::setArxLimits(UAR &uar, double uMin, double uMax, double yMin, double yMax)
{
    uar.getARX().ustawLimitWejscia(uMin, uMax);
    uar.getARX().ustawLimitWyjscia(yMin, yMax);
}

void WarstwaU::toggleArxLimits(UAR &uar, bool stan)
{
    uar.getARX().przelaczLimity(stan);
}

void WarstwaU::toggleArxNoise(UAR &uar, bool stan)
{
    uar.getARX().przelaczSzum(stan);
}

// ------------------- GWZ ----------------------

void WarstwaU::setGwzAmplitude(UAR &uar, double A)
{
    uar.getGWZ().setAmplituda(A);
}

void WarstwaU::setGwzPeriod(UAR &uar, double T)
{
    uar.getGWZ().setOkres(T);
}

void WarstwaU::setGwzStala(UAR &uar, double S)
{
    uar.getGWZ().setStala(S);
}

void WarstwaU::setGwzWypelnienie(UAR &uar, double p)
{
    uar.getGWZ().setWypelnienie(p);
}

void WarstwaU::setGwzType(UAR &uar, TypSygnalu typ)
{
    uar.getGWZ().setTyp(typ);
}

double WarstwaU::generateGwz(UAR &uar)
{
    return uar.getGWZ().obliczSygnal();
}

// ------------------- PID -------------------

void WarstwaU::setPidK(UAR &uar, double k)
{
    uar.getPID().setK(k);
}

void WarstwaU::setPidTI(UAR &uar, double TI)
{
    uar.getPID().setTI(TI);
}

void WarstwaU::setPidTD(UAR &uar, double TD)
{
    uar.getPID().setTD(TD);
}

void WarstwaU::setPidMode(UAR &uar, PID::trybCalki tryb)
{
    uar.getPID().setTryb(tryb);
}

void WarstwaU::resetPid(UAR &uar)
{
    uar.getPID().resetujSumeUchybu();
}

// ------------------- UAR ----------------------------------------

double WarstwaU::simulateUAR(UAR &uar, double zadanie)
{
    return uar.symuluj(zadanie);
}
