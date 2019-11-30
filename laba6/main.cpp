#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <glut.h>

const double PI = 3.14;
const double dt = 0.001;
const double k = 8.897551777E9;
const double Z = 1;
const double e = 1.602189246E-19;
const double m = 6.638E-27;
const double xmax = 3;
const double ymax = 3;
const double v0x = 3;
const double v0y = 0;
bool Flag = false;
bool flags = 0;
double x = -3;
double y = 0.1;
double vx = v0x;
double vy = v0y;

using namespace std;

double Force (double x, double y)
{
    double r = 0;
    r = x*x + y*y;
    r = sqrt(r);
    return (2*k*Z*e*e)/(m*r*r*r);
}

void ChangeSize(int w, int h)
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

void CoordinateSystem()
{

    glLineWidth(1.0);       //Толщина линий
    glColor3d(1, 1, 1);     //Цвет линий - черный
    glBegin(GL_LINES);
    glVertex3d(-1.4, 0.0, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    glVertex3d(1.2, -0.1, -5.0);
    glVertex3d(1.2, 0.1, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    glVertex3d(0.0, -1.4, -5.0);
    glVertex3d(0.0, 1.4, -5.0);
    glVertex3d(0.0, 1.4, -5.0);
    glVertex3d(0.1, 1.2, -5.0);
    glVertex3d(-0.1, 1.2, -5.0);
    glVertex3d(0.0, 1.4, -5.0);
    glEnd();

}

void Circle()
{

    double radian = 0.0;
    double xx, yy;
    glColor3d(0.3, 0.5, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    while (radian <= 2 * PI)
    {
        xx = 0.01*cos(radian);
        yy = 0.01*sin(radian);
        glVertex3d(x + xx, y + yy, -5.0);
        radian += 0.05;
    }
    glEnd();
}


void RenderCartoon()
{
    glLoadIdentity();
    CoordinateSystem(); // Отрисовка координатной системы
    Circle();
    if (!(x < xmax) || !(y < ymax))
        Flag = true;

    if (Flag == false)
    {
        vx = vx + Force(x, y)*dt;
        vy = vy + Force(y, x)*dt;
        x = x + vx*dt;
        y = y + vy*dt;
    }
    glutSwapBuffers();
}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Cartoon");
    glutDisplayFunc(RenderCartoon);
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(RenderCartoon);
    glutMainLoop();
    return 0;
}
