#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "Hero.h"
#include "Bullet.h"
#include "EventNuke.h"
#include "EventView.h"
#include "GameOver.h"
#include "DisplayManager.h"
#include "Explosion.h"

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse *p_mouse_event)
{
  // Pressed button?
  if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
      (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
    fire(p_mouse_event->getMousePosition());
}

// Event handler respond to keyboard
int Hero::eventHandler(const df::Event *p_e)
{
  if (p_e->getType() == df::COLLISION_EVENT)
  {
    const df::EventCollision *p_collision_event =
        dynamic_cast<const df::EventCollision *>(p_e);
    hit(p_collision_event);
    return 1;
  }
  if (p_e->getType() == df::KEYBOARD_EVENT)
  {
    const df::EventKeyboard *p_keyboard_event =
        dynamic_cast<const df::EventKeyboard *>(p_e);
    kbd(p_keyboard_event);
    return 1;
  }
  if (p_e->getType() == df::STEP_EVENT)
  {
    step();
    return 1;
  }

  if (p_e->getType() == df::MSE_EVENT)
  {
    const df::EventMouse *p_mouse_event =
        dynamic_cast<const df::EventMouse *>(p_e);
    mouse(p_mouse_event);
    return 1;
  }

  return 0;
}

void Hero::fire(df::Vector target)
{
  if (fire_countdown > 0)
    return;
  fire_countdown = fire_slowdown;
  // Fire Bullet towards target.
  // Compute normalized vector to position, then scale by speed (1).
  df::Vector v = target - getPosition();
  v.normalize();
  v.scale(1);
  Bullet *p = new Bullet(getPosition());
  p->setVelocity(v);

  // Play "fire" sound.
  df::Sound *p_sound = RM.getSound("fire");
  if (p_sound)
    p_sound->play();
}

void Hero::nuke()
{
  // Check if nukes left.
  if (!nuke_count)
    return;
  nuke_count--;
  // Create "nuke" event and send to interested Objects.
  EventNuke nuke;
  WM.onEvent(&nuke);
  // Send "view" event with nukes to interested ViewObjects.
  df::EventView ev("Nukes", -1, true);
  WM.onEvent(&ev);

  // Play "nuke" sound.
  df::Sound *p_sound = RM.getSound("nuke");
  if (p_sound)
    p_sound->play();

  // Shake screen (severity 15 pixels x&y, duration 5 frames).
  DM.shake(15, 15, 5);
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard *p_keyboard_event)
{

  switch (p_keyboard_event->getKey())
  {
  case df::Keyboard::Q: // quit
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
      WM.markForDelete(this);
    break;
  case df::Keyboard::W: // up
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
    {
      if (current_tier > 0)
      {
        current_tier--;
        float tier_height = WM.getBoundary().getVertical() / 3.0f;
        float target_y = tier_height * current_tier + tier_height / 2;
        df::Vector new_pos(getPosition().getX(), target_y);
        WM.moveObject(this, new_pos);
      }
    }
    break;
  case df::Keyboard::S: // down
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
    {
      if (current_tier < 2)
      {
        current_tier++;
        float tier_height = WM.getBoundary().getVertical() / 3.0f;
        float target_y = tier_height * current_tier + tier_height / 2;
        df::Vector new_pos(getPosition().getX(), target_y);
        WM.moveObject(this, new_pos);
      }
    }
    break;
  case df::Keyboard::SPACE:
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
      nuke();
    break;

  default:
    return;
  }
}

// Move up or down (no longer used with tier system).
void Hero::move(int dy)
{
  // Tier movement is now handled in kbd()
}

void Hero::hit(const df::EventCollision *p_c)
{
  // If Pterodactyl, mark Pterodactyl for destruction. lives - 1. Descturct hero if lives eq 0.
  int destroyed = 0;
  if ((p_c->getObject1()->getType()) == "Pterodactyl")
  {
    WM.markForDelete(p_c->getObject1());
    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion->setPosition(p_c->getObject1()->getPosition());
    destroyed = 1;
  }
  if ((p_c->getObject2()->getType()) == "Pterodactyl")
  {
    WM.markForDelete(p_c->getObject2());
    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion->setPosition(p_c->getObject2()->getPosition());
    destroyed = 1;
  }
  if (destroyed)
  {
    lives--;
    df::EventView ev("Lives", -1, true);
    WM.onEvent(&ev);

    // Play "explode" sound.
    df::Sound *p_sound = RM.getSound("explode");
    if (p_sound)
      p_sound->play();

    if (lives == 0)
    {
      WM.markForDelete(this);
    }
  }
}

// Decrease rate restriction counters.
void Hero::step()
{
  // Fire countdown.
  fire_countdown--;
  if (fire_countdown < 0)
    fire_countdown = 0;
}

Hero::Hero()
{
  dy = 0;
  move_slowdown = 2;
  move_countdown = move_slowdown;
  fire_slowdown = 15;
  fire_countdown = fire_slowdown;
  nuke_count = 1;
  lives = 3;
  current_tier = 1; // Start at middle tier

  // Link to "dino" sprite.
  int ret = setSprite("dino");
  if (ret != 0)
  {
    LM.writeLog("set sprite failed!!!!");
  }
  else
  {
    LM.writeLog("set sprite suceed!!!!");
  }

  // Object registered in keyboard event
  registerInterest(df::KEYBOARD_EVENT);
  registerInterest(df::STEP_EVENT);
  registerInterest(df::MSE_EVENT);
  registerInterest(df::COLLISION_EVENT);

  // Hero on left edge of the window, mid way down verti
  setType("Hero");
  df::Vector p(10, WM.getBoundary().getVertical() / 2);
  setPosition(p);

  // Create reticle for firing bullets.
  p_reticle = new Reticle();
  p_reticle->draw();
}

Hero::~Hero()
{
  // Create GameOver object.
  new GameOver;
  // Mark Reticle for deletion.
  WM.markForDelete(p_reticle);
  // Make a big explosion with particles.
  df::addParticles(df::SPARKS, getPosition(), 4, df::RED);
}