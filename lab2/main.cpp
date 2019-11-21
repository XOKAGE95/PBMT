#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#define M_PI 3.14159
#define alfa a*M_PI/180
#define g 9.8
#define e 2.71828
#define vx v*cos(alfa)
#define vy v*sin(alfa)

using namespace std;

void SLUCHAI1 (float v, double a, double deltaT)
{
    ofstream fp;
    fp.open("VIVOD1.txt");
    fp << "  x\ty\n";
    for (double t = 0; t <= (2 * v*sin(alfa) / g); t += deltaT)
    {
        fp << vx*t << "\t";
        fp << vy*t - g * t*t / 2 << endl;
    }
    fp.close();
    cout << "1 OK" << endl;
}

void SLUCHAI2(float v, float k, double a, double deltaT, int m)
{
    ofstream fp;
    fp.open("VIVOD2.txt");
    fp << "  x\ty\n";
    double t = 0;
    double y = 0;
    while (y >= 0)
        //	for (double t=0; t < 5; t+= deltaT)
    {
        fp << setw(10) << vx*(m/k)*(1-pow(e, -k*t/m)) << "\t";
        y = m / k * ((vy + m * g / k)*(1 - pow(e, -k * t / m)) - g * t);
        fp << setw(10) << y << endl;
        t += deltaT;
    }
    fp.close();
    cout << "2 OK" << endl;
}
void SLUCHAI3(float v, float k, double a, double dt, int m)
{
    float v_x, v_y;
    double x, y;
    v_x = v * cos(alfa);
    v_y = v * sin(alfa);
    double A;
    ofstream file;
    file.open("VIVOD3.txt");
    file << setw(10) << "x";
    file << setw(10) << "y" << endl;
    y = 0;
    x = 0;
    while (y >= 0)
    {   A = 1 - k/m *sqrt (v_x*v_x + v_y*v_y)*dt;
        v_x *= A;
        x += v_x*dt;
        v_y = v_y * A - g*dt;
        y += v_y * dt;
        file << setw(10) << x;
        file << setw(10) << y << endl;
    }
    file.close();
    cout << "3 OK" << endl;
}

int main()
{
    double a, x=0, y=0;
    float v, k;
    cout << "Enter delta:\n";
    double deltaT;
    cin >> deltaT;
    cout << "Enter angle:\n";
    cin >> a;
    cout << "Enter Speed:\n";
    cin >> v;
    cout << "Enter k:\n";
    cin >> k;
    cout << "Enter m:\n";
    int m;
    cin >> m;
    SLUCHAI1(v, a, deltaT);
    SLUCHAI2(v, k, a, deltaT, m);
    SLUCHAI3(v, k, a, deltaT, m);
    return 0;
}
