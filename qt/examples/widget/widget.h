#pragma once

#include <list>
#include <QPoint>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget();

protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent* event) override;

  std::list<std::pair<QPoint, QColor>> points;
};
