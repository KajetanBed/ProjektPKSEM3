#pragma once
#include <vector>
#include "ARX.h"
#include "GWZ.h"
#include "PID.h"
#include "UAR.h"

class WarstwaU
{
public:
    WarstwaU();

    // --- ARX ---
    void setArxA(UAR &uar, const std::vector<double> &a);
    void setArxB(UAR &uar, const std::vector<double> &b);
    void setArxDelay(UAR &uar, int k);
    void setArxLimits(UAR &uar, double uMin, double uMax, double yMin, double yMax);
    void toggleArxLimits(UAR &uar, bool stan);
    void toggleArxNoise(UAR &uar, bool stan);

    // --- GWZ ---
    void setGwzAmplitude(UAR &uar, double A);
    void setGwzPeriod(UAR &uar, double T);
    void setGwzStala(UAR &uar, double S);
    void setGwzWypelnienie(UAR &uar, double p);
    void setGwzType(UAR &uar, TypSygnalu typ);
    double generateGwz(UAR &uar);

    // --- PID ---
    void setPidK(UAR &uar, double k);
    void setPidTI(UAR &uar, double TI);
    void setPidTD(UAR &uar, double TD);
    void setPidMode(UAR &uar, PID::trybCalki tryb);
    void resetPid(UAR &uar);

    // --- UAR ---
    double simulateUAR(UAR &uar, double zadanie);
};
