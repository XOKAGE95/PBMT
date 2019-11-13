#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
const double G = 6.67408E-11;
const double M = 5.97E24;
const double R = 6.37E6;
const double Betta = 1.29E-4;
const double Alfa = 3135;
const double c = 0.45;
const double S = 83.322;
const double F = 4 * 1E6;

using namespace std;

int main()
{
	double m0, m, a, v, h, dt, t, mk, k2, g, ro, ro0;
		// Зададим началтные данные
	h = 0;
	t = 0;
	ro0 = 1.29;
	m0 = 3E5;
	mk = 3E4;
	v = 0;
    k2 = c*S*ro;		// Формула для коэффициента сопротивления среды
    cout << "Enter dt" <<endl;
    cin >> dt;
    ofstream file;
    file.open("case_1.txt");
    do
    {
        m = (m0- Alfa * t);		// Формула для массы ракеты
        g = (G * M)/((R + h)*(R + h));  // Формула для ускорения свободного падения
        ro = ro0* exp(-Betta*h); 	// Формула для плотности среды




        a = (F - m*g - k2 * v * v)/m;
        file << setw(15) << setprecision(5) << left << a;
        v += a * dt;
        file << setw(15) << setprecision(10) << left << v;


        h += v * dt;
        file << setw(10) << left << h  << endl;

        t += dt;

    }
    while (m > mk);
    cout << "Time =" << t << " Seconds";
    file.close();
}
