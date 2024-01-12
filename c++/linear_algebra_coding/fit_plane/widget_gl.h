#pragma once

#include <memory>
#include <random>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "./../../helper/buffer.h"
#include "./../../helper/texture.h"
#include "./../../helper/program.h"

class WidgetGL : public QOpenGLWidget, private QOpenGLFunctions {
  Q_OBJECT
public:
  WidgetGL(QWidget* parent);

private slots:
  void xAngleChanged(int angle);
  void yAngleChanged(int angle);
  void zAngleChanged(int angle);

private:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

  float x_rad = 0.0f;
  float y_rad = 0.0f;
  float z_rad = 0.0f;

  std::unique_ptr<opengl::Program> program;
  std::unique_ptr<opengl::Buffer<Eigen::Vector3f, GL_ARRAY_BUFFER>> points_buffer;
};
