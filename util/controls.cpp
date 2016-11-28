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
  switch (key) {
    case 27: // ESC
      exit(0);
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
      cout << "Fireworks..." << endl;
      mode = 2;
      particleSet.clear();
      numParticles = 0;
      break;
    case 2:
      cout << "Settings..." << endl;
      break;
    case 10:
      cout << "Exiting the program..." << endl;
      exit(0);
    default:
      break;
  }
}

void settingsMenuProcess(int menuEntry) {
  switch(menuEntry) {
    case 1:
      cout << "Option 1" << endl;
      break;
    case 2:
      cout << "Option 2" << endl;
      break;
    case 3:
      cout << "Option 3" << endl;
      break;
    default:
      break;
  }
}

void explosionsMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  cout << menuEntry << endl;
}

void fireworkMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  cout << menuEntry << endl;
}

void emitterMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  cout << menuEntry << endl;
}

void maxFireworkHeightMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  cout << menuEntry << endl;
}

void minFireworkHeightMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  cout << menuEntry << endl;
}

void explosionPressureMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  cout << (float)menuEntry/100.0 << endl;
}

void gravityStengthMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  cout << (float)menuEntry/100.0 << endl;
}

void initMainMenu() {

  // For the explosion pressure
  int gravityStengthMenu = glutCreateMenu(gravityStengthMenuProcess);
  glutAddMenuEntry("== Gravity % == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("10%", 10);
  glutAddMenuEntry("20%", 20);
  glutAddMenuEntry("50%", 50);
  glutAddMenuEntry("100%", 100);
  glutAddMenuEntry("150%", 150);
  glutAddMenuEntry("200%", 200);
  glutAddMenuEntry("500%", 500);

  // For the explosion pressure
  int explosionPressureMenu = glutCreateMenu(explosionPressureMenuProcess);
  glutAddMenuEntry("== Explosion Pressure % == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("10%", 10);
  glutAddMenuEntry("20%", 20);
  glutAddMenuEntry("50%", 50);
  glutAddMenuEntry("100%", 100);
  glutAddMenuEntry("150%", 150);
  glutAddMenuEntry("200%", 200);
  glutAddMenuEntry("500%", 500);

  // For the max firework height
  int maxFireworkHeightMenu = glutCreateMenu(maxFireworkHeightMenuProcess);
  glutAddMenuEntry("== Max Firework Height == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("200", 200);
  glutAddMenuEntry("205", 205);
  glutAddMenuEntry("210", 210);
  glutAddMenuEntry("220", 220);
  glutAddMenuEntry("300", 300);
  glutAddMenuEntry("500", 500);
  glutAddMenuEntry("1000", 1000);

  // For the min firework height
  int minFireworkHeightMenu = glutCreateMenu(minFireworkHeightMenuProcess);
  glutAddMenuEntry("== Min Firework Height == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("1", 1);
  glutAddMenuEntry("5", 5);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("20", 20);
  glutAddMenuEntry("100", 100);
  glutAddMenuEntry("200", 1000);

  // For the firework count
  int explosionsMenu = glutCreateMenu(explosionsMenuProcess);
  glutAddMenuEntry("== # Explosion 'Rings' == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("1", 1);
  glutAddMenuEntry("5", 5);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("20", 20);
  glutAddMenuEntry("100", 100);
  glutAddMenuEntry("1000", 1000);
  glutAddMenuEntry("10000", 10000);

  // For the firework count
  int fireworkMenu = glutCreateMenu(fireworkMenuProcess);
  glutAddMenuEntry("     == # Rockets ==      ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("1", 1);
  glutAddMenuEntry("5", 5);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("20", 20);
  glutAddMenuEntry("100", 100);
  glutAddMenuEntry("1000", 1000);
  glutAddMenuEntry("10000", 10000);

  // For the emitter count
  int emittersMenu = glutCreateMenu(emitterMenuProcess);
  glutAddMenuEntry("      == Emitters ==      ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("1", 1);
  glutAddMenuEntry("2", 2);
  glutAddMenuEntry("5", 5);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("20", 20);
  glutAddMenuEntry("50", 50);

  // For the settings menu
  int settingsMenu = glutCreateMenu(settingsMenuProcess);
  glutAddMenuEntry("      == Settings ==      ", 999);
  glutAddMenuEntry("", 999);
  glutAddSubMenu("# Emitters", emittersMenu);
  glutAddSubMenu("# Rockets", fireworkMenu);
  glutAddSubMenu("# Explosion Particles", explosionsMenu);
  glutAddSubMenu("Min Rocket Height", minFireworkHeightMenu);
  glutAddSubMenu("Max Rocket Height", maxFireworkHeightMenu);
  glutAddSubMenu("Explosion Pressure", explosionPressureMenu);
  glutAddSubMenu("Gravity Coefficient", gravityStengthMenu);

  // For the main menu
  glutCreateMenu(menu);
  glutAddMenuEntry(" == Firework Simulator == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("Start Simulation", 1);
  glutAddSubMenu("Settings", settingsMenu);
  glutAddMenuEntry("Quit", 10);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initMenus() {
  glClearColor(0.0, 0.0, 0.0, 0.0);

  initMainMenu();

  glEnable(GL_DEPTH_TEST);
}
