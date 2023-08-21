#include "gl_window.h"

#include <QKeyEvent>

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 150
    in vec4 vertex;
    in vec4 inColor;
    out vec3 outColor;
    void main(void) {
        gl_Position = vertex;
        outColor = inColor.xyz;
    })";

static const char fragment_shader[] = R"(
    #version 150
    in vec3 outColor;
    out vec4 fragColor;
    void main(void) {
        fragColor = vec4(outColor, 1.0f);
    })";

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
      {-0.5f, -0.5f},
      {0.0f, -0.75f},
      {+0.5f, -0.5f},
      {+0.75f, 0.0f},
      {+0.5f, +0.5f},
      {0.0f, +0.75f},
      {-0.5f, +0.5f},
      {-0.75f, +0.0f}
  };
  const std::vector<Vector3f> colors = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 0.0f}
  };

  color_buffer = std::make_unique<Buffer<Vector3f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, colors);
  vertex_buffer = std::make_unique<Buffer<Vector2f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, points);
}

void WindowGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void WindowGL::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  Program::Use use(*program);

  program->setAttribute("vertex", *vertex_buffer);
  program->setAttribute("inColor", *color_buffer);

  program->enableVertexAttribArray("vertex");
  program->enableVertexAttribArray("inColor");
  switch (mode) {
    case POINTS:
      glDrawArrays(GL_POINTS, 0, vertex_buffer->size());
      break;
    case LINES:
      glDrawArrays(GL_LINES, 0, vertex_buffer->size());
      break;
    case LINE_STRIP:
      glDrawArrays(GL_LINE_STRIP, 0, vertex_buffer->size());
      break;
    case LINE_LOOP:
      glDrawArrays(GL_LINE_LOOP, 0, vertex_buffer->size());
      break;
  }
  program->disableVertexAttribArray("vertex");
  program->disableVertexAttribArray("inColor");
}

void WindowGL::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_F1:
      mode = POINTS;
      break;
    case Qt::Key_F2:
      mode = LINES;
      break;
    case Qt::Key_F3:
      mode = LINE_STRIP;
      break;
    case Qt::Key_F4:
      mode = LINE_LOOP;
      break;
  }
  update();
}

