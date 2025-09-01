#include "Saucer.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

Saucer::Saucer() {
    // Setup "saucer" sprite
    setSprite("saucer");

    // Set speed in horizontal direction.
    setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frame 1/4

    // Set starting location in the middle of window.
    int world_horiz = (int) WM.getBoundary().getHorizontal();
    int world_vert = (int) WM.getBoundary().getVertical();
    df::Vector p(world_horiz/2, world_vert/2);
    setPosition(p);

}