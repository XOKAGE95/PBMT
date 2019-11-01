
#include <glut.h>
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

void renderScene(void)
{

    ifstream file;
    file.open("case_1.txt");
    float a, t;
    glClearColor(0.0, 0.4, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    while (!file.eof())
    {
        file >> a;
        file >> t;
        cout << setw(10)<< a << setw(10) << t << endl;
        glVertex2f(a, t);

    }
    file.close();
    glEnd();

    glutSwapBuffers();

}

int main(int argc, char **argv)
{

    // èíèöèàëèçàöèÿ
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("ÍÈ×ÅÃÎ ÍÅ ÐÀÁÎÒÀÅÒ");
    glLoadIdentity();
    gluOrtho2D(0, 320, 0, 240);

    glutDisplayFunc(renderScene);

    glutMainLoop();

    return 1;
}
