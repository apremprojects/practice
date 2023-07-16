#include "widget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <iostream>

#include <vector>
#include <queue>
#include <array>
#include <map>

bool operator<(const QPoint& a, const QPoint& b) {
    if (a.x() < b.x()) {
        return true;
    }
    else if (a.x() == b.x()){
        return a.y() < b.y();
    }
    return false;
}

void populate_path(std::map<QPoint, QPoint> &prev_nodes, QImage &image, QPoint &prev, const QPoint &src) {
    while (prev != src) {
        image.setPixelColor(prev, QColor(0, 255, 0));
        prev = prev_nodes[prev];
    }
}

void bfs(const QPoint& src, const QPoint& dest, QImage& image) {
    qDebug() << "BFS Pathfinding\n";
    QPoint prev;
    std::queue<QPoint> queue;
    std::array<QPoint, 8> neighbors{
        QPoint(-1, 1), QPoint(0, 1), QPoint(1, 1), QPoint(-1, 0), QPoint(1, 0), QPoint(-1, 1), QPoint(0, 1), QPoint(1, 1)
    };
    std::vector<bool> visited(image.width() * image.height());
    std::map<QPoint, QPoint> prev_nodes;
    queue.push(src);
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();
        if (visited[(image.width() * node.y()) + node.x()]) {
            continue;
        }
        visited[(image.width() * node.y()) + node.x()] = true;
        prev = node;
        for (auto n : neighbors) {
            auto p = node + n;
            if (p.x() >= 0 && p.y() >= 0 && p.x() < image.width() && p.y() < image.height() 
                && !visited[image.width() * p.y() + p.x()] && image.pixelColor(p) == QColor(255, 255, 255)) {
                queue.push(p);
                prev_nodes[p] = prev;
                if (p == dest) {
                    populate_path(prev_nodes, image, prev, src);
                }
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
    bfs(QPoint(0, 0), QPoint(image.width() - 1, image.height() - 1), image);
    update();
  }
}
