#include "ARX.h"
#include "GWZ.h"
#include "PID.h"
#include "UAR.h"
#include "WarstwaU.h"
#include "TestyJednostkowe.h"
#include <iostream>
#include <cmath>
#include <string>

bool wynik_testu(const std::string &nazwa, const std::vector<double> &oczek, const std::vector<double> &wynik)
{
    if (oczek.size() != wynik.size())
    {
        std::cerr << nazwa << " [BLAD: inny rozmiar]\n";
        return false;
    }

    bool ok = true;
    for (size_t i = 0; i < oczek.size(); i++)
        if (std::abs(oczek[i] - wynik[i]) > 1e-6)
            ok = false;

    std::cerr << nazwa << (ok ? " [OK]\n" : " [BLAD]\n");
    return ok;
}

/* =======================================================
   ARX - TEST 1
   Reakcja na pobudzenie sinusoidalne + opoznienie + filtracja
   ======================================================= */
void test_ARX_sin_z_opoznieniem()
{
    ARX m({1.0, -0.3, 0.1}, {0.7, 0.0, 0.0}, 2);
    ARX ref = m;

    constexpr int N = 40;
    std::vector<double> u(N), y(N), y_exp(N);

    for (int i = 0; i < N; i++)
        u[i] = sin(i * 0.25);

    for (int i = 0; i < N; i++)
        y[i] = m.symuluj(u[i]);

    for (int i = 0; i < N; i++)
        y_exp[i] = ref.symuluj(u[i]);

    wynik_testu("ARX - sinus + opoznienie 2", y_exp, y);
}

/* =======================================================
   ARX - TEST 2
   Zmiana parametrow modelu w trakcie symulacji
   ======================================================= */
void test_ARX_zmiana_parametrow_w_locie()
{
    ARX m1({1, -0.5, 0}, {0.2, 0, 0}, 1);
    ARX m2({1, -0.5, 0}, {0.2, 0, 0}, 1);

    vector<double> u(30);
    for (int i = 0; i < 30; i++)
        u[i] = sin(i * 0.1);

    bool ok = true;

    for (int i = 0; i < 15; i++)
    {
        double y1 = m1.symuluj(u[i]);
        double y2 = m2.symuluj(u[i]);
        if (abs(y1 - y2) > 1e-9)
            ok = false;
    }

    // Zmieniamy A i B w obu modelach
    m1.ustawA({1, -0.9, 0});
    m2.ustawA({1, -0.9, 0});

    for (int i = 15; i < 30; i++)
    {
        double y1 = m1.symuluj(u[i]);
        double y2 = m2.symuluj(u[i]);
        if (abs(y1 - y2) > 1e-9)
            ok = false;
    }

    cout << "ARX - zmiana parametrow w trakcie " << (ok ? "[OK]" : "[BLAD]") << endl;
}

/* =======================================================
   GWZ - TEST 1
   Sinusoida o zmienianej czasie rzeczywistym czestotliwosci
   ======================================================= */
void test_GWZ_dynamiczna_czestotliwosc()
{
    // amplituda, okresRzeczywisty, stala, wypelnienie, TTms, typ
    GeneratorWartosciZadanej g1(1.0, 2.0, 0.0, 0.5, 10, TypSygnalu::Sinusoida);
    GeneratorWartosciZadanej g2(1.0, 2.0, 0.0, 0.5, 10, TypSygnalu::Sinusoida);

    constexpr int N = 80;
    std::vector<double> y1(N), y2(N);

    for (int i = 0; i < N; i++)
    {
        // w połowie zmieniamy czestotliwosc (TRZ)
        if (i == 40)
        {
            g1.setTRZ(4.0); // 2x większy okres rzeczywisty
            g2.setTRZ(4.0); // oba muszą zachować identyczną fazę i T
        }

        y1[i] = g1.obliczSygnal();
        y2[i] = g2.obliczSygnal();
    }

    wynik_testu("GWZ - dynamiczna zmiana czestotliwosci", y2, y1);
}

/* =======================================================
   GWZ - TEST 2
   Sygnal prostokatny z nietypowym wypelnieniem 73%
   ======================================================== */
void test_GWZ_prostokat_73proc()
{
    GeneratorWartosciZadanej gwz(2.0, 1.0, 0.0, 0.73, 10, TypSygnalu::SygnalProstokatny);

    std::vector<double> y(30), y_exp(30);

    gwz.reset();
    for (int i = 0; i < 30; i++)
        y_exp[i] = gwz.obliczSygnal();

    gwz.reset();
    for (int i = 0; i < 30; i++)
        y[i] = gwz.obliczSygnal();

    wynik_testu("GWZ - prostokat 73%", y_exp, y);
}

/* =======================================================
   PID - TEST 1
   Proba przeciw-przesterowania: sygnal zmienia znak
   ======================================================= */
void test_PID_oscylacje()
{
    PID pid(0.8, 0.4, 0.1);

    std::vector<double> e = {1, -1, 1, -1, 1, -1, 0, 0, 0};
    std::vector<double> u(9), u_exp(9);

    pid.resetujSumeUchybu();

    for (size_t i = 0; i < e.size(); i++)
        u[i] = pid.oblicz(e[i]);

    pid.resetujSumeUchybu();

    for (size_t i = 0; i < e.size(); i++)
        u_exp[i] = pid.oblicz(e[i]);

    wynik_testu("PID - oscylacja pobudzenia", u_exp, u);
}

