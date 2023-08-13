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
    auto color = image.pixelColor(point);
    static const std::array<QPoint, 8> neighbors{
        QPoint(-1, 1), QPoint(0, 1), QPoint(1, 0),
        QPoint(-1, 0), QPoint(1, 0),
        QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1)
    };
    std::queue<QPoint> queue;
    queue.push(point);
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();
        for (auto n : neighbors) {
            auto p = node + n;
            if (p.x() >= 0 && p.y() >= 0 && p.x() < image.width() && p.y() < image.height()) {
                if (image.pixelColor(p) == color) {
                    image.setPixelColor(p, new_color);
                    queue.push(p);
                }
            }
        }
    }
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
