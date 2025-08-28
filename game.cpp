  // Engine includes
  #include "ResourceManager.h"
  #include "GameManager.h"
  #include "LogManager.h"

  void loadResources(void) {
    // Load saucer sprite.
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
  }

  int main(int argc, char *argv[]) {

    // Start up Game Manager.
    if (GM.startUp())  {
      LM.writeLog("Error starting game manager!");
      GM.shutDown();
      return 1;
    }

    // Set flush of logfile during development (when done, make false).
    LM.setFlush(true);

    // Show splash screen.
    df::splash();

    // Shut everything down.
    GM.shutDown();

    return 0;
  }

  