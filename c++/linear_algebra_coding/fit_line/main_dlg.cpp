#include "main_dlg.h"

#include <QDebug>

#include <vector>
#include <random>
#include <iostream>

#include <Eigen/Core>

using namespace Eigen;

std::vector<Eigen::Vector2f> randomPoints(const size_t size) {
  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> x_dis(-1.0f, 1.0f);
  std::uniform_real_distribution<float> y_dis(-0.05f, 0.05f);
  std::vector<Eigen::Vector2f> points;
  points.reserve(size);
  const float theta = (4.0f*std::atan(1.0f)/180.0f)*(rand()%60);
  Eigen::Matrix3f mat;
  mat << cos(theta), -sin(theta), x_dis(gen),
         sin(theta), cos(theta), x_dis(gen),
         0.0f, 0.0f, 1.0f;
  for (size_t i = 0; i < size; i++) {
    const float scale = y_dis(gen);
    const auto p = mat*Eigen::Vector3f(x_dis(gen), scale*y_dis(gen), 1.0f);
    points.emplace_back(p.x(), p.y());
  }
  return points;
}

struct Line {
  Line(const float m, const float b):m(m), b(b) {};
  float m;
  float b;
};

Line fitLine(const std::vector<Eigen::Vector2f>& points) {
  MatrixXd A(points.size(), 2);
  VectorXd B(points.size());
  for (int row = 0; row < points.size(); row++) {
      A(row, 0) = 1;
      A(row, 1) = points[row](0);
      B(row) = points[row](1);
  }
  //A^T * A * x = A^T * b
  //x = (A.transpose() * A).inverse() * A.transpose() * b
  Vector2d x = (A.transpose() * A).inverse() * A.transpose() * B;
  return Line(x(1), x(0));
}

MainDlg::MainDlg()
  : QDialog(nullptr, Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint) {
  setupUi(this);

  widget_gl->setFocus();

  connect(fit_line_btn, SIGNAL(clicked()), this, SLOT(fitLineClicked()));
  connect(spin_x, SIGNAL(valueChanged(int)), widget_gl, SLOT(xAngleChanged(int)));
  connect(spin_y, SIGNAL(valueChanged(int)), widget_gl, SLOT(yAngleChanged(int)));
  connect(spin_z, SIGNAL(valueChanged(int)), widget_gl, SLOT(zAngleChanged(int)));
}

void MainDlg::fitLineClicked() {
  const auto points = randomPoints(1000000);
  widget_gl->update(points);
  Line line = fitLine(points);
  Vector2f start_point{ -320.0f, line.m * -320.0f + line.b };
  Vector2f end_point{ 320.0f, line.m * 320.0f + line.b };
  widget_gl->update(start_point, end_point); 
}
