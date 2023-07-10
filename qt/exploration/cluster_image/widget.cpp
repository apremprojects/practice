#include "widget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <array>

void dfs(const QPoint& p, const QColor& color, QImage& image) {
    static std::array<QPoint, 8> neighbors = {
      QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1),
      QPoint(-1, 0), QPoint(1, 0),
      QPoint(-1, 1), QPoint(0, 1), QPoint(1, 1)
    };
    std::stack<QPoint> stack;
    stack.push(p);
    while (!stack.empty()) {
        QPoint point = stack.top();
        stack.pop();
        if (image.pixelColor(point) == QColor(0, 0, 0)) {
            image.setPixelColor(point, color);
            for (const auto& r : neighbors) {
                auto p = point + r;
                if (p.x() < image.width() && p.y() < image.height() && p.x() >= 0 && p.y() >= 0) {
                    if (image.pixelColor(p) == QColor(0, 0, 0)) {
                        stack.push(p);
                    }
                }
            }
        }
    }
}

void bfs(const QPoint& p, const QColor& color, QImage& image) {
    static std::array<QPoint, 8> neighbors = {
      QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1),
      QPoint(-1, 0), QPoint(1, 0),
      QPoint(-1, 1), QPoint(0, 1), QPoint(1, 1)
    };
    std::queue<QPoint> queue;
    queue.push(p);
    while (!queue.empty()) {
        QPoint point = queue.front();
        queue.pop();
        if (image.pixelColor(point) == QColor(0, 0, 0)) {
            image.setPixelColor(point, color);
            for (const auto& r : neighbors) {
                auto p = point + r;
                if (p.x() < image.width() && p.y() < image.height() && p.x() >= 0 && p.y() >= 0) {
                    if (image.pixelColor(p) == QColor(0, 0, 0)) {
                        queue.push(p);
                    }
                }
            }
        }
    }
}

void clusterImage(QImage& image) {
  std::vector<QColor> colors = { 
    QColor(255, 0, 0), 
    QColor(0, 255, 0), 
    QColor(0, 0, 255), 
    QColor(0, 255, 255), 
    QColor(255, 0, 255) };

  size_t index = 0;
  for (size_t y = 0; y < image.height(); y++) {
      for (size_t x = 0; x < image.width(); x++) {
          if (image.pixelColor(x, y) == QColor(0, 0, 0)) {
              bfs(QPoint(x, y), colors[index], image);
              index = (index + 1) % colors.size();
          }
      }
  }
}

Widget::Widget(const QString& file_path)
  : QWidget(nullptr),
    image(file_path) {}

void Widget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.drawImage(QRect(0, 0, width(), height()), image);
}

void Widget::mousePressEvent(QMouseEvent* event) {
}

void Widget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    clusterImage(image);
    update();
  }
}
