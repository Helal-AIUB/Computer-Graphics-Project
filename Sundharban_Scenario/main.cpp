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
//birdssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
const int BIRD_COUNT = 10;
float birdX[BIRD_COUNT];
float birdY[BIRD_COUNT];

void initBirds() {
    for (int i = 0; i < BIRD_COUNT; i++) {
        birdX[i] = width / 2 + i * 100;
        birdY[i] = (rand() % 80) + height / 4 + 120;
    }
}




//birdssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
void drawSundarbanBird(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(-10, 10);
        glVertex2f(0, 0);
        glVertex2f(10, 10);
    glEnd();
    glPopMatrix();
}

void drawSundarbanAllBirds() {
    for (int i = 0; i < BIRD_COUNT; i++) {
        drawSundarbanBird(birdX[i], birdY[i]);
    }
}

// round treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanRoundLeafTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Trunk
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-15, 0);
        glVertex2f(15, 0);
        glVertex2f(8, 60);
        glVertex2f(-8, 60);
    glEnd();

    // Leaf (circle)
    glColor3f(0.0f, 0.7f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 90);
        for (int i = 0; i <= 100; i++) {
            float angle = 2.0f * 3.1416f * i / 100;
            float dx = 35 * cosf(angle);
            float dy = 35 * sinf(angle);
            glVertex2f(dx, dy + 90);
        }
    glEnd();

    glPopMatrix();
}



// Draw simple tree at (x,y)
void drawSundarbanSimpleTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Trunk
    glColor3f(0.36f, 0.25f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(-30, 0);
        glVertex2f(5, 0);
        glVertex2f(10, 60);
        glVertex2f(-10, 60);
    glEnd();

    // Leaves - 3 triangles stacked
    glColor3f(0.0f, 0.6f, 0.0f);

    // Bottom triangle
    glBegin(GL_TRIANGLES);
        glVertex2f(-40, 60);
        glVertex2f(40, 60);
        glVertex2f(0, 120);
    glEnd();

    // Middle triangle
    glBegin(GL_TRIANGLES);
        glVertex2f(-30, 90);
        glVertex2f(30, 90);
        glVertex2f(0, 140);
    glEnd();

    // Top triangle
    glBegin(GL_TRIANGLES);
        glVertex2f(-20, 120);
        glVertex2f(20, 120);
        glVertex2f(0, 170);
    glEnd();

    glPopMatrix();
}

// Function to draw a simple leg
void drawSundarbanLeg(float x, float y) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 10, y - 30);
    glVertex2f(x, y - 30);
    glEnd();
}

// Function to draw deer antlers
void drawSundarbanAntlers(float x, float y) {
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x - 10, y + 30);
    glVertex2f(x, y);
    glVertex2f(x + 10, y + 30);

    // branches
    glVertex2f(x - 5, y + 20);
    glVertex2f(x - 15, y + 35);
    glVertex2f(x + 5, y + 20);
    glVertex2f(x + 15, y + 35);
    glEnd();
}




// Draw the deerrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
void drawSundarbanDeer(float x, float y) {
    glColor3f(1.0f, 1.6f, 0.f); // green

    // Body
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 70, y-5);
    glVertex2f(x + 60, y + 30);
    glVertex2f(x, y + 30);
    glEnd();

    // Legs
    glColor3f(1.0f, 1.75f, 0.75f);
    drawSundarbanLeg(x + 5, y);
    drawSundarbanLeg(x + 20, y);
    drawSundarbanLeg(x + 35, y);
    drawSundarbanLeg(x + 50, y);

    // Neck
    glBegin(GL_POLYGON);
    glVertex2f(x + 45, y + 30);
    glVertex2f(x + 55, y + 30);
    glVertex2f(x + 55, y + 55);
    glVertex2f(x + 45, y + 55);
    glEnd();

    // Head
    glBegin(GL_POLYGON);
    glVertex2f(x + 40, y + 55);
    glVertex2f(x + 60, y + 55);
    glVertex2f(x + 60, y + 65);
    glVertex2f(x + 40, y + 65);
    glEnd();

    // Ear
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 42, y + 65);
    glVertex2f(x + 46, y + 70);
    glVertex2f(x + 44, y + 65);
    glEnd();

    // Eye
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(x + 58, y + 62);
    glEnd();

    //tail
    glColor3f(0.3f, 0.2f, 0.1f); // dark brown tail color
    glBegin(GL_POLYGON);
        glVertex2f(x, y + 15);
        glVertex2f(x - 10, y + 20);
        glVertex2f(x - 12, y + 18);
        glVertex2f(x - 5, y + 10);
    glEnd();

    // Antlers
    glColor3f(0.3f, 0.2f, 0.1f);
    drawSundarbanAntlers(x + 50, y + 65);
}


// Tigerrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
void drawSundarbanTiger(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    // Body
    glColor3f(1.0f, 0.6f, 0.0f); // orange
    glBegin(GL_POLYGON);
        glVertex2f(-40, 0); glVertex2f(40, 0);
        glVertex2f(40, 30); glVertex2f(-45, 30);
    glEnd();

    // Stripes
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = -30; i <= 30; i += 15) {
        glBegin(GL_LINES);
            glVertex2f(i, 0);
            glVertex2f(i + 10, 30);
        glEnd();
    }

    // Head
    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(45, 10); glVertex2f(60, 10);
        glVertex2f(60, 30); glVertex2f(40, 30);
    glEnd();

    // Eye
    glColor3f(0, 0, 0);
    glPointSize(4);
    glBegin(GL_POINTS);
        glVertex2f(55, 25);
    glEnd();

    // Ears
    glBegin(GL_TRIANGLES);
        glVertex2f(43, 30); glVertex2f(46, 40); glVertex2f(49, 30); // Left ear
        glVertex2f(51, 30); glVertex2f(54, 40); glVertex2f(57, 30); // Right ear
    glEnd();

    // Legs
    for (int i = -30; i <= 30; i += 20) {
        glBegin(GL_QUADS);
            glVertex2f(i, -20);
             glVertex2f(i + 15, -20);
            glVertex2f(i + 10, 0);
             glVertex2f(i, 0);

        glEnd();
    }

    // Tail
    glBegin(GL_LINES);
        glVertex2f(-40, 20);
        glVertex2f(-60, -10);
    glEnd();

    glPopMatrix();
}



// Draw skyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
void drawSundarbanSky() {
    glBegin(GL_QUADS);
        if (isNight)
            glColor3f(0.0f, 0.0f, 0.2f); // night dark blue
        else
            glColor3f(0.53f, 0.81f, 0.98f); // day sky blue

        glVertex2f(-width/2, -height/2);
        glVertex2f(width/2, -height/2);
        glVertex2f(width/2, height/2);
        glVertex2f(-width/2, height/2);
    glEnd();
}


// Draw riverrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
void drawSundarbanRiver() {
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.4f, 0.8f);
        glVertex2f(-width/2, -height/2 + 20);
        glVertex2f(width/2, -height/2 + 20);
        glVertex2f(width/2, -height/3 + 60);
        glVertex2f(-width/2, -height/3 + 60);
    glEnd();
}

// Draw soilllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll
void drawSundarbanSoil() {
    glBegin(GL_QUADS);
        glColor3f(0.55f, 0.27f, 0.07f);
        glVertex2f(-width/2, -height/3 + 60);
        glVertex2f(width/2, -height/3 + 60);
        glVertex2f(width/2, -height/4 + 60);
        glVertex2f(-width/2, -height/4 + 60);
    glEnd();
}

// Recursive branch drawingggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg
void drawSundarbanBranch(float x1, float y1, float angle, float length, float thickness) {
    float x2 = x1 + length * cos(angle);
    float y2 = y1 + length * sin(angle);

    glColor3f(0.36f, 0.25f, 0.20f);
    glLineWidth(thickness);
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

    if (length > 5) {
        if (length < 20) {
            glColor3f(0.0f, 0.6f, 0.0f);
            glPointSize(4);
            glBegin(GL_POINTS);
                glVertex2f(x2, y2);
            glEnd();
        }

        drawSundarbanBranch(x2, y2, angle - 0.3f, length * 0.7f, thickness * 0.7f);
        drawSundarbanBranch(x2, y2, angle + 0.3f, length * 0.7f, thickness * 0.7f);
    }
}

// Tree 1-4 (recursive)
void drawSundarbanTree(float xOffset) {
    glPushMatrix();
    glTranslatef(xOffset, -height / 4 + 60, 0.0f);
    drawSundarbanBranch(0, 0, 1.57f, 120, 10);
    glPopMatrix();
}

