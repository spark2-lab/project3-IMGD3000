#include "Object.h"
#include "Event.h"

#define STAR_CHAR '.'

class Star : public df::Object
{

private:
    void out();

public:
    Star();
    int draw(void) override;
    int eventHandler(const df::Event *p_e) override;
};