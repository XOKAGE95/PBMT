#include<glut.h>
#include<cmath>
#define PI 3.1415926535
#define dt 0.00005

double acceleration(double v, double z, double l, double ta)
{
    double r;
    r = z*z + l*l;
    r = sqrt(r);
    return (v - (z / (r*r*r)*ta));
}

void draw(double tk, float x, float y, double vx, double vy, double red, double green, double blue)
{
    glColor3d(red, green,blue);
    glBegin(GL_POINTS);
    double t = 0;
    while (t <= tk)
    {
        glVertex2d(x, y);
        vx = acceleration(vx, x, y, dt);
        vy = acceleration(vy, y, x, dt);
        x += vx*dt;
        y += vy*dt;
        t += dt;
    }
    glEnd();
}
void change_size(GLsizei w, GLsizei h)
{
    GLdouble aspect_ratio;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspect_ratio = (GLdouble)w / (GLdouble)h;
    if (w <= h)
        glOrtho(-40.0, 6.0, -23.0 / aspect_ratio, 23.0 / aspect_ratio, -1.0, 1.0);
    else
        glOrtho(-40.0*aspect_ratio, 6.0*aspect_ratio, -23.0, 23.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void initialise()
{
    //Задается цвет очистки окна - черный
    glClearColor(1.0, 1.0, 1.0, 1.0);
}
void render_scene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Отрисовка осей
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-39.0, 0.0);
    glVertex2f(5.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0, -22.0);
    glVertex2f(0.0, 22.0);
    glEnd();
    glColor3f(0.0, 0.5, 1.0);
    //конец отрисовки осей

    double radian = 0.0;
    double xx, yy;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    while (radian <= 2 * PI)
    {
        xx = cos(radian);
        yy = sin(radian);
        glVertex2d(xx, yy);
        radian += 0.05;
    }
    glEnd();
    draw (70, 1.2, 0, 0, 1.2, 1.0, 0.5, 0.0);
    draw (200, 1.25, 0, 0, 1.2, 0.5, 0.5, .5);
    draw (220, 1.3, 0, 0, 1.2, 0.5, 1.0, 0.0);
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //Задается размер окна
    glutInitWindowSize(640, 640);
    //Определяется позиции окна на рабочем столе
    glutInitWindowPosition(20, 20);
    //Создается окно с названием в кавычках
    glutCreateWindow("Движение небесных тел");
    //Дисплейная функция
    glutDisplayFunc(render_scene);
    //Функция перерисовки
    glutReshapeFunc(change_size);
    initialise();
    //Запускается оболочка GLUT
    glutMainLoop();
    return 0;
}
