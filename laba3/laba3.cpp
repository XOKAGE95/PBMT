 #include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#define g 9.8
#define m_pi 3.141592
using namespace std;

float eps = 0.000001;
/*
Лабораторная 3 будет весь раздел "СВОБОДНОЕ ПАДЕНИЕ ТЕЛА С УЧЕТОМ СОПРОТИВЛЕНИЯ СРЕДЫ".
Везде надо будет строить графики h(t), v(t), a(t) согласно своему варианту, который соответствует номеру записи в журнале старосты
*/

Case1 (float v, float dt)
{
	float m = 65, h = 1.5 , r = 0.5 , c = 1.22, k2, dh = 0, a = 0, ai = 0, vi, t = 0;
    vi = v;
    k2 = h * r * 0.5 * c * 1.29;
    ofstream file;
    file.open("case 1.txt");
    file << setw(15) << left << "acceleration" << setw(15) << left <<"speed"<< setw(10) << left << "distance" << endl;
    do
    {
        v = vi;
        a = ai;

        a = (m * g - k2 * v * v)/m;
        file << setw(15) << setprecision(5) << left << a;


        vi = v + dt/2*((m*g - k2*v*v)/m + (m*g - k2*pow((v + dt * (m*g - k2*v*v)/m), 2))/m);
        file << setw(15) << setprecision(10) << left << vi;


        dh += vi * dt;
        file << setw(10) << left << dh << endl;

        t += dt;

    }
    while (abs(v - vi) >= eps);
    cout << "Time = " << t << endl;
}

Case2 (float v, float dt)
{
    float m = 80, r = 2.5 , c = 0.4, k2, dh = 0, a = 0, vi, t = 0;
    vi = v;
    k2 = m_pi * r * r * 0.5 * c * 1.29;
    ofstream file;
    file.open("case 2.txt");
    file << setw(15) << left << "acceleration" << setw(15) << left <<"speed"<< setw(10) << left << "distance" << endl;
    do
    {
        v = vi;

        a = (m * g - k2 * v * v)/m;
        file << setw(15) << setprecision(5) << left << a;


        vi = v + dt/2*((m*g - k2*v*v)/m + (m*g - k2*pow((v + dt * (m*g - k2*v*v)/m), 2))/m);
        file << setw(15) << setprecision(10) << left << vi;


        dh += vi * dt;
        file << setw(10) << left << dh << endl;

        t += dt;

    }
    while (abs(v - vi) >= eps);
    cout << "Time = " << t << endl;;
}

Case3 (float v, float dt)
{
    float m, r = 0.1 , ro_b = 8930, ro_s = 1000, k1, dh = 0, a = 0, vi, t = 0, mu = 1180;
    vi = v;
    float V = 4/3*m_pi*r;
    k1 = 6*m_pi*r*mu;
    m = ro_b*V;
    float m1 = (ro_b - ro_s) * V;
    ofstream file;
    file.open("case 3.txt");
    file << setw(15) << left << "acceleration" << setw(15) << left <<"speed"<< setw(10) << left << "distance" << endl;
    do
    {
        v = vi;

        a = (m * g - k1 * v)/m;
        file << setw(15) << setprecision(5) << left << a;


        vi = v + dt/2*((m1*g - k1*v)/m + (m1*g - k1*((v + dt * (m1*g - k1*v)/m)))/m);
        file << setw(15) << setprecision(10) << left << vi;


        dh += vi * dt;
        file << setw(10) << left << dh << endl;

        t += dt;

    }
    while (abs(v - vi) >= eps);
    cout << "Time = " << t << endl;;

}

int main()
{
    float v, dt;
    cout << "Enter v: ";
    cin >> v;
    cout << "Enter dt: ";
    cin >> dt;

    Case1(v, dt);
    Case2(v, dt);
    Case3(v, dt);
    return 0;
}
