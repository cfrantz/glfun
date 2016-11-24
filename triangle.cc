#include "triangle.h"

const char *kVertexShader = R"ZZ(
#version 150
in vec3 vp;
void main() {
    gl_Position = vec4(vp, 1.0);
})ZZ";

const char *kFragmentShader = R"ZZ(
#version 150
out vec4 frag_color;
void main() {
    frag_color = vec4(0.5, 0.0, 0.5, 1.0);
})ZZ";


void Triangle::Init() {
    vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_, 1, &kVertexShader, nullptr);
    glCompileShader(vertex_shader_);

    fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_, 1, &kFragmentShader, nullptr);
    glCompileShader(fragment_shader_);

    shader_program_ = glCreateProgram();
    glAttachShader(shader_program_, fragment_shader_);
    glAttachShader(shader_program_, vertex_shader_);
    glLinkProgram(shader_program_);

    float points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Triangle::Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
