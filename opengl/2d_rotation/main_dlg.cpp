#include "main_dlg.h"

MainDlg::MainDlg()
  : QDialog(nullptr, Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint) {
  horiz_layout = new QHBoxLayout(this);
  widget_gl = new WidgetGL(this);

  slider_angle = new QSlider(this);
  slider_angle->setOrientation(Qt::Vertical);
  slider_angle->setRange(0, 360);

  horiz_layout->addWidget(widget_gl);
  horiz_layout->addWidget(slider_angle);

  setLayout(horiz_layout);
  setMinimumSize(1280, 720);
  setWindowTitle(tr("2D Rotation"));

  connect(slider_angle, SIGNAL(valueChanged(int)), widget_gl, SLOT(angleValueChanged(int)));
}
