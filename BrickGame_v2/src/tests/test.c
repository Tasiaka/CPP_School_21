#include "testik.h"
START_TEST(test_tetris_game_1) {
  FullGameStat data_tetris_add = {0};
  RESTARTing(&data_tetris_add);
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      ck_assert_int_eq(0, data_tetris_add.MotionField[i][j]);
  ck_assert_int_eq(0, data_tetris_add.data_tetris.score);
  ck_assert_int_eq(0, data_tetris_add.data_tetris.pause);
  ck_assert_int_eq(1, data_tetris_add.data_tetris.level);
}
END_TEST

START_TEST(test_tetris_game_2) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      ck_assert_int_eq(0, data_tetris_add.data_tetris.field[i][j]);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      ck_assert_int_eq(0, data_tetris_add.data_tetris.next[i][j]);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
  ck_assert_ptr_null(data_tetris_add.data_tetris.field);
  ck_assert_ptr_null(data_tetris_add.data_tetris.next);
}
END_TEST

START_TEST(test_tetris_game_3) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  for (int i = 0; i < 19; i++)
    for (int j = 0; j < 10; j++) data_tetris_add.MotionField[i][j] = 1;
  GetReadyField(&data_tetris_add);
  for (int i = 0; i < 19; i++)
    for (int j = 0; j < 10; j++)
      ck_assert_int_eq(1, data_tetris_add.data_tetris.field[i][j]);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      ck_assert_int_eq(0, data_tetris_add.data_tetris.next[i][j]);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
END_TEST

START_TEST(test_tetris_game_4) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  int i = 0;
  while (i < 1000) {
    RandomTetromin(&data_tetris_add);
    i++;
    ck_assert_float_ne(0, data_tetris_add.figure.future);
  }
  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
END_TEST

START_TEST(test_tetris_game_5) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++) data_tetris_add.UsedField[i][j] = 1;
  ck_assert_int_eq(1, ControlGameOver(&data_tetris_add));

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
END_TEST

START_TEST(test_tetris_game_6) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  RandomTetromin(&data_tetris_add);
  FutureFig(&data_tetris_add);
  ck_assert_int_eq(0, data_tetris_add.figure.x);
  ck_assert_int_eq(4, data_tetris_add.figure.y);
  ck_assert_int_ne(0, data_tetris_add.figure.now);
  ck_assert_int_eq(0, data_tetris_add.figure.future);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}

START_TEST(test_tetris_game_7) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) data_tetris_add.data_tetris.next[i][j] = 1;
  FutureFig(&data_tetris_add);
  CopyBrickToMoveField(&data_tetris_add);
  for (int i = 0; i < 4; i++)
    for (int j = 4; j < 8; j++)
      ck_assert_int_eq(1, data_tetris_add.MotionField[i][j]);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}

START_TEST(test_tetris_game_8) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  for (int i = -1; i < 100; i++) {
    RandomTetromin(&data_tetris_add);
    FutureFig(&data_tetris_add);
    data_tetris_add.figure.y = i % 9;
    MainActFunc(&data_tetris_add);
  }
  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_9) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  RandomTetromin(&data_tetris_add);
  FutureFig(&data_tetris_add);
  PushRight(&data_tetris_add);
  ck_assert_int_eq(5, data_tetris_add.figure.y);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_10) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  RandomTetromin(&data_tetris_add);
  FutureFig(&data_tetris_add);
  PushLeft(&data_tetris_add);
  ck_assert_int_eq(3, data_tetris_add.figure.y);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_11) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.data_tetris.level = 1;
  bool res = 0;
  res = ControlFalling(&data_tetris_add);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, data_tetris_add.TimeStart);
  ck_assert_int_ne(0, data_tetris_add.Time);
}

START_TEST(test_tetris_game_12) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.data_tetris.level = 1;
  bool res = 0;
  while (!res) {
    res = ControlFalling(&data_tetris_add);
  }
  ck_assert_int_eq(1, res);
  ck_assert_int_eq(0, data_tetris_add.TimeStart);
  ck_assert_int_eq(0, data_tetris_add.Time);
}

