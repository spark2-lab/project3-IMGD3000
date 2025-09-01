// Engine includes
#include "ResourceManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Hero.h"
#include "Saucer.h"

void loadResources(void)
{
  // Load saucer sprite.
  RM.loadSprite("sprites/saucer-spr.txt", "saucer");
  RM.loadSprite("sprites/ship-spr.txt", "ship");
  RM.loadSprite("sprites/bullet-spr.txt", "bullet");
  RM.loadSprite("sprites/explosion-spr.txt", "explosion");
}

void populateWorld(void)
{
  new Saucer();
  new Hero();
}

int main(int argc, char *argv[])
{

  // Start up Game Manager.
  if (GM.startUp())
  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 1;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Show splash screen.
  df::splash();

  // Load game resources
  loadResources();

  // Populate game world with some objects
  populateWorld();

  GM.run();

  // Shut everything down.
  GM.shutDown();

  return 0;
}
