#include "mainwindow.h"
#include "ui_mainwindow.h" 
#include <QMessageBox> // Для вывода ошибок
#include <QDir>        // Для работы с путями

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    game_timer_ = new QTimer(this);
    connect(game_timer_, &QTimer::timeout, this, &MainWindow::updateGame);
    
    lib_initGame = nullptr;
    lib_destroyGame = nullptr;
    lib_userInput = nullptr;
    lib_updateCurrentState = nullptr;
}

MainWindow::~MainWindow() {
    unloadGameLibrary();
    delete ui;
}

void MainWindow::loadGameLibrary(const QString& libName) {
    unloadGameLibrary();

    // Формируем правильный путь к библиотеке относительно исполняемого файла
    QString path = QDir(qApp->applicationDirPath()).filePath(libName);

    game_library_.setFileName(path);
    if (!game_library_.load()) {
        // Показываем пользователю подробную ошибку
        QMessageBox::critical(this, "Library Load Error", game_library_.errorString());
        return;
    }
    
    lib_initGame = (void (*)())game_library_.resolve("initGame");
    lib_destroyGame = (void (*)())game_library_.resolve("destroyGame");
    lib_userInput = (void (*)(UserAction_t, bool))game_library_.resolve("userInput");
    lib_updateCurrentState = (GameInfo_t (*)())game_library_.resolve("updateCurrentState");

    if (!lib_initGame || !lib_destroyGame || !lib_userInput || !lib_updateCurrentState) {
        QMessageBox::critical(this, "Symbol Resolve Error", "Could not find one or more required functions in the library.");
        unloadGameLibrary();
        return;
    }

    lib_initGame();
    game_timer_->start(100);
}


// void MainWindow::loadGameLibrary(const QString& path) {
//     unloadGameLibrary();

//     game_library_.setFileName(path);
//     if (!game_library_.load()) {
//         return;
//     }
    
//     lib_initGame = (void (*)())game_library_.resolve("initGame");
//     lib_destroyGame = (void (*)())game_library_.resolve("destroyGame");
//     lib_userInput = (void (*)(UserAction_t, bool))game_library_.resolve("userInput");
//     lib_updateCurrentState = (GameInfo_t (*)())game_library_.resolve("updateCurrentState");

//     if (lib_initGame && lib_updateCurrentState && lib_userInput && lib_destroyGame) {
//         lib_initGame();
//         game_timer_->start(100);
//     } else {
//         unloadGameLibrary();
//     }
// }

void MainWindow::unloadGameLibrary() {
    if (game_library_.isLoaded()) {
        if (lib_destroyGame) {
            lib_destroyGame();
        }
        game_library_.unload();
    }
    lib_initGame = nullptr;
    lib_destroyGame = nullptr;
    lib_userInput = nullptr;
    lib_updateCurrentState = nullptr;
    game_timer_->stop();
}

void MainWindow::on_tetrisButton_clicked() {
    loadGameLibrary("../libtetris_lib.so"); 
}

void MainWindow::on_snakeButton_clicked() {
    loadGameLibrary("../libsnake_lib.so");
}

void MainWindow::updateGame() {
    if (lib_updateCurrentState) {
        current_game_info_ = lib_updateCurrentState();
        
        ui->scoreLcd->display(current_game_info_.score);
        ui->highScoreLcd->display(current_game_info_.high_score);
        ui->levelLcd->display(current_game_info_.level);
        
        ui->gameWidget->updateField(&current_game_info_);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!lib_userInput) return;

    UserAction_t action;
    bool known_key = true;
    switch (event->key()) {
        case Qt::Key_Left:  action = Left; break;
        case Qt::Key_Right: action = Right; break;
        case Qt::Key_Up:    action = Up; break;
        case Qt::Key_Down:  action = Down; break;
        case Qt::Key_Space: action = Action; break;
        case Qt::Key_S:     action = Start; break;
        case Qt::Key_P:     action = Pause; break;
        case Qt::Key_T:     action = Terminate; break;
        default: known_key = false; break;
    }
    
    if (known_key) {
        lib_userInput(action, false);
    }
}
