#pragma once

bool wynik_testu(const std::string& nazwa, const std::vector<double>& oczek, const std::vector<double>& wynik);
void test_ARX_sin_z_opoznieniem();
void test_ARX_zmiana_parametrow_w_locie();
void test_GWZ_dynamiczna_czestotliwosc();
void test_GWZ_prostokat_73proc();
void test_PID_oscylacje();
void test_PID_szybkie_impulsy();
void test_UAR_sinus_z_pid();
void test_UAR_skok_co_10();
void test_WarstwaU_dynamiczna_konfiguracja();
void test_WarstwaU_reset();

void testALL();