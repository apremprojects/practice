#include <QApplication>

#include "widget.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);  
  Widget window;
  window.setWindowTitle("Signals slots Example");
  window.show();
  return app.exec();
}
