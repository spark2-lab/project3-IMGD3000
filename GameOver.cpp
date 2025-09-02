#include "GameOver.h"
#include "Animation.h"
#include "Object.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"

// Count down to end of "message".
void GameOver::step()
{
    time_to_live--;
    if (time_to_live <= 0)
        WM.markForDelete(this);
}

int GameOver::eventHandler(const df::Event *p_e)
{
    LM.writeLog("position: %f,%f", getPosition().getX(), getPosition().getY());
    if (p_e->getType() == df::STEP_EVENT)
    {
        step();
        return 1;
    }
    return 0;
}

// Override default draw so as not to display "value".
int GameOver::draw()
{
    return df::Object::draw();
}

GameOver::GameOver()
{
    // Link to "message" sprite.
    if (setSprite("gameover") == 0)
        time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
    else
        time_to_live = 0;

    // Put in center of window.
    setLocation(df::CENTER_CENTER);

    // Register for step event.
    registerInterest(df::STEP_EVENT);
}

GameOver::~GameOver()
{

    // Remove Saucers and ViewObjects, re-activate GameStart.
    df::ObjectList object_list = WM.getAllObjects(true);
    for (int i = 0; i < object_list.getCount(); i++)
    {
        df::Object *p_o = object_list[i];
        if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject")
            WM.markForDelete(p_o);
        if (p_o->getType() == "GameStart")
            p_o->setActive(true);
    }
}