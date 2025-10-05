#include "EventKeyboard.h"
#include "GameManager.h"
#include "Hero.h"
#include "Pterodactyl.h"
#include "PterodactylSpawner.h"
#include "Points.h"
#include "WorldManager.h"
#include "EventMouse.h"
#include "Music.h"
#include "GameStart.h"
#include "ResourceManager.h"

int GameStart::eventHandler(const df::Event *p_e)
{

    if (p_e->getType() == df::KEYBOARD_EVENT)
    {
        df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *)p_e;
        switch (p_keyboard_event->getKey())
        {
        case df::Keyboard::P: // play
            start();
            break;
        case df::Keyboard::Q: // quit
            GM.setGameOver();
            break;
        default: // Key is not handled.
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// Override default draw so as not to display "value".
int GameStart::draw()
{
    return df::Object::draw();
}

void GameStart::start()
{
    // Create hero.
    new Hero;

    // Create pterodactyl spawner (spawns at regular intervals).
    new PterodactylSpawner;

    // Setup heads-up display.
    new Points; // Points display.

    // Nules Display
    df::ViewObject *p_vo = new df::ViewObject; // Count of nukes.
    p_vo->setLocation(df::TOP_LEFT);
    p_vo->setViewString("Nukes");
    p_vo->setValue(1);
    p_vo->setColor(df::YELLOW);

    // Lives Display
    df::ViewObject *p_vo2 = new df::ViewObject; // Count of lives.
    p_vo2->setLocation(df::TOP_CENTER);
    p_vo2->setViewString("Lives");
    p_vo2->setValue(3);
    p_vo2->setColor(df::RED);

    // HIgh Score Display
    df::ViewObject *p_vo3 = new df::ViewObject; // High Score
    p_vo3->setLocation(df::BOTTOM_CENTER);
    p_vo3->setViewString("High Score");
    p_vo3->setValue(Points::getHighScore());
    p_vo3->setColor(df::RED);

    // When game starts, become inactive.
    setActive(false);

    // Pause start music.
    p_music->pause();
}

void GameStart::playMusic()
{
    p_music->play();
}

GameStart::GameStart()
{
    setSprite("gamestart");
    setType("GameStart");

    registerInterest(df::KEYBOARD_EVENT);

    // Put in center of window.
    setLocation(df::CENTER_CENTER);

    // Play start music.
    p_music = RM.getMusic("start music");
    playMusic();
}