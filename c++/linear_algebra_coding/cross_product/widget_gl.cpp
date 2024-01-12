#include "widget_gl.h"

#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>

#include <array>

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 120
    attribute vec3 coord;
    uniform mat3 mat;
    void main(void)
    {
      vec3 pos = mat*coord;
      gl_Position = vec4(pos, 1.0f);
    })";

static const char fragment_shader[] = R"(
    #version 120
    uniform vec3 color;
    void main(void)
    {
        gl_FragColor = vec4(color, 1.0f);
    })";

#define DEG_TO_RADIAN(theta) ((4.0f * std::atan(1.0f) / 180.0f) * static_cast<float>(theta))

WidgetGL::WidgetGL(QWidget* parent)
  : QOpenGLWidget(parent) {
  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  setFormat(format);
}

void WidgetGL::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  static const std::map<GLenum, std::string> shaders = {
      { GL_VERTEX_SHADER, vertex_shader },
      { GL_FRAGMENT_SHADER, fragment_shader} };

  program = std::make_unique<Program>(shaders);
  const std::vector<Vector3f> points = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
  data_buffer = std::make_unique<Buffer<Vector3f, GL_ARRAY_BUFFER>>(GL_DYNAMIC_DRAW, points);
}

void WidgetGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void WidgetGL::paintGL() {
  const std::array<Vector3f, 3> colors = {
    Vector3f(1.0f, 0.0f, 0.0f), 
    Vector3f(0.0f, 1.0f, 0.0f), 
    Vector3f(0.0f, 0.0f, 1.0f) };
  const auto q = Eigen::AngleAxisf(x_rad, Eigen::Vector3f::UnitX()) *
                Eigen::AngleAxisf(y_rad, Eigen::Vector3f::UnitY()) *
                Eigen::AngleAxisf(z_rad, Eigen::Vector3f::UnitZ());
  for (unsigned i = 1; i < 4; i++) {
    Program::Use use(*program);
    program->setAttribute("coord", *data_buffer);
    program->setUniform("color", colors[i-1]);
    program->setUniform("mat", q);
    program->enableVertexAttribArray("coord");
    const std::array<unsigned, 2> indices = {0, i};
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indices.data());
    program->disableVertexAttribArray("coord");
  }
}

void WidgetGL::xAngleChanged(int angle) {
  x_rad = DEG_TO_RADIAN(angle);
  repaint();
}

void WidgetGL::yAngleChanged(int angle) {
  y_rad = DEG_TO_RADIAN(angle);
  repaint();
}

void WidgetGL::zAngleChanged(int angle) {
  z_rad = DEG_TO_RADIAN(angle);
  repaint();
}

void WidgetGL::update(const Eigen::Vector3f& a, const Eigen::Vector3f& b, const Eigen::Vector3f& c) {
  makeCurrent();
  data_buffer->load(1, 1, &a);
  data_buffer->load(2, 1, &b);
  data_buffer->load(3, 1, &c);
  doneCurrent();
  repaint();
}

