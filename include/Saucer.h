#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object
{
private:
  void hit(const df::EventCollision *p_c);
  void out();
  void moveToStart();

public:
  Saucer();
  int eventHandler(const df::Event *p_e) override;
};