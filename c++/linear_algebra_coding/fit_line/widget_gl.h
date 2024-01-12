#pragma once

#include <memory>
#include <QMutex>
#include <QQueue>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "C:\Users\arjun\source\helper\buffer.h"
#include "C:\Users\arjun\source\helper\texture.h"
#include "C:\Users\arjun\source\helper\program.h"
class WidgetGL : public QOpenGLWidget, private QOpenGLFunctions {
  Q_OBJECT
public:
  WidgetGL(QWidget* parent);

  void update(const std::vector<Eigen::Vector2f>& points);
  void update(const Eigen::Vector2f& start_point, const Eigen::Vector2f& end_point);
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
  std::unique_ptr<opengl::Buffer<Eigen::Vector2f, GL_ARRAY_BUFFER>> points_buffer;
  std::unique_ptr<opengl::Buffer<Eigen::Vector2f, GL_ARRAY_BUFFER>> line_buffer;
};
