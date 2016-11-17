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

GLuint axisList;
int AXIS_SIZE= 200;
int axisEnabled= 1;

// Trick GLUT into thinking we're working in C, not C++
char fakeParam[] = "fake";
char *fakeargv[] = { fakeParam, NULL };
int fakeargc = 1;

typedef struct {
  GLfloat initialX, initialY, initialZ;
  GLfloat directionX, directionY, directionZ;
  GLfloat r, g, b;
  GLfloat scale;
  GLfloat weight;
  GLint lifetime;
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

void keyboard(unsigned char key, int x, int y)
{
  if(key == 27) exit(0);
  glutPostRedisplay();
}

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
| Run the loop
|--------------------------------------------------------------------------
|
| Here we define the loop which will be the workhorse behind the process.
| We need to make sure that the view is set, the lookpoint is where it
| should be, and that the buffers are cleared.
*/

void display(){
  glLoadIdentity();
  gluLookAt(0.0, 100.0, 1000.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(axisEnabled) glCallList(axisList);
  glutSwapBuffers();
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
  initMenus();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  makeAxes();
}

int main()
{
  srand(time(NULL));
  initGraphics();
  glEnable(GL_POINT_SMOOTH);
  glutMainLoop();
}
