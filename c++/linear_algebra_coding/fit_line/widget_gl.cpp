#include "widget_gl.h"

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
}

void WidgetGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void WidgetGL::paintGL() {
  const auto q = Eigen::AngleAxisf(x_rad, Eigen::Vector3f::UnitX()) *
                Eigen::AngleAxisf(y_rad, Eigen::Vector3f::UnitY()) *
                Eigen::AngleAxisf(z_rad, Eigen::Vector3f::UnitZ());
  if (points_buffer) {
    Program::Use use(*program);
    program->setAttribute("coord", *points_buffer);
    program->setUniform("color", Eigen::Vector3f(1.0f, 0.0f, 0.0f));
    program->setUniform("mat", q);
    program->enableVertexAttribArray("coord");
    glDrawArrays(GL_POINTS, 0, points_buffer->size());
    program->disableVertexAttribArray("coord");
  }
  if (line_buffer) {
      Program::Use use(*program);
      program->setAttribute("coord", *line_buffer);
      program->setUniform("color", Eigen::Vector3f(0.0f, 1.0f, 0.0f));
      program->setUniform("mat", q);
      program->enableVertexAttribArray("coord");
      glDrawArrays(GL_LINES, 0, line_buffer->size());
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

void WidgetGL::update(const std::vector<Eigen::Vector2f>& points) {
  makeCurrent();
  points_buffer = std::make_unique<Buffer<Vector2f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, points);
  doneCurrent();
  repaint();
}

void WidgetGL::update(const Vector2f &start_point, const Vector2f &end_point) {
    makeCurrent();
    std::vector<Vector2f> points{start_point, end_point};
    line_buffer = std::make_unique<Buffer<Vector2f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, points);
    doneCurrent();
    repaint();
}