#include "WarstwaU.h"

// ------------------- KONSTRUKTOR -------------------

WarstwaU::WarstwaU() = default;

// ------------------- ARX -------------------

void WarstwaU::setArxA(ARX &arx, const std::vector<double> &a)
{
    arx.ustawA(a);
}

void WarstwaU::setArxB(ARX &arx, const std::vector<double> &b)
{
    arx.ustawB(b);
}

void WarstwaU::setArxDelay(ARX &arx, int k)
{
    arx.ustawOpoznienie(k);
}

void WarstwaU::setArxLimits(ARX &arx, double uMin, double uMax, double yMin, double yMax)
{
    arx.ustawLimitWejscia(uMin, uMax);
    arx.ustawLimitWyjscia(yMin, yMax);
}

void WarstwaU::toggleArxLimits(ARX &arx, bool stan)
{
    arx.przelaczLimity(stan);
}

void WarstwaU::toggleArxNoise(ARX &arx, bool stan)
{
    arx.przelaczSzum(stan);
}

// ------------------- GWZ ----------------------

void WarstwaU::setGwzAmplitude(GeneratorWartosciZadanej &gwz, double A)
{
    gwz.setAmplituda(A);
}

void WarstwaU::setGwzPeriod(GeneratorWartosciZadanej &gwz, double T)
{
    gwz.setOkres(T);
}

void WarstwaU::setGwzStala(GeneratorWartosciZadanej &gwz, double S)
{
    gwz.setStala(S);
}

void WarstwaU::setGwzWypelnienie(GeneratorWartosciZadanej &gwz, double p)
{
    gwz.setWypelnienie(p);
}

void WarstwaU::setGwzType(GeneratorWartosciZadanej &gwz, TypSygnalu typ)
{
    gwz.setTyp(typ);
}

double WarstwaU::generateGwz(GeneratorWartosciZadanej &gwz)
{
    return gwz.obliczSygnal();
}

// ------------------- PID -------------------

void WarstwaU::setPidK(PID &pid, double k)
{
    pid.setK(k);
}

void WarstwaU::setPidTI(PID &pid, double TI)
{
    pid.setTI(TI);
}

void WarstwaU::setPidTD(PID &pid, double TD)
{
    pid.setTD(TD);
}

void WarstwaU::setPidMode(PID &pid, PID::trybCalki tryb)
{
    pid.setTryb(tryb);
}

void WarstwaU::resetPid(PID &pid)
{
    pid.resetujSumeUchybu();
}

// ------------------- UAR ----------------------------------------

double WarstwaU::simulateUAR(UAR &uar, double zadanie)
{
    return uar.symuluj(zadanie);
}