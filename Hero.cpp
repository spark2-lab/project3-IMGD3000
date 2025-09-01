#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "Hero.h"

// Event handler respond to keyboard
int Hero::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
      const df::EventKeyboard *p_keyboard_event = 
                dynamic_cast <const df::EventKeyboard *> (p_e);
      kbd(p_keyboard_event);
    }
    if (p_e->getType() == df::STEP_EVENT) {
      step();
    }
    return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {
  
  switch(p_keyboard_event->getKey()) {
    case df::Keyboard::Q:    // quit
      if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
        GM.setGameOver();
      break;
    case df::Keyboard::W:    // up
      LM.writeLog("up");
      if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
        dy -= 1;
      if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
        dy += 1;
      break;
    case df::Keyboard::S:    // down
      LM.writeLog("down");
      if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
        dy += 1;
      if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
        dy -= 1;
      break;
    default:
      return;
  }
}

// Move up or down.
void Hero::move(int dy) {
  if (move_countdown > 0)
    return;
  move_countdown = move_slowdown;
  // If stays on window, allow move.
  df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
  if ((new_pos.getY() > 3) && (new_pos.getY() < WM.getBoundary().getVertical()-1)){
    WM.moveObject(this, new_pos);
  }
}

// Decrease rate restriction counters.
void Hero::step() {
  // If delta-y is non-zero, move.
  if (dy)
    move(dy);
  // Move countdown.
  move_countdown--;
  if (move_countdown < 0)
    move_countdown = 0;
}

Hero::Hero() {
    dy = 0;
    move_slowdown = 2;
    move_countdown = move_slowdown;
    // Link to "ship" sprite.
    setSprite("ship");

    // Object registered in keyboard event
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    // Hero on left edge of the window, mid way down verti
    setType("Hero");
    df::Vector p(7, WM.getBoundary().getVertical()/2);
    setPosition(p);
}