#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "Reticle.h"
#include "Vector.h"

// Draw reticle on window.
int Reticle::draw()
{
    return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}

int Reticle::eventHandler(const df::Event *p_e)
{

    if (p_e->getType() == df::MSE_EVENT)
    {
        const df::EventMouse *p_mouse_event =
            dynamic_cast<const df::EventMouse *>(p_e);
        if (p_mouse_event->getMouseAction() == df::MOVED)
        {
            // Change location to new mouse position.
            setPosition(p_mouse_event->getMousePosition());
            return 1;
        }
    }

    // If get here, have ignored this event.
    return 0;
}

void Reticle::moveToStart()
{
    df::Vector temp_pos;

    float world_horiz = WM.getBoundary().getHorizontal();
    float world_vert = WM.getBoundary().getVertical();

    // x is off right side of window
    temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

    // y is in vertical range
    temp_pos.setY(rand() % (int)(world_vert - 1) + 1.0f);

    WM.moveObject(this, temp_pos);
}

Reticle::Reticle()
{
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE); // Make Reticle in foreground.
    registerInterest(df::MSE_EVENT);

    moveToStart();
}