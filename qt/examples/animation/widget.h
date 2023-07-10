#pragma once

#include <list>
#include <QPoint>
#include <QWidget>
#include <QTimer>

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget(const QString& title);

private slots:
  void updatePoints();

private:
  void paintEvent(QPaintEvent* event) override;

  QTimer timer;
  std::list<QPoint> points;
  const size_t max_size = 25;
};
