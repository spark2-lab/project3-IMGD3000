// Engine includes
#include "ResourceManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Hero.h"
#include "Saucer.h"
#include "Points.h"
#include "Color.h"
#include "Star.h"
#include "GameStart.h"

void loadResources(void)
{
  // Load saucer sprite.
  RM.loadSprite("sprites/saucer-spr.txt", "saucer");
  RM.loadSprite("sprites/dino-spr.txt", "ship");
  RM.loadSprite("sprites/bullet-spr.txt", "bullet");
  RM.loadSprite("sprites/explosion-spr.txt", "explosion");
  RM.loadSprite("sprites/gameover-spr.txt", "gameover");
  RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
  RM.loadMusic("sounds/start-music.wav", "start music");
}

void populateWorld(void)
{

  // Create some Stars.
  for (int i = 0; i < 16; i++)
    new Star;

  // Spawn GameStart object.
  new GameStart();

  RM.loadSound("sounds/fire.wav", "fire");
  RM.loadSound("sounds/explode.wav", "explode");
  RM.loadSound("sounds/nuke.wav", "nuke");
  RM.loadSound("sounds/game-over.wav", "game over");
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
