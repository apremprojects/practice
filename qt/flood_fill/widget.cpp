#include "widget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QFileDialog>

#include <queue>
#include <array>
#include <map>

void bfsFill(const QPoint& point, const QColor& new_color, QImage& image) {

}

Widget::Widget()
  : QWidget(nullptr),
    image() {}

void Widget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.drawImage(QRect(0, 0, width(), height()), image);
}

void Widget::mousePressEvent(QMouseEvent* event) {
  const auto p = event->pos();
  const QPoint image_point(
    (static_cast<double>(p.x()) / static_cast<double>(width())) * image.width(),
    (static_cast<double>(p.y()) / static_cast<double>(height())) * image.height());
  bfsFill(image_point, QColor(0, 0xFF, 0), image);
  update();
}

void Widget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    auto file_path = QFileDialog::getOpenFileName(this, QString("Open"), QString(""), QString("*.png"));
    image.load(file_path);
    update();
  }
}
