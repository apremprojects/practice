#include <QApplication>

#include "widget.h"
#include <iostream>

int main(int argc, char** argv) {
  QApplication app(argc, argv);  
  Widget window;
  window.setWindowTitle("Flood fill");
  window.show();
  return app.exec();
}
