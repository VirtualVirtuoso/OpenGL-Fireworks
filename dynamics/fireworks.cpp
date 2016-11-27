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
void displayGrass() {
  for(unsigned int i = 0; i < grassSet.size(); i++) {
      glColor4ub(grassSet[i].r, grassSet[i].g, grassSet[i].b,
        grassSet[i].opacity);
      glVertex3f(grassSet[i].initialX,
                 grassSet[i].initialY,
                 grassSet[i].initialZ);
  }
}

void displayEmitters() {
  for(unsigned int i = 0; i < emitterSet.size(); i++) {
      glColor4ub(emitterSet[i].r, emitterSet[i].g, emitterSet[i].b,
                 emitterSet[i].opacity);
      glVertex3f(emitterSet[i].initialX,
                 emitterSet[i].initialY,
                 emitterSet[i].initialZ);
  }
}

void fireworkDynamics() {
  glBegin(GL_POINTS);

    displayGrass();
    displayEmitters();

  glEnd();

}
