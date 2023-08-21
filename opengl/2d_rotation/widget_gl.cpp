#include "widget_gl.h"

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 150
    in vec4 vertex;
    uniform mat2 mat;
    void main(void) {
        gl_Position = mat4(mat)*vertex;
    })";

static const char fragment_shader[] = R"(
    #version 150
    out vec4 fragColor;
    void main(void) {
        fragColor = vec4(0.0f, 1.0f, 0.0f, 0.0f);
    })";

WidgetGL::WidgetGL(QWidget* parent)
    : QOpenGLWidget(parent) {
  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setVersion(4, 5);
  setFormat(format);
}

void WidgetGL::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  static const std::map<GLenum, std::string> shaders = {
      { GL_VERTEX_SHADER, vertex_shader },
      { GL_FRAGMENT_SHADER, fragment_shader} };

  program = std::make_unique<Program>(shaders);

  const std::vector<Vector2f> points = {
    {0.0f, -0.004f},
    {0.25f, -0.004f},
    {0.25f, +0.004f},
    {0.0f, +0.004f},
    {0.25f, +0.02f},
    {0.27f, 0.0f},
    {0.25f, -0.02f}
  };
  const std::vector<unsigned int> indices = {
    0, 1, 2, 2, 3, 0, 4, 5, 6
  };

  vertex_buffer = std::make_unique<Buffer<Vector2f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, points);
  indices_buffer = std::make_unique<Buffer<unsigned int, GL_ELEMENT_ARRAY_BUFFER>>(GL_STATIC_DRAW, indices);
  angleValueChanged(0);
}

void WidgetGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void WidgetGL::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  Program::Use use(*program);

  program->setUniform("mat", mat);
  program->setAttribute("vertex", *vertex_buffer);

  program->enableVertexAttribArray("vertex");
  indices_buffer->bind();
  glDrawElements(GL_TRIANGLES, indices_buffer->size(), GL_UNSIGNED_INT, nullptr);
  indices_buffer->unbind();
  program->disableVertexAttribArray("vertex");
}

void WidgetGL::angleValueChanged(int angle) {
  const float theta = (4.0f * std::atan(1.0f) / 180.0f) * angle;
  mat(0, 0) = cos(theta);
  mat(0, 1) = -sin(theta);
  mat(1, 0) = sin(theta);
  mat(1, 1) = cos(theta);
  repaint();
}
