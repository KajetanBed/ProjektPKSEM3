#include "ARX.h"
#include "PID.h"
#include "GWZ.h"
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

int main()
{
    GeneratorWartosciZadanej g1(2.0, 1.0, 0.0, 0.5, 200, TypSygnalu::Sinusoida);

    std::cout << "Sinusoida (10 próbek):\n";
    for (int k = 0; k < 10; ++k)
    {
        double w = g1.obliczSygnal();
        std::cout << "i=" << std::setw(2) << k
                  << "   w = " << std::fixed << std::setprecision(3) << w << "\n";
    }
}