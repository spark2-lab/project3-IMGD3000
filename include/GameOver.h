#include "ViewObject.h"
#include "Event.h"

class GameOver : public df::ViewObject
{
private:
    int time_to_live;

public:
    GameOver();
    ~GameOver();

    void step();
    int eventHandler(const df::Event *p_e) override;
    int draw() override;
};