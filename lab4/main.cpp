#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <glut.h>
// glu32 glut32 opengl32
const double G = 6.67408E-11;
const double M = 5.97E24;
const double R = 6.37E6;
const double Betta = 1.29E-4;
const double Alfa = 3135;
const double c = 0.45;
const double S = 83.322;
const double F = 4 * 1E6;

using namespace std;

double dt;
int COUNT = 0;

void Display(double a, double v, double h, double t)
{
    if (COUNT == 0)
    {
    ofstream file;
    file.open("Case_1.txt", ios_base::app);
    file << setw(15) << setprecision(5) << left << a;
    file << setw(15) << setprecision(10) << left << v;
    file << setw(15) << setprecision(4) << left << h;
    file << setw(15) << setprecision(3) << left << t << endl;
    file.close();
    }
}
void render_scene()
{
double m, a, g, ro, vi, ai;
                    // Зададим начальные данные
double h = 0;
double t = 0;
double ro0 = 1.29;
double m0 = 3E5;
double mk = 3E4;
double v = 0;
double k2 = c*S*ro;
                    // Формула для коэффициента сопротивления среды

double V = 2096;
double T = (m0 - mk) / Alfa;

                // Оси
    glClearColor(1, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1.0);
    glColor3d(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3d(-1.4, 0.0, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(1.4, 0.0, -5.0);
    glVertex3d(1.2, -0.1, -5.0);
    glVertex3d(1.2, 0.1, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0.0, -1.4, -5.0);
    glVertex3d(0.0, 1.4, -5.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0.0, 1.4, -5.0);
    glVertex3d(0.1, 1.2, -5.0);
    glVertex3d(-0.1, 1.2, -5.0);
    glVertex3d(0.0, 1.4, -5.0);
    glEnd();
    glRasterPos3d(1.4, 0.1, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'V');
    glRasterPos3d(0.1, 1.4, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');

            //Граффик
    glBegin(GL_POINTS);

    v = 0;
    vi = 0;
    do
    {
        m = (m0- Alfa * t);		// Формула для массы ракеты
        g = (G * M)/((R + h)*(R + h));  // Формула для ускорения свободного падения
        ro = ro0* exp(-Betta*h); 	// Формула для плотности среды


        a = (F - m*g - k2 * v * v)/m;
        v += a * dt; //*/


        /*ai = (vi - v)/dt;
        v = vi;
        vi = v + dt/2*((m*g - k2*v*v)/m + (m*g - k2*pow((v + dt * (m*g - k2*v*v)/m), 2))/m);//*/

        h += v * dt;
        t += dt;

        glColor3d(1.0, 0.0, 0.5);
        glLineWidth(2.0);
        glVertex3d(t/T, v/V, -5.0);//*/

        //Display(ai, vi, h, t);
        Display(a, v, h, t);

    }
    while (m > mk);
    glEnd();
    if (COUNT == 0)
    {
    COUNT ++;
    cout << "Fact Time = " << t << " Seconds" << endl;
    }
    glutSwapBuffers();

}

void changeSize(int w, int h)
{
    if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(40,ratio,3,1000);
	gluOrtho2D(0, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char **argv)
{

    cout << "Enter dt" <<endl;
    cin >> dt;
    ofstream file;
    file.open("case_1.txt");
    file << setw(15) << left << "Acceleration";
    file << setw(15) << left << "Speed";
    file <<  setw(15) << left << "Height";
    file << setw(15) << left << "Time" << endl;
    file.close();
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Speed/t");
	glutDisplayFunc(render_scene);
	glutReshapeFunc(changeSize);
	glutMainLoop();
	return 0;
}
