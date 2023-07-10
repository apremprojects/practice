#include "widget.h"

#include <QPainter>
#include <QPaintEvent>

Widget::Widget(const QString& title) 
  : QWidget(nullptr), 
    timer(this) {
  setWindowTitle(title);
  points.push_back(QPoint(0, 0));
  timer.setInterval(1);
  connect(&timer, SIGNAL(timeout()), this, SLOT(updatePoints()));
  timer.start();
}

void Widget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  QPen pen(QColor(0xFF, 0, 0));
  pen.setWidth(3);
  painter.setPen(pen);
  auto itr = points.begin();
  QPoint prev = *itr++;
  for (; itr != points.end(); itr++) {
    painter.drawLine(prev, *itr);
    prev = *itr;
  }
}

void Widget::updatePoints() {
  if (points.size() >= max_size) {
    points.pop_front();
  }
  int x = points.back().x() + (5 - rand() % 10);
  int y = points.back().y() + (5 - rand() % 10);
  x = std::min(std::max(x, 0), width() - 1);
  y = std::min(std::max(y, 0), height() - 1);
  points.emplace_back(x, y);
  update();
}
