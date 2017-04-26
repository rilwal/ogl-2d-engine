
#include <cstdio>
#include <cinttypes>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

const int width  = 800;
const int height = 600;

uint32_t vertex_array_id;
uint32_t vertex_buffer_id;
uint32_t color_buffer_id;

void drawSquare(float x, float y, float w, float h) {
    //
    // x,y----x2,y
    // |        |
    // |        |
    // |        |
    // |        |
    // x,y2---x2,y2
    //

    float x2 = x + w;
    float y2 = y + h;

    float vertex_buffer[] = {
        x,  y,
        x,  y2,
        x2, y,
        x2, y,
        x,  y2,
        x2, y2
    };

    float color_buffer[] = {
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 0.0,
        0.0, 1.0, 1.0,
        1.0, 1.0, 1.0
    };

    static bool initialized = false;

    if (!initialized) {
        initialized = true;
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer), color_buffer, GL_STREAM_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void*)0);
    }

    glNamedBufferData(vertex_buffer_id, sizeof(vertex_buffer), vertex_buffer, GL_STREAM_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "games", 0, 0);
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    glewInit();

    Program default_shaders;

    default_shaders.attach(Shader(Shader::Type::Vertex,   "assets/shaders/default.vert"));
    default_shaders.attach(Shader(Shader::Type::Fragment, "assets/shaders/default.frag"));

    default_shaders.link();
    
    int uniform_window_width  = glGetUniformLocation(default_shaders.get_id(), "width");
    int uniform_window_height = glGetUniformLocation(default_shaders.get_id(), "height");


    default_shaders.use();
    glUniform1i(uniform_window_width,  width);
    glUniform1i(uniform_window_height, height);

    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    glGenBuffers(1, &vertex_buffer_id);
    glGenBuffers(1, &color_buffer_id);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        default_shaders.use();
        drawSquare(10, 10, 40, 40);
        drawSquare(10, 51, 40, 70);
        drawSquare(51, 10, 40, 111);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
}

