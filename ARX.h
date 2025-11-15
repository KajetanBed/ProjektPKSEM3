#pragma once
#include <vector>
#include <deque>
#include <random>
using namespace std;

class ARX
{
private:
    vector<double> a;
    vector<double> b;
    int k;
    deque<double> yHist;
    deque<double> uHist;
    deque<double> kBuffer;

    double uMin, uMax;
    double yMin, yMax;
    bool stanLimitow;

    double amplitudaSzumu;
    bool stanSzumu;
    random_device gen;
    mt19937 generator;
    normal_distribution<double> distribution;

    double generujSzum();

    double zastosujLimity(double, double, double);

public:
    ARX(vector<double>, vector<double>, int);
    double symuluj(double);

    void ustawParametry(vector<double>, vector<double>, int);
    void ustawA(vector<double>);
    void ustawB(vector<double>);
    void ustawOpoznienie(int);

    void ustawLimitWejscia(double, double);
    void ustawLimitWyjscia(double, double);

    void przelaczLimity(bool);
    void przelaczSzum(bool);
};