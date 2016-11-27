/*
|--------------------------------------------------------------------------
| Create the camera controls
|--------------------------------------------------------------------------
|
| Being able to see around the scene is essential for being able to both
| admire and debug the scene, when things go wrong.
*/

GLdouble lat, lon;                  /* View angles (degrees) */
GLdouble mouseLat, mouseLon;        /* Mouse look offset angles */
GLfloat  eyeX, eyeY, eyeZ;          /* Eye point */
GLfloat  centerX, centerY, centerZ; /* Look point */
GLfloat  upX, upY, upZ;             /* View up vector */

void initCamera() {
  eyeX = 250;
  eyeY = 100;
  eyeZ = 250;

  upX = 0.0;
  upY = 1.0;
  upZ = 0.0;

  lat = 1.71;
  lon = -138.1;

  mouseLat = 0.0;
  mouseLon = 0.0;
}

void calculateLookpoint() {
  GLfloat dirX = cos(lat * DEG_TO_RAD) * sin(lon * DEG_TO_RAD);
  GLfloat dirY = sin(lat * DEG_TO_RAD);
  GLfloat dirZ = cos(lat * DEG_TO_RAD) * cos(lon * DEG_TO_RAD);
  centerX = eyeX + dirX;
  centerY = eyeY + dirY;
  centerZ = eyeZ + dirZ;
}

void mouseMotion(int x, int y) {
  if(lat > 89){
    lat = lat - 10;
  }
  if(lat < -89){
    lat = lat + 10;
  }
  lon += (-(((double)x / ((double)width / 100)) - 50))/50;
  lat += (-(((double)y / ((double)height / 100)) - 50))/50;
}

void keyboard(unsigned char key, int x, int y) {
  if(key == 27) exit(0);
  switch (key) {
    case 119: // W
      eyeX += CAMERA_SPEED * sin(DEG_TO_RAD * lon);
      eyeZ += CAMERA_SPEED * cos(DEG_TO_RAD * lon);
      break;
    case 115: // S
        eyeX += -CAMERA_SPEED * sin(DEG_TO_RAD * lon);
        eyeZ += -CAMERA_SPEED * cos(DEG_TO_RAD * lon);
        break;
    case 97: // A
        eyeX += CAMERA_SPEED * sin((DEG_TO_RAD * lon)+(DEG_TO_RAD * 90));
        eyeZ += CAMERA_SPEED * cos((DEG_TO_RAD * lon)+(DEG_TO_RAD * 90));
        break;
    case 100: // D
        eyeX += -CAMERA_SPEED * sin((DEG_TO_RAD * lon)+(DEG_TO_RAD * 90));
        eyeZ += -CAMERA_SPEED * cos((DEG_TO_RAD * lon)+(DEG_TO_RAD * 90));
        break;
    case 113: // Q
        eyeY += CAMERA_SPEED;
        break;
    case 101: // E
        eyeY += -CAMERA_SPEED;
        break;
    }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  calculateLookpoint();
  gluLookAt(eyeX, eyeY, eyeZ,
            centerX, centerY, centerZ,
            upX, upY, upZ);
  if(axisEnabled) glCallList(axisList);

}

/*
|--------------------------------------------------------------------------
| Create the menus
|--------------------------------------------------------------------------
|
| Here, we have two functions. The first of which defines the actions
| associated with the actions for each button index.
|
| The second actually defines the menu, and the buttons which should
| appear
*/

void menu(int menuEntry) {
  switch(menuEntry) {
    case 1:
      cout << "BEES!..." << endl;
      mode = 1;
      particleSet.clear();
      numParticles = 0;
      break;
    case 2:
      cout << "Fireworks..." << endl;
      mode = 2;
      particleSet.clear();
      numParticles = 0;
      break;
    case 3:
      cout << "Strangeness..." << endl;
      mode = 3;
      particleSet.clear();
      numParticles = 0;
      break;
    case 4:
      cout << "Holes..." << endl;
      mode = 4;
      particleSet.clear();
      numParticles = 0;
      break;
    case 10:
      cout << "Exiting the program..." << endl;
      exit(0);
    default:
      break;
  }
}

void initMenus() {
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutCreateMenu(menu);

  glutAddMenuEntry("Bees", 1);
  glutAddMenuEntry("Fireworks", 2);
  glutAddMenuEntry("Attractors", 3);
  glutAddMenuEntry("Blackhold", 4);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("Quit", 10);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glEnable(GL_DEPTH_TEST);
}
