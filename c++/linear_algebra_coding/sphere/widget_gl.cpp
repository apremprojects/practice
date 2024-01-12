#include "widget_gl.h"

#include <QDebug>
#include <QKeyEvent>

#include <array>
#include <cmath>

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 120
    attribute vec3 coord;
    attribute vec3 color;
    varying vec3 outColor;
    uniform mat3 mat;
    void main(void)
    {
      vec3 pos = mat*coord;
      outColor = color;
      gl_Position = vec4(pos, 1.0f);
    })";

static const char fragment_shader[] = R"(
    #version 120
    varying vec3 outColor;
    void main(void)
    {
        gl_FragColor = vec4(outColor, 1.0f);
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
  std::vector<Eigen::Vector3f> points;
  std::vector<Eigen::Vector3f> colors;
  const float r = 0.5f;
  for (int phi = -90; phi <= 90; phi += 1) {
    for (int lamda = -180; lamda < 180; lamda += 1) {
      const float phi_rad = DEG_TO_RADIAN(phi);
      const float lamda_rad = DEG_TO_RADIAN(lamda);
      const float x = r * cos(phi_rad) * sin(lamda_rad);
      const float y = r * sin(phi_rad);
      const float z = r * cos(phi_rad) * cos(lamda_rad);
      points.emplace_back(x, y, z);
      const float r = (x > 0.0f)?x:(1.0f+x);
      const float g = (y > 0.0f)?y:(1.0f+y);
      const float b = (z > 0.0f)?z:(1.0f+z);
      colors.emplace_back(r, g, b);
    }
  }
  color_buffer = std::make_unique<Buffer<Vector3f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, colors);
  points_buffer = std::make_unique<Buffer<Vector3f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, points);
}

void WidgetGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void WidgetGL::paintGL() {
  const auto q = Eigen::AngleAxisf(x_rad, Eigen::Vector3f::UnitX()) *
                Eigen::AngleAxisf(y_rad, Eigen::Vector3f::UnitY()) *
                Eigen::AngleAxisf(z_rad, Eigen::Vector3f::UnitZ());
  {
    Program::Use use(*program);
    program->setAttribute("coord", *points_buffer);
    program->setAttribute("color", *color_buffer);
    program->setUniform("mat", q);
    program->enableVertexAttribArray("coord");
    program->enableVertexAttribArray("color");
    glDrawArrays(GL_POINTS, 0, points_buffer->size());
    program->disableVertexAttribArray("color");
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
