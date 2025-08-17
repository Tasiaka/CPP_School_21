#include "cli_hub.h"

extern "C" {

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);

void TetrisUserInput(UserAction_t action, bool hold);
GameInfo_t TetrisUpdateCurrentState(void);
}

namespace s21 {

using FnInput = void (*)(UserAction_t, bool);
using FnUpdate = GameInfo_t (*)();

struct GameApi {
  FnInput input;
  FnUpdate update;
  const char* name;
  GameKind kind;
};

static GameApi gSnake{&userInput, &updateCurrentState, "Snake",
                      GameKind::Snake};
static GameApi gTetris{&TetrisUserInput, &TetrisUpdateCurrentState, "Tetris",
                       GameKind::Tetris};

static GameApi* gActive = &gSnake;

void SelectGame(GameKind kind) {
  gActive = (kind == GameKind::Snake) ? &gSnake : &gTetris;
}

void SendInputToActiveGame(UserAction_t action, bool hold) {
  gActive->input(action, hold);
}

GameInfo_t UpdateActiveGameState() { return gActive->update(); }

const char* ActiveGameName() { return gActive->name; }
bool IsSnakeActive() { return gActive->kind == GameKind::Snake; }

}  // namespace s21