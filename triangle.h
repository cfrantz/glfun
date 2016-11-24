#ifndef GLFUN_TRIANGLE_H
#define GLFUN_TRIANGLE_H
#include <GL/glew.h>

class Triangle {
  public:
    void Init();
    void Draw();
  private:
    GLuint vao_;
    GLuint vbo_;
    GLuint vertex_shader_;
    GLuint fragment_shader_;
    GLuint shader_program_;
};

#endif // GLFUN_TRIANGLE_H
