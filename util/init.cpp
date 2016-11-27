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
