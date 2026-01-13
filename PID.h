#pragma once

class PID
{
public:
    enum class trybCalki
    {
        zew,
        wew
    };

private:
    double k;
    double TI;
    double TD;
    trybCalki typCalkowania;
    double sumaUchybu;
    double poprzedniUchyb;

    // --- NOWE ZMIENNE DO WYKRESÓW ---
    double lastP;
    double lastI;
    double lastD;

public:
    PID(double, double, double);

    void setK(double);
    void setTI(double);
    void setTD(double);
    void setTryb(trybCalki);

    void resetujSumeUchybu();

    double oblicz(double);

    // --- NOWE GETTERY ---
    double getP() const { return lastP; }
    double getI() const { return lastI; }
    double getD() const { return lastD; }
};
