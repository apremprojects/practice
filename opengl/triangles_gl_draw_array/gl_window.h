#pragma once

#include <memory>
#include <QOpenGLWindow>
#include <QOpenGLFunctions>

#include "../helper/buffer.h"
#include "../helper/program.h"

class WindowGL : public QOpenGLWindow, private QOpenGLFunctions {
  Q_OBJECT
public:
  WindowGL();
  ~WindowGL() = default;

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

  void keyPressEvent(QKeyEvent *event);

  enum Mode { POINTS, LINES, LINE_STRIP, LINE_LOOP };
  Mode mode = POINTS;

  std::unique_ptr<opengl::Program> program;
  std::unique_ptr<opengl::Buffer<Eigen::Vector3f, GL_ARRAY_BUFFER>> color_buffer;
  std::unique_ptr<opengl::Buffer<Eigen::Vector2f, GL_ARRAY_BUFFER>> vertex_buffer;
};
