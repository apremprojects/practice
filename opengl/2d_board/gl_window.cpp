#include "gl_window.h"

#include <QKeyEvent>

using namespace Eigen;
using namespace opengl;

static const char vertex_shader[] = R"(
    #version 150
    in vec4 vertex;
    uniform mat3 mat;
    uniform float max_range;
    void main(void) {
      vec3 pos = mat*vec3(vertex.xy/max_range, 1.0f);
      gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
    })";

static const char fragment_shader[] = R"(
    #version 150
    out vec4 fragColor;
    uniform int color;
    void main(void) {
      float r = float((color & 0xFF0000) >> 16)/255.0f;
      float g = float((color & 0xFF00) >> 8)/255.0f;
      float b = float(color & 0x0000FF)/255.0f;
      fragColor = vec4(r, g, b, 1.0f);
    })";

#define DEG_TO_RAD(theta) ((4.0f/180.0f)*std::atan(1.0f)*theta)

WindowGL::WindowGL()
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, nullptr) {
  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  setFormat(format);
}

std::vector<Vector2f> WindowGL::createBoard(const Vector2f& min_range, const Vector2f& max_range, const Vector2f& xy_inc) {
  std::vector<Vector2f> points;
  for (float x = min_range.x(); x <= max_range.x(); x += xy_inc.x()) {
    points.emplace_back(x, min_range.y());
    points.emplace_back(x, max_range.y());
  }
  for (float y = min_range.y(); y <= max_range.y(); y += xy_inc.y()) {
    points.emplace_back(min_range.x(), y);
    points.emplace_back(max_range.x(), y);
  }
  return points;
}

std::vector<Vector2f> WindowGL::createArrow() {
  const std::vector<Vector2f> points = {
    {0.0f, -0.2f},
    {12.5f, -0.2f},
    {12.5f, +0.2f},
    {0.0f, +0.2f},
    {12.5f, +1.0f},
    {13.5f, 0.0f},
    {12.5f, -1.0f}
  };
  return points;
}

void WindowGL::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  static const std::map<GLenum, std::string> shaders = {
      { GL_VERTEX_SHADER, vertex_shader },
      { GL_FRAGMENT_SHADER, fragment_shader} };

  program = std::make_unique<Program>(shaders);

  const auto board_points = createBoard(Vector2f(-100.0f, -100.0f), Vector2f(+100.0f, +100.0f), Vector2f(10.0f, 10.0f));
  board_buffer = std::make_unique<Buffer<Vector2f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, board_points);

  const auto arrow_points = createArrow();
  arrow_buffer = std::make_unique<Buffer<Vector2f, GL_ARRAY_BUFFER>>(GL_STATIC_DRAW, arrow_points);
  const std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0, 4, 5, 6 };
  arrow_indices = std::make_unique<Buffer<unsigned int, GL_ELEMENT_ARRAY_BUFFER>>(GL_STATIC_DRAW, indices);
  updateMatrix(Vector3f(0.0f, 0.0f, 1.0f));
}

void WindowGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void WindowGL::drawArrow() {
  Program::Use use(*program);
  program->setUniform("mat", matrix);
  program->setUniform("max_range", 100.0f);
  program->setUniform("color", 0x0000FF);
  program->setAttribute("vertex", *arrow_buffer);
  program->enableVertexAttribArray("vertex");
  arrow_indices->bind();
  glDrawElements(GL_TRIANGLES, arrow_indices->size(), GL_UNSIGNED_INT, nullptr);
  arrow_indices->unbind();
  program->disableVertexAttribArray("vertex");
}

void WindowGL::drawBoard() {
  Program::Use use(*program);
  const Matrix3f mat = Matrix3f::Identity();
  program->setUniform("mat", mat);
  program->setUniform("max_range", 100.0f);
  program->setUniform("color", 0xFF0000);
  program->setAttribute("vertex", *board_buffer);
  program->enableVertexAttribArray("vertex");
  glDrawArrays(GL_LINES, 0, board_buffer->size());
  program->disableVertexAttribArray("vertex");
}

void WindowGL::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  drawBoard();
  drawArrow();
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
