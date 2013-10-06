#include "gldemo.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

std::string fileContents(std::string filename)
{
    std::ostringstream oss;
    std::ifstream in(filename.c_str());
    if (!in.is_open())
        return std::string();
    oss << in.rdbuf();
    in.close();
    return oss.str();
}

GLuint makeShader(GLenum type, std::string filename)
{
    GLuint shader;
    std::string s = fileContents(filename);
    GLchar *source = (GLchar *)s.c_str();

    if (!source)
    {
        std::cerr << "Error: file contents is empty" << std::endl;
        return 0;
    }

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        std::cerr << "Error: shader compilation error " << filename << std::endl;

        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        char *log = new char[logLength];
        glGetShaderInfoLog(shader, logLength, NULL, log);
        std::cout << log << std::endl;
        delete log;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint makeProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLint result;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) 
    {
        std::cerr << "Error: could not create shader program" << std::endl;
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

void init()
{
    // Setup
    resources.xRotation = 0;
    resources.yRotation = 0;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xFFFF);
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    // Prepare shaders
    resources.vertexShader = makeShader(GL_VERTEX_SHADER, "gldemo.v.glsl");
    if (resources.vertexShader == 0)
        return;

    resources.fragmentShader = makeShader(GL_FRAGMENT_SHADER, "gldemo.f.glsl");
    if (resources.fragmentShader == 0)
        return;

    resources.program = makeProgram(resources.vertexShader, resources.fragmentShader);
    if (resources.program == 0)
        return;

    glUseProgram(resources.program);

    resources.projectionMatrixLoc = glGetUniformLocation(resources.program, "projectionMatrix");
    resources.viewMatrixLoc = glGetUniformLocation(resources.program, "viewMatrix");
    resources.modelMatrixLoc = glGetUniformLocation(resources.program, "modelMatrix");

    resources.viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f));
    resources.projectionMatrix = glm::perspective(60.0f, (float)resources.windowWidth / (float)resources.windowHeight, 0.1f, 100.f);

    glUniformMatrix4fv(resources.viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(resources.viewMatrix));
    glUniformMatrix4fv(resources.projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(resources.projectionMatrix));

    // Initalize buffers
    glGenVertexArrays(1, &resources.vertexArrayId);
    glBindVertexArray(resources.vertexArrayId);

    glGenBuffers(1, &resources.elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resources.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &resources.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, resources.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void *)sizeof(vertices));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    resources.modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f));
    resources.modelMatrix = glm::rotate(resources.modelMatrix, (float)resources.xRotation, glm::vec3(1.0f, 0.0f, 0.0f));
    resources.modelMatrix = glm::rotate(resources.modelMatrix, (float)resources.yRotation, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(resources.modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(resources.modelMatrix));
    glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);

    glutSwapBuffers();
    glutPostRedisplay();
}

void resize(int w, int h)
{
    resources.windowWidth = w;
    resources.windowHeight = h;

    glViewport(0, 0, resources.windowWidth, resources.windowHeight);

    resources.projectionMatrix = glm::perspective(60.0f, (float)resources.windowWidth / (float)resources.windowHeight, 0.1f, 100.f);
    glUniformMatrix4fv(resources.projectionMatrixLoc, 1, GL_FALSE, &resources.projectionMatrix[0][0]);
}

void keySpecialReleased(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            resources.yRotation--;
            break;
        case GLUT_KEY_RIGHT:
            resources.yRotation++;
            break;
        case GLUT_KEY_UP:
            if (resources.xRotation > -60.0f)
                resources.xRotation--;
            break;
        case GLUT_KEY_DOWN:
            if (resources.xRotation < 60.0f)
                resources.xRotation++;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    resources.windowWidth = 640;
    resources.windowHeight = 480;

    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(resources.windowWidth, resources.windowHeight);
    glutCreateWindow("OpenGL demo");
    glutDisplayFunc(&render);
    glutReshapeFunc(&resize);
    glutSpecialUpFunc(&keySpecialReleased);

    glewExperimental = GL_TRUE;
    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK)
        std::cerr << "Error: GLEW init problem" << std::endl;

    init();

    std::cout << "GL_VENDOR " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_RENDERER " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GL_VERSION " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL_SHADING_LANGUAGE_VERSION " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    glutMainLoop();
    return 0;
}
