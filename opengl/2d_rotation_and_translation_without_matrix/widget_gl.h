#pragma once

#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "./../helper/buffer.h"
#include "./../helper/program.h"

class WidgetGL : public QOpenGLWidget, private QOpenGLFunctions {
  Q_OBJECT
public:
  WidgetGL(QWidget* parent);
  ~WidgetGL() = default;

public slots:
  void xValueChanged(int x);
  void yValueChanged(int y);
  void angleValueChanged(int angle);

  void redValueChanged(int red);
  void blueValueChanged(int green);
  void greenValueChanged(int blue);

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

  float yaw = 0.0f;
  Eigen::Vector2f pos = Eigen::Vector2f::Zero();
  Eigen::Vector3f color = Eigen::Vector3f::Ones();

  std::unique_ptr<opengl::Program> program;
  std::unique_ptr<opengl::Buffer<Eigen::Vector2f, GL_ARRAY_BUFFER>> vertex_buffer;
  std::unique_ptr<opengl::Buffer<unsigned int, GL_ELEMENT_ARRAY_BUFFER>> indices_buffer;
};
