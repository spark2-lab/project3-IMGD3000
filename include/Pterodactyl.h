#include "Object.h"
#include "EventCollision.h"

class Pterodactyl : public df::Object
{
private:
  void hit(const df::EventCollision *p_c);
  void out();
  void moveToStart();
  void step();
  float acceleration;

public:
  Pterodactyl();
  ~Pterodactyl();
  int eventHandler(const df::Event *p_e) override;
};