#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <glut.h>
#define PI 3.1415926535


const double dt = 0.0001;
const double Emax = 10;
const double qmax = 2E-6;
const double R = 200;
const double L = 1;
const double C = 0.5E-6;
const double w = sqrt(1/(L*C));
const double b = R/L;
const double tmax = 0.1;


using namespace std;



void ChangeSize(int w, int h)
{
    if(h == 0)
        h = 1;
    float ratio = 1.0* w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(-5, 0, w, h);
    gluPerspective(50,ratio,3,1000);
    gluOrtho2D(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CoordinateSystem()
{
    glLineWidth(1.0);
    glColor3d(1, 1, 1);
    glBegin(GL_LINES);
    // Ось ох
    glVertex3d(-3.4, 0.0, -5.0);
    glVertex3d(1.4, 0.0, -5.0);

    glVertex3d(1.4, 0.0, -5.0);
    glVertex3d(1.2, -0.1, -5.0);

    glVertex3d(1.2, 0.1, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    // Ось Оу
    glVertex3d(-3.0, -1.4, -5.0);
    glVertex3d(-3.0, 1.4, -5.0);

    glVertex3d(-3.0, 1.4, -5.0);
    glVertex3d(-3.1, 1.2, -5.0);

    glVertex3d(-2.9, 1.2, -5.0);
    glVertex3d(-3.0, 1.4, -5.0);
    glEnd();

}


void RenderCartoon()
{
    bool flag = false;
double t = 0;
double k = 0;
double I = 0;
double q = qmax;
double E = 0;
    glColor3d(0.3, 0.5, 1.0);
    glLoadIdentity();
    CoordinateSystem();
        glBegin(GL_LINES);
    while (t <= tmax)
    {
        glVertex3d(k-3, q/3.53508E-5, -5.0);
        E = Emax*cos(w*t);
        I = I - (b*I + w*w*q - E/L)*dt;
        cout << I << endl;
        q = q + I*dt;
        t+=dt;
        k += 0.015;
        glVertex3d(k-3, q/3.53508E-5, -5.0);
    }
    glEnd();
    glutSwapBuffers();
}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Cos");
    glutDisplayFunc(RenderCartoon);
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(RenderCartoon);
    glutMainLoop();
    return 0;
}
