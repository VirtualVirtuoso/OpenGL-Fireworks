/*
|--------------------------------------------------------------------------
| Update Particle Existance
|--------------------------------------------------------------------------
|
| We start off by creating new particles, giving them some porperties, and
| then we add them to the worldspace.
|
| Likewise, there are some particles which have either expired their
| lifetime, or do not contribute to the scene (left the view and not
| returning) or are too faint to detect.
*/
void fireworkGeneration() {

  for(unsigned int i = 0; i < particleSet.size(); i++) {
      if(particleSet[i].lifetime == 0) {
        particleSet.erase(particleSet.begin() + i); // Not efficent, causes a shuffle!
        numParticles--;
      } else {
        particleSet[i].opacity = (particleSet[i].lifetime / particleSet[i].maxLifetime);
        particleSet[i].lifetime--;
      }

  }

  if(numParticles < MAX_PARTICLES) {
    particle newParticle = {
      10.0, 10.0, 10.0,
      0.0, 0.01, 0.01,
      255.0, 255.0, 0.0,
      0.0,
      1,
      1,
      (int)(myRandom() * 1000),
      (int)(myRandom() * 1000),
      1
    };
    particleSet.push_back(newParticle);
    numParticles++;
  }

}
