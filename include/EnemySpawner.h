#include "Object.h"

class EnemySpawner : public df::Object
{
private:
  int spawn_countdown;
  int spawn_interval; // Frames between spawns

public:
  EnemySpawner();
  int eventHandler(const df::Event *p_e) override;
  void step();
};
