#include "widget_gl.h"

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 150
    in vec4 vertex;
    uniform float yaw;
    uniform vec2 translation;
    void main(void) {
      float x = translation.x + vertex.x*cos(yaw) - vertex.y*sin(yaw);
      float y = translation.y + vertex.x*sin(yaw) + vertex.y*cos(yaw);
      gl_Position = vec4(x, y, 0.0f, 1.0f);
    })";

static const char fragment_shader[] = R"(
    #version 150
    uniform vec3 color;
    out vec4 fragColor;
    void main(void) {
      fragColor = vec4(color, 1.0f);
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
    {0.0f, 0.0125f},
    {0.05f, 0.0f},
    {0.0f, -0.0125f}
  };
  const std::vector<unsigned int> indices = { 0, 1, 2 };
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

  program->setUniform("yaw", yaw);
  program->setUniform("translation", pos);
  program->setUniform("color", color);
  program->setAttribute("vertex", *vertex_buffer);

  program->enableVertexAttribArray("vertex");
  indices_buffer->bind();
  glDrawElements(GL_TRIANGLES, indices_buffer->size(), GL_UNSIGNED_INT, nullptr);
  indices_buffer->unbind();
  program->disableVertexAttribArray("vertex");
}

void WidgetGL::xValueChanged(int x) {
  pos.x() = static_cast<float>(x) / 100.0f;
  repaint();
}

void WidgetGL::yValueChanged(int y) {
  pos.y() = static_cast<float>(y) / 100.0f;
  repaint();
}

void WidgetGL::angleValueChanged(int angle) {
  yaw = (4.0f * std::atan(1.0f) / 180.0f) * angle;
  repaint();
}

void WidgetGL::redValueChanged(int red) {
  color.x() = static_cast<float>(red) / 255.0f;
  repaint();
}

void WidgetGL::blueValueChanged(int green) {
  color.y() = static_cast<float>(green) / 255.0f;
  repaint();
}

void WidgetGL::greenValueChanged(int blue) {
  color.z() = static_cast<float>(blue) / 255.0f;
  repaint();
}
