#include <QApplication>

#include "widget.h"
#include <iostream>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Image path missing\n";
    exit(0);
  }
  QApplication app(argc, argv);  
  Widget window(argv[1]);
  window.setWindowTitle("Clustering");
  window.show();
  return app.exec();
}
