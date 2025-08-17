#include <gtest/gtest.h>
#include <unistd.h>  // usleep

extern "C" {
#include "../brick_game/common/common.h"
// C-обертки змейки из snake_adapter_c_api.cc
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);
}

// --- helpers ---
static GameInfo_t StartSnake() {
  userInput(Start, false);
  return updateCurrentState();
}

static void SleepForTick(const GameInfo_t& gi, double factor = 1.2) {
  int ms = gi.speed > 0 ? gi.speed : 100;
  usleep(static_cast<useconds_t>(ms * 1000 * factor));
}

// --- TESTS ---

TEST(SnakeFsm, InitDefaults) {
  auto gi = StartSnake();
  ASSERT_NE(gi.field, nullptr);
  EXPECT_EQ(gi.level, 1);
  EXPECT_EQ(gi.score, 0);
  EXPECT_EQ(gi.pause, 0);  // running
}

TEST(SnakeFsm, PauseResume) {
  auto gi = StartSnake();

  userInput(Pause, false);
  gi = updateCurrentState();
  EXPECT_EQ(gi.pause, 1);  // paused

  userInput(Pause, false);
  gi = updateCurrentState();
  EXPECT_EQ(gi.pause, 0);  // resumed
}

TEST(SnakeFsm, ActionHoldToggleDoesNotStickOrCrash) {
  auto gi = StartSnake();

  userInput(Action, true);  // accelerate (hold)
  gi = updateCurrentState();
  EXPECT_GE(gi.level, 1);  // still sane

  userInput(Action, false);  // release
  gi = updateCurrentState();
  EXPECT_GE(gi.level, 1);
}

TEST(SnakeFsm, QuickTurnsDoNotCrash) {
  auto gi = StartSnake();

  userInput(Left, false);
  gi = updateCurrentState();

  userInput(Right, false);
  gi = updateCurrentState();

  EXPECT_NE(gi.pause, 2);  // not GAME OVER
  EXPECT_NE(gi.pause, 3);  // not Terminate
}

TEST(SnakeFsm, HitWallEventuallyFinishesGame) {
  auto gi = StartSnake();

  // едем прямо до упора в стену; даём времени таймеру (tick)
  int safety = 40;
  while (safety-- > 0) {
    SleepForTick(gi, 1.3);
    gi = updateCurrentState();
    if (gi.pause == 2 || gi.pause == 3)
      break;  // GameOver or Terminate-after-GameOver
  }
  EXPECT_TRUE(gi.pause == 2 || gi.pause == 3) << "pause=" << gi.pause;
}

TEST(SnakeFsm, TerminateIsHandledOutsideModel_NoCrash) {
  auto gi = StartSnake();
  userInput(Terminate, false);
  gi = updateCurrentState();
  // модель может игнорировать Terminate (им занимается хаб/меню)
  EXPECT_TRUE(gi.pause == 0 || gi.pause == 1 || gi.pause == 3);
}
