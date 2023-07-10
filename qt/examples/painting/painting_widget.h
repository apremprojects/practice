#pragma once

#include <QList>
#include <QPoint>
#include <QVector>
#include <QWidget>

class PaintingWidget : public QWidget {
  Q_OBJECT
public:
  PaintingWidget(const QString& title);

private:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;

  QList<QList<QPoint>> points_list;
};