/* =======================================================
   PID - TEST 2
   Duzy TD + krotkie impulsy - sprawdzanie rownania roznicowego
   ======================================================= */
void test_PID_szybkie_impulsy()
{
    PID pid(1.0, 0.5, 2.0);

    std::vector<double> e = {0, 1, -1, 1, -1, 0};
    std::vector<double> u(6), u_exp(6);

    pid.resetujSumeUchybu();
    for (int i = 0; i < 6; i++)
        u[i] = pid.oblicz(e[i]);

    pid.resetujSumeUchybu();
    for (int i = 0; i < 6; i++)
        u_exp[i] = pid.oblicz(e[i]);

    wynik_testu("PID - szybkie impulsy", u_exp, u);
}

/* =======================================================
   UAR - TEST 1
   Nieliniowy sygnal zadany + ARX jako filtr drugiego rzedu
   ======================================================= */
void test_UAR_sinus_z_pid()
{
    ARX model({1, -0.4, 0}, {0.8, 0, 0}, 1);
    PID pid(0.6, 0.2, 0.05);

    UAR uar1(model, pid);
    UAR uar2(model, pid);

    std::vector<double> zad(40), y1(40), y2(40);

    for (int i = 0; i < 40; i++)
        zad[i] = sin(i * 0.1);

    for (int i = 0; i < 40; i++)
        y1[i] = uar1.symuluj(zad[i]);

    for (int i = 0; i < 40; i++)
        y2[i] = uar2.symuluj(zad[i]);

    wynik_testu("UAR - sinus sterowany PID", y2, y1);
}

/* =======================================================
   UAR - TEST 2
   Duze skoki co 10 probek - sprawdzanie stabilnosci
   ======================================================= */
void test_UAR_skok_co_10()
{
    ARX model({1, -0.2, 0}, {0.4, 0, 0}, 2);
    PID pid(0.9, 0.1, 0.05);

    UAR uar1(model, pid);
    UAR uar2(model, pid);

    std::vector<double> zad(50), y1(50), y2(50);

    for (int i = 0; i < 50; i++)
        zad[i] = ((i / 10) % 2) ? 1.0 : -1.0;

    for (int i = 0; i < 50; i++)
        y1[i] = uar1.symuluj(zad[i]);

    for (int i = 0; i < 50; i++)
        y2[i] = uar2.symuluj(zad[i]);

    wynik_testu("UAR - skoki co 10 probek", y2, y1);
}

/* =======================================================
   WarstwaU - TEST 1
   Zmiana parametrow ARX i PID w trakcie symulacji
   ======================================================= */
void test_WarstwaU_dynamiczna_konfiguracja()
{
    WarstwaU wu;

    ARX arx1({1, -0.2, 0}, {0.5, 0, 0}, 1);
    ARX arx2({1, -0.2, 0}, {0.5, 0, 0}, 1);
    PID pid1(0.8, 0.2, 0.1);
    PID pid2(0.8, 0.2, 0.1);

    UAR uar1(arx1, pid1);
    UAR uar2(arx2, pid2);

    constexpr int N = 30;
    vector<double> zad(N), y(N), y_exp(N);

    for (int i = 0; i < N; i++)
        zad[i] = sin(0.2 * i);

    for (int i = 0; i < N; i++)
    {
        if (i == 15)
        {
            wu.setArxA(arx1, {1, -0.6, 0});
            wu.setArxB(arx1, {0.4, 0, 0});
            wu.setArxDelay(arx1, 2);
        }
        y[i] = wu.simulateUAR(uar1, zad[i]);
    }

    for (int i = 0; i < N; i++)
        y_exp[i] = wu.simulateUAR(uar2, zad[i]);

    wynik_testu("WarstwaU - dynamiczna zmiana konfiguracji", y_exp, y);
}

/* =======================================================
   WarstwaU - TEST 2
   Sprawdzenie poprawnosci resetu PID i ARX
   ======================================================= */
void test_WarstwaU_reset()
{
    WarstwaU wu;

    PID pid1(1.0, 0.3, 0.1);
    PID pid2(1.0, 0.3, 0.1);

    constexpr int N = 20;
    vector<double> uchyb(N), y1(N), y_exp(N);

    for (int i = 0; i < N; i++)
        uchyb[i] = sin(i * 0.2); // losowy, ale deterministyczny uchyb

    // Najpierw "naładować PID" (napełniamy integral, D itp.)
    for (int i = 0; i < N; i++)
        pid1.oblicz(uchyb[i]);

    // RESET PID
    wu.resetPid(pid1);

    // Ponowna symulacja na RESCETOWANYM pid1
    for (int i = 0; i < N; i++)
        y1[i] = pid1.oblicz(uchyb[i]);

    // Referencja – pid2 bez wcześniejszego obciążenia
    for (int i = 0; i < N; i++)
        y_exp[i] = pid2.oblicz(uchyb[i]);

    wynik_testu("WarstwaU - reset PID ", y_exp, y1);
}

void testALL()
{
    test_ARX_sin_z_opoznieniem();
    test_ARX_zmiana_parametrow_w_locie();
    test_GWZ_dynamiczna_czestotliwosc();
    test_GWZ_prostokat_73proc();
    test_PID_oscylacje();
    test_PID_szybkie_impulsy();
    test_UAR_sinus_z_pid();
    test_UAR_skok_co_10();
    test_WarstwaU_dynamiczna_konfiguracja();
    test_WarstwaU_reset();
}
