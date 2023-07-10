#include <QApplication>

#include "widget.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);  
  Widget window;
  window.setWindowTitle("Widget Example");
  window.resize(1280, 720);
  window.show();
  return app.exec();
}
