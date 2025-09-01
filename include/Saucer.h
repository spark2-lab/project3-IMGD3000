#include "Object.h"

class Saucer : public df::Object
{

public:
  Saucer();
  int eventHandler(const df::Event *p_e) override;
  void out();
  void moveToStart();
};