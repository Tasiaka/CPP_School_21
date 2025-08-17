#include "game_window.h"

#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>

namespace s21 {

GameWindow::GameWindow(QWidget* parent) : QMainWindow(parent) {
  BuildUi();
  SelectGame(GameKind::Snake);
  connect(&tick_, &QTimer::timeout, this, &GameWindow::OnTick);
  tick_.start(100);
}

void GameWindow::BuildUi() {
  central_ = new QWidget(this);
  setCentralWidget(central_);

  view_ = new GameView(this);
  next_ = new NextView(this);

  // правая панель
  auto* right = new QWidget(this);
  auto* rightLay = new QVBoxLayout(right);
  rightLay->setContentsMargins(8, 8, 8, 8);
  rightLay->setSpacing(6);

  btnSnake_ = new QPushButton("Snake", right);
  btnTetris_ = new QPushButton("Tetris", right);
  connect(btnSnake_, &QPushButton::clicked, this, &GameWindow::OnSelectSnake);
  connect(btnTetris_, &QPushButton::clicked, this, &GameWindow::OnSelectTetris);

  gameName_ = new QLabel("GAME: Snake", right);
  best_ = new QLabel("BEST: 0", right);
  level_ = new QLabel("LEVEL: 1", right);
  score_ = new QLabel("SCORE: 0", right);
  speed_ = new QLabel("SPEED: 0 ms", right);

  hint1_ = new QLabel(right);
  hint2_ = new QLabel(right);
  hint3_ = new QLabel(right);

  auto* sep1 = new QFrame(right);
  sep1->setFrameShape(QFrame::HLine);
  auto* sep2 = new QFrame(right);
  sep2->setFrameShape(QFrame::HLine);

  rightLay->addWidget(btnSnake_);
  rightLay->addWidget(btnTetris_);
  rightLay->addWidget(sep1);
  rightLay->addWidget(gameName_);
  rightLay->addWidget(best_);
  rightLay->addWidget(level_);
  rightLay->addWidget(score_);
  rightLay->addWidget(speed_);
  rightLay->addWidget(sep2);
  rightLay->addWidget(hint1_);
  rightLay->addWidget(hint2_);
  rightLay->addWidget(hint3_);
  rightLay->addStretch(1);
  rightLay->addWidget(new QLabel("Esc - Menu/Exit", right));
  rightLay->addWidget(new QLabel("NEXT:", right));
  rightLay->addWidget(next_);

  auto* h = new QHBoxLayout(central_);
  h->setContentsMargins(8, 8, 8, 8);
  h->setSpacing(12);
  h->addWidget(view_, 0);
  h->addWidget(right, 0);

  setWindowTitle("BrickGame — Desktop GUI");
  resize(820, 520);

  OnSelectSnake();
}

void GameWindow::OnSelectSnake() {
  SelectGame(GameKind::Snake);
  ResetActionHold();
  view_->SetSnakeMode(true);
  next_->setVisible(false);
  hint1_->setText("←/→: turn left/right");
  hint2_->setText("Space (hold): accelerate");
  hint3_->setText("S: start  P: pause");
}

void GameWindow::OnSelectTetris() {
  SelectGame(GameKind::Tetris);
  ResetActionHold();
  view_->SetSnakeMode(false);
  next_->setVisible(true);
  hint1_->setText("←/→/↓: move");
  hint2_->setText("Space/↑: rotate");
  hint3_->setText("S: start  P: pause");
}

void GameWindow::OnTick() {
  GameInfo_t gi = UpdateActiveGameState();
  view_->UpdateFrame(gi);
  next_->UpdateNext(gi);
  UpdateHud(gi);
  UpdateTimerInterval(gi.speed);
}

void GameWindow::UpdateHud(const GameInfo_t& gi) {
  gameName_->setText(QString("GAME: %1").arg(ActiveGameName()));
  best_->setText(QString("BEST: %1").arg(gi.high_score));
  level_->setText(QString("LEVEL: %1").arg(gi.level));
  score_->setText(QString("SCORE: %1").arg(gi.score));
  speed_->setText(QString("SPEED: %1 ms").arg(gi.speed));
}

void GameWindow::UpdateTimerInterval(int ms) {
  if (ms <= 0) ms = 100;
  if (tick_.interval() != ms) tick_.start(ms);
}

void GameWindow::ResetActionHold() {
  if (actionHold_) {
    actionHold_ = false;
    SendInputToActiveGame(Action, false);
  }
}

void GameWindow::keyPressEvent(QKeyEvent* e) {
  bool isSnake = IsSnakeActive();
  switch (e->key()) {
    case Qt::Key_S:
      SendInputToActiveGame(Start, false);
      break;
    case Qt::Key_P:
      SendInputToActiveGame(Pause, false);
      break;
    case Qt::Key_Escape:
      SendInputToActiveGame(Terminate, false);
      break;
    case Qt::Key_Left:
      SendInputToActiveGame(Left, false);
      break;
    case Qt::Key_Right:
      SendInputToActiveGame(Right, false);
      break;
    case Qt::Key_Down:
      if (!isSnake) SendInputToActiveGame(Down, false);
      break;
    case Qt::Key_Up:
      if (!isSnake && !e->isAutoRepeat()) SendInputToActiveGame(Action, false);
      break;
    case Qt::Key_Space:
      if (isSnake) {
        if (!e->isAutoRepeat() && !actionHold_) {
          actionHold_ = true;
          SendInputToActiveGame(Action, true);  // ускорение hold
        }
      } else {
        if (!e->isAutoRepeat()) SendInputToActiveGame(Action, false);  // rotate
      }
      break;
    default:
      break;
  }
  QMainWindow::keyPressEvent(e);
}

void GameWindow::keyReleaseEvent(QKeyEvent* e) {
  if (IsSnakeActive() && e->key() == Qt::Key_Space && !e->isAutoRepeat()) {
    if (actionHold_) {
      actionHold_ = false;
      SendInputToActiveGame(Action, false);
    }
  }
  QMainWindow::keyReleaseEvent(e);
}

}  // namespace s21
