#pragma once
//
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

public:
    PID(double, double, double);

    void setK(double);
    void setTI(double);
    void setTD(double);
    void setTryb(trybCalki);

    void resetujSumeUchybu();

    double oblicz(double);
};