#include "Object.h"

class SmallDinoSpawner : public df::Object
{
private:
  int spawn_countdown;
  int spawn_interval; // Frames between spawns

public:
  SmallDinoSpawner();
  int eventHandler(const df::Event *p_e) override;
  void step();
};
