#include "EnemySpawner.h"
#include "Pterodactyl.h"
#include "SmallDino.h"
#include "EventStep.h"
#include <stdlib.h>

EnemySpawner::EnemySpawner()
{
  setType("EnemySpawner");
  spawn_interval = 150; // 150 frames = 5 seconds at 30 FPS
  spawn_countdown = spawn_interval;
  registerInterest(df::STEP_EVENT);
}

int EnemySpawner::eventHandler(const df::Event *p_e)
{
  if (p_e->getType() == df::STEP_EVENT)
  {
    step();
    return 1;
  }
  return 0;
}

void EnemySpawner::step()
{
  spawn_countdown--;
  if (spawn_countdown <= 0)
  {
    // Randomly spawn either Pterodactyl or SmallDino (50/50 chance)
    if (rand() % 2 == 0)
    {
      new Pterodactyl();
    }
    else
    {
      new SmallDino();
    }
    spawn_countdown = spawn_interval;
  }
}
