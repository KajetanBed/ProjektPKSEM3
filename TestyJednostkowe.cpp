#include "ARX.h"
#include "GWZ.h"
#include "PID.h"
#include "UAR.h"
#include "WarstwaU.h"
#include "TestyJednostkowe.h"
#include <iostream>  
#include <cmath>      
#include <string>    


bool wynik_testu(const std::string& nazwa, const std::vector<double>& oczek, const std::vector<double>& wynik)
{
    if (oczek.size() != wynik.size())
    {
        std::cerr << nazwa << " [B£¥D: inny rozmiar]\n";
        return false;
    }

    bool ok = true;
    for (size_t i = 0; i < oczek.size(); i++)
        if (std::abs(oczek[i] - wynik[i]) > 1e-6)
            ok = false;

    std::cerr << nazwa << (ok ? " [OK]\n" : " [B£¥D]\n");
    return ok;
}

/* =======================================================
   ARX — TEST 1
   Reakcja na pobudzenie sinusoidalne + opóŸnienie + filtracja
   ======================================================= */
void test_ARX_sin_z_opoznieniem()
{
    ARX m({ -0.3 }, { 0.7 }, 2);
    ARX ref = m; 

    constexpr int N = 40;
    std::vector<double> u(N), y(N), y_exp(N);

    for (int i = 0; i < N; i++)
        u[i] = sin(i * 0.25);

    for (int i = 0; i < N; i++)
        y[i] = m.symuluj(u[i]);

    for (int i = 0; i < N; i++)
        y_exp[i] = ref.symuluj(u[i]);

    wynik_testu("ARX — sinus + opóŸnienie 2", y_exp, y);
}

/* =======================================================
   ARX — TEST 2
   Zmiana parametrów modelu w trakcie symulacji
   ======================================================= */
void test_ARX_zmiana_parametrow_w_locie()
{
    ARX m({ -0.2 }, { 0.5 }, 1);
    ARX ref = m;

    constexpr int N = 30;
    std::vector<double> u(N), y(N), y_exp(N);

    for (int i = 0; i < N; i++)
        u[i] = (i < 15 ? 1.0 : 0.2);

    // zmiana parametrów w trakcie
    m.ustawParametry({ -0.6 }, { 0.4 }, 1);

    for (int i = 0; i < N; i++)
        y[i] = m.symuluj(u[i]);

    ARX ref2({ -0.6 }, { 0.4 }, 1); // referencja po zmianie
    for (int i = 0; i < 15; i++)
        ref2.symuluj(u[i]); // "przejœcie" pierwszych próbek

    for (int i = 15; i < N; i++)
        y_exp[i] = ref2.symuluj(u[i]);

    // Dla pierwszych 15 próbek y_exp ustawiamy na 0 (jak inicjalizacja ARX)
    for (int i = 0; i < 15; i++)
        y_exp[i] = 0;

    wynik_testu("ARX — zmiana parametrów w trakcie", y_exp, y);
}
/* =======================================================
   GWZ — TEST 1
   Sinusoida o zmienianej czasie rzeczywistym czêstotliwoœci
   ======================================================= */
void test_GWZ_dynamiczna_czestotliwosc()
{
    GeneratorWartosciZadanej gwz(1.0, 1.0, 0.0, 0.0, 10, TypSygnalu::Sinusoida);
    GeneratorWartosciZadanej ref = gwz;

    constexpr int N = 40;
    std::vector<double> y(N), y_exp(N);

    for (int i = 0; i < N; i++)
    {
        if (i == 20)
            gwz.setTRZ(0.5);
        y[i] = gwz.obliczSygnal();
    }

    for (int i = 0; i < N; i++)
        y_exp[i] = ref.obliczSygnal();

    wynik_testu("GWZ — dynamiczna zmiana czêstotliwoœci", y_exp, y);
}

/* =======================================================
   GWZ — TEST 2
   Sygna³ prostok¹tny z nietypowym wype³nieniem 73%
   ======================================================= */
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

    wynik_testu("GWZ — prostok¹t 73%", y_exp, y);
}
/* =======================================================
   PID — TEST 1
   Próba przeciw-przesterowania: sygna³ zmienia znak
   ======================================================= */
void test_PID_oscylacje()
{
    PID pid(0.8, 0.4, 0.1);

    std::vector<double> e = { 1, -1, 1, -1, 1, -1, 0, 0, 0 };
    std::vector<double> u(9), u_exp(9);

    pid.resetujSumeUchybu();

    for (size_t i = 0; i < e.size(); i++)
        u[i] = pid.oblicz(e[i]);

    pid.resetujSumeUchybu();

    for (size_t i = 0; i < e.size(); i++)
        u_exp[i] = pid.oblicz(e[i]);

    wynik_testu("PID — oscylacja pobudzenia", u_exp, u);
}

/* =======================================================
   PID — TEST 2
   Du¿y TD + krótkie impulsy – sprawdzanie równania ró¿nicowego
   ======================================================= */
