#include "main_dlg.h"

#include <QDebug>

#include <vector>
#include <random>

#include <Eigen/Core>

using namespace Eigen;

MainDlg::MainDlg()
  : QDialog(nullptr, Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint) {
  setupUi(this);

  widget_gl->setFocus();

  connect(spin_x, SIGNAL(valueChanged(int)), widget_gl, SLOT(xAngleChanged(int)));
  connect(spin_y, SIGNAL(valueChanged(int)), widget_gl, SLOT(yAngleChanged(int)));
  connect(spin_z, SIGNAL(valueChanged(int)), widget_gl, SLOT(zAngleChanged(int)));
}
