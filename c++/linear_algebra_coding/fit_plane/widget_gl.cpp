#include "widget_gl.h"

#include <QDebug>
#include <QKeyEvent>

#include <array>

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 120
    attribute vec3 coord;
    varying vec3 outColor;
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

std::vector<Vector3f> randomPointsInPlane(const size_t n) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(-0.25f, 0.25f);
  std::uniform_real_distribution<float> z_dis(-0.01f, 0.01f);
  const float pi = 4.0f*std::atan(1.0f);
  std::uniform_real_distribution<float> angle_dis(-pi, pi);
  std::vector<Vector3f> points(n);
  const Vector3f origin(dis(gen), dis(gen), z_dis(gen));
  const auto q = AngleAxisf(angle_dis(gen), Vector3f::UnitX())*
                 AngleAxisf(angle_dis(gen), Vector3f::UnitY())*
                 AngleAxisf(angle_dis(gen), Vector3f::UnitZ());
  for (size_t i = 0; i < n; i++) {
    const Vector3f p(dis(gen), dis(gen), z_dis(gen));
    points[i] = q*p;
  }
  return points;
}

struct Plane {
  float a;
  float b;
  float c;
};

Plane fitPlane(const std::vector<Vector3f>& points) {
  //
  return Plane();
}

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
  const auto points = randomPointsInPlane(200);
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
    program->setUniform("color", Vector3f(1.0f, 0.0f, 0.0f));
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
