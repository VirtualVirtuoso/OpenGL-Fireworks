#include "camera.cpp"

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

void menuProcess(int menuEntry) {
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

void settingsMenuProcess(int menuEntry) {}

void explosionPressureMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  GLfloat oldPressure = explosionPressure;
  explosionPressure = (float)menuEntry / 100.0;
  cout << "[Setting] Explosion pressure changed from: " << oldPressure * 100
       << "% to: " << explosionPressure * 100 << "%" << endl;
}

void fireworkMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  int oldRockets = maxRockets;
  maxRockets = menuEntry;
  cout << "[Setting] Max Rockets changed from: " << oldRockets
       << " to: " << maxRockets << endl;
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
  int oldHeight = maxRocketLifetime;
  maxRocketLifetime = menuEntry;
  cout << "[Setting] Max Firework Height changed from: " << oldHeight
       << " to: " << maxRocketLifetime << endl;
}

void minFireworkHeightMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  int oldHeight = minRocketLifetime;
  minRocketLifetime = menuEntry;
  cout << "[Setting] Min Firework Height changed from: " << oldHeight
       << " to: " << minRocketLifetime << endl;
}

void explosionsMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  int oldExplosionCount = explosionParticleFactor;
  explosionParticleFactor = menuEntry;
  cout << "[Setting] Explosion Particle Count Factor changed from: " << oldExplosionCount
       << " to: " << explosionParticleFactor << endl;
}

void gravityStengthMenuProcess(int menuEntry) {
  if(menuEntry == 999) {
    return;
  }
  GLfloat oldGravity = gravitationalFactor;
  gravitationalFactor = (float)menuEntry / 100.0;
  cout << "[Setting] Gravitational Force changed from: " << oldGravity * 100
       << "% to: " << gravitationalFactor * 100 << "%" << endl;
}

void printVariables(){
  cout << endl;
  cout << "[Info] Printing the parameters set..." << endl;
  cout << "[Info] Number of emitters: " << numEmitters << endl;
  cout << "[Info] Max Number of rockets: " << maxRockets << endl;
  cout << "[Info] Number of rings per explosion: " << explosionParticleFactor << endl;
  cout << "[Info] Minimum rocket height: " << minRocketLifetime << endl;
  cout << "[Info] Maximum rocket height: " << maxRocketLifetime << endl;
  cout << "[Info] Explosion Pressure: " << explosionPressure << endl;
  cout << "[Info] Gravity coefficient: " << gravitationalFactor << endl;
  cout << endl;
}

void utilMenuProcess(int menuEntry){
  if(menuEntry == 999) {
    return;
  }

  switch(menuEntry) {
    case 1:
      printVariables();
      break;
    case 2:
      cout << endl;
      cout << "[Info] Printing a description of the scene..." << endl;
      cout << "[Info] Number of rockets: " << rockets.size() << endl;
      cout << "[Info] Number of explosion particles: " << explosions.size() << endl;
      cout << "[Info] Number of grass particles: " << grassSet.size() << endl;
      cout << "[Info] Number of emitters: " << emitterSet.size() << endl;

      cout << "[Info] Current number of particles rendered: "
           << rockets.size() + explosions.size() + grassSet.size() + emitterSet.size()
           << endl;
      cout << endl;
      break;
    default:
      break;
  }
}

void setVariables(int thisR, int thisEPa, int thisMin,
                  int thisMax, int thisEPr, int thisG) {
  maxRockets = thisR;
  explosionParticleFactor = thisEPa;
  minRocketLifetime = thisMin;
  maxRocketLifetime = thisMax;
  explosionPressure = thisEPr;
  gravitationalFactor = thisG;
}

void scenarioMenuProcess(int menuEntry){
  if(menuEntry == 999) {
    return;
  }

  rockets.clear();
  explosions.clear();
  numRockets = 0;

  cout << endl;

  switch(menuEntry) {
    case 1:
      cout << "[Scenario] Loading energy circle..." << endl;
      setVariables(5000, 0, 500, 100, 50, 1);
      cout << endl;
      printVariables();
      break;
    case 2:
      cout << "[Scenario] Loading 3-Dimensional hyperdrive..." << endl;
      setVariables(5000, 2, 500, 1000, 50, 1);
      printVariables();
      break;
    case 3:
      cout << "[Scenario] Loading the death of a star..." << endl;
      setVariables(5000, 5, 500, 1000, 50, 1);
      printVariables();
      break;
    case 4:
      cout << "[Scenario] Loading splatty fireworks..." << endl;
      setVariables(20, 20, 100, 500, 5, 5);
      printVariables();
      break;
    case 5:
      cout << "[Scenario] Splatting the GPU with 85,000 particles ..." << endl;
      setVariables(30, 30, 500, 300, 50, 5);
      printVariables();
      break;
    default:
      break;
  }

}

