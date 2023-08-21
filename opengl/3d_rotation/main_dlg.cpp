#include "main_dlg.h"

MainDlg::MainDlg()
  : QDialog(nullptr, Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint) {
  horiz_layout = new QHBoxLayout(this);
  widget_gl = new WidgetGL(this);

  slider_roll = new QSlider(this);
  slider_roll->setOrientation(Qt::Vertical);
  slider_roll->setRange(0, 360);

  slider_pitch = new QSlider(this);
  slider_pitch->setOrientation(Qt::Vertical);
  slider_pitch->setRange(0, 360);

  slider_yaw = new QSlider(this);
  slider_yaw->setOrientation(Qt::Vertical);
  slider_yaw->setRange(0, 360);

  horiz_layout->addWidget(widget_gl);
  horiz_layout->addWidget(slider_roll);
  horiz_layout->addWidget(slider_pitch);
  horiz_layout->addWidget(slider_yaw);

  setLayout(horiz_layout);
  setMinimumSize(1280, 720);
  setWindowTitle(tr("3D Rotation"));

  connect(slider_roll, SIGNAL(valueChanged(int)), widget_gl, SLOT(rollValueChanged(int)));
  connect(slider_pitch, SIGNAL(valueChanged(int)), widget_gl, SLOT(pitchValueChanged(int)));
  connect(slider_yaw, SIGNAL(valueChanged(int)), widget_gl, SLOT(yawValueChanged(int)));
}
