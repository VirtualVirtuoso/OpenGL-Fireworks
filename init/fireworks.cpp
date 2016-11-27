/*
|--------------------------------------------------------------------------
| Initialise the scene
|--------------------------------------------------------------------------
|
| Perform any one time calculations which shouldn't be executed at every
| frame.
*/
#define NUMBER_EMITTERS 20

vector<particle> grassSet;
vector<particle> emitterSet;

void initGrass(){

  for(unsigned int i = 1; i < 80; i++) {
    for(unsigned int j = 1; j < 80; j++) {
      for(unsigned int k = 1; k < 3; k++) {
        GLfloat r = 30 + ((myRandom() - 0.1) * 60);
        GLfloat g = 144 + ((myRandom() - 0.5) * 30);
        GLfloat b = 24 + ((myRandom() - 0.5) * 10);

        GLfloat x = (i * 2.5) + (myRandom() - 0.5) * 1;
        GLfloat y = 1 + (0.1 * k);
        GLfloat z = (j * 2.5) + (myRandom() - 0.5) * 1;

        particle newParticle = {
          x, y, z,
          0.0, 0.0, 0.0,
          r, g, b,
          255.0,
          1,
          1,
          -1,
          -1,
          1
        };

        grassSet.push_back(newParticle);

      }
    }
  }
}

void initEmitters(){

  for(unsigned int i = 1; i < NUMBER_EMITTERS; i++) {
      GLfloat x = 100 + (50 * cos(i));
      GLfloat z = 100 + (50 * sin(i));

      particle newParticle = {
        x, 2, z,
        0.0, 0.00, 0.00,
        255.0, 255.0, 255.0,
        255.0,
        1,
        1,
        -1,
        -1,
        1
      };

      emitterSet.push_back(newParticle);
  }

}

void initFireworks(){
  initGrass();
  initEmitters();
}
