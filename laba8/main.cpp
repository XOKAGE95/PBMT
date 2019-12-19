#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<glut.h>
#include<clocale>
#include<cmath>

using namespace std;

#define step 0.000001
#define pi 3.14159265358979323846

void initialise()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void change_size_xy(GLsizei w, GLsizei h)
{
    double wh = 0.01;
    GLdouble aspect_ratio;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspect_ratio = (GLdouble)w / (GLdouble)h;
    if (w <= h)
        glOrtho(15*wh, 15*wh, -15*wh/aspect_ratio, 15*wh/aspect_ratio,-1.0,1.0);
    else
        glOrtho(-15*wh*aspect_ratio, 15*wh*aspect_ratio, -15*wh, 15*wh, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display_xy()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    // Рисуем сетку
    for (double i = -10; i <= 10; i += step * 10000)
    {
        glBegin(GL_LINES);
        glVertex2d(i, -10.0);
        glVertex2d(i, 10.0);
        glEnd();
    }

    for (double i = -10; i <= 10; i += step * 10000)
    {
        glBegin(GL_LINES);
        glVertex2d(-10.0, i);
        glVertex2d(10.0, i);
        glEnd();
    }
    // Рисуем оси
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(-10.0, 0.0);
    glVertex2d(10.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0.0, -10.0);
    glVertex2d(0.0, 10.0);
    glEnd();
    glColor3f(1.0, 0.0, 1.0);
    setlocale(LC_ALL, "eng");
            //Начальные условия модели 1
    double q = 5;
    double m = 0.05;
    double v = 300;
    double B = 100;
    double R = 0.05;
    double x0 = 0.0, y0 = R;
    double v0x = v, v0y = 0.0;
    double vx, vy;
    double x, y;
    ofstream file;
    file.open("xy.txt");
    x = x0;
    y = y0;
    file << "(" << x << ";" << y << ")" << endl;
    glBegin(GL_POINTS);
    glVertex2d(x,y);
    glEnd();
    vx = v0x - (q*B*v0y / m)*step / 2;
    vy = v0y - (-q*B*v0x / m)*step / 2;
    for (double t = step; t < step * 1000; t += step)
    {
        glBegin(GL_LINES);
        glVertex2d(x, y);
        vx = vx - (q*B*vy / m)*step;
        vy = vy - (-q*B*vx / m)*step;
        x = x + vx*step;
        y = y + vy*step;
        glVertex2d(x, y);
        glEnd();
        file << "(" << x << ";" << y << ")" << endl;
    }
    file.close();
    glFlush();
}

void look()
{
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.1, -0.1, 0.1, 0, 0, 0, 0, 0, 0.8);
}

