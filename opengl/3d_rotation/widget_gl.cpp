#include "widget_gl.h"

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 150
    in vec4 vertex;
    uniform mat3 mat;
    void main(void) {
        gl_Position = mat4(mat)*vertex;
    })";

static const char fragment_shader[] = R"(
    #version 150
    out vec4 fragColor;
    void main(void) {
        fragColor = vec4(0.0f, 1.0f, 0.0f, 0.0f);
    })";

#define DEG_TO_RADIAN(theta) ((4.0f * std::atan(1.0f) / 180.0f) * theta)

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

  const std::vector<Vector3f> points = {
    {0.0f, -0.004f, 0.0f},
    {0.25f, -0.004f, 0.0f},
    {0.25f, +0.004f, 0.0f},
    {0.0f, +0.004f, 0.0f},
    {0.25f, +0.02f, 0.0f},
    {0.27f, 0.0f, 0.0f},
    {0.25f, -0.02f, 0.0f}
  };
  const std::vector<unsigned int> indices = {
    0, 1, 2, 2, 3, 0, 4, 5, 6
  };

  vertex_buffer = std::make_unique<Buffer<Vector3f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, points);
  indices_buffer = std::make_unique<Buffer<unsigned int, GL_ELEMENT_ARRAY_BUFFER>>(GL_STATIC_DRAW, indices);
}

void WidgetGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void WidgetGL::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  Program::Use use(*program);

  program->setUniform("mat", matrix());
  program->setAttribute("vertex", *vertex_buffer);

  program->enableVertexAttribArray("vertex");
  indices_buffer->bind();
  glDrawElements(GL_TRIANGLES, indices_buffer->size(), GL_UNSIGNED_INT, nullptr);
  indices_buffer->unbind();
  program->disableVertexAttribArray("vertex");
}

void WidgetGL::rollValueChanged(int angle) {
  roll_ = DEG_TO_RADIAN(angle);
  repaint();
}

void WidgetGL::pitchValueChanged(int angle) {
  pitch_ = DEG_TO_RADIAN(angle);
  repaint();
}

void WidgetGL::yawValueChanged(int angle) {
  yaw_ = DEG_TO_RADIAN(angle);
  repaint();
}

Matrix3f WidgetGL::matrix() const {
  Matrix3f yaw_mat;
  yaw_mat << cos(yaw_), -sin(yaw_), 0.0f,
             sin(yaw_),  cos(yaw_), 0.0f,
             0.0f,       0.0f,      1.0f;

  Matrix3f roll_mat;
  roll_mat << cos(roll_), 0.0f, -sin(roll_),
              0.0f,       1.0f,  0.0f,
              sin(roll_), 0.0f,  cos(roll_);

  Matrix3f pitch_mat;
  pitch_mat << 1.0f,  0.0f,         0.0f,
               0.0f,  cos(pitch_), -sin(pitch_),
               0.0f,  sin(pitch_),  cos(pitch_);

  return yaw_mat * roll_mat * pitch_mat;
}
