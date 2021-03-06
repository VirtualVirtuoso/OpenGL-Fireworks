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
void beeDynamics() {
  glBegin(GL_POINTS);

  for(unsigned int i = 0; i < particleSet.size(); i++) {
    particleSet[i].initialX += ( - 0.5) * 5;
    particleSet[i].initialY += (myRandom() - 0.5) * 5;
    particleSet[i].initialZ += (myRandom() - 0.5) * 5;

    glColor4f(particleSet[i].r, particleSet[i].g, particleSet[i].b,
      particleSet[i].opacity);
    glVertex3f(particleSet[i].initialX,
               particleSet[i].initialY,
               particleSet[i].initialZ);


  }
  glEnd();

}
