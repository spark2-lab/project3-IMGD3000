Platform : Mac OS
Game mod : 
  1. game screen shakes when nuke() called
  2. Hero lives setted to 3. It is displyed in the top center. When hero collides with Saucer, explosion
  and sound effect comes out and lives decreases 1. If lives become 0, hero explode and game over.
  3. High score of the player is recorded in high_score.txt. If the player achieved higher score then the
  score written in the high_score, it will be exchanged to the new highest_score and then retrieved in the
  next round, displayed in the bottom center of the screen.
How to compile : type "make". "./game" to execute.
File directory structure: 
  Points.cpp, include/Points.h, Reticle.cpp, include/Reticle.cpp, Saucer.cpp, include/Saucer.h,
  Star.cpp, include/Star.h, Bullet.cpp, include/Bullet.h, EventNuke.cpp, include/EventNuke.h,
  Explosion.cpp, include/Explosion.h, GameOver.cpp, include/GameOver.h, GameStart.cpp, include/GameStart.h,
  Hero.cpp, include/Hero.h,
  are added from the starter file.
  
