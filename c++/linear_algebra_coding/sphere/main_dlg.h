#pragma once

#include <QDialog>

#include "ui_main_dlg.h"

#include <Eigen/Core>

class MainDlg : public QDialog, private Ui::MainDlgUi {
  Q_OBJECT
public:
  MainDlg();

};
