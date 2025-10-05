#include "PterodactylSpawner.h"
#include "Pterodactyl.h"
#include "EventStep.h"

PterodactylSpawner::PterodactylSpawner()
{
  setType("PterodactylSpawner");
  spawn_interval = 150; // 150 frames = 5 seconds at 30 FPS
  spawn_countdown = spawn_interval;
  registerInterest(df::STEP_EVENT);
}

int PterodactylSpawner::eventHandler(const df::Event *p_e)
{
  if (p_e->getType() == df::STEP_EVENT)
  {
    step();
    return 1;
  }
  return 0;
}

void PterodactylSpawner::step()
{
  spawn_countdown--;
  if (spawn_countdown <= 0)
  {
    new Pterodactyl();
    spawn_countdown = spawn_interval;
  }
}
