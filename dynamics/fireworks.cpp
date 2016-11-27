/*
|--------------------------------------------------------------------------
| Update Particle Dynamics
|--------------------------------------------------------------------------
|
| We then model the particles based on which model they're currently
| simulating. I've decided to implement three very different examples:
|
| 1. Fireworks
| 2. Strange attactors
| 3. A black hole
*/

#define NUMBER_EMITTERS 20

void fireworkDynamics() {
  glBegin(GL_POINTS);

  for(unsigned int i = 1; i < NUMBER_EMITTERS; i++) {
      GLint x = 30 + (20 * cos(i));
      GLint y = 20 + (20 * sin(i));

      glColor4f(255, 255, 255, 255);
      glVertex3f(x, 0, y);
  }

  // for(unsigned int i = 0; i < particleSet.size(); i++) {
  //   particleSet[i].initialX += (myRandom() - 0.5) * 5;
  //   particleSet[i].initialY += (myRandom() - 0.5) * 5;
  //   particleSet[i].initialZ += (myRandom() - 0.5) * 5;
  //
  //   glColor4f(particleSet[i].r, particleSet[i].g, particleSet[i].b,
  //     particleSet[i].opacity);
  //   glVertex3f(particleSet[i].initialX,
  //              particleSet[i].initialY,
  //              particleSet[i].initialZ);
  //
  //
  // }
  glEnd();

}