void particleTypeMenuProcess(int menuEntry){
  if (menuEntry == 999) {
    return;
  }

  switch(menuEntry) {
    case 1:
      cout << "[Particle] Now using points..." << endl;
      particleType = 1;
      break;
    case 2:
      cout << "[Particle] Now using quads..." << endl;
      particleType = 2;
      break;
    case 3:
      cout << "[Particle] Now using trails..." << endl;
      particleType = 3;
      break;
    default:
      break;
  }
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
  glutAddMenuEntry("1000%", 1000);
  glutAddMenuEntry("2000%", 2000);
  glutAddMenuEntry("5000%", 5000);

  // For the max firework height
  int maxFireworkHeightMenu = glutCreateMenu(maxFireworkHeightMenuProcess);
  glutAddMenuEntry("== Max Firework Height == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("500", 500);
  glutAddMenuEntry("600", 600);
  glutAddMenuEntry("750", 750);
  glutAddMenuEntry("1000", 1000);
  glutAddMenuEntry("1250", 1250);
  glutAddMenuEntry("1500", 1500);
  glutAddMenuEntry("2000", 2000);

  // For the min firework height
  int minFireworkHeightMenu = glutCreateMenu(minFireworkHeightMenuProcess);
  glutAddMenuEntry("== Min Firework Height == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("0", 0);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("50", 50);
  glutAddMenuEntry("100", 100);
  glutAddMenuEntry("200", 200);
  glutAddMenuEntry("500", 500);

  // For the firework count
  int explosionsMenu = glutCreateMenu(explosionsMenuProcess);
  glutAddMenuEntry("== # Explosion 'Rings' == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("0", 0);
  glutAddMenuEntry("1", 1);
  glutAddMenuEntry("2", 2);
  glutAddMenuEntry("5", 5);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("20", 20);
  glutAddMenuEntry("30", 30);
  glutAddMenuEntry("50", 50);

  // For the firework count
  int fireworkMenu = glutCreateMenu(fireworkMenuProcess);
  glutAddMenuEntry("     == # Rockets ==      ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("1", 1);
  glutAddMenuEntry("5", 5);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("20", 20);
  glutAddMenuEntry("50*", 50);
  glutAddMenuEntry("100", 100);
  glutAddMenuEntry("200", 200);
  glutAddMenuEntry("500", 500);
  glutAddMenuEntry("1000", 1000);
  glutAddMenuEntry("2000", 2000);
  glutAddMenuEntry("5000", 5000);

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

  int particleTypeMenu = glutCreateMenu(particleTypeMenuProcess);
  glutAddMenuEntry("      == Particles ==      ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("Point", 1);
  glutAddMenuEntry("Quad", 2);
  glutAddMenuEntry("Trail", 3);

  // For the settings menu
  int settingsMenu = glutCreateMenu(settingsMenuProcess);
  glutAddMenuEntry("      == Settings ==      ", 999);
  glutAddMenuEntry("", 999);
  glutAddSubMenu("Particle Type", particleTypeMenu);
  glutAddSubMenu("# Emitters", emittersMenu);
  glutAddSubMenu("# Rockets", fireworkMenu);
  glutAddSubMenu("# Explosion Particles", explosionsMenu);
  glutAddSubMenu("Min Rocket Height", minFireworkHeightMenu);
  glutAddSubMenu("Max Rocket Height", maxFireworkHeightMenu);
  glutAddSubMenu("Explosion Pressure", explosionPressureMenu);
  glutAddSubMenu("Gravity Coefficient", gravityStengthMenu);

  int scenariosMenu = glutCreateMenu(scenarioMenuProcess);
  glutAddMenuEntry("      == Scenarios ==      ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("Energy Circle", 1);
  glutAddMenuEntry("3 Dimensional Hyperdrive", 2);
  glutAddMenuEntry("Death of a star", 3);
  glutAddMenuEntry("Splatty fireworks", 4);
  glutAddMenuEntry("Let's crash the GPU", 5);

  int utilMenu = glutCreateMenu(utilMenuProcess);
  glutAddMenuEntry("        == Util ==        ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("Print coefficients", 1);
  glutAddMenuEntry("Print #particles", 2);

  // For the main menu
  glutCreateMenu(menuProcess);
  glutAddMenuEntry(" == Firework Simulator == ", 999);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("Start Simulation", 1);
  glutAddSubMenu("Settings", settingsMenu);
  glutAddSubMenu("Scenarios", scenariosMenu);
  glutAddSubMenu("Util", utilMenu);
  glutAddMenuEntry("Quit", 10);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initMenus() {
  glClearColor(0.0, 0.0, 0.0, 0.0);

  initMainMenu();

  glEnable(GL_DEPTH_TEST);
}
