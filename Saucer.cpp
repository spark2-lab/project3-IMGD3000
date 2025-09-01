#include "Saucer.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Event.h"
#include "EventOut.h"
#include <stdlib.h>

// Get invoked with every even game world passes to Object
int Saucer::eventHandler(const df::Event *p_e) {
    LM.writeLog("position: %f,%f", getPosition().getX(), getPosition().getY());
    if (p_e->getType() == df::OUT_EVENT) {
      out();
      return 1;
    }

    return 0;
  }

  void Saucer::out() {
    if (getPosition().getX() >= 0){
        return;
    }
    moveToStart();
  }

  void Saucer::moveToStart() {
    df::Vector temp_pos;

    float world_horiz = WM.getBoundary().getHorizontal();
    float world_vert = WM.getBoundary().getVertical();

    // x is off right side of window
    temp_pos.setX(world_horiz + rand() % (int) world_horiz + 3.0f);

    // y is in vertical range
    temp_pos.setY(rand() % (int) (world_vert-1) + 1.0f);

    WM.moveObject(this, temp_pos);
  }



Saucer::Saucer() {
    // Setup "saucer" sprite
    setSprite("saucer");
    setType("Saucer");

    // Set speed in horizontal direction.
    setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frame 1/4

    // Set starting location in the right of window.
    moveToStart();
}