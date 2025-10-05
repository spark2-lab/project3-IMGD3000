#include "SmallDino.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Event.h"
#include "EventOut.h"
#include "EventStep.h"
#include "Explosion.h"
#include "EventNuke.h"
#include "EventView.h"
#include "Points.h"
#include <stdlib.h>

void SmallDino::hit(const df::EventCollision *p_c)
{
  // If SmallDino hit SmallDino, ignore.
  if ((p_c->getObject1()->getType() == "SmallDino") &&
      (p_c->getObject2()->getType() == "SmallDino"))
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
  }
}

// Get invoked with every even game world passes to Object
int SmallDino::eventHandler(const df::Event *p_e)
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
  }
  if (p_e->getType() == df::STEP_EVENT)
  {
    step();
    return 1;
  }

  return 0;
}

void SmallDino::step()
{
  // Gradually increase speed (accelerate to the left)
  df::Vector current_vel = getVelocity();
  current_vel.setX(current_vel.getX() - acceleration);
  setVelocity(current_vel);
}

void SmallDino::out()
{
  if (getPosition().getX() >= 0)
  {
    return;
  }
  WM.markForDelete(this);
}

void SmallDino::moveToStart()
{
  df::Vector temp_pos;

  float world_horiz = WM.getBoundary().getHorizontal();
  float world_vert = WM.getBoundary().getVertical();

  // x is off right side of window
  temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

  // y is in bottom tier only.
  int tier = 2; // 2 = bottom tier
  float tier_height = world_vert / 3.0f;
  float tier_y = tier_height * tier + tier_height / 2;
  temp_pos.setY(tier_y);

  // If collision, move right slightly until empty space.
  df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
  while (collision_list.getCount() != 0)
  {
    temp_pos.setX(temp_pos.getX() + 1);
    collision_list = WM.getCollisions(this, temp_pos);
  }

  WM.moveObject(this, temp_pos);
}

SmallDino::SmallDino()
{
  // Setup "smalldino" sprite
  setSprite("smalldino");
  setType("SmallDino");

  // Set speed in horizontal direction.
  setVelocity(df::Vector(-0.5, 0)); // 1 space left every 2 frames
  acceleration = 0.05; // Much faster acceleration
  registerInterest(df::COLLISION_EVENT);
  registerInterest(NUKE_EVENT);
  registerInterest(df::STEP_EVENT);

  // Set starting location in the right of window.
  moveToStart();
}

SmallDino::~SmallDino()
{
  // Send "view" event with points to interested ViewObjects.
  // Add 10 points.
  df::EventView ev(POINTS_STRING, 10, true);
  WM.onEvent(&ev);
}
