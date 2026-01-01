#include <GL/glut.h>
#include <cmath>
#include <cstdlib>



// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Sundarban project  AIUB");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutKeyboardFunc(handleKeypress);


    glutMainLoop();
    return 0;
}
