#include "EventStep.h"
#include "Explosion.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"

void Explosion::step()
{
    time_to_live--;
    if (time_to_live <= 0)
        WM.markForDelete(this);
}

int Explosion::eventHandler(const df::Event *p_e)
{
    if (p_e->getType() == df::STEP_EVENT)
    {
        step();
        return 1;
    }
    return 0;
}

Explosion::Explosion()
{
    // Link to "explosion" sprite.
    if (setSprite("explosion") == 0)
        // Set live time as long as sprite length.
        time_to_live = getAnimation().getSprite()->getFrameCount();
    else
        time_to_live = 0;

    setType("Explosion");
    setSolidness(df::SPECTRAL);
    registerInterest(df::STEP_EVENT);
}