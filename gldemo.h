#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static struct
{
    int windowWidth;
    int windowHeight;
    int xRotation;
    int yRotation;

    GLuint vertexArrayId;

    GLuint vertexBuffer;
    GLuint elementBuffer;

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;

    GLuint projectionMatrixLoc;
    GLuint viewMatrixLoc;
    GLuint modelMatrixLoc;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 modelMatrix;
} resources;

const GLfloat vertices[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
};

const GLfloat colors[] = {
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,
};

const GLushort indices[] = {
    0, 1, 2, 3, 6, 7, 4, 5, 0xFFFF, 2, 6, 0, 4, 1, 5, 3, 7
};
