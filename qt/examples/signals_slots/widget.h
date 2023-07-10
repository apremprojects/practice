#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget();

protected slots:
  void add();
  void subtract();
  void multiply();

protected:
  QLineEdit* out_edit;
  QLineEdit* num1_edit;
  QLineEdit* num2_edit;
  QPushButton* add_button;
  QPushButton* sub_button;
  QPushButton* mul_button;
  QGridLayout* grid_layout;
};
