#pragma once
#include <vector>
#include "ARX.h"
#include "GWZ.h"
#include "PID.h"
#include "UAR.h"

class WarstwaU
{
private:
    UAR *symulator; // WarstwaU jest teraz właścicielem obiektu UAR

public:
    WarstwaU();
    ~WarstwaU(); // Destruktor do posprzątania po UAR

    // --- ARX ---
    // Usunięto argument 'UAR* uar' ze wszystkich metod
    void setArxA(const std::vector<double> &a);
    void setArxB(const std::vector<double> &b);
    void setArxK(int k);
    void setArxDelay(int k);
    void setArxLimits(double uMin, double uMax, double yMin, double yMax);
    void setArxInputLimit(double Min, double Max);
    void setArxOutputLimit(double Min, double Max);
    void toggleArxLimits(bool stan);
    void toggleArxNoise(bool stan);
    double calculateARX(double u);
    std::vector<double> getArxA();
    std::vector<double> getArxB();
    int getArxK();
    double getArxNoise();
    double getArxUMin();
    double getArxUMax();
    double getArxYMin();
    double getArxYMax();
    bool getArxLimitsActive();
    bool getArxNoiseActive();

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
    void resetPid();
    double calculatePID(double uchyb, double dt);
    PID::trybCalki getPidMode();

    // --- UAR ---
    double simulateUAR(double zadanie);
};
