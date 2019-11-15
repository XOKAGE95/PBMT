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
const double Alfa = 2520;
const double c = 0.45;
const double S = 83.322;
const double F = 3E6;
//const double I = 2520;
using namespace std;

double dt;
int COUNT = 0;

void Display1(double a, double v, double h, double t)
{
    if (COUNT == 0)
    {
    ofstream file;
    file.open("Case_1.txt", ios_base::app);
    file << setw(15) << setprecision(5) << left << a;
    file << setw(15) << setprecision(10) << left << v;
    file << setw(15) << setprecision(7) << left << h;
    file << setw(15) << setprecision(7) << left << t << endl;
    file.close();
    }
}

void Display2(double a, double v, double h, double t)
{
    if (COUNT == 0)
    {
    ofstream file;
    file.open("Case_2.txt", ios_base::app);
    file << setw(15) << setprecision(5) << left << a;
    file << setw(15) << setprecision(10) << left << v;
    file << setw(15) << setprecision(7) << left << h;
    file << setw(15) << setprecision(7) << left << t << endl;
    file.close();
    }
}
void render_scene()
{
double m, a, g, ro, vi, ai, v2;
                    // Зададим начальные данные
double h = 0;
double t = 0;
double ro0 = 1.29;
double m0 = 3E5;
double mk = 3E4;
double v = 0;
double k2 = c*S*ro;
                    // Формула для коэффициента сопротивления среды

double V = 1692.762027;
double A = 90.359;
double H = 38618.14;
double T = (m0 - mk) / Alfa;

                // Прорисовка координатной оси
    glClearColor(1, 1, 1, 1.0);     // Цвет фона - белый
    glClear(GL_COLOR_BUFFER_BIT); //Очистка экрана (На случай, если там был трэш)
    glLineWidth(1.0);       //Толщина линий
    glColor3d(0, 0, 0);     //Цвет линий - черный
    glBegin(GL_LINES);  //Прорисовка линиями (рисуются линии для каждых 2х точек)
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

                        //Прорисовка букв на координатных осях

    glColor3d(0.0, 0.0, 0.0);
    glRasterPos3d(1.4, 0.1, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');

    glColor3d(1.0, 0.0, 0.5);
    glRasterPos3d(0.1, 1.4, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'V');

    glColor3d(0.0, 0.0, 0.0);
    glRasterPos3d(0.17, 1.4, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ',');

    glColor3d(0.0, 1.0, 0.5);
    glRasterPos3d(0.2, 1.4, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');

    glColor3d(0.0, 0.0, 0.0);
    glRasterPos3d(0.27, 1.4, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ',');

    glColor3d(0.5, 0.0, 1.0);
    glRasterPos3d(0.30, 1.4, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'H');


            //Граффик
    glBegin(GL_POINTS);

    v = 0;
    vi = 0;
    v2 = 0;
    do
    {
        m = (m0- Alfa * t);		// Формула для массы ракеты
        g = (G * M)/((R + h)*(R + h));  // Формула для ускорения свободного падения
        ro = ro0* exp(-Betta*h); 	// Формула для плотности среды



        ai = (vi - v2)/dt;
        v2 = vi;
        vi = v2 + dt/2*((F - m*g - k2*v2*v2)/m + (F - m*g - k2*pow((v2 + dt * (F - m*g - k2*v2*v2)/m), 2))/m);
        Display2(ai, vi, h, t); //*/

        a = (F - m*g - k2 * v * v)/m;
        v += a * dt; //*/

        h += v2 * dt;
        t += dt;

        glColor3d(1.0, 0.0, 0.5);
        glLineWidth(2.0);
        glVertex3d(t/T, v/V, -5.0);//*/

        glColor3d(0.0, 1.0, 0.5);
        glLineWidth(2.0);
        glVertex3d(t/T, a/A, -5.0);//*/

        glColor3d(0.5, 0.0, 1.0);
        glLineWidth(2.0);
        glVertex3d(t/T, h/H, -5.0);//*/

        Display1(a, v, h, t);

    }
    while (m > mk);
    glEnd();
    if (COUNT == 0)
    {
    COUNT ++;
    cout << "Factual Time = " << t << " Seconds" << endl;
   /* cout << "Theoretical Time = " << T << " Seconds" << endl;
    cout << "Factual speed = " << v << " m/s "<< endl;
    cout << "Theoretical speed = " << V << " m/s "<< endl;*/
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
	gluPerspective(35,ratio,3,1000);
	gluOrtho2D(0, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char **argv)
{

    cout << "Enter dt" <<endl;
    cin >> dt;
    ofstream file;
    file.open("Case_1.txt");
    file << setw(15) << left << "Acceleration";
    file << setw(15) << left << "Speed";
    file <<  setw(15) << left << "Height";
    file << setw(15) << left << "Time" << endl;
    file.close();

    ofstream file1;
    file1.open("Case_2.txt");
    file1 << setw(15) << left << "Acceleration";
    file1 << setw(15) << left << "Speed";
    file1 <<  setw(15) << left << "Height";
    file1 << setw(15) << left << "Time" << endl;
    file1.close();
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
