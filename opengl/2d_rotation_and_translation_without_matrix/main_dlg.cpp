#include "main_dlg.h"

MainDlg::MainDlg()
  : QDialog(nullptr, Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint) {
  setupUi(this);
  connect(slider_x, SIGNAL(valueChanged(int)), widget_gl, SLOT(xValueChanged(int)));
  connect(slider_y, SIGNAL(valueChanged(int)), widget_gl, SLOT(yValueChanged(int)));
  connect(slider_yaw, SIGNAL(valueChanged(int)), widget_gl, SLOT(angleValueChanged(int)));
  connect(red_box, SIGNAL(valueChanged(int)), widget_gl, SLOT(redValueChanged(int)));
  connect(green_box, SIGNAL(valueChanged(int)), widget_gl, SLOT(greenValueChanged(int)));
  connect(blue_box, SIGNAL(valueChanged(int)), widget_gl, SLOT(blueValueChanged(int)));
}
