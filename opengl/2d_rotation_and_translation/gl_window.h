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

  void updateMatrix(const Eigen::Vector3f& pos);

  float angle = 0.0f;
  Eigen::Matrix3f matrix = Eigen::Matrix3f::Identity();

  std::unique_ptr<opengl::Program> program;
  std::unique_ptr<opengl::Buffer<Eigen::Vector2f, GL_ARRAY_BUFFER>> vertex_buffer;
  std::unique_ptr<opengl::Buffer<unsigned int, GL_ELEMENT_ARRAY_BUFFER>> indices_buffer;
};
