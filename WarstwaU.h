#pragma once
#include "ARX.h"
#include "GWZ.h"
#include "PID.h"
#include "UAR.h"

class WarstwaU
{
public:
    WarstwaU() = default;

    // --- ARX ---
    void setArxA(ARX& arx, const vector<double>& a) { arx.ustawA(a); }
    void setArxB(ARX& arx, const vector<double>& b) { arx.ustawB(b); }
    void setArxDelay(ARX& arx, int k) { arx.ustawOpoznienie(k); }
    void setArxLimits(ARX& arx, double uMin, double uMax, double yMin, double yMax)
    {
        arx.ustawLimitWejscia(uMin, uMax);
        arx.ustawLimitWyjscia(yMin, yMax);
    }
    void toggleArxLimits(ARX& arx, bool stan) { arx.przelaczLimity(stan); }
    void toggleArxNoise(ARX& arx, bool stan) { arx.przelaczSzum(stan); }

    // --- GWZ ---
    void setGwzAmplitude(GeneratorWartosciZadanej& gwz, double A) { gwz.setAmplituda(A); }
    void setGwzPeriod(GeneratorWartosciZadanej& gwz, double T) { gwz.setOkres(T); }
    void setGwzStala(GeneratorWartosciZadanej& gwz, double S) { gwz.setStala(S); }
    void setGwzWypelnienie(GeneratorWartosciZadanej& gwz, double p) { gwz.setWypelnienie(p); }
    void setGwzType(GeneratorWartosciZadanej& gwz, TypSygnalu typ) { gwz.setTyp(typ); }
    double generateGwz(GeneratorWartosciZadanej& gwz) { return gwz.obliczSygnal(); }

    // --- PID ---
    void setPidK(PID& pid, double k) { pid.setK(k); }
    void setPidTI(PID& pid, double TI) { pid.setTI(TI); }
    void setPidTD(PID& pid, double TD) { pid.setTD(TD); }
    void setPidMode(PID& pid, PID::trybCalki tryb) { pid.setTryb(tryb); }
    void resetPid(PID& pid) { pid.resetujSumeUchybu(); }

    // --- UAR ---
    double simulateUAR(UAR& uar, double zadanie) { return uar.symuluj(zadanie); }
};
