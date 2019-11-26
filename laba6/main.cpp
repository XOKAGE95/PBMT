#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <glut.h>

const double dt = 0.001;
const double k = 8.897551777E9;
const double Z = 1;
const double e = 1.602189246E-19;
const double m = 6.638E-27;
const double xmax = 1;
const double ymax = 2;
const double v0x = 3;
const double v0y = 0;
bool Flag = false;
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
    glClearColor(1, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); //Очистка экрана (На случай, если там был трэш)
    glLineWidth(1.0);       //Толщина линий
    glColor3d(0, 0, 0);     //Цвет линий - черный
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
void RenderScene()
{
        double vx = v0x;
        double vy = v0y;
        double x = -3.0;
        double y = 0.1;
        CoordinateSystem(); // Отрисовка координатной системы
        glColor3d(0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        while ((x < xmax) && (y < ymax))
        {
        vx = vx + Force(x, y)*dt;
        vy = vy + Force(y, x)*dt;
        x = x + vx*dt;
        y = y + vy*dt;
        cout << y << endl;
        glVertex3d(x, y, -5.0);
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
	glutCreateWindow("Speed/t");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	//glutIdleFunc(RenderScene);
	glutMainLoop();
	return 0;
}
