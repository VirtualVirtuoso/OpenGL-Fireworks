/*
|--------------------------------------------------------------------------
| Initialise the data structs
|--------------------------------------------------------------------------
|
| Since we're going to be modifying a lot of the data structures in real
| time, especially some of the parameters for the purposes of driving an
| interactive experience, I've moved all of the global variables into this
| file. It just makes it far easier to find them when I'm trying to edit them.
*/

// All of the constants we don't want to be changing
#define MAX_PARTICLES          100
#define DEG_TO_RAD             0.017453293
#define CAMERA_SPEED           10
#define TURN_ANGLE             4.0
#define NUMBER_EMITTERS        20
#define MAX_ROCKETS            10
#define GRAVITATIONAL_CONSTANT 9.81
#define PI                     3.14159
#define STEPS                  20
#define SCALE_FACTOR           4000

GLuint axisList;
GLint width= 1200, height= 800; // Size of initial screen

int AXIS_SIZE= 200;
int axisEnabled= 1;
int numParticles = 0;
int mode = 0; // 0 -- bees, 1 -- fireworks, 2 --

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

// The data structures which will be holding the particles
vector<particle> particleSet;
vector<particle> grassSet;
vector<particle> emitterSet;
vector<particle> rockets;
vector<particle> explosions;

// Firework specific variables which will be changed
int numRockets = 0;
int minRocketLifetime = 500;
int maxRocketLifetime = 1000;
int fireworkRadius = 20;
int explodeLifetime = 400;
int rocketLaunchCone = 5;

// Each of the colours which have been defined for the fireworks
// Red, orange, yellow, green, blue, purple, pink
int coloursRed[] = {219, 219, 219, 113, 15, 15, 103, 219};
int coloursBlue[] = {69, 124, 192, 219, 219, 124, 15, 15};
int coloursGreen[] = {15, 15, 15, 15, 171, 219, 219, 212};
