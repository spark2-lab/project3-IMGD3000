#include "SmallDinoSpawner.h"
#include "SmallDino.h"
#include "EventStep.h"

SmallDinoSpawner::SmallDinoSpawner()
{
  setType("SmallDinoSpawner");
  spawn_interval = 150; // 150 frames = 5 seconds at 30 FPS
  spawn_countdown = spawn_interval;
  registerInterest(df::STEP_EVENT);
}

int SmallDinoSpawner::eventHandler(const df::Event *p_e)
{
  if (p_e->getType() == df::STEP_EVENT)
  {
    step();
    return 1;
  }
  return 0;
}

void SmallDinoSpawner::step()
{
  spawn_countdown--;
  if (spawn_countdown <= 0)
  {
    new SmallDino();
    spawn_countdown = spawn_interval;
  }
}
