#include "gl_window.h"

#include <QKeyEvent>

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 150
    in vec4 vertex;
    uniform mat3 mat;
    void main(void) {
      vec3 pos = mat*vec3(vertex.xy, 1.0f);
      gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
    })";

static const char fragment_shader[] = R"(
    #version 150
    out vec4 fragColor;
    uniform vec3 color;
    void main(void) {
      fragColor = vec4(color, 1.0f);
    })";

#define DEG_TO_RAD(theta) ((4.0f/180.0f)*std::atan(1.0f)*theta)

WindowGL::WindowGL()
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, nullptr) {
  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setVersion(4, 5);
  setFormat(format);
}

void WindowGL::initializeGL() {
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
  const std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0, 4, 5, 6 };
  vertex_buffer = std::make_unique<Buffer<Vector2f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, points);
  indices_buffer = std::make_unique<Buffer<unsigned int, GL_ELEMENT_ARRAY_BUFFER>>(GL_STATIC_DRAW, indices);
  updateMatrix(Vector3f(0.0f, 0.0f, 1.0f));
}

void WindowGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void WindowGL::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  Program::Use use(*program);

  program->setUniform("mat", matrix);
  program->setUniform("color", Vector3f(0.5f, 0.5f, 0.5f));
  program->setAttribute("vertex", *vertex_buffer);
  program->enableVertexAttribArray("vertex");
  indices_buffer->bind();
  glDrawElements(GL_TRIANGLES, indices_buffer->size(), GL_UNSIGNED_INT, nullptr);
  indices_buffer->unbind();
  program->disableVertexAttribArray("vertex");
}

void WindowGL::updateMatrix(const Vector3f& pos) {
  const float angle_rad = DEG_TO_RAD(angle);
  matrix(0, 0) = cos(angle_rad);
  matrix(0, 1) = -sin(angle_rad);
  matrix(1, 0) = sin(angle_rad);
  matrix(1, 1) = cos(angle_rad);
  const Vector3f t = matrix * pos;
  matrix(0, 2) = t.x();
  matrix(1, 2) = t.y();
}

void WindowGL::keyPressEvent(QKeyEvent *event) {
  Vector3f pos = {0.0f, 0.0f, 1.0f};
  switch (event->key()) {
    case Qt::Key_Up:
      pos.x() = 0.005f;
      break;
    case Qt::Key_Down:
      pos.x() = -0.005f;
      break;
    case Qt::Key_Left:
      angle += 1.0f;
      break;
    case Qt::Key_Right:
      angle -= 1.0f;
      break;
  }
  updateMatrix(pos);
  update();
}
