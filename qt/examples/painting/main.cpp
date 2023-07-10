#include <QApplication>

#include "painting_widget.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);  
  PaintingWidget window("Painting");
  window.show();
  return app.exec();
}
