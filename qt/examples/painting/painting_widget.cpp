#include "painting_widget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>

PaintingWidget::PaintingWidget(const QString& title) : QWidget(nullptr) {
  setWindowTitle(title);
}

void PaintingWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setPen(QPen(QColor(0xFF, 0, 0), 3));
  for (const auto& points : points_list) {
    if (points.empty()) continue;
    auto itr = points.begin();
    auto prev = *itr++;
    for (; itr < points.end(); itr++) {
      painter.drawLine(prev, *itr);
      prev = *itr;
    }
  }
}

void PaintingWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    QList<QPoint> points;
    points_list.push_back(std::move(points));
    points_list.back().push_back(event->pos());
    update();
  }
}

void PaintingWidget::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    points_list.back().push_back(event->pos());
    update();
  }
}

void PaintingWidget::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    points_list.back().push_back(event->pos());
    update();
  }
}

void PaintingWidget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Backspace) {
    if (!points_list.empty()) {
      points_list.pop_back();
    }
    update();
  }
}