void change_size_xyz(GLsizei w, GLsizei h)
{
    /*glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (GLfloat)w / (GLfloat)h, 0.01, 100);*/
    double wh = 0.01;
    GLdouble aspect_ratio;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspect_ratio = (GLdouble)w / (GLdouble)h;
    if (w <= h)
        glOrtho(25 * wh, 25 * wh, -25 * wh / aspect_ratio, 25 * wh / aspect_ratio, -5, 5);
    else
        glOrtho(-25 * wh*aspect_ratio, 25 * wh*aspect_ratio, -25 * wh, 25 * wh, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    look();
}
GLdouble angle = 45;
void Rotate()
{
    angle += 0.05;
    if (angle > 360)
        angle = 0;
}
void display_xyz()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    look();
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(100.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0.0, 100.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 100.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    //Начальные условия модели 2
    double z0 = 0.0;
    double vz = 0.0;
    double alpha = pi / 3;
    double betta = pi / 3;
    double q = 5;
    double m = 0.05;
    double v = 300;
    double B = 100;
    double R = 0.05;
    double x0 = 0.0, y0 = R;
    double v0x, v0y;
    double vx, vy;
    double x, y;
    x = x0;
    y = y0;
    vz = v*cos(alpha);

    v0x = v*sin(alpha);
    v0y = v*sin(alpha);

    v0x = vx*cos(betta);
    v0y = vy*sin(betta);

    vx = v0x - (q*B*v0y / m)*step / 2;
    vy = v0y - (-q*B*v0x / m)*step / 2;

    double z = z0;
    glBegin(GL_POINTS);
    glVertex3d(x,y,z);
    glEnd();

    for (double t = step; t < step * 1000; t += step)
    {
        glBegin(GL_LINES);
        glVertex3d(x, y, z);
        vx = vx - (q*B*vy / m)*step;
        vy = vy - (-q*B*vx / m)*step;
        x = x + vx*step;
        y = y + vy*step;
        z = z + vz*step;
        glVertex3d(x, y, z);
        glEnd();
    }
    glPopMatrix();
    glutSwapBuffers();
}
void change_size_xy2(GLsizei w, GLsizei h)
{
    double wh = 0.01;
    GLdouble aspect_ratio;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspect_ratio = (GLdouble)w / (GLdouble)h;
    if (w <= h)
        glOrtho(15 * wh, 15 * wh, -15 * wh / aspect_ratio, 15 * wh / aspect_ratio, -1.0, 1.0);
    else
        glOrtho(-15 * wh*aspect_ratio, 15 * wh*aspect_ratio, -15 * wh, 15 * wh, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display_xy2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    for (double i = -10; i <= 10; i += step * 10000)
    {
        glBegin(GL_LINES);
        glVertex2d(i, -10.0);
        glVertex2d(i, 10.0);
        glEnd();
    }
    for (double i = -10; i <= 10; i += step * 10000)
    {
        glBegin(GL_LINES);
        glVertex2d(-10.0, i);
        glVertex2d(10.0, i);
        glEnd();
    }
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(-10.0, 0.0);
    glVertex2d(10.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0.0, -10.0);
    glVertex2d(0.0, 10.0);
    glEnd();
    glColor3f(0.0, 1.0, 1.0);
//Начальные условия модели 2
    double z0 = 0.0;
    double vz = 0.0;
    double alpha = pi / 3;
    double q = 5;
    double m = 0.05;
    double v = 300;
    double B = 100;
    double R = 0.05;
    double x0 = 0.0, y0 = R;
    double v0x = v, v0y = 0.0;
    double vx, vy;
    double x, y;
    x = x0;
    y = y0;
    v0x = v*sin(alpha), v0y = 0.0*sin(alpha);
    vz = v*cos(alpha);
    vx = v0x - (q*B*v0y / m)*step / 2;
    vx = vx*sin(alpha);
    vy = v0y - (-q*B*v0x / m)*step / 2;
    vy = vy*sin(alpha);
    double z = z0;
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
    for (double t = step; t < step * 1000; t += step)
    {
        glBegin(GL_LINES);
        glVertex2d(x, y);
        vx = vx - (q*B*vy / m)*step;
        vy = vy - (-q*B*vx / m)*step;
        x = x + vx*step;
        y = y + vy*step;
        z = z + vz*step;
        glVertex2d(x, y);
        glEnd();
    }
}
void change_size_xz(GLsizei w, GLsizei h)
{
    double wh = 0.01;
    GLdouble aspect_ratio;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspect_ratio = (GLdouble)w / (GLdouble)h;
    if (w <= h)
        glOrtho(18 * wh, 18 * wh, -18 * wh / aspect_ratio, 18 * wh / aspect_ratio, -1.0, 1.0);
    else
        glOrtho(-18 * wh*aspect_ratio, 18 * wh*aspect_ratio, -18 * wh, 18 * wh, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display_xz()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    for (double i = -10; i <= 10; i += step * 10000)
    {
        glBegin(GL_LINES);
        glVertex2d(i, -10.0);
        glVertex2d(i, 10.0);
        glEnd();
    }
    for (double i = -10; i <= 10; i += step * 10000)
    {
        glBegin(GL_LINES);
        glVertex2d(-10.0, i);
        glVertex2d(10.0, i);
        glEnd();
    }
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(-10.0, 0.0);
    glVertex2d(10.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0.0, -10.0);
    glVertex2d(0.0, 10.0);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
//Начальные условия модели 2
    double z0 = 0.0;
    double vz = 0.0;
    double alpha = pi / 3;
    double q = 5;
    double m = 0.05;
    double v = 300;
    double B = 100;
    double R = 0.05;
    double x0 = 0.0, y0 = R;
    double v0x = v, v0y = 0.0;
    double vx, vy;
    double x, y;
    x = x0;
    y = y0;
    v0x = v*sin(alpha), v0y = 0.0*sin(alpha);
    vz = v*cos(alpha);
    vx = v0x - (q*B*v0y / m)*step / 2;
    vx = vx*sin(alpha);
    vy = v0y - (-q*B*v0x / m)*step / 2;
    vy = vy*sin(alpha);
    double z = z0;
    glBegin(GL_POINTS);
    glVertex2d(x, z);
    glEnd();
    for (double t = step; t < step * 1000; t += step)
    {
        glBegin(GL_LINES);
        glVertex2d(x, z);
        vx = vx - (q*B*vy / m)*step;
        vy = vy - (-q*B*vx / m)*step;
        x = x + vx*step;
        y = y + vy*step;
        z = z + vz*step;
        glVertex2d(x, z);
        glEnd();
    }
}
void

change_size_yz(GLsizei w, GLsizei h)
{
    double wh = 0.01;
    GLdouble aspect_ratio;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspect_ratio = (GLdouble)w / (GLdouble)h;
    if (w <= h)
        glOrtho(18 * wh, 18 * wh, -18 * wh / aspect_ratio, 18 * wh / aspect_ratio, -1.0, 1.0);
    else
        glOrtho(-18 * wh*aspect_ratio, 18 * wh*aspect_ratio, -18 * wh, 18 * wh, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display_yz()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    for (double i = -10; i <= 10; i += step * 10000)
    {
        glBegin(GL_LINES);
        glVertex2d(i, -10.0);
        glVertex2d(i, 10.0);
        glEnd();
    }
    for (double i = -10; i <= 10; i += step * 10000)
    {
        glBegin(GL_LINES);
        glVertex2d(-10.0, i);
        glVertex2d(10.0, i);
        glEnd();
    }
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(-10.0, 0.0);
    glVertex2d(10.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0.0, -10.0);
    glVertex2d(0.0, 10.0);
    glEnd();
    glColor3f(1.0, 1.0, 0.0);
//Начальные условия модели 2
    double z0 = 0.0;
    double vz = 0.0;
    double alpha = pi / 3;
    double q = 5;
    double m = 0.05;
    double v = 300;
    double B = 100;
    double R = 0.05;
    double x0 = 0.0, y0 = R;
    double v0x = v, v0y = 0.0;
    double vx, vy;
    double x, y;
    x = x0;
    y = y0;
    v0x = v*sin(alpha), v0y = 0.0*sin(alpha);
    vz = v*cos(alpha);
    vx = v0x - (q*B*v0y / m)*step / 2;
    vx = vx*sin(alpha);
    vy = v0y - (-q*B*v0x / m)*step / 2;
    vy = vy*sin(alpha);
    double z = z0;
    glBegin(GL_POINTS);
    glVertex2d(y, z);
    glEnd();
    for (double t = step; t < step * 1000; t += step)
    {
        glBegin(GL_LINES);
        glVertex2d(y, z);
        vx = vx - (q*B*vy / m)*step;
        vy = vy - (-q*B*vx / m)*step;
        x = x + vx*step;
        y = y + vy*step;
        z = z + vz*step;
        glVertex2d(y, z);
        glEnd();
    }
}
void my_init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280/2, 720/2);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Движение заряженной частицы в магнитном поле: скорость частицы составляет угол pi/2 с вектором магнитной индукции");
    glutDisplayFunc(display_xy);
    glutReshapeFunc(change_size_xy);
    initialise();
    glutInitWindowPosition(0, 400);
    glutCreateWindow("2 случай, график y(x)");
    glutDisplayFunc(display_xy2);
    glutReshapeFunc(change_size_xy2);
    initialise();
    glutInitWindowPosition(400, 400);
    glutCreateWindow("2 случай, график z(x)");
    glutDisplayFunc(display_xz);
    glutReshapeFunc(change_size_xz);
    initialise();
    glutInitWindowPosition(800, 400);
    glutCreateWindow("2 случай, график z(y)");
    glutDisplayFunc(display_yz);
    glutReshapeFunc(change_size_yz);
    initialise();
    /*glutInitWindowPosition(0, 0);
    glutCreateWindow("Движение заряженной частицы в магнитном поле: скорость составляет с вектором магнитной индукции произвольный угол");
    my_init();
    glutDisplayFunc(display_xyz);
    glutReshapeFunc(change_size_xyz);
    glutIdleFunc(Rotate);*/
    glutMainLoop();
    return 0;
}
