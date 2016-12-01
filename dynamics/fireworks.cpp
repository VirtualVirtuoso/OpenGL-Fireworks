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
    if(emitterSet[i].lifetime == 0) {
      glColor4ub(emitterSet[i].r, emitterSet[i].g, emitterSet[i].b,
                 emitterSet[i].opacity);
      glVertex3f(emitterSet[i].initialX,
                 emitterSet[i].initialY,
                 emitterSet[i].initialZ);
    } else {
      glColor4ub(255, 0, 0,
                 emitterSet[i].opacity);
      glVertex3f(emitterSet[i].initialX,
                 emitterSet[i].initialY,
                 emitterSet[i].initialZ);
      emitterSet[i].lifetime--;
    }
  }
}

int getRandomEmitter(){
  return (rand() % (int)(emitterSet.size() + 1));
}

int getRocketLifetime(){
  return minRocketLifetime +
    (rand() % (int)(maxRocketLifetime - minRocketLifetime + 1));
}

void createFireworkStream() {
  if(numRockets < maxRockets) {
    GLint emitterNum = getRandomEmitter();
    emitterSet[emitterNum].lifetime = emitterSet[emitterNum].maxLifetime;
    particle emitter = emitterSet[emitterNum];
    GLint lifetime = getRocketLifetime();

    GLfloat varianceX = (-rocketLaunchCone) + (rand() % (int)(rocketLaunchCone - (-rocketLaunchCone) + 1));
    GLfloat varianceZ = (-rocketLaunchCone) + (rand() % (int)(rocketLaunchCone - (-rocketLaunchCone) + 1));

    particle newParticle = {
      emitter.initialX, emitter.initialY, emitter.initialZ,
      varianceX/200, 0.2, varianceZ/200,
      255.0, 255.0, 255.0,
      255.0,
      2.0,
      5.0,
      lifetime,
      lifetime,
      0
    };

    rockets.push_back(newParticle);
    numRockets++;
  }
}

void createExplode(particle origin)  {

  int min = 0;
  int max = (sizeof(coloursRed)/sizeof(*coloursRed)) - 1;
  int random = min + (rand() % (int)(max - min + 1));
  GLfloat red = (float)coloursRed[random];
  GLfloat green = (float)coloursGreen[random];
  GLfloat blue = (float)coloursBlue[random];

  for(float theta = 0.0; theta < PI*2; theta += PI/explosionParticleFactor) {

    for(float omega = 0.0; omega < PI*2; omega += PI/explosionParticleFactor) {
      GLfloat x = origin.initialX;
      GLfloat y = origin.initialY;
      GLfloat z = origin.initialZ;
      GLfloat xDirection = (((explodeLifetime + 1) /2) * cos(theta) * sin(omega)) / SCALE_FACTOR;
      GLfloat yDirection = (((explodeLifetime + 1) /2) * sin(theta) * sin(omega)) / SCALE_FACTOR;
      GLfloat zDirection = (((explodeLifetime + 1) /2) * cos(omega)) / SCALE_FACTOR;

      // Now take into account the pressure defined in the menu
      xDirection *= explosionPressure;
      yDirection *= explosionPressure;
      zDirection *= explosionPressure;

      particle newParticle = {
        x, y, z,
        xDirection, yDirection, zDirection,
        red, green, blue,
        255.0,
        2.0,
        5.0,
        explodeLifetime,
        explodeLifetime,
        0
      };

      explosions.push_back(newParticle);
    }

  }
}

void drawExplode() {
  glBegin(GL_POINTS);
  for(unsigned int i = 0; i < explosions.size(); i++) {
    if(explosions[i].lifetime == 0) {
      explosions.erase(explosions.begin() + i);
    } else {
      explosions[i].lifetime--;
      explosions[i].directionY += (-0.0002 * GRAVITATIONAL_CONSTANT * gravitationalFactor); // Simulate gravity
      explosions[i].initialX += explosions[i].directionX;
      explosions[i].initialZ += explosions[i].directionZ;

      // Simulate hitting the grass field
      if(explosions[i].initialY >= 5) {
        explosions[i].initialY += explosions[i].directionY;
      } else {
        if((explosions[i].initialX < 0 || explosions[i].initialX > 200) ||
           (explosions[i].initialZ < 0 || explosions[i].initialZ > 200)) {
             explosions[i].initialY += explosions[i].directionY;
        }
      }

      if(explosions[i].maxLifetime == 0) {
        explosions[i].maxLifetime = 1;
      }

      explosions[i].opacity = ((float)explosions[i].lifetime / (float)explosions[i].maxLifetime);

      glColor4f(explosions[i].r/255, explosions[i].g/255, explosions[i].b/255,
        explosions[i].opacity);
      glVertex3f(explosions[i].initialX,
        explosions[i].initialY,
        explosions[i].initialZ);
    }
  }
  glEnd();
}

void drawFireworkStream() {
  glBegin(GL_POINTS);

  for(unsigned int i = 0; i < rockets.size(); i++) {
    if(rockets[i].lifetime == 0) {
      createExplode(rockets[i]);
      rockets.erase(rockets.begin() + i);
      numRockets--;
    } else {
      rockets[i].initialX += rockets[i].directionX;
      rockets[i].initialY += rockets[i].directionY;
      rockets[i].initialZ += rockets[i].directionZ;
      rockets[i].lifetime--;
      glColor4ub(rockets[i].r, rockets[i].g, rockets[i].b,
        rockets[i].opacity);
      glVertex3f(rockets[i].initialX,
        rockets[i].initialY,
        rockets[i].initialZ);
    }
  }

  glEnd();
}

void renderFireWorkStream(){
  createFireworkStream();
  drawFireworkStream();
}

void fireworkDynamics() {
  glBegin(GL_POINTS);

    displayGrass();
    displayEmitters();
    renderFireWorkStream();
    drawExplode();

  glEnd();

}
