/* --- Файл: gamewidget.cpp --- */
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent), game_info_(nullptr) {
    setFixedSize(10 * block_width_ + 2, 20 * block_height_ + 2);
}

void GameWidget::updateField(GameInfo_t* info) {
    game_info_ = info;
    update(); // Говорит Qt перерисовать виджет
}

void GameWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width() - 1, height() - 1);

    if (!game_info_ || !game_info_->field) {
        return;
    }

    painter.setBrush(Qt::green);
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (game_info_->field[i][j] == 1) {
                painter.drawRect(j * block_width_ + 1, i * block_height_ + 1, block_width_, block_height_);
            }
        }
    }
}
