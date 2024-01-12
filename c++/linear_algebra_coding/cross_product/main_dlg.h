#pragma once

#include <QDialog>

#include "ui_main_dlg.h"

#include <Eigen/Core>

class MainDlg : public QDialog, private Ui::MainDlgUi {
  Q_OBJECT
public:
  MainDlg();

private slots:
  void valueChangedAx(double val);
  void valueChangedAy(double val);
  void valueChangedAz(double val);
  void valueChangedBx(double val);
  void valueChangedBy(double val);
  void valueChangedBz(double val);

private:
  void vectorsUpdated();

  Eigen::Vector3f a;
  Eigen::Vector3f b;
  Eigen::Vector3f c;
};
