#include <GL/glew.h>
#include <GL/glut.h>

void render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL demo");
    glutDisplayFunc(&render);

    glewInit();

    glutMainLoop();
    return 0;
}
