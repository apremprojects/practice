#pragma once

#include <QDialog>
#include <QSlider>
#include <QHBoxLayout>

#include "widget_gl.h"

class MainDlg : public QDialog {
  Q_OBJECT
public:
  MainDlg();

private:
  QHBoxLayout* horiz_layout;

  WidgetGL* widget_gl;
  QSlider* slider_roll;
  QSlider* slider_pitch;
  QSlider* slider_yaw;
};