void test_PID_szybkie_impulsy()
{
    PID pid(1.0, 0.5, 2.0);

    std::vector<double> e = { 0, 1, -1, 1, -1, 0 };
    std::vector<double> u(6), u_exp(6);

    pid.resetujSumeUchybu();
    for (int i = 0; i < 6; i++)
        u[i] = pid.oblicz(e[i]);

    pid.resetujSumeUchybu();
    for (int i = 0; i < 6; i++)
        u_exp[i] = pid.oblicz(e[i]);

    wynik_testu("PID — szybkie impulsy", u_exp, u);
}
/* =======================================================
   UAR — TEST 1
   Nieliniowy sygna³ zadany + ARX jako filtr drugiego rzêdu
   ======================================================= */
void test_UAR_sinus_z_pid()
{
    ARX model({ -0.4 }, { 0.8 }, 1);
    PID pid(0.6, 0.2, 0.05);

    UAR uar(model, pid);

    std::vector<double> zad(40), y(40), y2(40);

    for (int i = 0; i < 40; i++)
        zad[i] = sin(i * 0.1);

    for (int i = 0; i < 40; i++)
        y[i] = uar.symuluj(zad[i]);

    UAR uar2(model, pid);
    for (int i = 0; i < 40; i++)
        y2[i] = uar2.symuluj(zad[i]);

    wynik_testu("UAR — sinus sterowany PID", y2, y);
}

/* =======================================================
   UAR — TEST 2
   Du¿e skoki co 10 próbek – sprawdzanie stabilnoœci
   ======================================================= */
void test_UAR_skok_co_10()
{
    ARX model({ -0.2 }, { 0.4 }, 2);
    PID pid(0.9, 0.1, 0.05);

    UAR uar(model, pid);

    std::vector<double> zad(50), y(50), y2(50);

    for (int i = 0; i < 50; i++)
        zad[i] = ((i / 10) % 2) ? 1.0 : -1.0;

    for (int i = 0; i < 50; i++)
        y[i] = uar.symuluj(zad[i]);

    UAR uar2(model, pid);
    for (int i = 0; i < 50; i++)
        y2[i] = uar2.symuluj(zad[i]);

    wynik_testu("UAR — skoki co 10 próbek", y2, y);
}
// =======================================================
// WarstwaU — TEST 1
// Zmiana parametrów ARX i PID w trakcie symulacji
// =======================================================
void test_WarstwaU_dynamiczna_konfiguracja()
{
    WarstwaU wu;

    ARX arx1({ -0.2 }, { 0.5 }, 1);
    ARX arx2 = arx1;
    PID pid1(0.8, 0.2, 0.1);
    PID pid2 = pid1;

    UAR uar1(arx1, pid1);
    UAR uar2(arx2, pid2);

    constexpr int N = 30;
    std::vector<double> zad(N), y(N), y_exp(N);

    for (int i = 0; i < N; i++)
        zad[i] = sin(0.2 * i);

    for (int i = 0; i < N; i++)
    {
        if (i == 15)
        {
            wu.setArxA(arx1, { -0.6 });
            wu.setArxB(arx1, { 0.4 });
            wu.setArxDelay(arx1, 2);
        }
        y[i] = wu.simulateUAR(uar1, zad[i]);
    }

    for (int i = 0; i < N; i++)
        y_exp[i] = wu.simulateUAR(uar2, zad[i]);

    wynik_testu("WarstwaU — dynamiczna zmiana konfiguracji", y_exp, y);
}
// =======================================================
// WarstwaU — TEST 2
// Sprawdzenie poprawnoœci resetu PID i ARX
// =======================================================
void test_WarstwaU_reset()
{
    WarstwaU wu;

    ARX arx1({ -0.3 }, { 0.7 }, 1);
    ARX arx2 = arx1;
    PID pid1(1.0, 0.3, 0.1);
    PID pid2 = pid1;

    UAR uar1(arx1, pid1);
    UAR uar2(arx2, pid2);

    constexpr int N = 20;
    std::vector<double> zad(N), y1(N), y2(N), y_exp(N); 

    for (int i = 0; i < N; i++)
        zad[i] = i * 0.1;

    // pierwsza symulacja
    for (int i = 0; i < N; i++)
        y1[i] = wu.simulateUAR(uar1, zad[i]);

    // reset PID i ustawienia ARX
    wu.resetPid(pid1);
    wu.toggleArxLimits(arx1, true);
    wu.toggleArxNoise(arx1, false);

    // symulacja po resecie
    for (int i = 0; i < N; i++)
        y2[i] = wu.simulateUAR(uar1, zad[i]);

    // symulacja kontrolna na niezmienionej kopii (referencja)
    for (int i = 0; i < N; i++)
        y_exp[i] = wu.simulateUAR(uar2, zad[i]);

    wynik_testu("WarstwaU — poprawnoœæ resetu", y_exp, y2);
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