START_TEST(test_tetris_game_13) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.data_tetris.level = 1;
  bool res = 0;
  res = ControlBottomOfTetromino(&data_tetris_add);
  ck_assert_int_eq(0, res);
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++) data_tetris_add.UsedField[i][j] = 1;
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++) data_tetris_add.MotionField[i][j] = 1;
  res = ControlBottomOfTetromino(&data_tetris_add);
  ck_assert_int_eq(1, res);
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++) data_tetris_add.UsedField[i][j] = 0;
  res = ControlBottomOfTetromino(&data_tetris_add);
  ck_assert_int_eq(1, res);
}
START_TEST(test_tetris_game_14) {
  FullGameStat data_tetris_add = {0};
  Initialization(&data_tetris_add);
  RandomTetromin(&data_tetris_add);
  FutureFig(&data_tetris_add);
  Motion(&data_tetris_add);
  ck_assert_int_eq(1, data_tetris_add.figure.x);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_15) {
  FullGameStat data_tetris_add = {0};
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 10; j++) data_tetris_add.MotionField[i][j] = 1;
  MotionBeforeTouch(&data_tetris_add);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 10; j++)
      ck_assert_int_eq(0, data_tetris_add.MotionField[i][j]);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 10; j++)
      ck_assert_int_eq(1, data_tetris_add.UsedField[i][j]);
}
START_TEST(test_tetris_game_16) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.data_tetris.level = 1;
  for (int i = 19; i < 20; i++)
    for (int j = 0; j < 10; j++) data_tetris_add.UsedField[i][j] = 1;
  CalculateScore(&data_tetris_add);
  ck_assert_int_eq(100, data_tetris_add.data_tetris.score);
}
START_TEST(test_tetris_game_17) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Start;
  MainState(&data_tetris_add);
  ck_assert_ptr_nonnull(data_tetris_add.data_tetris.field);
  ck_assert_ptr_nonnull(data_tetris_add.data_tetris.next);
  ck_assert_int_eq(SPAWN, data_tetris_add.state);
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Terminate;
  MainState(&data_tetris_add);
  ck_assert_int_eq(EXIT_STATE, data_tetris_add.state);
  MainState(&data_tetris_add);
  ck_assert_int_eq(3, data_tetris_add.data_tetris.pause);
  ck_assert_ptr_null(data_tetris_add.data_tetris.field);
  ck_assert_ptr_null(data_tetris_add.data_tetris.next);
}

START_TEST(test_tetris_game_18) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Start;
  MainState(&data_tetris_add);
  MainState(&data_tetris_add);
  ck_assert_int_eq(MOVING, data_tetris_add.state);
  ck_assert_int_eq(4, data_tetris_add.figure.y);
  ck_assert_int_eq(0, data_tetris_add.figure.x);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}

START_TEST(test_tetris_game_19) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Start;
  MainState(&data_tetris_add);
  MainState(&data_tetris_add);
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Action;
  MainState(&data_tetris_add);
  ck_assert_int_eq(MOVING, data_tetris_add.state);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_20) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Start;
  MainState(&data_tetris_add);
  MainState(&data_tetris_add);
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Down;
  MainState(&data_tetris_add);
  ck_assert_int_eq(SHIFTING, data_tetris_add.state);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_21) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Start;
  MainState(&data_tetris_add);
  MainState(&data_tetris_add);
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Right;
  MainState(&data_tetris_add);
  ck_assert_int_eq(MOVING, data_tetris_add.state);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_22) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Start;
  MainState(&data_tetris_add);
  MainState(&data_tetris_add);
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Left;
  MainState(&data_tetris_add);
  ck_assert_int_eq(MOVING, data_tetris_add.state);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_23) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Start;
  MainState(&data_tetris_add);
  MainState(&data_tetris_add);
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Terminate;
  MainState(&data_tetris_add);
  ck_assert_int_eq(EXIT_STATE, data_tetris_add.state);

  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_24) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = START;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Start;
  MainState(&data_tetris_add);
  MainState(&data_tetris_add);
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Pause;
  MainState(&data_tetris_add);
  ck_assert_int_eq(PAUSE, data_tetris_add.state);
  ck_assert_int_eq(1, data_tetris_add.data_tetris.pause);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add.data_tetris.next), 4);
}
START_TEST(test_tetris_game_25) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = PAUSE;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Pause;
  MainState(&data_tetris_add);
  ck_assert_int_eq(MOVING, data_tetris_add.state);
  ck_assert_int_eq(0, data_tetris_add.data_tetris.pause);
  data_tetris_add.data_tetris.pause = 1;
  data_tetris_add.state = PAUSE;
  data_tetris_add.NewInput = true;
  data_tetris_add.input = Terminate;
  MainState(&data_tetris_add);
  ck_assert_int_eq(EXIT_STATE, data_tetris_add.state);
  ck_assert_int_eq(1, data_tetris_add.data_tetris.pause);
}
START_TEST(test_tetris_game_26) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = SHIFTING;
  MainState(&data_tetris_add);
  ck_assert_int_eq(MOVING, data_tetris_add.state);
  data_tetris_add.state = SHIFTING;
  for (int i = 19; i < 20; i++)
    for (int j = 0; j < 10; j++) data_tetris_add.MotionField[i][j] = 1;
  MainState(&data_tetris_add);
  ck_assert_int_eq(ATTACHING, data_tetris_add.state);
}
START_TEST(test_tetris_game_27) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = ATTACHING;
  MainState(&data_tetris_add);
  ck_assert_int_eq(SPAWN, data_tetris_add.state);
}
START_TEST(test_tetris_game_28) {
  FullGameStat data_tetris_add = {0};
  data_tetris_add.state = GAMEOVER;
  MainState(&data_tetris_add);
  ck_assert_int_eq(START, data_tetris_add.state);
  ck_assert_int_eq(2, data_tetris_add.data_tetris.pause);
}

