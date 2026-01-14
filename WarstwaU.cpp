#include "WarstwaU.h"

// ------------------- KONSTRUKTOR -------------------

// ------------------- ARX -------------------

void WarstwaU::setArxA(UAR *uar, const std::vector<double> &a)
{
    uar->getARX().ustawA(a);
}

void WarstwaU::setArxB(UAR *uar, const std::vector<double> &b)
{
    uar->getARX().ustawB(b);
}

void WarstwaU::setArxDelay(UAR *uar, int k)
{
    uar->getARX().ustawOpoznienie(k);
}

void WarstwaU::setArxLimits(UAR *uar, double uMin, double uMax, double yMin, double yMax)
{
    uar->getARX().ustawLimitWejscia(uMin, uMax);
    uar->getARX().ustawLimitWyjscia(yMin, yMax);
}

void WarstwaU::toggleArxLimits(UAR *uar, bool stan)
{
    uar->getARX().przelaczLimity(stan);
}

void WarstwaU::toggleArxNoise(UAR *uar, bool stan)
{
    uar->getARX().przelaczSzum(stan);
}

double WarstwaU::calculateARX(UAR *uar, double u)
{
    return uar->getARX().symuluj(u);
}

std::vector<double> WarstwaU::getArxA(UAR *uar)
{
    return uar->getARX().getA();
}

std::vector<double> WarstwaU::getArxB(UAR *uar)
{
    return uar->getARX().getB();
}

int WarstwaU::getArxK(UAR *uar)
{
    return uar->getARX().getK();
}

void WarstwaU::setArxInputLimit(UAR *uar, double Min, double Max)
{
    uar->getARX().ustawLimitWejscia(Min, Max);
}

void WarstwaU::setArxOutputLimit(UAR *uar, double Min, double Max)
{
    uar->getARX().ustawLimitWyjscia(Min, Max);
}

void WarstwaU::setArxK(UAR *uar, int k)
{
    uar->getARX().ustawOpoznienie(k);
}

// ------------------- GWZ ----------------------

void WarstwaU::setGwzAmplitude(UAR *uar, double A)
{
    uar->getGWZ().setAmplituda(A);
}

void WarstwaU::setGwzPeriod(UAR *uar, double T)
{
    uar->getGWZ().setTRZ(T);
}

void WarstwaU::setGwzStala(UAR *uar, double S)
{
    uar->getGWZ().setStala(S);
}

void WarstwaU::setGwzWypelnienie(UAR *uar, double p)
{
    uar->getGWZ().setWypelnienie(p);
}

void WarstwaU::setGwzType(UAR *uar, TypSygnalu typ)
{
    uar->getGWZ().setTyp(typ);
}

void WarstwaU::setGwzTT(UAR *uar, double tt)
{
    uar->getGWZ().setTT(tt);
}

double WarstwaU::generateGwz(UAR *uar)
{
    return uar->getGWZ().obliczSygnal();
}

void WarstwaU::resetGwz(UAR *uar)
{
    uar->getGWZ().reset();
}

// ------------------- PID -------------------

void WarstwaU::setPidK(UAR *uar, double k)
{
    uar->getPID().setK(k);
}

void WarstwaU::setPidTI(UAR *uar, double TI)
{
    uar->getPID().setTI(TI);
}

void WarstwaU::setPidTD(UAR *uar, double TD)
{
    uar->getPID().setTD(TD);
}

void WarstwaU::setPidMode(UAR *uar, PID::trybCalki tryb)
{
    uar->getPID().setTryb(tryb);
}

void WarstwaU::resetPid(UAR *uar)
{
    uar->getPID().resetujSumeUchybu();
}

double WarstwaU::calculatePID(UAR *uar, double uchyb, double dt)
{
    return uar->getPID().oblicz(uchyb, dt);
}

double WarstwaU::PIDgetP(UAR *uar)
{
    return uar->getPID().getP();
}

double WarstwaU::PIDgetI(UAR *uar)
{
    return uar->getPID().getI();
}

double WarstwaU::PIDgetD(UAR *uar)
{
    return uar->getPID().getD();
}

// ------------------- UAR ----------------------------------------

double WarstwaU::simulateUAR(UAR *uar, double zadanie)
{
    return uar->symuluj(zadanie);
}
