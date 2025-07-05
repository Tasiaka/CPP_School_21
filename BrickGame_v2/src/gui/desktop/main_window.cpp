#include "main_window.h"
#include <QVBoxLayout>

using s21::SnakeModel;
using s21::SnakeController;
using s21::SnakeWidget;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    stack_(new QStackedWidget(this)),
    btn_tetris_(new QPushButton("Play Tetris", this)),
    btn_snake_(new QPushButton("Play Snake", this)),
    menu_(new QWidget(this))
{
  setWindowTitle("BrickGame v2");
  resize(360, 420);

  // Tetris
  TetrisWidget *tetris = new TetrisWidget(this);

  // Snake MVC
  SnakeModel      *model   = new SnakeModel();
  SnakeController *ctrl    = new SnakeController(model);
  SnakeWidget     *snake   = new SnakeWidget(ctrl, this);

  // Меню
  QVBoxLayout *menuLayout = new QVBoxLayout(menu_);
  menuLayout->addWidget(btn_tetris_);
  menuLayout->addWidget(btn_snake_);
  menu_->setLayout(menuLayout);

  // Стек
  stack_->addWidget(menu_);   // 0
  stack_->addWidget(tetris);  // 1
  stack_->addWidget(snake);   // 2
  setCentralWidget(stack_);

  // Подключаем лямбды вместо слотов
  connect(btn_tetris_, &QPushButton::clicked,
          this, [this]() { stack_->setCurrentIndex(1); });
  connect(btn_snake_, &QPushButton::clicked,
          this, [this]() { stack_->setCurrentIndex(2); });
}

MainWindow::~MainWindow() = default;
