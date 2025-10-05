#include "Object.h"

class PterodactylSpawner : public df::Object
{
private:
  int spawn_countdown;
  int spawn_interval; // Frames between spawns

public:
  PterodactylSpawner();
  int eventHandler(const df::Event *p_e) override;
  void step();
};