START_TEST(test_tetris_game_29) {
  FullGameStat* data_tetris_add = NULL;
  data_tetris_add = get_current_data_tetris_add();
  ck_assert_ptr_nonnull(data_tetris_add);
}

START_TEST(test_tetris_game_30) {
  FullGameStat* data_tetris_add = NULL;
  data_tetris_add = get_current_data_tetris_add();
  GameInfo_t data_tetris = {0};
  data_tetris = updateCurrentState();
  ck_assert_ptr_null(data_tetris.field);
  ck_assert_ptr_null(data_tetris.next);
  data_tetris_add->NewInput = true;
  data_tetris_add->input = Start;
  data_tetris = updateCurrentState();
  ck_assert_ptr_nonnull(data_tetris.field);
  ck_assert_ptr_nonnull(data_tetris.next);
  RemoveMemoryForField(&(data_tetris_add->data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add->data_tetris.next), 4);
}

START_TEST(test_tetris_game_31) {
  FullGameStat* data_tetris_add = NULL;
  data_tetris_add = get_current_data_tetris_add();
  userInput(Action, false);
  ck_assert_int_eq(Action, data_tetris_add->input);
  ck_assert_int_eq(1, data_tetris_add->NewInput);
}

Suite* game_test(void) {
  Suite* s;
  TCase* tcase;
  s = suite_create("\033[45m-=TETRIS_GAME_TESTS=-\033[0m");
  tcase = tcase_create("case_add");
  tcase_add_test(tcase, test_tetris_game_1);
  tcase_add_test(tcase, test_tetris_game_2);
  tcase_add_test(tcase, test_tetris_game_3);
  tcase_add_test(tcase, test_tetris_game_4);
  tcase_add_test(tcase, test_tetris_game_5);
  tcase_add_test(tcase, test_tetris_game_6);
  tcase_add_test(tcase, test_tetris_game_7);
  tcase_add_test(tcase, test_tetris_game_8);
  tcase_add_test(tcase, test_tetris_game_9);
  tcase_add_test(tcase, test_tetris_game_10);
  tcase_add_test(tcase, test_tetris_game_11);
  tcase_add_test(tcase, test_tetris_game_12);
  tcase_add_test(tcase, test_tetris_game_13);
  tcase_add_test(tcase, test_tetris_game_14);
  tcase_add_test(tcase, test_tetris_game_15);
  tcase_add_test(tcase, test_tetris_game_16);
  tcase_add_test(tcase, test_tetris_game_17);
  tcase_add_test(tcase, test_tetris_game_18);
  tcase_add_test(tcase, test_tetris_game_19);
  tcase_add_test(tcase, test_tetris_game_20);
  tcase_add_test(tcase, test_tetris_game_21);
  tcase_add_test(tcase, test_tetris_game_22);
  tcase_add_test(tcase, test_tetris_game_23);
  tcase_add_test(tcase, test_tetris_game_24);
  tcase_add_test(tcase, test_tetris_game_25);
  tcase_add_test(tcase, test_tetris_game_26);
  tcase_add_test(tcase, test_tetris_game_27);
  tcase_add_test(tcase, test_tetris_game_28);
  tcase_add_test(tcase, test_tetris_game_29);
  tcase_add_test(tcase, test_tetris_game_30);
  tcase_add_test(tcase, test_tetris_game_31);

  suite_add_tcase(s, tcase);
  return s;
}
