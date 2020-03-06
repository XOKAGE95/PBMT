#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include<glut.h>
#define g 9.8
#define m_pi 3.141592
using namespace std;

float eps = 0.000001;
float v, dt;
/*
Лабораторная 3 будет весь раздел "СВОБОДНОЕ ПАДЕНИЕ ТЕЛА С УЧЕТОМ СОПРОТИВЛЕНИЯ СРЕДЫ".
Везде надо будет строить графики h(t), v(t), a(t) согласно своему варианту, который соответствует номеру записи в журнале старосты
*/

void coordinate()
{
    glClearColor(1, 1, 1, 1.0);     // Öâåò ôîíà - áåëûé
    glClear(GL_COLOR_BUFFER_BIT); //Î÷èñòêà ýêðàíà (Íà ñëó÷àé, åñëè òàì áûë òðýø)
    glLineWidth(1.0);       //Òîëùèíà ëèíèé
    glColor3d(0, 0, 0);     //Öâåò ëèíèé - ÷åðíûé
    glBegin(GL_LINES);  //Ïðîðèñîâêà ëèíèÿìè (ðèñóþòñÿ ëèíèè äëÿ êàæäûõ 2õ òî÷åê)
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

void Case1 ()
{
	float m = 65, h = 1.5 , r = 0.5 , c = 1.22, k2, dh = 0, a = 0, ai = 0, vi, t = 0;
    vi = v;
    k2 = h * r * 0.5 * c * 1.29;
    ofstream file1, file2,file3;
    file1.open("case 1_1.txt");
    file2.open("case 1_2.txt");
    file3.open("case 1_3.txt");
    do
    {
        v = vi;
        a = ai;

        a = (m * g - k2 * v * v)/m;
        file1 << a << endl << t << endl;


        vi = v + dt/2*((m*g - k2*v*v)/m + (m*g - k2*pow((v + dt * (m*g - k2*v*v)/m), 2))/m);
        file2 << vi << endl << t << endl;

        dh += vi * dt;
        file3 << dh << endl << t << endl;

        t += dt;

    }
    while (abs(v - vi) >= eps);
    file1.close();
    file2.close();
    file3.close();
}

void Case2 ()
{
    float m = 80, r = 2.5 , c = 0.4, k2, dh = 0, a = 0, vi, t = 0;
    vi = v;
    k2 = m_pi * r * r * 0.5 * c * 1.29;
    ofstream file1, file2, file3;
    file1.open("case 2_1.txt");
    file2.open("case 2_2.txt");
    file3.open("case 2_3.txt");
    do
    {
        v = vi;

        a = (m * g - k2 * v * v)/m;
        file1 << a << endl << t << endl;


        vi = v + dt/2*((m*g - k2*v*v)/m + (m*g - k2*pow((v + dt * (m*g - k2*v*v)/m), 2))/m);
        file2 << vi << endl << t << endl;


        dh += vi * dt;
        file3 << dh << endl << t << endl;

        t += dt;

    }
    while (abs(v - vi) >= eps);
    file1.close();
    file2.close();
    file3.close();
}

void Case3 ()
{
    float m, r = 0.1 , ro_b = 8930, ro_s = 1000, k1, dh = 0, a = 0, vi, t = 0, mu = 1180;
    vi = v;
    float V = 4/3*m_pi*r;
    k1 = 6*m_pi*r*mu;
    m = ro_b*V;
    float m1 = (ro_b - ro_s) * V;
    ofstream file1,file2,file3;
    file1.open("case 3_1.txt");
    file2.open("case 3_2.txt");
    file3.open("case 3_3.txt");
    do
    {
        v = vi;

        a = (m * g - k1 * v)/m;
        file1 << a << endl << t << endl;


        vi = v + dt/2*((m1*g - k1*v)/m + (m1*g - k1*((v + dt * (m1*g - k1*v)/m)))/m);
        file2 << vi << endl << t << endl;

        dh += vi * dt;
        file3 << dh << endl << t << endl;

        t += dt;

    }
    while (abs(v - vi) >= eps);
    file1.close();
    file2.close();
    file3.close();

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

void maximal(double &X, double &Y, ifstream &file)
{
    double x = 0, y = 0;
    while (!file.eof())
    {
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        if (abs(x) > X) X = abs(x);
        if (abs(y) > Y) Y = abs(y);
    }
}

void Case11()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 1_1.txt");
    file2.open("case 1_1.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}

void Case12()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 1_2.txt");
    file2.open("case 1_2.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}

void Case13()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 1_3.txt");
    file2.open("case 1_3.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}

void Case21()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 2_1.txt");
    file2.open("case 2_1.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}

void Case22()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 2_2.txt");
    file2.open("case 2_2.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}

void Case23()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 2_3.txt");
    file2.open("case 2_3.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}

void Case31()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 3_1.txt");
    file2.open("case 3_1.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}

void Case32()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 3_2.txt");
    file2.open("case 3_2.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}

void Case33()
{
    double MaxX = 0, MaxY = 0, *ptrX, *ptrY;
    ptrX = &MaxX;
    ptrY = &MaxY;

    coordinate();
    ifstream file, file2;
    file.open("case 3_3.txt");
    file2.open("case 3_3.txt");
    maximal(*ptrX, *ptrY, file2);
    double x = 0, y = 0;
    glBegin(GL_LINES);
    while (!file.eof())
    {
        glVertex3d(x/MaxX, y/MaxY, -5.0);
        file >> x;
        file.ignore(255, '\n');
        file >> y;
        file.ignore(255, '\n');
        glVertex3d(x/MaxX, y/MaxY, -5.0);
    }
    glEnd();
    file.close();
    glutSwapBuffers();

}
int main(int argc, char **argv)
{
    cout << "Enter v: ";
    cin >> v;
    cout << "Enter dt: ";
    cin >> dt;
    Case1();
    Case2();
    Case3();

glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("a(t)_1");
	glutDisplayFunc(Case11);
	glutReshapeFunc(changeSize);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("v(t)_1");
	glutDisplayFunc(Case12);
	glutReshapeFunc(changeSize);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("h(t)_1");
	glutDisplayFunc(Case13);
	glutReshapeFunc(changeSize);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("a(t)_2");
	glutDisplayFunc(Case21);
	glutReshapeFunc(changeSize);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("v(t)_2");
	glutDisplayFunc(Case22);
	glutReshapeFunc(changeSize);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("h(t)_2");
	glutDisplayFunc(Case23);
	glutReshapeFunc(changeSize);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("a(t)_3");
	glutDisplayFunc(Case31);
	glutReshapeFunc(changeSize);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("v(t)_3");
	glutDisplayFunc(Case32);
	glutReshapeFunc(changeSize);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(860, 620);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("h(t)_3");
	glutDisplayFunc(Case33);
	glutReshapeFunc(changeSize);
	glutMainLoop();
    return 0;
}
