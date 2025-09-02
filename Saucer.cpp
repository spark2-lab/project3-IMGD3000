#include "Saucer.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Event.h"
#include "EventOut.h"
#include "Explosion.h"
#include "EventNuke.h"
#include "EventView.h"
#include "Points.h"
#include <stdlib.h>

void Saucer::hit(const df::EventCollision *p_c)
{
  // If Saucer hit Saucer, ignore.
  if ((p_c->getObject1()->getType() == "Saucer") &&
      (p_c->getObject2()->getType() == "Saucer"))
    return;

  // If Bullet...
  if ((p_c->getObject1()->getType() == "Bullet") ||
      (p_c->getObject2()->getType() == "Bullet"))
  {

    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion->setPosition(this->getPosition());

    // Play "explode" sound.
    df::Sound *p_sound = RM.getSound("explode");
    if (p_sound)
      p_sound->play();

    // Saucers appear stay around perpetually.
    new Saucer;
  }

  // If Hero, mark both objects for destruction.
  if (((p_c->getObject1()->getType()) == "Hero") ||
      ((p_c->getObject2()->getType()) == "Hero"))
  {
    WM.markForDelete(p_c->getObject1());
    WM.markForDelete(p_c->getObject2());
  }
}

// Get invoked with every even game world passes to Object
int Saucer::eventHandler(const df::Event *p_e)
{
  LM.writeLog("position: %f,%f", getPosition().getX(), getPosition().getY());
  if (p_e->getType() == df::OUT_EVENT)
  {
    out();
    return 1;
  }
  if (p_e->getType() == df::COLLISION_EVENT)
  {
    const df::EventCollision *p_collision_event =
        dynamic_cast<const df::EventCollision *>(p_e);
    hit(p_collision_event);
    return 1;
  }
  if (p_e->getType() == NUKE_EVENT)
  {
    WM.markForDelete(this);

    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion->setPosition(this->getPosition());

    // Saucers appear stay around perpetually.
    new Saucer;
  }

  return 0;
}

void Saucer::out()
{
  if (getPosition().getX() >= 0)
  {
    return;
  }
  moveToStart();
  // Spawn new Saucer to make the game get harder.
  new Saucer;
}

void Saucer::moveToStart()
{
  df::Vector temp_pos;

  float world_horiz = WM.getBoundary().getHorizontal();
  float world_vert = WM.getBoundary().getVertical();

  // x is off right side of window
  temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

  // y is in vertical range
  temp_pos.setY(rand() % (int)(world_vert - 1) + 1.0f);

  // If collision, move right slightly until empty space.
  df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
  while (collision_list.getCount() != 0)
  {
    temp_pos.setX(temp_pos.getX() + 1);
    collision_list = WM.getCollisions(this, temp_pos);
  }

  WM.moveObject(this, temp_pos);
}

Saucer::Saucer()
{
  // Setup "saucer" sprite
  setSprite("saucer");
  setType("Saucer");

  // Set speed in horizontal direction.
  setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frame 1/4
  registerInterest(df::COLLISION_EVENT);
  registerInterest(NUKE_EVENT);

  // Set starting location in the right of window.
  moveToStart();
}

Saucer::~Saucer()
{
  // Send "view" event with points to interested ViewObjects.
  // Add 10 points.
  df::EventView ev(POINTS_STRING, 10, true);
  WM.onEvent(&ev);
}