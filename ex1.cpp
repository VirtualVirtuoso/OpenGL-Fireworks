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

#include "util/data.cpp"


/*
|--------------------------------------------------------------------------
| Utility Methods
|--------------------------------------------------------------------------
|
| Here we some reusable functions which don't really fit anywhere else
*/

double myRandom() {
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

void reshape(int width, int height) {
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
| Initialise the scene
|--------------------------------------------------------------------------
|
| Perform any one time calculations which shouldn't be executed at every
| frame.
*/
#include "init/fireworks.cpp"

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

#include "generation/bee.cpp"
#include "generation/fireworks.cpp"

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

#include "dynamics/bee.cpp"
#include "dynamics/fireworks.cpp"

void strangeProcess() {

}

void blackHoleProcess() {

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

void animate() {
  switch(mode) {
    case 1:
      beeGeneration();
      beeDynamics();
      break;
    case 2:
      fireworkGeneration();
      fireworkDynamics();
      break;
    default:
      break;
  }
  glutSwapBuffers();
  glutPostRedisplay();
}

/*
|--------------------------------------------------------------------------
| Initialise the application
|--------------------------------------------------------------------------
|
| These are the GLUT calls which are required to setup a basic scene, and
| will also setup the scene, before we run the main loop
*/
#include "util/controls.cpp"
#include "init/init.cpp"

int main() {

  initGraphics();
  glutMainLoop();

  return 0;
}
