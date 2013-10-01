#include <GL/glew.h>
#include <GL/freeglut.h>

static struct
{
    GLuint vertexArrayId;

    GLuint vertexBuffer;
    GLuint elementBuffer;

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
} resources;

const GLfloat vertices[] = {
    -0.9f, -0.9f,
    -0.9f, 0.9f,
    0.9f, 0.9f,
    0.9f, -0.9f
};

const GLfloat colors[] = {
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f
};

const GLushort indices[] = {
    0, 3, 1, 2
};
