#include <iostream>
#include <cmath>
#include <fstream>
#include<glut.h>
#include <iomanip>
#define M_PI 3.14159
#define alfa a*M_PI/180
#define g 9.8
#define e 2.71828
#define vx v*cos(alfa)
#define vy v*sin(alfa)

using namespace std;

double a, MX1, MX2, MX3, MY1, MY2, MY3, m;
    float v, k;
        double deltaT;


void coordinate()
{
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

}
void max1()
{
    MX1 = 0;
    MY1 = 0;
    for (double t = 0; t <= (2 * v*sin(alfa) / g); t += deltaT)
    {   double x = vx*t;
        double y = vy*t - g * t*t / 2;
        if (x > MX1) MX1 = x;
        if (y > MY1) MY1 = y;
    }

}

void max2()
{
    MX2 = 0;
    MY2 = 0;
    double t = 0;
    double x, y;
    while (y >= 0)
        //	for (double t=0; t < 5; t+= deltaT)
    {
        x =  vx*(m/k)*(1-pow(e, -k*t/m));
        y = m / k * ((vy + m * g / k)*(1 - pow(e, -k * t / m)) - g * t);
        t += deltaT;
        if (x > MX2) MX2 = x;
        if (y > MY2) MY2 = y;
    }

}

void max3()
{

    float v_x, v_y;
    double x, y;
    v_x = v * cos(alfa);
    v_y = v * sin(alfa);
    double A;
    y = 0;
    x = 0;
    while (y >= 0)
    {
        A = 1 - k/m *sqrt (v_x*v_x + v_y*v_y)*deltaT;
        v_x *= A;
        x += v_x*deltaT;
        v_y = v_y * A - g*deltaT;
        y += v_y * deltaT;
        if (x > MX3) MX3 = x;
        if (y > MY3) MY3 = y;
    }
}
void SLUCHAI1 ()
{
    coordinate();
    ofstream fp;
    fp.open("VIVOD1.txt");
    fp << "  x\ty\n";
    double x, y;
    glBegin(GL_LINES);
    for (double t = 0; t <= (2 * v*sin(alfa) / g); t += deltaT)
    {
        glVertex3d(x/MX1, y/MY1, -5.0);
        x = vx*t;
        y = vy*t - g * t*t / 2;
        fp << vx*t << "\t";
        fp << vy*t - g * t*t / 2 << endl;
        glVertex3d(x/MX1, y/MY1, -5.0);
    }
    glEnd();
    fp.close();
    cout << "1 OK" << endl;
    glutSwapBuffers();
}

void SLUCHAI2()
{
    coordinate();
    ofstream fp;
    fp.open("VIVOD2.txt");
    fp << "  x\ty\n";
    double t = 0;
    double y = 0;
    double x = 0;
    glBegin(GL_LINES);
    while (y >= 0)
    {
        glVertex3d(x/MX2, y/MY2, -5.0);
        x = vx*(m/k)*(1-pow(e, -k*t/m));
        fp << setw(10) << x << "\t";
        y = m / k * ((vy + m * g / k)*(1 - pow(e, -k * t / m)) - g * t);
        fp << setw(10) << y << endl;
        t += deltaT;
        glVertex3d(x/MX2, y/MY2, -5.0);
    }
    glEnd();
    fp.close();
    cout << "2 OK" << endl;
    glutSwapBuffers();
}
void SLUCHAI3()
{
    coordinate();
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
    glBegin(GL_LINES);
    while (y >= 0)
    {
        glVertex3d(x/MX3, y/MY3, -5.0);
        A = 1 - k/m *sqrt (v_x*v_x + v_y*v_y)*deltaT;
        v_x *= A;
        x += v_x*deltaT;
        v_y = v_y * A - g*deltaT;
        y += v_y * deltaT;
        file << setw(10) << x;
        file << setw(10) << y << endl;
        glVertex3d(x/MX3, y/MY3, -5.0);
    }
    glEnd();
    file.close();
    cout << "3 OK" << endl;
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

    cout << "Enter delta:\n";
    cin >> deltaT;
    cout << "Enter angle:\n";
    cin >> a;
    cout << "Enter Speed:\n";
    cin >> v;
    cout << "Enter k:\n";
    cin >> k;
    cout << "Enter m:\n";
    cin >> m;
    max1();
    max2();
    max3();
    glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("first");
	glutDisplayFunc(SLUCHAI1);
	glutReshapeFunc(changeSize);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("second");
	glutDisplayFunc(SLUCHAI2);
	glutReshapeFunc(changeSize);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("third");
	glutDisplayFunc(SLUCHAI3);
	glutReshapeFunc(changeSize);
	glutMainLoop();
    return 0;
}
