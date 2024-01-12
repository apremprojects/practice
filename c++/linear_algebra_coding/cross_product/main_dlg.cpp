#include "main_dlg.h"

#include <QTime>
#include <QDebug>
#include <QFileDialog>

#include <vector>
#include <fstream>

#include <Eigen/Core>

using namespace Eigen;

MainDlg::MainDlg()
  : QDialog(nullptr, Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint) {
  setupUi(this);

  widget_gl->setFocus();

  connect(spin_x, SIGNAL(valueChanged(int)), widget_gl, SLOT(xAngleChanged(int)));
  connect(spin_y, SIGNAL(valueChanged(int)), widget_gl, SLOT(yAngleChanged(int)));
  connect(spin_z, SIGNAL(valueChanged(int)), widget_gl, SLOT(zAngleChanged(int)));

  connect(edit_a_x, SIGNAL(valueChanged(double)), this, SLOT(valueChangedAx(double)));
  connect(edit_a_y, SIGNAL(valueChanged(double)), this, SLOT(valueChangedAy(double)));
  connect(edit_a_z, SIGNAL(valueChanged(double)), this, SLOT(valueChangedAz(double)));

  connect(edit_b_x, SIGNAL(valueChanged(double)), this, SLOT(valueChangedBx(double)));
  connect(edit_b_y, SIGNAL(valueChanged(double)), this, SLOT(valueChangedBy(double)));
  connect(edit_b_z, SIGNAL(valueChanged(double)), this, SLOT(valueChangedBz(double)));
}

void MainDlg::valueChangedAx(double val) {
  a.x() = static_cast<float>(val);
  vectorsUpdated();
}

void MainDlg::valueChangedAy(double val) {
  a.y() = static_cast<float>(val);
  vectorsUpdated();
}

void MainDlg::valueChangedAz(double val) {
  a.z() = static_cast<float>(val);
  vectorsUpdated();
}

void MainDlg::valueChangedBx(double val) {
  b.x() = static_cast<float>(val);
  vectorsUpdated();
}

void MainDlg::valueChangedBy(double val) {
  b.y() = static_cast<float>(val);
  vectorsUpdated();
}

void MainDlg::valueChangedBz(double val) {
  b.z() = static_cast<float>(val);
  vectorsUpdated();
}

void MainDlg::vectorsUpdated() {
 // Compute cross product c = axb
 
 edit_c_x->setValue(c.x());
 edit_c_y->setValue(c.y());
 edit_c_z->setValue(c.z());
 widget_gl->update(a, b, c);
}
