#pragma once

#include <list>
#include <QPoint>
#include <QWidget>
#include <QTimer>
#include <QSerialPort>

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget();

protected:
  void paintEvent(QPaintEvent* event) override;

  QTimer timer;
  QSerialPort port;
};
