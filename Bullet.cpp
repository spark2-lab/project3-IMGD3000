#include "Bullet.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Vector.h"
#include "EventOut.h"

// If Bullet hits Pterodactyl, mark Pterodactyl and Bullet for deletion.
void Bullet::hit(const df::EventCollision *p_collision_event)
{
    LM.writeLog("Collision Event");
    if ((p_collision_event->getObject1()->getType() == "Pterodactyl") ||
        (p_collision_event->getObject2()->getType() == "Pterodactyl"))
    {
        WM.markForDelete(p_collision_event->getObject1());
        WM.markForDelete(p_collision_event->getObject2());
        LM.writeLog("Maked for deletion");
    }
}

// If Bullet moves outside world, mark self for deletion.
void Bullet::out()
{
    WM.markForDelete(this);
}

int Bullet::eventHandler(const df::Event *p_e)
{
    if (p_e->getType() == df::COLLISION_EVENT)
    {
        const df::EventCollision *p_collision_event =
            dynamic_cast<const df::EventCollision *>(p_e);
        hit(p_collision_event);
        return 1;
    }
    if (p_e->getType() == df::OUT_EVENT)
    {
        out();
        return 1;
    }

    return 0;
}

Bullet::Bullet(df::Vector hero_pos)
{
    setSprite("bullet");
    setType("Bullet");

    registerInterest(df::COLLISION_EVENT);
    registerInterest(df::OUT_EVENT);

    // Set starting location, based on hero's position passed in.
    df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
    setPosition(p);

    // Bullets move 1 space each game loop.
    // The direction is set when the Hero fires.
    setSpeed(1);

    // Make the Bullets soft so can pass through Hero.
    setSolidness(df::SOFT);
}