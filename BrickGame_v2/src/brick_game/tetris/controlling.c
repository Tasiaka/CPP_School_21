#include "tetris.h"

static void STARTing(FullGameStat *data_tetris_add);
static void SPAWNing(FullGameStat *data_tetris_add);
static void MOVing(FullGameStat *data_tetris_add);
static void PAUSing(FullGameStat *data_tetris_add);
static void SHIFTing(FullGameStat *data_tetris_add);
static void ATTACHing(FullGameStat *data_tetris_add);
static void FINISHing(FullGameStat *data_tetris_add);  // game over
static void EXITing(FullGameStat *data_tetris_add);

FullGameStat *get_current_data_tetris_add() {
  static FullGameStat data_tetris_add = {0};
  return &data_tetris_add;
}

void MainState(FullGameStat *data_tetris_add) {
  switch (data_tetris_add->state) {
    case START:
      STARTing(data_tetris_add);
      break;
    case SPAWN:
      SPAWNing(data_tetris_add);
      break;
    case MOVING:
      MOVing(data_tetris_add);
      break;
    case PAUSE:
      PAUSing(data_tetris_add);
      break;
    case SHIFTING:
      SHIFTing(data_tetris_add);
      break;
    case ATTACHING:
      ATTACHing(data_tetris_add);
      break;
    case GAMEOVER:
      FINISHing(data_tetris_add);
      break;
    case EXIT_STATE:
      EXITing(data_tetris_add);
      break;
    default:
      break;
  }
  GetReadyField(data_tetris_add);
}

void RESTARTing(FullGameStat *data_tetris_add) {
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      data_tetris_add->MotionField[i][j] = 0;  // перезагрузка статичного поля
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      data_tetris_add->UsedField[i][j] = 0;  // перезагрузка статичного поля
  data_tetris_add->data_tetris.score = 0;
  data_tetris_add->data_tetris.pause = 0;
  data_tetris_add->data_tetris.level = 1;
}

static void STARTing(FullGameStat *data_tetris_add) {
  if (data_tetris_add->NewInput) {
    switch (data_tetris_add->input) {
      case Start:
        if (data_tetris_add->data_tetris.pause ==
            2) {  // после game_over pause = 2
          RESTARTing(data_tetris_add);
        }
        Initialization(data_tetris_add);
        RandomTetromin(data_tetris_add);
        data_tetris_add->state = SPAWN;
        break;
      case Terminate:
        data_tetris_add->state = EXIT_STATE;
        break;
      default:
        break;
    }
  }
  data_tetris_add->NewInput = false;
}

static void SPAWNing(FullGameStat *data_tetris_add) {
  FutureFig(data_tetris_add);
  RandomTetromin(data_tetris_add);
  CopyBrickToMoveField(data_tetris_add);
  data_tetris_add->state = MOVING;
}

static void MOVing(FullGameStat *data_tetris_add) {
  if (data_tetris_add->NewInput) switch (data_tetris_add->input) {
      case Action:
        MainActFunc(data_tetris_add);
      case Up:
        break;
      case Down:
        data_tetris_add->state = SHIFTING;
        break;
      case Right:
        PushRight(data_tetris_add);
        break;
      case Left:
        PushLeft(data_tetris_add);
        break;
      case Terminate:
        data_tetris_add->state = EXIT_STATE;
        break;
      case Pause:
        data_tetris_add->state = PAUSE;
        data_tetris_add->data_tetris.pause = 1;
        break;
      default:
        break;
    }
  if (ControlFalling(data_tetris_add)) {
    data_tetris_add->state = SHIFTING;
  }
  data_tetris_add->NewInput = false;
}

static void PAUSing(FullGameStat *data_tetris_add) {
  if (data_tetris_add->NewInput) {
    switch (data_tetris_add->input) {
      case Pause:
        data_tetris_add->data_tetris.pause = 0;
        data_tetris_add->state = MOVING;
        break;
      case Terminate:
        data_tetris_add->state = EXIT_STATE;
        break;
      default:
        break;
    }
  }
  data_tetris_add->NewInput = false;
}

static void SHIFTing(FullGameStat *data_tetris_add) {
  if (ControlBottomOfTetromino(data_tetris_add)) {
    data_tetris_add->state = ATTACHING;
  } else {
    Motion(data_tetris_add);
    data_tetris_add->state = MOVING;
  }
}

static void ATTACHing(FullGameStat *data_tetris_add) {
  MotionBeforeTouch(data_tetris_add);
  CalculateScore(data_tetris_add);
  if (ControlGameOver(data_tetris_add))
    data_tetris_add->state = GAMEOVER;
  else {
    data_tetris_add->state = SPAWN;
  }
}

static void FINISHing(FullGameStat *data_tetris_add) {
  data_tetris_add->state = START;
  data_tetris_add->data_tetris.pause = 2;  // game_over
}

static void EXITing(FullGameStat *data_tetris_add) {
  RemoveMemoryForField(&(data_tetris_add->data_tetris.field), 20);
  RemoveMemoryForField(&(data_tetris_add->data_tetris.next), 4);
  data_tetris_add->data_tetris.pause = 3;  // terminate app
}
