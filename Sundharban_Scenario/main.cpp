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
     // Head
    glColor3f(0.0f, 0.9f, 0.0f);
    float headY = waveAmplitude * sin(time);
    drawSundarbanCircle(numSegments * segmentLength, headY, bodyRadius * 2.0f, 50);

    // Eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawSundarbanCircle(numSegments * segmentLength + 7, headY + 5, 2, 20);
    drawSundarbanCircle(numSegments * segmentLength + 7, headY - 5, 2, 20);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawSundarbanCircle(numSegments * segmentLength + 7, headY + 5, 1, 20);
    drawSundarbanCircle(numSegments * segmentLength + 7, headY - 5, 1, 20);

    // Tongue
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(numSegments * segmentLength + 18, headY);
        glVertex2f(numSegments * segmentLength + 28, headY + 5);
        glVertex2f(numSegments * segmentLength + 18, headY);
        glVertex2f(numSegments * segmentLength + 28, headY - 5);
    glEnd();

    glPopMatrix();
}

// Tree 1: Simple triangle treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanTree1(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(0.4f, 0.26f, 0.13f); // Trunk

    glBegin(GL_QUADS);
        glVertex2f(-5, 0); glVertex2f(5, 0);
        glVertex2f(5, 50); glVertex2f(-5, 30);
    glEnd();

    glColor3f(0.0f, 0.6f, 0.0f); // Leaves

    glBegin(GL_TRIANGLES);
        glVertex2f(-20, 30); glVertex2f(0, 70); glVertex2f(20, 30);
    glEnd();

    glPopMatrix();
}




// Tree 2: Round top treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanTree2(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-4, 0); glVertex2f(4, 0);
        glVertex2f(4, 25); glVertex2f(-4, 25);
    glEnd();

    glColor3f(0.1f, 0.6f, 0.2f);
    for (int i = 0; i < 3; i++) {

        glBegin(GL_POLYGON);
        for (int j = 0; j < 100; j++) {
            float angle = 2.0f * M_PI * j / 100;
            float x1 = cos(angle) * 15 + (i - 1) * 10;
            float y1 = sin(angle) * 15 + 40;
            glVertex2f(x1, y1);
        }
        glEnd();
    }

    glPopMatrix();
}



// Tree 3: Palm treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanTree3(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(0.4f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-3, 0); glVertex2f(3, 0);
        glVertex2f(3, 70); glVertex2f(-3, 70);
    glEnd();

    glColor3f(0.0f, 0.8f, 0.0f);
    for (int i = 0; i < 5; i++) {
        glBegin(GL_LINES);
            glVertex2f(0, 70);
            glVertex2f(cos(i * M_PI / 2.5f) * 30, 70 + sin(i * M_PI / 2.5f) * 30);
        glEnd();
    }

    glPopMatrix();
}



// Tree 5: Bushy treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanTree5(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-3, 0); glVertex2f(3, 0);
        glVertex2f(3, 20); glVertex2f(-3, 20);
    glEnd();

    glColor3f(0.0f, 0.6f, 0.0f);
    for (int i = 0; i < 5; ++i) {
        float offset = (i - 2) * 8;
        glBegin(GL_POLYGON);
        for (int j = 0; j < 100; ++j) {
            float theta = 2.0f * M_PI * j / 100;
            glVertex2f(offset + cos(theta) * 10, 30 + sin(theta) * 10);
        }
        glEnd();
    }

    glPopMatrix();
}

// Tree 8: Mango Treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanTree8(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-4, 0); glVertex2f(4, 0);
        glVertex2f(4, 30); glVertex2f(-4, 30);
    glEnd();

    glColor3f(0.0f, 0.5f, 0.0f);
    for (int i = 0; i < 6; i++) {
        float offset = i * M_PI / 3;
        glBegin(GL_POLYGON);
        for (int j = 0; j < 50; ++j) {
            float theta = j * 2 * M_PI / 50;
            glVertex2f(cos(theta) * 20 + cos(offset) * 20, sin(theta) * 15 + 40 + sin(offset) * 20);
        }
        glEnd();
    }
    glPopMatrix();
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
