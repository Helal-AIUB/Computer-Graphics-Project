#include <GL/glut.h>
#include <cmath>
#include <cstdlib>


//night
bool isNight = false;

//rain

bool isRain = false;
const int RAIN_DROPS = 300;
float rainX[RAIN_DROPS], rainY[RAIN_DROPS];



// Window dimensions
int width = 1000;
int height = 600;

// Boat positions
float boatX1 = 500, boatX2 = 700, boatX3 = 900, boatX4 = 1100;

// Cloud positions
float cloudX1 = 400, cloudX2 = 700, cloudX3 = 1000;


// Tiger position
float tigerX = -600;

// Deer position
float deerX = -600;



// snak3

float snakeX = -width / 2 - 300;  // sanake bam theke cholbe
float snakeY = -height / 4 - 100; // nodite position

const int numSegments = 15;
const float segmentLength = 7.0f;
const float bodyRadius = 4.0f;

float waveAmplitude = 7.0f;
float waveFrequency = 0.4f;
float timeValue = 0.0f;


// snake
void drawSundarbanCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1416f * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}
// snakeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee

void drawSundarbanSnake(float baseX, float baseY, float time) {
    glPushMatrix();
    glTranslatef(baseX, baseY, 0.0f);

    glColor3f(0.0f, 0.7f, 0.0f);

    for (int i = 0; i < numSegments; i++) {
        float x = i * segmentLength;  // matha theke dan a
        float y = waveAmplitude * sin(waveFrequency * i + time);

        drawSundarbanCircle(x, y, bodyRadius, 40);
    }

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
