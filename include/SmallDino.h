#include "Object.h"
#include "EventCollision.h"

class SmallDino : public df::Object
{
private:
  void hit(const df::EventCollision *p_c);
  void out();
  void moveToStart();
  void step();
  float acceleration;

public:
  SmallDino();
  ~SmallDino();
  int eventHandler(const df::Event *p_e) override;
};
