#pragma once
#include "ARX.h"
#include "GWZ.h"
#include "PID.h"
#include "UAR.h"

class WarstwaU
{
public:
    WarstwaU();

    // --- ARX ----
    void setArxA(ARX &arx, const std::vector<double> &a);
    void setArxB(ARX &arx, const std::vector<double> &b);
    void setArxDelay(ARX &arx, int k);
    void setArxLimits(ARX &arx, double uMin, double uMax, double yMin, double yMax);
    void toggleArxLimits(ARX &arx, bool stan);
    void toggleArxNoise(ARX &arx, bool stan);
    // --- GWZ ---
    void setGwzAmplitude(GeneratorWartosciZadanej &gwz, double A);
    void setGwzPeriod(GeneratorWartosciZadanej &gwz, double T);
    void setGwzStala(GeneratorWartosciZadanej &gwz, double S);
    void setGwzWypelnienie(GeneratorWartosciZadanej &gwz, double p);
    void setGwzType(GeneratorWartosciZadanej &gwz, TypSygnalu typ);
    double generateGwz(GeneratorWartosciZadanej &gwz);

    // --- PID ---
    void setPidK(PID &pid, double k);
    void setPidTI(PID &pid, double TI);
    void setPidTD(PID &pid, double TD);
    void setPidMode(PID &pid, PID::trybCalki tryb);
    void resetPid(PID &pid);

    // --- UAR ---
    double simulateUAR(UAR &uar, double zadanie);
};