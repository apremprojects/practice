#include "widget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>

Widget::Widget() : QWidget(nullptr), timer(this), port(this) {
  port.setPortName("COM5");
  port.setBaudRate(QSerialPort::Baud115200);
  port.setDataBits(QSerialPort::Data8);
  port.setFlowControl(QSerialPort::NoFlowControl);
  port.setParity(QSerialPort::NoParity);
  port.open(QIODevice::ReadWrite);
  
  timer.setInterval(50);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  timer.start();
}

void Widget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  if (port.isOpen()) {
    char buffer[1024];
    size_t size_w = port.write("r");
    size_t size_r = port.read(buffer, 1024);
    buffer[size_r] = '\0';
    painter.drawText(QRect(0, 0, width(), height()), buffer, QTextOption(Qt::AlignHCenter|Qt::AlignVCenter));
    //qDebug() << size_w << ", " << size_r << ", " << buffer;
  } else {
    qDebug() << "Failed";
  }
}
