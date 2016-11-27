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
#define MAX_ROCKETS 10

vector<particle> rockets;
vector<particle> explosions;

int numRockets = 0;
int minRocketLifetime = 500;
int maxRocketLifetime = 1000;
int fireworkRadius = 20;
int explodeLifetime = 400;

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
  if(numRockets < MAX_ROCKETS) {
    GLint emitterNum = getRandomEmitter();
    emitterSet[emitterNum].lifetime = emitterSet[emitterNum].maxLifetime;
    particle emitter = emitterSet[emitterNum];
    GLint lifetime = getRocketLifetime();

    particle newParticle = {
      emitter.initialX, emitter.initialY, emitter.initialZ,
      0, 0.2, 0,
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
  for(int i = 0; i < 20; i++) {
    GLfloat xDirection = (((explodeLifetime + 1) /2) * cos(i)) / 20;
    GLfloat zDirection = (((explodeLifetime + 1) /2) * sin(i)) / 20;
    GLfloat x = origin.initialX;
    GLfloat y = origin.initialY;
    GLfloat z = origin.initialZ;

    particle newParticle = {
      x, y, z,
      ((xDirection+1) / 100), 0, ((zDirection+1) /100),
      255.0, 0, 255.0,
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

void drawExplode() {
  glBegin(GL_POINTS);
  for(unsigned int i = 0; i < explosions.size(); i++) {
    if(explosions[i].lifetime == 0) {
      explosions.erase(explosions.begin() + i);
    } else {
      explosions[i].lifetime--;
      explosions[i].initialX += explosions[i].directionX;
      explosions[i].initialZ += explosions[i].directionZ;

      glColor4ub(explosions[i].r, explosions[i].g, explosions[i].b,
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
      rockets[i].initialY += rockets[i].directionY;
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
