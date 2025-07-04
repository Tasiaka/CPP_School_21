/* --- Файл: gamewidget.h --- */
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include "../../brick_game/common/brick_game.h"

class GameWidget : public QWidget {
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    void updateField(GameInfo_t* info);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    GameInfo_t* game_info_;
    const int block_width_ = 20;
    const int block_height_ = 20;
};

#endif
