#pragma once

#include <QImage>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget(const QString& file_path);

private:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent* event) override;

  QImage image;
};
