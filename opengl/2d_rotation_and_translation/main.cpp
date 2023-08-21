#include <QApplication>

#include "gl_window.h"

int main(int argc, char** argv) {
  QGuiApplication app(argc, argv);  
  WindowGL window;
  window.resize(1280, 720);
  window.show();
  return app.exec();
}