// Draw Mango tree (big, leafy)mangooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
void drawSundarbanMangoTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Trunk
    glColor3f(0.36f, 0.25f, 0.20f);
    glLineWidth(7);
    glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(0, 150);
    glEnd();

    // Leaves
    glColor3f(0.0f, 0.5f, 0.0f);
    for (int i = 0; i < 5; i++) {
        float angle = i * 2 * 3.1416f / 5;
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0, 150); // center top  trunk
            for (int j = 0; j <= 20; j++) {
                float theta = j * 3.1416f / 20;
                float xLeaf = cos(theta) * 40 * (1 - j/20.0f) * 0.8f + cos(angle) * 50;
                float yLeaf = sin(theta) * 40 * (1 - j/20.0f) * 0.8f + sin(angle) * 50 + 150;
                glVertex2f(xLeaf, yLeaf);
            }
        glEnd();
    }

    glPopMatrix();
}


//mangroveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanMangrove(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    // Trunk
    glColor3f(0.36f, 0.25f, 0.20f);
    glLineWidth(6);
    glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(0, 70);
    glEnd();

    // Prop roots
    glLineWidth(3);
    for (int i = -3; i <= 3; i++) {
        if(i == 0) continue;
        glBegin(GL_LINES);
            glVertex2f(0, 10);
            glVertex2f(i * 10, -10);
        glEnd();
    }

    // Branches & leaves
    glColor3f(0.0f, 0.5f, 0.0f);
    for (int i = 0; i < 3; i++) {
        glBegin(GL_TRIANGLES);
            glVertex2f(0, 70 - i*15);
            glVertex2f(-15, 50 - i*15);
            glVertex2f(15, 50 - i*15);
        glEnd();
    }

    glPopMatrix();
}




void drawSundarbanBamboo(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(0.0f, 0.6f, 0.1f);
    glLineWidth(5);

    // Bamboo stalk
    for (int i = -1; i <= 1; i++) {
        glBegin(GL_LINES);
            glVertex2f(i * 7, 0);
            glVertex2f(i * 7, 80);
        glEnd();

        // Bamboo nodes
        glLineWidth(3);
        for (int j = 0; j < 5; j++) {
            glBegin(GL_LINES);
                glVertex2f(i * 7 - 5, j * 15 + 5);
                glVertex2f(i * 7 + 5, j * 15 + 5);
            glEnd();
        }
        glLineWidth(5);
    }

    // Leaves
    glColor3f(0.0f, 0.8f, 0.0f);
    for (int i = 0; i < 3; i++) {
        glBegin(GL_POLYGON);
            glVertex2f(10, 60 + i * 5);
            glVertex2f(40, 70 + i * 10);
            glVertex2f(10, 80 + i * 5);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(-10, 60 + i * 5);
            glVertex2f(-40, 70 + i * 10);
            glVertex2f(-10, 80 + i * 5);
        glEnd();
    }

    glPopMatrix();
}


// Draw Palm treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanPalmTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Trunk
    glColor3f(0.36f, 0.25f, 0.20f);
    glLineWidth(6);
    glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(0, 200);
    glEnd();

    // Leaves
    glColor3f(0.0f, 0.7f, 0.0f);
    glLineWidth(3);
    for (int i = 0; i < 5; i++) {
        float offsetY = 180 + i * 8;
        float spread = 50 - i * 8;
        glBegin(GL_LINES);
            // Left leaf
            glVertex2f(0, offsetY);
            glVertex2f(-spread, offsetY + 40);

            // Right leaf
            glVertex2f(0, offsetY);
            glVertex2f(spread, offsetY + 40);
        glEnd();
    }

    glPopMatrix();
}



