#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "Hero.h"
#include "Bullet.h"
#include "EventMouse.h"
#include "EventNuke.h"

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
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard *p_keyboard_event)
{

  switch (p_keyboard_event->getKey())
  {
  case df::Keyboard::Q: // quit
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
      GM.setGameOver();
    break;
  case df::Keyboard::W: // up
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
      dy -= 1;
    if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
      dy += 1;
    break;
  case df::Keyboard::S: // down
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
      dy += 1;
    if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
      dy -= 1;
    break;
  case df::Keyboard::SPACE:
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
      nuke();
    break;

  default:
    return;
  }
}

// Move up or down.
void Hero::move(int dy)
{
  if (move_countdown > 0)
    return;
  move_countdown = move_slowdown;
  // If stays on window, allow move.
  df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
  if ((new_pos.getY() > 3) && (new_pos.getY() < WM.getBoundary().getVertical() - 1))
  {
    WM.moveObject(this, new_pos);
  }
}

// Decrease rate restriction counters.
void Hero::step()
{
  // If delta-y is non-zero, move.
  if (dy)
    move(dy);

  // Move countdown.
  move_countdown--;
  if (move_countdown < 0)
    move_countdown = 0;

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

  // Link to "ship" sprite.
  setSprite("ship");

  // Object registered in keyboard event
  registerInterest(df::KEYBOARD_EVENT);
  registerInterest(df::STEP_EVENT);
  registerInterest(df::MSE_EVENT);

  // Hero on left edge of the window, mid way down verti
  setType("Hero");
  df::Vector p(7, WM.getBoundary().getVertical() / 2);
  setPosition(p);

  // Create reticle for firing bullets.
  p_reticle = new Reticle();
  p_reticle->draw();
}

Hero::~Hero()
{
  GM.setGameOver();
}