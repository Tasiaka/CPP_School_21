#src / gui / desktop / desktop.pro

QT += core gui widgets
TEMPLATE = app
TARGET = BrickGame_desktop

CONFIG += console c++17
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -Wall -Wextra -Werror
QMAKE_CFLAGS   += -Wall -Wextra -Werror

INCLUDEPATH += \
    $$PWD \
    $$PWD/../cli \
    $$PWD/../../brick_game/common \
    $$PWD/../../brick_game/snake  \
    $$PWD/../../brick_game/tetris

HEADERS += \
    $$files($$PWD/*.h) \
    $$files($$PWD/../cli/*.h) \
    $$files($$PWD/../../brick_game/common/*.h) \
    $$files($$PWD/../../brick_game/snake/*.h)  \
    $$files($$PWD/../../brick_game/tetris/*.h)

SOURCES += \
    $$files($$PWD/*.cpp) \
    $$PWD/../cli/cli_hub.cpp \
    $$files($$PWD/../../brick_game/snake/*.cpp) \
    $$files($$PWD/../../brick_game/tetris/*.c)
