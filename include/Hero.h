#include "Object.h"
#include "EventKeyboard.h"
#include "Reticle.h"

class Hero : public df::Object
{

private:
  void kbd(const df::EventKeyboard *p_keyboard_event);
  void move(int dy);
  void step();
  void mouse(const df::EventMouse *p_mouse_event);
  void fire(df::Vector target);

  int dy;
  int move_slowdown;
  int move_countdown;
  int fire_slowdown;
  int fire_countdown;

  Reticle *p_reticle;

public:
  Hero();
  int eventHandler(const df::Event *p_e) override;
};