/ Draw boatttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
void drawSundarbanBoat(float x, float y) {
glPushMatrix();
glTranslatef(x, y, 0.0f);
glColor3f(0.3f, 0.1f, 0.0f);
glBegin(GL_POLYGON);
glVertex2f(-70, 0);
glVertex2f(60, 0);
glVertex2f(20, -10);
glVertex2f(-20, -10);
glEnd();
glColor3f(1.0f, 0.0f, 1.0f);
glBegin(GL_QUADS);
glVertex2f(-25, 0);
glVertex2f(20, 0);
glVertex2f(10, 10);
glVertex2f(-10, 10);
glEnd();
glPopMatrix();
}
// Draw
cloudddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
void drawSundarbanCloud(float x, float y) {
glPushMatrix();
glTranslatef(x, y, 0.0f);
glColor3f(1.0f, 1.0f, 1.0f);
for (int i = 0; i < 3; i++) {
glBegin(GL_POLYGON);
for (int j = 0; j < 100; j++) {
float theta = 2.0f * 3.1416f * j / 100;
float dx = 30 * cosf(theta);
float dy = 30 * sinf(theta);
glVertex2f(dx + i * 30, dy);
}
glEnd();
}
glPopMatrix();
}
// Draw
sunnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
void drawSundarbanSun() {
if (isNight) return; // rat hole sun thakbe na
float sunX = width/2 - 150;
float sunY = height/2 - 100;
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(sunX, sunY);
for (int i = 0; i <= 100; i++) {
float angle = 2.0f * 3.1416f * i / 100;
float x = sunX + cos(angle) * 50;
float y = sunY + sin(angle) * 50;
glVertex2f(x, y);
}
glEnd();
glColor3f(1.0f, 0.4f, 0.4f);
glLineWidth(3);
glBegin(GL_LINES);
for (int i = 0; i < 12; i++) {
float angle = i * 3.1416f / 6;
float x1 = sunX + cos(angle) * 55;
float y1 = sunY + sin(angle) * 55;
float x2 = sunX + cos(angle) * 80;
float y2 = sunY + sin(angle) * 80;
glVertex2f(x1, y1);
glVertex2f(x2, y2);
}
glEnd();
}
// moon night
void drawSundarbanMoon() {
if (!isNight) return;
float moonX = width/2 - 150;
float moonY = height/2 - 100;
glColor3f(1.0f, 1.0f, 0.9f); // light yellowish moon
glBegin(GL_TRIANGLE_FAN);
glVertex2f(moonX, moonY);
for (int i = 0; i <= 100; i++) {
float angle = 2.0f * 3.1416f * i / 100;
float x = moonX + cos(angle) * 40;
float y = moonY + sin(angle) * 40;
glVertex2f(x, y);
}
glEnd();
}
//rain
void drawSundarbanRain() {
if (!isRain) return;
glColor3f(0.7f, 0.7f, 1.0f); // bristy color
glLineWidth(1.5);
glBegin(GL_LINES);
for (int i = 0; i < RAIN_DROPS; i++) {
glVertex2f(rainX[i], rainY[i]);
glVertex2f(rainX[i], rainY[i] - 10);
}
glEnd();
}
// Draw coconut
treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanCoconutTree(float x, float y) {
glPushMatrix();
glTranslatef(x, y, 0.0f);
glColor3f(0.36f, 0.25f, 0.20f); // trunk color
glLineWidth(5);
glBegin(GL_LINES);
glVertex2f(0, 0);
glVertex2f(0, 200); // tall trunk
glEnd();
// Leaves
glColor3f(0.0f, 0.8f, 0.0f);
glLineWidth(2);
for (int i = 0; i < 5; i++) {
float offset = i * 8;
glBegin(GL_LINES);
glVertex2f(0, 200);
glVertex2f(-50 + offset, 240); // left
glVertex2f(0, 200);
glVertex2f(50 - offset, 240); // right
glEnd();
}
glPopMatrix();
}
void updateBirds() {
for (int i = 0; i < BIRD_COUNT; i++) {
birdX[i] -= 2.5;
if (birdX[i] < -width / 2 - 50) {
birdX[i] = width / 2 + rand() % 200;
birdY[i] = (rand() % 80) + height / 4 + 120;
}
}
}
//
Display+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void display() {
glClear(GL_COLOR_BUFFER_BIT);
drawSundarbanSky();
drawSundarbanRiver();
drawSundarbanSoil();
// Old big trees
drawSundarbanTree(-300);
drawSundarbanTree(-100);
drawSundarbanTree(100);
drawSundarbanTree(300);
// Coconut trees
drawSundarbanCoconutTree(-200, -height / 4 + 60);
drawSundarbanCoconutTree(200, -height / 4 + 60);
//snake
drawSundarbanSnake(snakeX, snakeY, timeValue);
//Boat
drawSundarbanBoat(boatX1, -height / 2 + 40);
drawSundarbanBoat(boatX2, -height / 2 + 60);
drawSundarbanBoat(boatX3, -height / 2 + 80);
drawSundarbanBoat(boatX4, -height / 2 + 100);
// cloud
drawSundarbanCloud(cloudX1, 360);
drawSundarbanCloud(cloudX2, 380);
drawSundarbanCloud(cloudX3, 340);
// Draw some simple trees
drawSundarbanSimpleTree(-720, -height / 4 + 60);
drawSundarbanSimpleTree(720, -height / 4 + 60);
drawSundarbanSimpleTree(600, -height / 4 + 60);
drawSundarbanSimpleTree(30, -height / 4 + 60);
// round tree
drawSundarbanRoundLeafTree(660, -height / 4 + 60);
// mango tree
drawSundarbanMangoTree(-450, -height / 4 + 60);
drawSundarbanMangoTree(350, -height / 4 + 60);
//plam tree
drawSundarbanPalmTree(-550, -height / 4 + 60);
drawSundarbanPalmTree(450, -height / 4 + 60);
// mango tree
drawSundarbanMangrove(-350, -height / 4 + 60);
drawSundarbanMangrove(-300, -height / 4 + 65);
//bamboo tree
drawSundarbanBamboo(-490, -height / 4 + 60);
drawSundarbanBamboo(380, -height / 4 + 55);
// tiger
drawSundarbanTiger(tigerX, -height / 4 + 80);
// 3 deer side by side
float deerY = (-height / 4 + 50) + 30;
drawSundarbanDeer(deerX, deerY); // 1st deer
drawSundarbanDeer(deerX + 70, deerY); // 2nd deer
drawSundarbanDeer(deerX + 140, deerY); // 3rd deer
glutSwapBuffers();
// nodir dharer tree
drawSundarbanCoconutTree(-650, -height / 50 -190);
drawSundarbanSimpleTree(-610, -height / 50 -190);
drawSundarbanSimpleTree(-420, -height / 50 -190);
drawSundarbanSimpleTree(510, -height / 50 -190);
// tree 123456
drawSundarbanTree1(-170, -150);
drawSundarbanTree2(-60, -150);
drawSundarbanTree3(-250, -180);
drawSundarbanTree3(-270, -180);
drawSundarbanTree3(250, -180);
drawSundarbanTree3(270, -180);
drawSundarbanTree5(60, -190);
drawSundarbanTree8(420, -190);
// sun
drawSundarbanSun();
drawSundarbanMoon();
//birds
drawSundarbanAllBirds();
//rain
drawSundarbanRain();
glFlush();
}
//********************************************************************************************************************
//handlekeypress
void handleKeypress(unsigned char key, int x, int y) {
if (key == 'n' || key == 'N') {
isNight = true;
}
if (key == 'd' || key == 'D') {
isNight = false;
}
if (key == 'r' || key == 'R') {
isRain = !isRain;
}
glutPostRedisplay(); // Redraw screen
}
//
Update+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void update(int value) {
boatX1 -= 2;
boatX2 -= 1.5;
boatX3 -= 1.8;
boatX4 -= 1.2;
if (boatX1 < -width / 2 - 50) boatX1 = width / 2 + 50;
if (boatX2 < -width / 2 - 50) boatX2 = width / 2 + 100;
if (boatX3 < -width / 2 - 50) boatX3 = width / 2 + 150;
if (boatX4 < -width / 2 - 50) boatX4 = width / 2 + 200;
// cloud
cloudX1 -= 1.0;
cloudX2 -= 0.8;
cloudX3 -= 0.9;
if (cloudX1 < -width/2 - 90) cloudX1 = width/2 + 60;
if (cloudX2 < -width/2 - 90) cloudX2 = width/2 + 100;
if (cloudX3 < -width/2 - 90) cloudX3 = width/2 + 160;
//tiger
tigerX += 2.5;
if (tigerX > width / 2 + 100) {
tigerX = -width / 2 - 100;
}
deerX += 4.00f;
// reset when off-screen
if (deerX > width + 100) deerX = -700;
//birds
updateBirds();
//snake
snakeX += 3.0f; // bam theke dan jabe
if (snakeX > width / 4 + 300)
snakeX = -width / 2 - 300;
timeValue += 0.3f;
//rain
if (isRain) {
for (int i = 0; i < RAIN_DROPS; i++) {
rainY[i] -= 5;
if (rainY[i] < -height/2) {
rainY[i] = height/2;
rainX[i] = rand() % width - width/2;
}
}
}
glutPostRedisplay();
glutTimerFunc(30, update, 0);
}
// Reshape
void reshape(int w, int h) {
width = w;
height = h;
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-w/2, w/2, -h/2, h/2, -1, 1);
glMatrixMode(GL_MODELVIEW);
}
//rain
void initRain() {
for (int i = 0; i < RAIN_DROPS; i++) 
{
rainX[i] = rand() % width - width / 2;
rainY[i] = rand() % height - height / 2;
}
}



// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Sundarban project  AIUB");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutKeyboardFunc(handleKeypress);
    initRain();

    initBirds();

    glutMainLoop();
    return 0;
}
