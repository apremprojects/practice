#include "widget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>

Widget::Widget() : QWidget(nullptr) {}

void Widget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  for (const auto& p : points) {
    painter.setPen(p.second);
    painter.drawText(p.first.x(), p.first.y(), tr("Hello"));
  }
}

void Widget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    points.emplace_back(event->pos(), QColor(rand() % 256, rand() % 256, rand() % 256));
    repaint();
  }
}

void Widget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Backspace) {
    if (!points.empty()) {
      points.pop_back();
    }
    repaint();
  }
}
