#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLibrary>
#include <QKeyEvent>
#include "../../brick_game/common/brick_game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame();
    void on_tetrisButton_clicked();
    void on_snakeButton_clicked();

private:
    void loadGameLibrary(const QString& path);
    void unloadGameLibrary();

    Ui::MainWindow *ui;
    QTimer *game_timer_;
    GameInfo_t current_game_info_;

    void (*lib_initGame)();
    void (*lib_destroyGame)();
    void (*lib_userInput)(UserAction_t, bool);
    GameInfo_t (*lib_updateCurrentState)();
    
    QLibrary game_library_;
};
#endif
