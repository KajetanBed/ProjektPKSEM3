#pragma once
#include <vector>
#include "ARX.h"
#include "GWZ.h"
#include "PID.h"
#include "UAR.h"

class WarstwaU
{
public:
    WarstwaU() = default;

    // --- ARX ---
    void setArxA(UAR *uar, const std::vector<double> &a);
    void setArxB(UAR *uar, const std::vector<double> &b);
    void setArxK(UAR *uar, int k);
    void setArxDelay(UAR *uar, int k);
    void setArxLimits(UAR *uar, double uMin, double uMax, double yMin, double yMax);
    void setArxInputLimit(UAR *uar, double Min, double Max);
    void setArxOutputLimit(UAR *uar, double Min, double Max);
    void toggleArxLimits(UAR *uar, bool stan);
    void toggleArxNoise(UAR *uar, bool stan);
    double calculateARX(UAR *uar, double u);
    std::vector<double> getArxA(UAR *uar);
    std::vector<double> getArxB(UAR *uar);
    int getArxK(UAR *uar);

    // --- GWZ ---
    void setGwzAmplitude(UAR *uar, double A);
    void setGwzPeriod(UAR *uar, double T);
    void setGwzStala(UAR *uar, double S);
    void setGwzWypelnienie(UAR *uar, double p);
    void setGwzType(UAR *uar, TypSygnalu typ);
    void setGwzTT(UAR *uar, double tt);
    double generateGwz(UAR *uar);
    void resetGwz(UAR *uar);

    // --- PID ---
    void setPidK(UAR *uar, double k);
    void setPidTI(UAR *uar, double TI);
    void setPidTD(UAR *uar, double TD);
    double PIDgetP(UAR *uar);
    double PIDgetI(UAR *uar);
    double PIDgetD(UAR *uar);
    void setPidMode(UAR *uar, PID::trybCalki tryb);
    void resetPid(UAR *uar);
    double calculatePID(UAR *uar, double uchyb, double dt);

    // --- UAR ---
    double simulateUAR(UAR *uar, double zadanie);
};
