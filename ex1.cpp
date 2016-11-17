/*
|--------------------------------------------------------------------------
| Strange Attractions
|--------------------------------------------------------------------------
|
| School of Computer Science
| The University of Manchester
|
| This code is licensed under the terms of the Creative Commons
| Attribution 2.0 Generic (CC BY 3.0) License.
|
| Skeleton code for COMP37111 coursework, 2013-14
|
| Authors: Struan McDonough, Arturs Bekasovs, Toby Howard
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;

/*
|--------------------------------------------------------------------------
| Define the globals
|--------------------------------------------------------------------------
|
| Here, we define variables which will be shared by the entire application.
| The most important parts here are the particle struct and the particle
| vector, which defines the worldspace.
*/

#define MAX_PARTICLES 100
#define DEG_TO_RAD    0.017453293
#define CAMERA_SPEED  10
#define TURN_ANGLE    4.0

GLuint axisList;
GLint width= 800, height= 600; // Size of initial screen

int AXIS_SIZE= 200;
int axisEnabled= 1;
int numParticles = 0;

// Trick GLUT into thinking we're working in C, not C++
char fakeParam[] = "fake";
char *fakeargv[] = { fakeParam, NULL };
int fakeargc = 1;

typedef struct {
  GLfloat initialX, initialY, initialZ;
  GLfloat directionX, directionY, directionZ;
  GLfloat r, g, b;
  GLfloat opacity;
  GLfloat scale;
  GLfloat weight;
  GLint maxLifetime;
  GLint lifetime; // -1 for infinite
  GLint type; // 0 - point, 1 - line, 2 - voxel, 3 - image
} particle;

vector<particle> particleSet;

double myRandom()
{
  return (rand()/(double)RAND_MAX);
}

/*
|--------------------------------------------------------------------------
| Handle global events
|--------------------------------------------------------------------------
|
| Define what we're going to do, if someone hits a button, or the size of
| the window changes
*/

void reshape(int width, int height)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
  glMatrixMode(GL_MODELVIEW);
}

/*
|--------------------------------------------------------------------------
| Create the axes
|--------------------------------------------------------------------------
|
| This comes out of the box with the demo provided for this exercise. It
| simply creates some axis to show that the application has been working
*/

void makeAxes() {
// Create a display list for drawing coord axis
  axisList = glGenLists(1);
  glNewList(axisList, GL_COMPILE);
      glLineWidth(2.0);
      glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);       // X axis - red
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(AXIS_SIZE, 0.0, 0.0);
      glColor3f(0.0, 1.0, 0.0);       // Y axis - green
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, AXIS_SIZE, 0.0);
      glColor3f(0.0, 0.0, 1.0);       // Z axis - blue
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, AXIS_SIZE);
    glEnd();
  glEndList();
}


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

void fireworkGeneration(){

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

void fireworkDynamics(){
  glBegin(GL_POINTS);

  for(unsigned int i = 0; i < particleSet.size(); i++) {
    particleSet[i].initialX += (myRandom() - 0.5) * 5;
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

void strangeProcess(){

}

void blackHoleProcess(){

}

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

void initCamera(){
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

void keyboard(unsigned char key, int x, int y)
{
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

void display(){
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
| Run the loop
|--------------------------------------------------------------------------
|
| Here we define the loop which will be the workhorse behind the process.
| We need to make sure that the view is set, the lookpoint is where it
| should be, and that the buffers are cleared.
*/

void animate(){
  fireworkGeneration();
  fireworkDynamics();
  glutSwapBuffers();
  glutPostRedisplay();
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
      cout << "Menu entry 1 clicked..." << endl;
      break;
    case 2:
      cout << "Menu entry 2 clicked..." << endl;
      break;
    case 3:
      cout << "Exiting the program..." << endl;
      exit(0);
    default:
      break;
  }
}

void initMenus(){
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutCreateMenu(menu);

  glutAddMenuEntry("Option 1", 1);
  glutAddMenuEntry("Option 2", 2);
  glutAddMenuEntry("", 999);
  glutAddMenuEntry("Quit", 3);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glEnable(GL_DEPTH_TEST);
}

/*
|--------------------------------------------------------------------------
| Initialise the application
|--------------------------------------------------------------------------
|
| These are the GLUT calls which are required to setup a basic scene, and
| will also setup the scene, before we run the main loop
*/

void initGraphics() {
  glutInit(&fakeargc, fakeargv);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutCreateWindow("COMP37111 Particles");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  initMenus();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  glutIdleFunc(animate);
  glPointSize(3);

  initCamera();

  glutPassiveMotionFunc (mouseMotion);

  glEnable(GL_POINT_SMOOTH);

  makeAxes();
}

int main()
{
  // srand(time(NULL));
  initGraphics();
  glutMainLoop();

  return 0;
}
