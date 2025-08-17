#include <QApplication>

#include "game_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::GameWindow w;
  w.show();
  return app.exec();
}
