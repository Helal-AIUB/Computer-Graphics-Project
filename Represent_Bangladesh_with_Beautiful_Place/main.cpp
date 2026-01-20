#include <GL/glut.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <cmath>
//#define PI 3.1415926535898
float cloudX = 0.0f;
float rotorAngle = 0.0f;
float heliX = 0.0f;   //left
float heliY = 0.0f;   //bottom
bool movingUp = true;  //vertical first.
// Movement variables
float planeX = -2.00f;
float cloudOffsetX = 0.0f;
float bus = 3.0f;
float bus2 = -2.5f;
float cargo = 1.0f;

float trainPosX = 3.0f; // Starting X position (off-screen)
bool isYellow = false;
bool isDay = true;  // true = day, false = night
bool changeColor = false;



 //Scenario : Sundarban


//night
bool isNight_Sundarban = false;

//rain

bool isRain_Sundarban = false;
const int RAIN_DROPS = 300;
float rainX[RAIN_DROPS], rainY[RAIN_DROPS];



// Window dimensions
int width_S = 1000;
int height_S = 600;

// Boat positions
float boatX1 = 500, boatX2 = 700, boatX3 = 900, boatX4 = 1100;

// Cloud positions
float cloudX1_S = 400, cloudX2 = 700, cloudX3 = 1000;

// Tiger position
float tigerX = -600;

// Deer position
float deerX = -600;



// snake

float snakeX = -width_S / 2 - 300;  // sanake bam theke cholbe
float snakeY = -height_S / 4 - 100; // snake river position

const int numSegments_S = 15;
const float segmentLength_S = 7.0f;
const float bodyRadius_S = 4.0f;

float waveAmplitude_S = 7.0f;
float waveFrequency = 0.4f;
float timeValue_S = 0.0f;


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



// snakeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee

void drawSundarbanSnake(float baseX, float baseY, float time) {
    glPushMatrix();
    glTranslatef(baseX, baseY, 0.0f);
    glColor3f(0.0f, 0.7f, 0.0f);


    for (int i = 0; i < numSegments_S; i++) {
        float x = i * segmentLength_S;
        float y = waveAmplitude_S * sin(waveFrequency * i + time);

        drawSundarbanCircle(x, y, bodyRadius_S, 40);
    }

    // Head
    glColor3f(0.0f, 0.9f, 0.0f);
    float headY_S = waveAmplitude_S * sin(time);
    drawSundarbanCircle(numSegments_S * segmentLength_S, headY_S, bodyRadius_S * 2.0f, 50);

    // Eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawSundarbanCircle(numSegments_S * segmentLength_S + 7, headY_S + 5, 2, 20);
    drawSundarbanCircle(numSegments_S * segmentLength_S + 7, headY_S - 5, 2, 20);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawSundarbanCircle(numSegments_S * segmentLength_S + 7, headY_S + 5, 1, 20);
    drawSundarbanCircle(numSegments_S * segmentLength_S + 7, headY_S - 5, 1, 20);

    // Tongue
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(numSegments_S * segmentLength_S + 18, headY_S);
        glVertex2f(numSegments_S * segmentLength_S + 28, headY_S + 5);
        glVertex2f(numSegments_S * segmentLength_S + 18, headY_S);
        glVertex2f(numSegments_S * segmentLength_S + 28, headY_S - 5);
    glEnd();

    glPopMatrix();
}








// Tree 1: Simple triangle treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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




// Tree 2: Round top treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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



// Tree 3: Palm treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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



// Tree 5: Bushy treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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




// Tree 8: Mango Treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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






//birdsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
const int BIRD_COUNT = 10;
float birdX[BIRD_COUNT];
float birdY[BIRD_COUNT];

void initBirds() {
    for (int i = 0; i < BIRD_COUNT; i++) {
        birdX[i] = width_S / 2 + i * 100;
        birdY[i] = (rand() % 80) + height_S / 4 + 120;
    }
}




//birdsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
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







// round treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanRoundLeafTree(float x, float y){
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



// Draw simple treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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





// draw a simple leg deerrrrrrrrrrrrrrrrrrrrrrrrrrrrr
void drawSundarbanLeg(float x, float y) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 10, y - 30);
    glVertex2f(x, y - 30);
    glEnd();
}

//draw deer antlerssssssssssssssssssssssssssssssssssss
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

// Draw the deerrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
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
    glColor3f(0.3f, 0.2f, 0.1f);
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


// Tigerrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
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
        glVertex2f(43, 30); glVertex2f(46, 40); glVertex2f(49, 30);
        glVertex2f(51, 30); glVertex2f(54, 40); glVertex2f(57, 30);
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



// Draw skyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
void drawSundarbanSky() {
    glBegin(GL_QUADS);
        if (isNight_Sundarban)
            glColor3f(0.0f, 0.0f, 0.2f); // night dark blue
        else
            glColor3f(0.53f, 0.81f, 0.98f); // day sky blue

        glVertex2f(-width_S/2, -height_S/2);
        glVertex2f(width_S/2, -height_S/2);
        glVertex2f(width_S/2, height_S/2);
        glVertex2f(-width_S/2, height_S/2);
    glEnd();
}


// Draw riverrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
void drawSundarbanRiver() {
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.4f, 0.8f);
        glVertex2f(-width_S/2, -height_S/2 + 20);
        glVertex2f(width_S/2, -height_S/2 + 20);
        glVertex2f(width_S/2, -height_S/3 + 60);
        glVertex2f(-width_S/2, -height_S/3 + 60);
    glEnd();
}

// Draw soillllllllllllllllllllllllllllllllllllllllll
void drawSundarbanSoil() {
    glBegin(GL_QUADS);
        glColor3f(0.55f, 0.27f, 0.07f);
        glVertex2f(-width_S/2, -height_S/3 + 60);
        glVertex2f(width_S/2, -height_S/3 + 60);
        glVertex2f(width_S/2, -height_S/4 + 60);
        glVertex2f(-width_S/2, -height_S/4 + 60);
    glEnd();
}


// Recursive branch drawinggggggggggggggggggggggggggggggg
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
    glTranslatef(xOffset, -height_S / 4 + 60, 0.0f);
    drawSundarbanBranch(0, 0, 1.57f, 120, 10);
    glPopMatrix();
}

// Draw Mango tree (big, leafy)mangooooooooooooooooooooooooooo
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


//mangroveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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



// draw bamboo treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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


// Draw Palm treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
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


// Draw boatttttttttttttttttttttttttttttttttttttttttttttttt
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


// Draw cloudddddddddddddddddddddddddddddddddddddddddddddd
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


// Draw sunnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
void drawSundarbanSun() {

    if (isNight_Sundarban) return;  // rat hole sun thakbe na

    float sunX = width_S/2 - 150;
    float sunY = height_S/2 - 100;

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


// draw moon nightttttttttttttttttttttttttttttttttttt
void drawSundarbanMoon() {
    if (!isNight_Sundarban) return;

    float moonX = width_S/2 - 150;
    float moonY = height_S/2 - 100;

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


// draw rainnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn

void drawSundarbanRain() {
    if (!isRain_Sundarban) return;

    glColor3f(0.7f, 0.7f, 1.0f);  // bristy  color
    glLineWidth(1.5);

    glBegin(GL_LINES);
    for (int i = 0; i < RAIN_DROPS; i++) {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i], rainY[i] - 10);
    }
    glEnd();
}



// Draw coconut treeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void drawSundarbanCoconutTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.36f, 0.25f, 0.20f);  // trunk color
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(0, 200);  // tall trunk
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
            glVertex2f(50 - offset, 240);  // right
        glEnd();
    }

    glPopMatrix();
}



//birds update
void updateBirds() {
    for (int i = 0; i < BIRD_COUNT; i++) {
        birdX[i] -= 2.5;
        if (birdX[i] < -width_S / 2 - 50) {
            birdX[i] = width_S / 2 + rand() % 200;
            birdY[i] = (rand() % 80) + height_S / 4 + 120;
        }
    }
}



// Display++++++++++++++++++++++++++++++++++++++++++
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& DISPLAY
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

//sky
    drawSundarbanSky();
//river
    drawSundarbanRiver();
//spil
    drawSundarbanSoil();

// Old big trees
    drawSundarbanTree(-300);
    drawSundarbanTree(-100);
    drawSundarbanTree(-750);
    drawSundarbanTree(300);
    drawSundarbanTree(100);
    drawSundarbanTree(750);






// Coconut trees
    drawSundarbanCoconutTree(-200, -height_S / 4 + 60);
    drawSundarbanCoconutTree(200, -height_S / 4 + 60);


//snake
    drawSundarbanSnake(snakeX, snakeY, timeValue_S);


//Boat
    drawSundarbanBoat(boatX1, -height_S / 2 + 40);
    drawSundarbanBoat(boatX2, -height_S / 2 + 60);
    drawSundarbanBoat(boatX3, -height_S / 2 + 80);
    drawSundarbanBoat(boatX4, -height_S / 2 + 100);

// cloud
    drawSundarbanCloud(cloudX1_S, 360);
    drawSundarbanCloud(cloudX2, 380);
    drawSundarbanCloud(cloudX3, 340);



// Draw traingl 3 tree
    drawSundarbanSimpleTree(-720, -height_S / 4 + 60);
    drawSundarbanSimpleTree(720, -height_S / 4 + 60);
    drawSundarbanSimpleTree(600, -height_S / 4 + 60);
    drawSundarbanSimpleTree(30, -height_S / 4 + 60);


// round tree
drawSundarbanRoundLeafTree(660, -height_S / 4 + 60);



// mango tree
drawSundarbanMangoTree(-450, -height_S / 4 + 60);
drawSundarbanMangoTree(350, -height_S / 4 + 60);


//plam tree

        drawSundarbanPalmTree(-550, -height_S / 4 +70);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 65);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 90);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 75);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 80);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 85);
        drawSundarbanPalmTree(-550, -height_S / 4 +73);
        drawSundarbanPalmTree(-550, -height_S / 4 + 60);




        drawSundarbanPalmTree(450, -height_S / 4 + 60);
        drawSundarbanPalmTree(450, -height_S / 4 +70);
        drawSundarbanCoconutTree(450, -height_S / 4 + 65);
        drawSundarbanCoconutTree(450, -height_S / 4 + 90);
        drawSundarbanCoconutTree(450, -height_S / 4 + 75);
        drawSundarbanCoconutTree(450, -height_S / 4 + 80);
        drawSundarbanCoconutTree(450, -height_S / 4 + 85);
        drawSundarbanPalmTree(450, -height_S / 4 +73);
        drawSundarbanPalmTree(450, -height_S / 4 + 60);







// mango tree
    drawSundarbanMangrove(-350, -height_S / 4 + 60);
    drawSundarbanMangrove(-300, -height_S / 4 + 65);

//bamboo tree
    drawSundarbanBamboo(-490, -height_S / 4 + 60);
    drawSundarbanBamboo(380, -height_S / 4 + 55);

// tiger
    drawSundarbanTiger(tigerX, -height_S / 4 + 80);


// 3 deer side by side
    float deerY = (-height_S / 4 + 50) + 30;
    drawSundarbanDeer(deerX, deerY);               // 1st deer
    drawSundarbanDeer(deerX + 70, deerY);          // 2nd deer
    drawSundarbanDeer(deerX + 140, deerY);         // 3rd deer
    glutSwapBuffers();


// down river side tree
//traingl 3 tree
    drawSundarbanSimpleTree(-610, -height_S / 50 -190);
    drawSundarbanSimpleTree(-420, -height_S / 50 -190);
    drawSundarbanSimpleTree(510, -height_S / 50 -190);





// tree 123456
         drawSundarbanTree1(-170, -150);

         drawSundarbanTree2(+120, -150);
         drawSundarbanTree2(-60, -150);


         drawSundarbanTree3(-250, -180);
         drawSundarbanTree3(-270, -180);

         drawSundarbanTree3(-370, -150);
         drawSundarbanTree3(-370, -155);
         drawSundarbanTree3(-370, -160);
         drawSundarbanTree3(-370, -165);
         drawSundarbanTree3(-370, -170);

         drawSundarbanTree3(+170, -150);
         drawSundarbanTree3(+170, -155);
         drawSundarbanTree3(+170, -160);
         drawSundarbanTree3(+170, -165);
         drawSundarbanTree3(+170, -170);

         drawSundarbanTree3(250, -180);
         drawSundarbanTree3(270, -180);




         drawSundarbanTree5(60, -190);

         drawSundarbanTree8(420, -190);

         //down tree 1 lot off tree
        drawSundarbanPalmTree(550, -height_S / 4 +20);
        drawSundarbanCoconutTree(550, -height_S / 4 + 15);
        drawSundarbanCoconutTree(550, -height_S / 4 + 10);
        drawSundarbanCoconutTree(550, -height_S / 4 + 5);
        drawSundarbanCoconutTree(550, -height_S / 4 + 0);
        drawSundarbanCoconutTree(550, -height_S / 4 + 25);
        drawSundarbanPalmTree(550, -height_S / 4 -2);


        drawSundarbanCoconutTree(-650, -height_S / 50 -190);




        drawSundarbanPalmTree(-550, -height_S / 4 +20);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 15);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 10);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 5);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 0);
        drawSundarbanCoconutTree(-550, -height_S / 4 + 25);
        drawSundarbanPalmTree(-550, -height_S / 4 -2);









// sun
      drawSundarbanSun();

      drawSundarbanMoon();

//birds
      drawSundarbanAllBirds();

//rain
      drawSundarbanRain();



    glFlush();
}

//********************************************************************************
//handlekeypress

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 'n' || key == 'N') {
        isNight_Sundarban = true;
    }
    if (key == 'd' || key == 'D') {
        isNight_Sundarban = false;
    }

    if (key == 'r' || key == 'R') {
        isRain_Sundarban = !isRain_Sundarban;
    }


    glutPostRedisplay(); // Redraw screen
}



// Update+++++++++++++++++++++++++++++++++++++++++++++++++++++++
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% UPDATE
void update_S(int value) {

    //boat
    boatX1 -= 2;
    boatX2 -= 1.5;
    boatX3 -= 1.8;
    boatX4 -= 1.2;

    if (boatX1 < -width_S / 2 - 50) boatX1 = width_S / 2 + 50;
    if (boatX2 < -width_S / 2 - 50) boatX2 = width_S / 2 + 100;
    if (boatX3 < -width_S / 2 - 50) boatX3 = width_S / 2 + 150;
    if (boatX4 < -width_S / 2 - 50) boatX4 = width_S / 2 + 200;

// cloud
    cloudX1_S -= 1.0;
    cloudX2 -= 0.8;
    cloudX3 -= 0.9;

    if (cloudX1_S < -width_S/2 - 90) cloudX1_S = width_S/2 + 60;
    if (cloudX2 < -width_S/2 - 90) cloudX2 = width_S/2 + 100;
    if (cloudX3 < -width_S/2 - 90) cloudX3 = width_S/2 + 160;



//tiger
      tigerX += 2.5;
     if (tigerX > width_S / 2 + 100) {
        tigerX = -width_S / 2 - 100;
     }


     deerX += 4.00f;

// reset when off-screen
    if (deerX > width_S + 100) deerX = -700;

//birds
      updateBirds();

//snake
     snakeX += 3.0f;  // bam theke dan jabe

    if (snakeX > width_S / 4 + 300)
        snakeX = -width_S / 2 - 300;

    timeValue_S += 0.3f;


//rain

    if (isRain_Sundarban) {
    for (int i = 0; i < RAIN_DROPS; i++) {
        rainY[i] -= 5;
        if (rainY[i] < -height_S/2) {
            rainY[i] = height_S/2;
            rainX[i] = rand() % width_S - width_S/2;
        }
    }
}



    glutPostRedisplay();
    glutTimerFunc(30, update_S, 0);
}







// Reshape
void reshape_S(int w, int h) {
    width_S = w;
    height_S = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

//rain
void initRain() {
    for (int i = 0; i < RAIN_DROPS; i++) {
        rainX[i] = rand() % width_S - width_S / 2;
        rainY[i] = rand() % height_S - height_S / 2;
    }
}





































// Map :







void display_2() {

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Bangladesh Total Map
    glBegin(GL_LINE_LOOP);
    glColor3f(0.2f, 0.8f, 0.3f);
    glVertex2f(-0.413462f, 0.901709f);
    glVertex2f(-0.413462f, 0.897436f);
    glVertex2f(-0.416667f, 0.893162f);
    glVertex2f(-0.416667f, 0.888889f);
    glVertex2f(-0.419872f, 0.884615f);
    glVertex2f(-0.419872f, 0.880342f);
    glVertex2f(-0.419872f, 0.876068f);
    glVertex2f(-0.423077f, 0.871795f);
    glVertex2f(-0.423077f, 0.867521f);
    glVertex2f(-0.426282f, 0.863248f);
    glVertex2f(-0.426282f, 0.858974f);
    glVertex2f(-0.426282f, 0.854701f);
    glVertex2f(-0.426282f, 0.850427f);
    glVertex2f(-0.423077f, 0.846154f);
    glVertex2f(-0.419872f, 0.846154f);
    glVertex2f(-0.419872f, 0.850427f);
    glVertex2f(-0.419872f, 0.854701f);
    glVertex2f(-0.416667f, 0.858974f);
    glVertex2f(-0.413462f, 0.854701f);
    glVertex2f(-0.410256f, 0.854701f);
    glVertex2f(-0.407051f, 0.854701f);
    glVertex2f(-0.403846f, 0.854701f);
    glVertex2f(-0.400641f, 0.850427f);
    glVertex2f(-0.397436f, 0.850427f);
    glVertex2f(-0.394231f, 0.846154f);
    glVertex2f(-0.394231f, 0.841880f);
    glVertex2f(-0.391026f, 0.837607f);
    glVertex2f(-0.391026f, 0.833333f);
    glVertex2f(-0.387821f, 0.829060f);
    glVertex2f(-0.387821f, 0.824786f);
    glVertex2f(-0.391026f, 0.820513f);
    glVertex2f(-0.394231f, 0.820513f);
    glVertex2f(-0.397436f, 0.820513f);
    glVertex2f(-0.400641f, 0.820513f);
    glVertex2f(-0.403846f, 0.820513f);
    glVertex2f(-0.403846f, 0.816239f);
    glVertex2f(-0.407051f, 0.811966f);
    glVertex2f(-0.410256f, 0.811966f);
    glVertex2f(-0.413462f, 0.807692f);
    glVertex2f(-0.416667f, 0.803419f);
    glVertex2f(-0.419872f, 0.799145f);
    glVertex2f(-0.419872f, 0.794872f);
    glVertex2f(-0.423077f, 0.790598f);
    glVertex2f(-0.423077f, 0.786325f);
    glVertex2f(-0.423077f, 0.782051f);
    glVertex2f(-0.423077f, 0.777778f);
    glVertex2f(-0.426282f, 0.773504f);
    glVertex2f(-0.429487f, 0.773504f);
    glVertex2f(-0.432692f, 0.769231f);
    glVertex2f(-0.435897f, 0.769231f);
    glVertex2f(-0.439103f, 0.769231f);
    glVertex2f(-0.442308f, 0.764957f);
    glVertex2f(-0.445513f, 0.764957f);
    glVertex2f(-0.448718f, 0.760684f);
    glVertex2f(-0.451923f, 0.756410f);
    glVertex2f(-0.455128f, 0.756410f);
    glVertex2f(-0.458333f, 0.752137f);
    glVertex2f(-0.458333f, 0.747863f);
    glVertex2f(-0.461538f, 0.743590f);
    glVertex2f(-0.461538f, 0.739316f);
    glVertex2f(-0.461538f, 0.735043f);
    glVertex2f(-0.461538f, 0.730769f);
    glVertex2f(-0.461538f, 0.726496f);
    glVertex2f(-0.458333f, 0.722222f);
    glVertex2f(-0.461538f, 0.717949f);
    glVertex2f(-0.464744f, 0.713675f);
    glVertex2f(-0.467949f, 0.709402f);
    glVertex2f(-0.467949f, 0.705128f);
    glVertex2f(-0.471154f, 0.700855f);
    glVertex2f(-0.471154f, 0.696581f);
    glVertex2f(-0.471154f, 0.692308f);
    glVertex2f(-0.471154f, 0.688034f);
    glVertex2f(-0.474359f, 0.683761f);
    glVertex2f(-0.477564f, 0.679487f);
    glVertex2f(-0.474359f, 0.675214f);
    glVertex2f(-0.474359f, 0.670940f);
    glVertex2f(-0.474359f, 0.666667f);
    glVertex2f(-0.474359f, 0.662393f);
    glVertex2f(-0.474359f, 0.658120f);
    glVertex2f(-0.474359f, 0.653846f);
    glVertex2f(-0.471154f, 0.649573f);
    glVertex2f(-0.467949f, 0.645299f);
    glVertex2f(-0.467949f, 0.641026f);
    glVertex2f(-0.464744f, 0.636752f);
    glVertex2f(-0.461538f, 0.636752f);
    glVertex2f(-0.458333f, 0.636752f);
    glVertex2f(-0.455128f, 0.641026f);
    glVertex2f(-0.451923f, 0.641026f);
    glVertex2f(-0.448718f, 0.645299f);
    glVertex2f(-0.445513f, 0.645299f);
    glVertex2f(-0.442308f, 0.645299f);
    glVertex2f(-0.439103f, 0.641026f);
    glVertex2f(-0.435897f, 0.636752f);
    glVertex2f(-0.432692f, 0.632479f);
    glVertex2f(-0.429487f, 0.628205f);
    glVertex2f(-0.426282f, 0.623932f);
    glVertex2f(-0.423077f, 0.619658f);
    glVertex2f(-0.419872f, 0.615385f);
    glVertex2f(-0.416667f, 0.611111f);
    glVertex2f(-0.413462f, 0.611111f);
    glVertex2f(-0.410256f, 0.606838f);
    glVertex2f(-0.407051f, 0.602564f);
    glVertex2f(-0.403846f, 0.598291f);
    glVertex2f(-0.403846f, 0.594017f);
    glVertex2f(-0.403846f, 0.589744f);
    glVertex2f(-0.403846f, 0.585470f);
    glVertex2f(-0.403846f, 0.581197f);
    glVertex2f(-0.400641f, 0.576923f);
    glVertex2f(-0.397436f, 0.572650f);
    glVertex2f(-0.394231f, 0.572650f);
    glVertex2f(-0.391026f, 0.568376f);
    glVertex2f(-0.391026f, 0.564103f);
    glVertex2f(-0.387821f, 0.559829f);
    glVertex2f(-0.384615f, 0.555556f);
    glVertex2f(-0.381410f, 0.551282f);
    glVertex2f(-0.378205f, 0.551282f);
    glVertex2f(-0.375000f, 0.551282f);
    glVertex2f(-0.371795f, 0.551282f);
    glVertex2f(-0.368590f, 0.551282f);
    glVertex2f(-0.365385f, 0.547009f);
    glVertex2f(-0.362179f, 0.547009f);
    glVertex2f(-0.358974f, 0.542735f);
    glVertex2f(-0.355769f, 0.542735f);
    glVertex2f(-0.352564f, 0.538462f);
    glVertex2f(-0.349359f, 0.538462f);
    glVertex2f(-0.346154f, 0.542735f);
    glVertex2f(-0.342949f, 0.547009f);
    glVertex2f(-0.339744f, 0.547009f);
    glVertex2f(-0.336538f, 0.547009f);
    glVertex2f(-0.333333f, 0.551282f);
    glVertex2f(-0.330128f, 0.551282f);
    glVertex2f(-0.326923f, 0.547009f);
    glVertex2f(-0.323718f, 0.542735f);
    glVertex2f(-0.320513f, 0.538462f);
    glVertex2f(-0.320513f, 0.534188f);
    glVertex2f(-0.320513f, 0.529915f);
    glVertex2f(-0.323718f, 0.525641f);
    glVertex2f(-0.323718f, 0.521368f);
    glVertex2f(-0.323718f, 0.517094f);
    glVertex2f(-0.320513f, 0.512821f);
    glVertex2f(-0.320513f, 0.508547f);
    glVertex2f(-0.317308f, 0.504274f);
    glVertex2f(-0.317308f, 0.500000f);
    glVertex2f(-0.314103f, 0.495726f);
    glVertex2f(-0.310897f, 0.495726f);
    glVertex2f(-0.307692f, 0.495726f);
    glVertex2f(-0.304487f, 0.491453f);
    glVertex2f(-0.301282f, 0.491453f);
    glVertex2f(-0.298077f, 0.491453f);
    glVertex2f(-0.294872f, 0.491453f);
    glVertex2f(-0.291667f, 0.491453f);
    glVertex2f(-0.288462f, 0.491453f);
    glVertex2f(-0.285256f, 0.487179f);
    glVertex2f(-0.285256f, 0.482906f);
    glVertex2f(-0.288462f, 0.478632f);
    glVertex2f(-0.291667f, 0.474359f);
    glVertex2f(-0.294872f, 0.474359f);
    glVertex2f(-0.298077f, 0.470085f);
    glVertex2f(-0.298077f, 0.465812f);
    glVertex2f(-0.298077f, 0.461538f);
    glVertex2f(-0.301282f, 0.457265f);
    glVertex2f(-0.304487f, 0.452991f);
    glVertex2f(-0.307692f, 0.452991f);
    glVertex2f(-0.310897f, 0.452991f);
    glVertex2f(-0.314103f, 0.457265f);
    glVertex2f(-0.317308f, 0.457265f);
    glVertex2f(-0.320513f, 0.457265f);
    glVertex2f(-0.323718f, 0.457265f);
    glVertex2f(-0.323718f, 0.452991f);
    glVertex2f(-0.326923f, 0.448718f);
    glVertex2f(-0.330128f, 0.448718f);
    glVertex2f(-0.333333f, 0.448718f);
    glVertex2f(-0.336538f, 0.448718f);
    glVertex2f(-0.339744f, 0.448718f);
    glVertex2f(-0.342949f, 0.452991f);
    glVertex2f(-0.346154f, 0.452991f);
    glVertex2f(-0.349359f, 0.457265f);
    glVertex2f(-0.352564f, 0.457265f);
    glVertex2f(-0.355769f, 0.457265f);
    glVertex2f(-0.358974f, 0.457265f);
    glVertex2f(-0.362179f, 0.457265f);
    glVertex2f(-0.365385f, 0.457265f);
    glVertex2f(-0.368590f, 0.457265f);
    glVertex2f(-0.371795f, 0.452991f);
    glVertex2f(-0.375000f, 0.452991f);
    glVertex2f(-0.378205f, 0.452991f);
    glVertex2f(-0.381410f, 0.452991f);
    glVertex2f(-0.384615f, 0.457265f);
    glVertex2f(-0.387821f, 0.457265f);
    glVertex2f(-0.391026f, 0.457265f);
    glVertex2f(-0.394231f, 0.457265f);
    glVertex2f(-0.397436f, 0.457265f);
    glVertex2f(-0.400641f, 0.457265f);
    glVertex2f(-0.400641f, 0.452991f);
    glVertex2f(-0.400641f, 0.448718f);
    glVertex2f(-0.400641f, 0.444444f);
    glVertex2f(-0.400641f, 0.440171f);
    glVertex2f(-0.400641f, 0.435897f);
    glVertex2f(-0.400641f, 0.431624f);
    glVertex2f(-0.400641f, 0.427350f);
    glVertex2f(-0.400641f, 0.423077f);
    glVertex2f(-0.400641f, 0.418803f);
    glVertex2f(-0.403846f, 0.414530f);
    glVertex2f(-0.403846f, 0.410256f);
    glVertex2f(-0.403846f, 0.405983f);
    glVertex2f(-0.407051f, 0.401709f);
    glVertex2f(-0.410256f, 0.397436f);
    glVertex2f(-0.410256f, 0.393162f);
    glVertex2f(-0.410256f, 0.388889f);
    glVertex2f(-0.413462f, 0.384615f);
    glVertex2f(-0.413462f, 0.380342f);
    glVertex2f(-0.416667f, 0.376068f);
    glVertex2f(-0.419872f, 0.371795f);
    glVertex2f(-0.419872f, 0.367521f);
    glVertex2f(-0.423077f, 0.363248f);
    glVertex2f(-0.426282f, 0.358974f);
    glVertex2f(-0.429487f, 0.358974f);
    glVertex2f(-0.432692f, 0.358974f);
    glVertex2f(-0.435897f, 0.358974f);
    glVertex2f(-0.439103f, 0.363248f);
    glVertex2f(-0.439103f, 0.367521f);
    glVertex2f(-0.442308f, 0.371795f);
    glVertex2f(-0.442308f, 0.376068f);
    glVertex2f(-0.445513f, 0.380342f);
    glVertex2f(-0.448718f, 0.380342f);
    glVertex2f(-0.451923f, 0.380342f);
    glVertex2f(-0.455128f, 0.380342f);
    glVertex2f(-0.458333f, 0.380342f);
    glVertex2f(-0.461538f, 0.376068f);
    glVertex2f(-0.464744f, 0.376068f);
    glVertex2f(-0.467949f, 0.371795f);
    glVertex2f(-0.467949f, 0.367521f);
    glVertex2f(-0.464744f, 0.363248f);
    glVertex2f(-0.464744f, 0.358974f);
    glVertex2f(-0.464744f, 0.354701f);
    glVertex2f(-0.461538f, 0.350427f);
    glVertex2f(-0.464744f, 0.346154f);
    glVertex2f(-0.467949f, 0.341880f);
    glVertex2f(-0.471154f, 0.337607f);
    glVertex2f(-0.474359f, 0.333333f);
    glVertex2f(-0.474359f, 0.329060f);
    glVertex2f(-0.477564f, 0.324786f);
    glVertex2f(-0.480769f, 0.324786f);
    glVertex2f(-0.480769f, 0.320513f);
    glVertex2f(-0.480769f, 0.316239f);
    glVertex2f(-0.480769f, 0.311966f);
    glVertex2f(-0.483974f, 0.307692f);
    glVertex2f(-0.483974f, 0.303419f);
    glVertex2f(-0.487179f, 0.299145f);
    glVertex2f(-0.487179f, 0.294872f);
    glVertex2f(-0.487179f, 0.290598f);
    glVertex2f(-0.487179f, 0.286325f);
    glVertex2f(-0.483974f, 0.286325f);
    glVertex2f(-0.480769f, 0.282051f);
    glVertex2f(-0.477564f, 0.277778f);
    glVertex2f(-0.474359f, 0.273504f);
    glVertex2f(-0.474359f, 0.269231f);
    glVertex2f(-0.474359f, 0.264957f);
    glVertex2f(-0.474359f, 0.260684f);
    glVertex2f(-0.474359f, 0.256410f);
    glVertex2f(-0.474359f, 0.252137f);
    glVertex2f(-0.471154f, 0.247863f);
    glVertex2f(-0.467949f, 0.243590f);
    glVertex2f(-0.464744f, 0.239316f);
    glVertex2f(-0.461538f, 0.239316f);
    glVertex2f(-0.458333f, 0.239316f);
    glVertex2f(-0.455128f, 0.235043f);
    glVertex2f(-0.451923f, 0.230769f);
    glVertex2f(-0.448718f, 0.230769f);
    glVertex2f(-0.445513f, 0.226496f);
    glVertex2f(-0.442308f, 0.226496f);
    glVertex2f(-0.439103f, 0.222222f);
    glVertex2f(-0.435897f, 0.222222f);
    glVertex2f(-0.432692f, 0.217949f);
    glVertex2f(-0.429487f, 0.217949f);
    glVertex2f(-0.426282f, 0.213675f);
    glVertex2f(-0.423077f, 0.213675f);
    glVertex2f(-0.419872f, 0.209402f);
    glVertex2f(-0.416667f, 0.209402f);
    glVertex2f(-0.413462f, 0.205128f);
    glVertex2f(-0.410256f, 0.205128f);
    glVertex2f(-0.407051f, 0.200855f);
    glVertex2f(-0.403846f, 0.196581f);
    glVertex2f(-0.400641f, 0.192308f);
    glVertex2f(-0.397436f, 0.192308f);
    glVertex2f(-0.394231f, 0.188034f);
    glVertex2f(-0.391026f, 0.183761f);
    glVertex2f(-0.387821f, 0.183761f);
    glVertex2f(-0.384615f, 0.183761f);
    glVertex2f(-0.381410f, 0.183761f);
    glVertex2f(-0.378205f, 0.183761f);
    glVertex2f(-0.375000f, 0.183761f);
    glVertex2f(-0.371795f, 0.183761f);
    glVertex2f(-0.368590f, 0.179487f);
    glVertex2f(-0.365385f, 0.179487f);
    glVertex2f(-0.362179f, 0.179487f);
    glVertex2f(-0.358974f, 0.179487f);
    glVertex2f(-0.355769f, 0.179487f);
    glVertex2f(-0.355769f, 0.183761f);
    glVertex2f(-0.352564f, 0.188034f);
    glVertex2f(-0.349359f, 0.192308f);
    glVertex2f(-0.346154f, 0.188034f);
    glVertex2f(-0.342949f, 0.183761f);
    glVertex2f(-0.339744f, 0.179487f);
    glVertex2f(-0.336538f, 0.175214f);
    glVertex2f(-0.336538f, 0.170940f);
    glVertex2f(-0.336538f, 0.166667f);
    glVertex2f(-0.336538f, 0.162393f);
    glVertex2f(-0.333333f, 0.158120f);
    glVertex2f(-0.336538f, 0.153846f);
    glVertex2f(-0.339744f, 0.149573f);
    glVertex2f(-0.342949f, 0.145299f);
    glVertex2f(-0.346154f, 0.145299f);
    glVertex2f(-0.349359f, 0.141026f);
    glVertex2f(-0.349359f, 0.136752f);
    glVertex2f(-0.349359f, 0.132479f);
    glVertex2f(-0.349359f, 0.128205f);
    glVertex2f(-0.349359f, 0.123932f);
    glVertex2f(-0.349359f, 0.119658f);
    glVertex2f(-0.349359f, 0.115385f);
    glVertex2f(-0.349359f, 0.111111f);
    glVertex2f(-0.346154f, 0.106838f);
    glVertex2f(-0.346154f, 0.102564f);
    glVertex2f(-0.342949f, 0.102564f);
    glVertex2f(-0.339744f, 0.098291f);
    glVertex2f(-0.342949f, 0.094017f);
    glVertex2f(-0.342949f, 0.089744f);
    glVertex2f(-0.342949f, 0.085470f);
    glVertex2f(-0.342949f, 0.081197f);
    glVertex2f(-0.342949f, 0.076923f);
    glVertex2f(-0.342949f, 0.072650f);
    glVertex2f(-0.342949f, 0.068376f);
    glVertex2f(-0.346154f, 0.064103f);
    glVertex2f(-0.349359f, 0.059829f);
    glVertex2f(-0.352564f, 0.055556f);
    glVertex2f(-0.355769f, 0.051282f);
    glVertex2f(-0.358974f, 0.051282f);
    glVertex2f(-0.362179f, 0.051282f);
    glVertex2f(-0.365385f, 0.051282f);
    glVertex2f(-0.368590f, 0.051282f);
    glVertex2f(-0.371795f, 0.047009f);
    glVertex2f(-0.371795f, 0.042735f);
    glVertex2f(-0.371795f, 0.038462f);
    glVertex2f(-0.371795f, 0.034188f);
    glVertex2f(-0.371795f, 0.029915f);
    glVertex2f(-0.375000f, 0.025641f);
    glVertex2f(-0.375000f, 0.021368f);
    glVertex2f(-0.375000f, 0.017094f);
    glVertex2f(-0.375000f, 0.012821f);
    glVertex2f(-0.375000f, 0.008547f);
    glVertex2f(-0.375000f, 0.004274f);
    glVertex2f(-0.375000f, -0.000000f);
    glVertex2f(-0.375000f, -0.004274f);
    glVertex2f(-0.378205f, -0.008547f);
    glVertex2f(-0.378205f, -0.012821f);
    glVertex2f(-0.378205f, -0.017094f);
    glVertex2f(-0.378205f, -0.021368f);
    glVertex2f(-0.375000f, -0.025641f);
    glVertex2f(-0.375000f, -0.029915f);
    glVertex2f(-0.375000f, -0.034188f);
    glVertex2f(-0.371795f, -0.038462f);
    glVertex2f(-0.368590f, -0.038462f);
    glVertex2f(-0.365385f, -0.038462f);
    glVertex2f(-0.362179f, -0.042735f);
    glVertex2f(-0.358974f, -0.047009f);
    glVertex2f(-0.355769f, -0.051282f);
    glVertex2f(-0.355769f, -0.055556f);
    glVertex2f(-0.352564f, -0.059829f);
    glVertex2f(-0.349359f, -0.064103f);
    glVertex2f(-0.346154f, -0.064103f);
    glVertex2f(-0.342949f, -0.068376f);
    glVertex2f(-0.342949f, -0.072650f);
    glVertex2f(-0.339744f, -0.072650f);
    glVertex2f(-0.336538f, -0.072650f);
    glVertex2f(-0.333333f, -0.076923f);
    glVertex2f(-0.333333f, -0.081197f);
    glVertex2f(-0.333333f, -0.085470f);
    glVertex2f(-0.336538f, -0.089744f);
    glVertex2f(-0.336538f, -0.094017f);
    glVertex2f(-0.336538f, -0.098291f);
    glVertex2f(-0.339744f, -0.102564f);
    glVertex2f(-0.339744f, -0.106838f);
    glVertex2f(-0.342949f, -0.111111f);
    glVertex2f(-0.342949f, -0.115385f);
    glVertex2f(-0.346154f, -0.119658f);
    glVertex2f(-0.346154f, -0.123932f);
    glVertex2f(-0.346154f, -0.128205f);
    glVertex2f(-0.346154f, -0.132479f);
    glVertex2f(-0.346154f, -0.136752f);
    glVertex2f(-0.346154f, -0.141026f);
    glVertex2f(-0.342949f, -0.145299f);
    glVertex2f(-0.339744f, -0.145299f);
    glVertex2f(-0.336538f, -0.145299f);
    glVertex2f(-0.333333f, -0.145299f);
    glVertex2f(-0.330128f, -0.149573f);
    glVertex2f(-0.326923f, -0.149573f);
    glVertex2f(-0.323718f, -0.149573f);
    glVertex2f(-0.320513f, -0.145299f);
    glVertex2f(-0.317308f, -0.145299f);
    glVertex2f(-0.314103f, -0.145299f);
    glVertex2f(-0.310897f, -0.145299f);
    glVertex2f(-0.307692f, -0.149573f);
    glVertex2f(-0.304487f, -0.149573f);
    glVertex2f(-0.301282f, -0.153846f);
    glVertex2f(-0.298077f, -0.153846f);
    glVertex2f(-0.294872f, -0.153846f);
    glVertex2f(-0.291667f, -0.158120f);
    glVertex2f(-0.294872f, -0.162393f);
    glVertex2f(-0.298077f, -0.166667f);
    glVertex2f(-0.301282f, -0.170940f);
    glVertex2f(-0.304487f, -0.175214f);
    glVertex2f(-0.307692f, -0.179487f);
    glVertex2f(-0.310897f, -0.183761f);
    glVertex2f(-0.310897f, -0.188034f);
    glVertex2f(-0.314103f, -0.192308f);
    glVertex2f(-0.314103f, -0.196581f);
    glVertex2f(-0.314103f, -0.200855f);
    glVertex2f(-0.314103f, -0.205128f);
    glVertex2f(-0.314103f, -0.209402f);
    glVertex2f(-0.314103f, -0.213675f);
    glVertex2f(-0.314103f, -0.217949f);
    glVertex2f(-0.314103f, -0.222222f);
    glVertex2f(-0.314103f, -0.226496f);
    glVertex2f(-0.314103f, -0.230769f);
    glVertex2f(-0.310897f, -0.235043f);
    glVertex2f(-0.307692f, -0.239316f);
    glVertex2f(-0.307692f, -0.243590f);
    glVertex2f(-0.307692f, -0.247863f);
    glVertex2f(-0.304487f, -0.252137f);
    glVertex2f(-0.304487f, -0.256410f);
    glVertex2f(-0.301282f, -0.256410f);
    glVertex2f(-0.298077f, -0.260684f);
    glVertex2f(-0.294872f, -0.264957f);
    glVertex2f(-0.291667f, -0.269231f);
    glVertex2f(-0.294872f, -0.273504f);
    glVertex2f(-0.294872f, -0.277778f);
    glVertex2f(-0.294872f, -0.282051f);
    glVertex2f(-0.298077f, -0.286325f);
    glVertex2f(-0.301282f, -0.290598f);
    glVertex2f(-0.301282f, -0.294872f);
    glVertex2f(-0.301282f, -0.299145f);
    glVertex2f(-0.301282f, -0.303419f);
    glVertex2f(-0.298077f, -0.307692f);
    glVertex2f(-0.298077f, -0.311966f);
    glVertex2f(-0.298077f, -0.316239f);
    glVertex2f(-0.298077f, -0.320513f);
    glVertex2f(-0.294872f, -0.324786f);
    glVertex2f(-0.294872f, -0.329060f);
    glVertex2f(-0.291667f, -0.333333f);
    glVertex2f(-0.291667f, -0.337607f);
    glVertex2f(-0.291667f, -0.341880f);
    glVertex2f(-0.291667f, -0.346154f);
    glVertex2f(-0.294872f, -0.350427f);
    glVertex2f(-0.298077f, -0.350427f);
    glVertex2f(-0.298077f, -0.354701f);
    glVertex2f(-0.294872f, -0.354701f);
    glVertex2f(-0.291667f, -0.358974f);
    glVertex2f(-0.288462f, -0.363248f);
    glVertex2f(-0.285256f, -0.367521f);
    glVertex2f(-0.285256f, -0.371795f);
    glVertex2f(-0.285256f, -0.376068f);
    glVertex2f(-0.282051f, -0.380342f);
    glVertex2f(-0.282051f, -0.384615f);
    glVertex2f(-0.282051f, -0.388889f);
    glVertex2f(-0.282051f, -0.393162f);
    glVertex2f(-0.285256f, -0.397436f);
    glVertex2f(-0.285256f, -0.401709f);
    glVertex2f(-0.282051f, -0.405983f);
    glVertex2f(-0.282051f, -0.410256f);
    glVertex2f(-0.282051f, -0.414530f);
    glVertex2f(-0.282051f, -0.418803f);
    glVertex2f(-0.282051f, -0.423077f);
    glVertex2f(-0.278846f, -0.427350f);
    glVertex2f(-0.278846f, -0.431624f);
    glVertex2f(-0.278846f, -0.435897f);
    glVertex2f(-0.278846f, -0.440171f);
    glVertex2f(-0.275641f, -0.444444f);
    glVertex2f(-0.272436f, -0.448718f);
    glVertex2f(-0.272436f, -0.452991f);
    glVertex2f(-0.269231f, -0.457265f);
    glVertex2f(-0.266026f, -0.461538f);
    glVertex2f(-0.266026f, -0.465812f);
    glVertex2f(-0.266026f, -0.470085f);
    glVertex2f(-0.266026f, -0.474359f);
    glVertex2f(-0.269231f, -0.478632f);
    glVertex2f(-0.269231f, -0.482906f);
    glVertex2f(-0.269231f, -0.487179f);
    glVertex2f(-0.269231f, -0.491453f);
    glVertex2f(-0.269231f, -0.495726f);
    glVertex2f(-0.269231f, -0.500000f);
    glVertex2f(-0.269231f, -0.504274f);
    glVertex2f(-0.266026f, -0.508547f);
    glVertex2f(-0.266026f, -0.512821f);
    glVertex2f(-0.262821f, -0.517094f);
    glVertex2f(-0.262821f, -0.521368f);
    glVertex2f(-0.262821f, -0.525641f);
    glVertex2f(-0.262821f, -0.529915f);
    glVertex2f(-0.266026f, -0.534188f);
    glVertex2f(-0.266026f, -0.538462f);
    glVertex2f(-0.269231f, -0.542735f);
    glVertex2f(-0.272436f, -0.542735f);
    glVertex2f(-0.272436f, -0.547009f);
    glVertex2f(-0.272436f, -0.551282f);
    glVertex2f(-0.269231f, -0.555556f);
    glVertex2f(-0.269231f, -0.559829f);
    glVertex2f(-0.269231f, -0.564103f);
    glVertex2f(-0.269231f, -0.568376f);
    glVertex2f(-0.269231f, -0.572650f);
    glVertex2f(-0.269231f, -0.576923f);
    glVertex2f(-0.272436f, -0.581197f);
    glVertex2f(-0.269231f, -0.585470f);
    glVertex2f(-0.266026f, -0.589744f);
    glVertex2f(-0.262821f, -0.594017f);
    glVertex2f(-0.262821f, -0.598291f);
    glVertex2f(-0.259615f, -0.598291f);
    glVertex2f(-0.256410f, -0.602564f);
    glVertex2f(-0.253205f, -0.602564f);
    glVertex2f(-0.250000f, -0.598291f);
    glVertex2f(-0.250000f, -0.594017f);
    glVertex2f(-0.250000f, -0.589744f);
    glVertex2f(-0.250000f, -0.585470f);
    glVertex2f(-0.246795f, -0.581197f);
    glVertex2f(-0.243590f, -0.581197f);
    glVertex2f(-0.240385f, -0.585470f);
    glVertex2f(-0.240385f, -0.589744f);
    glVertex2f(-0.240385f, -0.594017f);
    glVertex2f(-0.237179f, -0.598291f);
    glVertex2f(-0.237179f, -0.602564f);
    glVertex2f(-0.237179f, -0.606838f);
    glVertex2f(-0.237179f, -0.611111f);
    glVertex2f(-0.240385f, -0.615385f);
    glVertex2f(-0.240385f, -0.619658f);
    glVertex2f(-0.237179f, -0.623932f);
    glVertex2f(-0.233974f, -0.628205f);
    glVertex2f(-0.230769f, -0.628205f);
    glVertex2f(-0.227564f, -0.623932f);
    glVertex2f(-0.224359f, -0.623932f);
    glVertex2f(-0.221154f, -0.619658f);
    glVertex2f(-0.217949f, -0.619658f);
    glVertex2f(-0.217949f, -0.615385f);
    glVertex2f(-0.221154f, -0.611111f);
    glVertex2f(-0.221154f, -0.606838f);
    glVertex2f(-0.221154f, -0.602564f);
    glVertex2f(-0.221154f, -0.598291f);
    glVertex2f(-0.217949f, -0.594017f);
    glVertex2f(-0.217949f, -0.589744f);
    glVertex2f(-0.221154f, -0.585470f);
    glVertex2f(-0.221154f, -0.581197f);
    glVertex2f(-0.217949f, -0.576923f);
    glVertex2f(-0.214744f, -0.572650f);
    glVertex2f(-0.214744f, -0.568376f);
    glVertex2f(-0.211538f, -0.564103f);
    glVertex2f(-0.211538f, -0.559829f);
    glVertex2f(-0.208333f, -0.555556f);
    glVertex2f(-0.205128f, -0.551282f);
    glVertex2f(-0.201923f, -0.555556f);
    glVertex2f(-0.201923f, -0.559829f);
    glVertex2f(-0.205128f, -0.564103f);
    glVertex2f(-0.205128f, -0.568376f);
    glVertex2f(-0.205128f, -0.572650f);
    glVertex2f(-0.205128f, -0.576923f);
    glVertex2f(-0.205128f, -0.581197f);
    glVertex2f(-0.205128f, -0.585470f);
    glVertex2f(-0.205128f, -0.589744f);
    glVertex2f(-0.205128f, -0.594017f);
    glVertex2f(-0.205128f, -0.598291f);
    glVertex2f(-0.201923f, -0.602564f);
    glVertex2f(-0.198718f, -0.606838f);
    glVertex2f(-0.195513f, -0.602564f);
    glVertex2f(-0.192308f, -0.602564f);
    glVertex2f(-0.189103f, -0.598291f);
    glVertex2f(-0.185897f, -0.594017f);
    glVertex2f(-0.182692f, -0.589744f);
    glVertex2f(-0.182692f, -0.585470f);
    glVertex2f(-0.182692f, -0.581197f);
    glVertex2f(-0.182692f, -0.576923f);
    glVertex2f(-0.182692f, -0.572650f);
    glVertex2f(-0.182692f, -0.568376f);
    glVertex2f(-0.182692f, -0.564103f);
    glVertex2f(-0.182692f, -0.559829f);
    glVertex2f(-0.179487f, -0.555556f);
    glVertex2f(-0.176282f, -0.551282f);
    glVertex2f(-0.173077f, -0.547009f);
    glVertex2f(-0.173077f, -0.542735f);
    glVertex2f(-0.173077f, -0.538462f);
    glVertex2f(-0.173077f, -0.534188f);
    glVertex2f(-0.169872f, -0.529915f);
    glVertex2f(-0.169872f, -0.525641f);
    glVertex2f(-0.166667f, -0.521368f);
    glVertex2f(-0.163462f, -0.525641f);
    glVertex2f(-0.163462f, -0.529915f);
    glVertex2f(-0.163462f, -0.534188f);
    glVertex2f(-0.163462f, -0.538462f);
    glVertex2f(-0.163462f, -0.542735f);
    glVertex2f(-0.163462f, -0.547009f);
    glVertex2f(-0.163462f, -0.551282f);
    glVertex2f(-0.163462f, -0.555556f);
    glVertex2f(-0.166667f, -0.559829f);
    glVertex2f(-0.169872f, -0.564103f);
    glVertex2f(-0.169872f, -0.568376f);
    glVertex2f(-0.169872f, -0.572650f);
    glVertex2f(-0.169872f, -0.576923f);
    glVertex2f(-0.169872f, -0.581197f);
    glVertex2f(-0.169872f, -0.585470f);
    glVertex2f(-0.169872f, -0.589744f);
    glVertex2f(-0.169872f, -0.594017f);
    glVertex2f(-0.166667f, -0.598291f);
    glVertex2f(-0.166667f, -0.602564f);
    glVertex2f(-0.163462f, -0.606838f);
    glVertex2f(-0.160256f, -0.611111f);
    glVertex2f(-0.157051f, -0.611111f);
    glVertex2f(-0.153846f, -0.606838f);
    glVertex2f(-0.153846f, -0.602564f);
    glVertex2f(-0.153846f, -0.598291f);
    glVertex2f(-0.157051f, -0.594017f);
    glVertex2f(-0.153846f, -0.589744f);
    glVertex2f(-0.150641f, -0.589744f);
    glVertex2f(-0.147436f, -0.594017f);
    glVertex2f(-0.144231f, -0.594017f);
    glVertex2f(-0.141026f, -0.594017f);
    glVertex2f(-0.137821f, -0.594017f);
    glVertex2f(-0.134615f, -0.589744f);
    glVertex2f(-0.134615f, -0.585470f);
    glVertex2f(-0.134615f, -0.581197f);
    glVertex2f(-0.137821f, -0.576923f);
    glVertex2f(-0.141026f, -0.572650f);
    glVertex2f(-0.137821f, -0.568376f);
    glVertex2f(-0.134615f, -0.568376f);
    glVertex2f(-0.131410f, -0.572650f);
    glVertex2f(-0.128205f, -0.572650f);
    glVertex2f(-0.125000f, -0.568376f);
    glVertex2f(-0.121795f, -0.568376f);
    glVertex2f(-0.118590f, -0.572650f);
    glVertex2f(-0.115385f, -0.572650f);
    glVertex2f(-0.112179f, -0.568376f);
    glVertex2f(-0.108974f, -0.568376f);
    glVertex2f(-0.108974f, -0.564103f);
    glVertex2f(-0.105769f, -0.559829f);
    glVertex2f(-0.102564f, -0.559829f);
    glVertex2f(-0.099359f, -0.555556f);
    glVertex2f(-0.096154f, -0.555556f);
    glVertex2f(-0.096154f, -0.551282f);
    glVertex2f(-0.096154f, -0.547009f);
    glVertex2f(-0.096154f, -0.542735f);
    glVertex2f(-0.099359f, -0.538462f);
    glVertex2f(-0.099359f, -0.534188f);
    glVertex2f(-0.102564f, -0.529915f);
    glVertex2f(-0.102564f, -0.525641f);
    glVertex2f(-0.102564f, -0.521368f);
    glVertex2f(-0.102564f, -0.517094f);
    glVertex2f(-0.102564f, -0.512821f);
    glVertex2f(-0.102564f, -0.508547f);
    glVertex2f(-0.102564f, -0.504274f);
    glVertex2f(-0.102564f, -0.500000f);
    glVertex2f(-0.099359f, -0.495726f);
    glVertex2f(-0.099359f, -0.491453f);
    glVertex2f(-0.096154f, -0.487179f);
    glVertex2f(-0.096154f, -0.482906f);
    glVertex2f(-0.096154f, -0.478632f);
    glVertex2f(-0.096154f, -0.474359f);
    glVertex2f(-0.092949f, -0.470085f);
    glVertex2f(-0.089744f, -0.474359f);
    glVertex2f(-0.089744f, -0.478632f);
    glVertex2f(-0.089744f, -0.482906f);
    glVertex2f(-0.089744f, -0.487179f);
    glVertex2f(-0.089744f, -0.491453f);
    glVertex2f(-0.089744f, -0.495726f);
    glVertex2f(-0.089744f, -0.500000f);
    glVertex2f(-0.089744f, -0.504274f);
    glVertex2f(-0.089744f, -0.508547f);
    glVertex2f(-0.086538f, -0.512821f);
    glVertex2f(-0.086538f, -0.517094f);
    glVertex2f(-0.086538f, -0.521368f);
    glVertex2f(-0.083333f, -0.525641f);
    glVertex2f(-0.080128f, -0.525641f);
    glVertex2f(-0.076923f, -0.525641f);
    glVertex2f(-0.073718f, -0.525641f);
    glVertex2f(-0.070513f, -0.521368f);
    glVertex2f(-0.067308f, -0.521368f);
    glVertex2f(-0.064103f, -0.521368f);
    glVertex2f(-0.060897f, -0.525641f);
    glVertex2f(-0.064103f, -0.529915f);
    glVertex2f(-0.064103f, -0.534188f);
    glVertex2f(-0.064103f, -0.538462f);
    glVertex2f(-0.064103f, -0.542735f);
    glVertex2f(-0.064103f, -0.547009f);
    glVertex2f(-0.064103f, -0.551282f);
    glVertex2f(-0.067308f, -0.555556f);
    glVertex2f(-0.067308f, -0.559829f);
    glVertex2f(-0.064103f, -0.564103f);
    glVertex2f(-0.060897f, -0.564103f);
    glVertex2f(-0.057692f, -0.564103f);
    glVertex2f(-0.054487f, -0.568376f);
    glVertex2f(-0.051282f, -0.572650f);
    glVertex2f(-0.048077f, -0.572650f);
    glVertex2f(-0.044872f, -0.572650f);
    glVertex2f(-0.041667f, -0.576923f);
    glVertex2f(-0.038462f, -0.576923f);
    glVertex2f(-0.035256f, -0.576923f);
    glVertex2f(-0.032051f, -0.581197f);
    glVertex2f(-0.028846f, -0.576923f);
    glVertex2f(-0.025641f, -0.576923f);
    glVertex2f(-0.022436f, -0.572650f);
    glVertex2f(-0.019231f, -0.568376f);
    glVertex2f(-0.016026f, -0.568376f);
    glVertex2f(-0.012821f, -0.564103f);
    glVertex2f(-0.012821f, -0.559829f);
    glVertex2f(-0.009615f, -0.555556f);
    glVertex2f(-0.006410f, -0.559829f);
    glVertex2f(-0.006410f, -0.564103f);
    glVertex2f(-0.003205f, -0.568376f);
    glVertex2f(0.000000f, -0.564103f);
    glVertex2f(0.000000f, -0.559829f);
    glVertex2f(0.003205f, -0.555556f);
    glVertex2f(0.003205f, -0.551282f);
    glVertex2f(0.003205f, -0.547009f);
    glVertex2f(0.006410f, -0.542735f);
    glVertex2f(0.009615f, -0.542735f);
    glVertex2f(0.012821f, -0.547009f);
    glVertex2f(0.016026f, -0.551282f);
    glVertex2f(0.019231f, -0.547009f);
    glVertex2f(0.022436f, -0.547009f);
    glVertex2f(0.022436f, -0.542735f);
    glVertex2f(0.025641f, -0.538462f);
    glVertex2f(0.028846f, -0.538462f);
    glVertex2f(0.028846f, -0.534188f);
    glVertex2f(0.032051f, -0.529915f);
    glVertex2f(0.032051f, -0.525641f);
    glVertex2f(0.035256f, -0.521368f);
    glVertex2f(0.038462f, -0.521368f);
    glVertex2f(0.041667f, -0.521368f);
    glVertex2f(0.044872f, -0.517094f);
    glVertex2f(0.048077f, -0.512821f);
    glVertex2f(0.048077f, -0.508547f);
    glVertex2f(0.048077f, -0.504274f);
    glVertex2f(0.048077f, -0.500000f);
    glVertex2f(0.048077f, -0.495726f);
    glVertex2f(0.051282f, -0.491453f);
    glVertex2f(0.054487f, -0.495726f);
    glVertex2f(0.054487f, -0.500000f);
    glVertex2f(0.054487f, -0.504274f);
    glVertex2f(0.054487f, -0.508547f);
    glVertex2f(0.057692f, -0.512821f);
    glVertex2f(0.060897f, -0.512821f);
    glVertex2f(0.064103f, -0.517094f);
    glVertex2f(0.064103f, -0.521368f);
    glVertex2f(0.067308f, -0.521368f);
    glVertex2f(0.070513f, -0.521368f);
    glVertex2f(0.073718f, -0.517094f);
    glVertex2f(0.076923f, -0.512821f);
    glVertex2f(0.080128f, -0.508547f);
    glVertex2f(0.083333f, -0.504274f);
    glVertex2f(0.086538f, -0.500000f);
    glVertex2f(0.089744f, -0.500000f);
    glVertex2f(0.092949f, -0.495726f);
    glVertex2f(0.096154f, -0.491453f);
    glVertex2f(0.096154f, -0.487179f);
    glVertex2f(0.099359f, -0.482906f);
    glVertex2f(0.102564f, -0.478632f);
    glVertex2f(0.102564f, -0.474359f);
    glVertex2f(0.102564f, -0.470085f);
    glVertex2f(0.105769f, -0.465812f);
    glVertex2f(0.105769f, -0.461538f);
    glVertex2f(0.105769f, -0.457265f);
    glVertex2f(0.105769f, -0.452991f);
    glVertex2f(0.105769f, -0.448718f);
    glVertex2f(0.105769f, -0.444444f);
    glVertex2f(0.105769f, -0.440171f);
    glVertex2f(0.105769f, -0.435897f);
    glVertex2f(0.105769f, -0.431624f);
    glVertex2f(0.105769f, -0.427350f);
    glVertex2f(0.105769f, -0.423077f);
    glVertex2f(0.105769f, -0.418803f);
    glVertex2f(0.105769f, -0.414530f);
    glVertex2f(0.105769f, -0.410256f);
    glVertex2f(0.105769f, -0.405983f);
    glVertex2f(0.105769f, -0.401709f);
    glVertex2f(0.108974f, -0.397436f);
    glVertex2f(0.108974f, -0.393162f);
    glVertex2f(0.108974f, -0.388889f);
    glVertex2f(0.108974f, -0.384615f);
    glVertex2f(0.105769f, -0.380342f);
    glVertex2f(0.102564f, -0.376068f);
    glVertex2f(0.099359f, -0.371795f);
    glVertex2f(0.096154f, -0.367521f);
    glVertex2f(0.092949f, -0.363248f);
    glVertex2f(0.089744f, -0.358974f);
    glVertex2f(0.089744f, -0.354701f);
    glVertex2f(0.086538f, -0.350427f);
    glVertex2f(0.086538f, -0.346154f);
    glVertex2f(0.086538f, -0.341880f);
    glVertex2f(0.086538f, -0.337607f);
    glVertex2f(0.083333f, -0.333333f);
    glVertex2f(0.083333f, -0.329060f);
    glVertex2f(0.080128f, -0.324786f);
    glVertex2f(0.076923f, -0.320513f);
    glVertex2f(0.076923f, -0.316239f);
    glVertex2f(0.073718f, -0.311966f);
    glVertex2f(0.073718f, -0.307692f);
    glVertex2f(0.070513f, -0.303419f);
    glVertex2f(0.070513f, -0.299145f);
    glVertex2f(0.070513f, -0.294872f);
    glVertex2f(0.067308f, -0.290598f);
    glVertex2f(0.067308f, -0.286325f);
    glVertex2f(0.067308f, -0.282051f);
    glVertex2f(0.064103f, -0.277778f);
    glVertex2f(0.067308f, -0.273504f);
    glVertex2f(0.070513f, -0.273504f);
    glVertex2f(0.070513f, -0.269231f);
    glVertex2f(0.067308f, -0.264957f);
    glVertex2f(0.064103f, -0.260684f);
    glVertex2f(0.060897f, -0.256410f);
    glVertex2f(0.057692f, -0.252137f);
    glVertex2f(0.054487f, -0.252137f);
    glVertex2f(0.051282f, -0.252137f);
    glVertex2f(0.048077f, -0.252137f);
    glVertex2f(0.044872f, -0.252137f);
    glVertex2f(0.041667f, -0.247863f);
    glVertex2f(0.041667f, -0.243590f);
    glVertex2f(0.038462f, -0.239316f);
    glVertex2f(0.035256f, -0.235043f);
    glVertex2f(0.038462f, -0.230769f);
    glVertex2f(0.041667f, -0.230769f);
    glVertex2f(0.044872f, -0.230769f);
    glVertex2f(0.048077f, -0.230769f);
    glVertex2f(0.051282f, -0.230769f);
    glVertex2f(0.054487f, -0.230769f);
    glVertex2f(0.057692f, -0.235043f);
    glVertex2f(0.057692f, -0.239316f);
    glVertex2f(0.060897f, -0.239316f);
    glVertex2f(0.064103f, -0.239316f);
    glVertex2f(0.067308f, -0.239316f);
    glVertex2f(0.070513f, -0.239316f);
    glVertex2f(0.067308f, -0.235043f);
    glVertex2f(0.070513f, -0.230769f);
    glVertex2f(0.073718f, -0.226496f);
    glVertex2f(0.076923f, -0.230769f);
    glVertex2f(0.076923f, -0.235043f);
    glVertex2f(0.080128f, -0.239316f);
    glVertex2f(0.080128f, -0.243590f);
    glVertex2f(0.080128f, -0.247863f);
    glVertex2f(0.083333f, -0.252137f);
    glVertex2f(0.083333f, -0.256410f);
    glVertex2f(0.086538f, -0.260684f);
    glVertex2f(0.086538f, -0.264957f);
    glVertex2f(0.086538f, -0.269231f);
    glVertex2f(0.086538f, -0.273504f);
    glVertex2f(0.089744f, -0.277778f);
    glVertex2f(0.089744f, -0.282051f);
    glVertex2f(0.089744f, -0.286325f);
    glVertex2f(0.092949f, -0.290598f);
    glVertex2f(0.096154f, -0.294872f);
    glVertex2f(0.099359f, -0.299145f);
    glVertex2f(0.099359f, -0.303419f);
    glVertex2f(0.102564f, -0.307692f);
    glVertex2f(0.102564f, -0.311966f);
    glVertex2f(0.105769f, -0.311966f);
    glVertex2f(0.108974f, -0.311966f);
    glVertex2f(0.112179f, -0.316239f);
    glVertex2f(0.112179f, -0.320513f);
    glVertex2f(0.115385f, -0.324786f);
    glVertex2f(0.118590f, -0.329060f);
    glVertex2f(0.118590f, -0.333333f);
    glVertex2f(0.121795f, -0.337607f);
    glVertex2f(0.125000f, -0.341880f);
    glVertex2f(0.128205f, -0.346154f);
    glVertex2f(0.131410f, -0.346154f);
    glVertex2f(0.134615f, -0.346154f);
    glVertex2f(0.137821f, -0.346154f);
    glVertex2f(0.141026f, -0.346154f);
    glVertex2f(0.144231f, -0.341880f);
    glVertex2f(0.147436f, -0.341880f);
    glVertex2f(0.150641f, -0.341880f);
    glVertex2f(0.153846f, -0.346154f);
    glVertex2f(0.153846f, -0.350427f);
    glVertex2f(0.157051f, -0.354701f);
    glVertex2f(0.160256f, -0.358974f);
    glVertex2f(0.163462f, -0.358974f);
    glVertex2f(0.166667f, -0.358974f);
    glVertex2f(0.169872f, -0.358974f);
    glVertex2f(0.173077f, -0.363248f);
    glVertex2f(0.169872f, -0.367521f);
    glVertex2f(0.166667f, -0.367521f);
    glVertex2f(0.163462f, -0.371795f);
    glVertex2f(0.163462f, -0.376068f);
    glVertex2f(0.163462f, -0.380342f);
    glVertex2f(0.166667f, -0.384615f);
    glVertex2f(0.169872f, -0.384615f);
    glVertex2f(0.173077f, -0.384615f);
    glVertex2f(0.176282f, -0.380342f);
    glVertex2f(0.179487f, -0.380342f);
    glVertex2f(0.182692f, -0.376068f);
    glVertex2f(0.182692f, -0.371795f);
    glVertex2f(0.182692f, -0.367521f);
    glVertex2f(0.182692f, -0.363248f);
    glVertex2f(0.179487f, -0.363248f);
    glVertex2f(0.176282f, -0.358974f);
    glVertex2f(0.179487f, -0.354701f);
    glVertex2f(0.182692f, -0.354701f);
    glVertex2f(0.185897f, -0.350427f);
    glVertex2f(0.189103f, -0.346154f);
    glVertex2f(0.192308f, -0.341880f);
    glVertex2f(0.192308f, -0.337607f);
    glVertex2f(0.192308f, -0.333333f);
    glVertex2f(0.195513f, -0.329060f);
    glVertex2f(0.195513f, -0.324786f);
    glVertex2f(0.192308f, -0.320513f);
    glVertex2f(0.192308f, -0.316239f);
    glVertex2f(0.189103f, -0.316239f);
    glVertex2f(0.185897f, -0.316239f);
    glVertex2f(0.182692f, -0.311966f);
    glVertex2f(0.179487f, -0.307692f);
    glVertex2f(0.179487f, -0.303419f);
    glVertex2f(0.182692f, -0.299145f);
    glVertex2f(0.185897f, -0.299145f);
    glVertex2f(0.189103f, -0.303419f);
    glVertex2f(0.189103f, -0.307692f);
    glVertex2f(0.192308f, -0.307692f);
    glVertex2f(0.195513f, -0.307692f);
    glVertex2f(0.198718f, -0.307692f);
    glVertex2f(0.201923f, -0.307692f);
    glVertex2f(0.205128f, -0.307692f);
    glVertex2f(0.208333f, -0.307692f);
    glVertex2f(0.208333f, -0.303419f);
    glVertex2f(0.208333f, -0.299145f);
    glVertex2f(0.211538f, -0.294872f);
    glVertex2f(0.214744f, -0.294872f);
    glVertex2f(0.217949f, -0.290598f);
    glVertex2f(0.221154f, -0.286325f);
    glVertex2f(0.224359f, -0.290598f);
    glVertex2f(0.227564f, -0.290598f);
    glVertex2f(0.224359f, -0.286325f);
    glVertex2f(0.224359f, -0.282051f);
    glVertex2f(0.227564f, -0.277778f);
    glVertex2f(0.230769f, -0.273504f);
    glVertex2f(0.233974f, -0.277778f);
    glVertex2f(0.233974f, -0.282051f);
    glVertex2f(0.233974f, -0.286325f);
    glVertex2f(0.233974f, -0.290598f);
    glVertex2f(0.237179f, -0.290598f);
    glVertex2f(0.240385f, -0.294872f);
    glVertex2f(0.240385f, -0.299145f);
    glVertex2f(0.243590f, -0.303419f);
    glVertex2f(0.246795f, -0.303419f);
    glVertex2f(0.250000f, -0.307692f);
    glVertex2f(0.253205f, -0.307692f);
    glVertex2f(0.256410f, -0.311966f);
    glVertex2f(0.256410f, -0.316239f);
    glVertex2f(0.259615f, -0.320513f);
    glVertex2f(0.262821f, -0.324786f);
    glVertex2f(0.262821f, -0.329060f);
    glVertex2f(0.266026f, -0.333333f);
    glVertex2f(0.269231f, -0.337607f);
    glVertex2f(0.269231f, -0.341880f);
    glVertex2f(0.272436f, -0.346154f);
    glVertex2f(0.275641f, -0.350427f);
    glVertex2f(0.278846f, -0.354701f);
    glVertex2f(0.278846f, -0.358974f);
    glVertex2f(0.282051f, -0.363248f);
    glVertex2f(0.282051f, -0.367521f);
    glVertex2f(0.285256f, -0.371795f);
    glVertex2f(0.285256f, -0.376068f);
    glVertex2f(0.288462f, -0.380342f);
    glVertex2f(0.288462f, -0.384615f);
    glVertex2f(0.291667f, -0.388889f);
    glVertex2f(0.291667f, -0.393162f);
    glVertex2f(0.294872f, -0.397436f);
    glVertex2f(0.294872f, -0.401709f);
    glVertex2f(0.294872f, -0.405983f);
    glVertex2f(0.298077f, -0.410256f);
    glVertex2f(0.298077f, -0.414530f);
    glVertex2f(0.298077f, -0.418803f);
    glVertex2f(0.298077f, -0.423077f);
    glVertex2f(0.298077f, -0.427350f);
    glVertex2f(0.298077f, -0.431624f);
    glVertex2f(0.298077f, -0.435897f);
    glVertex2f(0.301282f, -0.440171f);
    glVertex2f(0.301282f, -0.444444f);
    glVertex2f(0.304487f, -0.448718f);
    glVertex2f(0.307692f, -0.452991f);
    glVertex2f(0.307692f, -0.457265f);
    glVertex2f(0.307692f, -0.461538f);
    glVertex2f(0.307692f, -0.465812f);
    glVertex2f(0.310897f, -0.470085f);
    glVertex2f(0.310897f, -0.474359f);
    glVertex2f(0.310897f, -0.478632f);
    glVertex2f(0.314103f, -0.482906f);
    glVertex2f(0.317308f, -0.487179f);
    glVertex2f(0.317308f, -0.491453f);
    glVertex2f(0.320513f, -0.495726f);
    glVertex2f(0.320513f, -0.500000f);
    glVertex2f(0.320513f, -0.504274f);
    glVertex2f(0.320513f, -0.508547f);
    glVertex2f(0.320513f, -0.512821f);
    glVertex2f(0.323718f, -0.517094f);
    glVertex2f(0.323718f, -0.521368f);
    glVertex2f(0.323718f, -0.525641f);
    glVertex2f(0.323718f, -0.529915f);
    glVertex2f(0.323718f, -0.534188f);
    glVertex2f(0.320513f, -0.538462f);
    glVertex2f(0.317308f, -0.542735f);
    glVertex2f(0.314103f, -0.547009f);
    glVertex2f(0.314103f, -0.551282f);
    glVertex2f(0.314103f, -0.555556f);
    glVertex2f(0.314103f, -0.559829f);
    glVertex2f(0.314103f, -0.564103f);
    glVertex2f(0.314103f, -0.568376f);
    glVertex2f(0.314103f, -0.572650f);
    glVertex2f(0.314103f, -0.576923f);
    glVertex2f(0.314103f, -0.581197f);
    glVertex2f(0.310897f, -0.585470f);
    glVertex2f(0.310897f, -0.589744f);
    glVertex2f(0.310897f, -0.594017f);
    glVertex2f(0.310897f, -0.598291f);
    glVertex2f(0.314103f, -0.602564f);
    glVertex2f(0.317308f, -0.606838f);
    glVertex2f(0.317308f, -0.611111f);
    glVertex2f(0.317308f, -0.615385f);
    glVertex2f(0.317308f, -0.619658f);
    glVertex2f(0.317308f, -0.623932f);
    glVertex2f(0.320513f, -0.628205f);
    glVertex2f(0.320513f, -0.632479f);
    glVertex2f(0.320513f, -0.636752f);
    glVertex2f(0.320513f, -0.641026f);
    glVertex2f(0.320513f, -0.645299f);
    glVertex2f(0.320513f, -0.649573f);
    glVertex2f(0.320513f, -0.653846f);
    glVertex2f(0.317308f, -0.658120f);
    glVertex2f(0.317308f, -0.662393f);
    glVertex2f(0.317308f, -0.666667f);
    glVertex2f(0.320513f, -0.670940f);
    glVertex2f(0.320513f, -0.675214f);
    glVertex2f(0.323718f, -0.675214f);
    glVertex2f(0.326923f, -0.675214f);
    glVertex2f(0.326923f, -0.670940f);
    glVertex2f(0.330128f, -0.666667f);
    glVertex2f(0.333333f, -0.666667f);
    glVertex2f(0.336538f, -0.666667f);
    glVertex2f(0.339744f, -0.666667f);
    glVertex2f(0.342949f, -0.670940f);
    glVertex2f(0.342949f, -0.675214f);
    glVertex2f(0.339744f, -0.679487f);
    glVertex2f(0.336538f, -0.679487f);
    glVertex2f(0.336538f, -0.683761f);
    glVertex2f(0.336538f, -0.688034f);
    glVertex2f(0.339744f, -0.692308f);
    glVertex2f(0.339744f, -0.696581f);
    glVertex2f(0.342949f, -0.700855f);
    glVertex2f(0.346154f, -0.705128f);
    glVertex2f(0.349359f, -0.709402f);
    glVertex2f(0.349359f, -0.713675f);
    glVertex2f(0.352564f, -0.717949f);
    glVertex2f(0.352564f, -0.722222f);
    glVertex2f(0.355769f, -0.726496f);
    glVertex2f(0.355769f, -0.730769f);
    glVertex2f(0.358974f, -0.735043f);
    glVertex2f(0.358974f, -0.739316f);
    glVertex2f(0.358974f, -0.743590f);
    glVertex2f(0.358974f, -0.747863f);
    glVertex2f(0.358974f, -0.752137f);
    glVertex2f(0.358974f, -0.756410f);
    glVertex2f(0.355769f, -0.760684f);
    glVertex2f(0.358974f, -0.764957f);
    glVertex2f(0.358974f, -0.769231f);
    glVertex2f(0.358974f, -0.773504f);
    glVertex2f(0.362179f, -0.777778f);
    glVertex2f(0.362179f, -0.782051f);
    glVertex2f(0.365385f, -0.786325f);
    glVertex2f(0.368590f, -0.790598f);
    glVertex2f(0.371795f, -0.794872f);
    glVertex2f(0.371795f, -0.799145f);
    glVertex2f(0.375000f, -0.803419f);
    glVertex2f(0.375000f, -0.807692f);
    glVertex2f(0.378205f, -0.807692f);
    glVertex2f(0.381410f, -0.811966f);
    glVertex2f(0.384615f, -0.816239f);
    glVertex2f(0.387821f, -0.820513f);
    glVertex2f(0.387821f, -0.824786f);
    glVertex2f(0.391026f, -0.829060f);
    glVertex2f(0.391026f, -0.833333f);
    glVertex2f(0.391026f, -0.837607f);
    glVertex2f(0.391026f, -0.841880f);
    glVertex2f(0.394231f, -0.846154f);
    glVertex2f(0.394231f, -0.850427f);
    glVertex2f(0.397436f, -0.854701f);
    glVertex2f(0.397436f, -0.858974f);
    glVertex2f(0.400641f, -0.863248f);
    glVertex2f(0.403846f, -0.867521f);
    glVertex2f(0.403846f, -0.871795f);
    glVertex2f(0.407051f, -0.876068f);
    glVertex2f(0.407051f, -0.880342f);
    glVertex2f(0.410256f, -0.884615f);
    glVertex2f(0.410256f, -0.888889f);
    glVertex2f(0.410256f, -0.893162f);
    glVertex2f(0.413462f, -0.897436f);
    glVertex2f(0.416667f, -0.897436f);
    glVertex2f(0.419872f, -0.897436f);
    glVertex2f(0.419872f, -0.893162f);
    glVertex2f(0.419872f, -0.888889f);
    glVertex2f(0.416667f, -0.884615f);
    glVertex2f(0.416667f, -0.880342f);
    glVertex2f(0.416667f, -0.876068f);
    glVertex2f(0.413462f, -0.871795f);
    glVertex2f(0.413462f, -0.867521f);
    glVertex2f(0.413462f, -0.863248f);
    glVertex2f(0.413462f, -0.858974f);
    glVertex2f(0.410256f, -0.854701f);
    glVertex2f(0.407051f, -0.850427f);
    glVertex2f(0.407051f, -0.846154f);
    glVertex2f(0.403846f, -0.841880f);
    glVertex2f(0.403846f, -0.837607f);
    glVertex2f(0.403846f, -0.833333f);
    glVertex2f(0.403846f, -0.829060f);
    glVertex2f(0.403846f, -0.824786f);
    glVertex2f(0.403846f, -0.820513f);
    glVertex2f(0.403846f, -0.816239f);
    glVertex2f(0.403846f, -0.811966f);
    glVertex2f(0.403846f, -0.807692f);
    glVertex2f(0.403846f, -0.803419f);
    glVertex2f(0.403846f, -0.799145f);
    glVertex2f(0.400641f, -0.794872f);
    glVertex2f(0.397436f, -0.790598f);
    glVertex2f(0.394231f, -0.786325f);
    glVertex2f(0.394231f, -0.782051f);
    glVertex2f(0.391026f, -0.777778f);
    glVertex2f(0.387821f, -0.773504f);
    glVertex2f(0.387821f, -0.769231f);
    glVertex2f(0.387821f, -0.764957f);
    glVertex2f(0.387821f, -0.760684f);
    glVertex2f(0.387821f, -0.756410f);
    glVertex2f(0.387821f, -0.752137f);
    glVertex2f(0.387821f, -0.747863f);
    glVertex2f(0.387821f, -0.743590f);
    glVertex2f(0.387821f, -0.739316f);
    glVertex2f(0.387821f, -0.735043f);
    glVertex2f(0.387821f, -0.730769f);
    glVertex2f(0.387821f, -0.726496f);
    glVertex2f(0.391026f, -0.722222f);
    glVertex2f(0.391026f, -0.717949f);
    glVertex2f(0.394231f, -0.713675f);
    glVertex2f(0.394231f, -0.709402f);
    glVertex2f(0.394231f, -0.705128f);
    glVertex2f(0.397436f, -0.700855f);
    glVertex2f(0.400641f, -0.696581f);
    glVertex2f(0.403846f, -0.692308f);
    glVertex2f(0.407051f, -0.692308f);
    glVertex2f(0.410256f, -0.692308f);
    glVertex2f(0.413462f, -0.688034f);
    glVertex2f(0.416667f, -0.683761f);
    glVertex2f(0.419872f, -0.683761f);
    glVertex2f(0.423077f, -0.688034f);
    glVertex2f(0.426282f, -0.692308f);
    glVertex2f(0.426282f, -0.696581f);
    glVertex2f(0.426282f, -0.700855f);
    glVertex2f(0.426282f, -0.705128f);
    glVertex2f(0.429487f, -0.709402f);
    glVertex2f(0.432692f, -0.709402f);
    glVertex2f(0.435897f, -0.709402f);
    glVertex2f(0.439103f, -0.709402f);
    glVertex2f(0.442308f, -0.713675f);
    glVertex2f(0.445513f, -0.713675f);
    glVertex2f(0.448718f, -0.713675f);
    glVertex2f(0.451923f, -0.709402f);
    glVertex2f(0.455128f, -0.709402f);
    glVertex2f(0.458333f, -0.713675f);
    glVertex2f(0.458333f, -0.717949f);
    glVertex2f(0.461538f, -0.722222f);
    glVertex2f(0.461538f, -0.726496f);
    glVertex2f(0.461538f, -0.730769f);
    glVertex2f(0.464744f, -0.735043f);
    glVertex2f(0.464744f, -0.739316f);
    glVertex2f(0.464744f, -0.743590f);
    glVertex2f(0.467949f, -0.747863f);
    glVertex2f(0.471154f, -0.747863f);
    glVertex2f(0.474359f, -0.743590f);
    glVertex2f(0.477564f, -0.743590f);
    glVertex2f(0.480769f, -0.739316f);
    glVertex2f(0.483974f, -0.735043f);
    glVertex2f(0.483974f, -0.730769f);
    glVertex2f(0.483974f, -0.726496f);
    glVertex2f(0.483974f, -0.722222f);
    glVertex2f(0.480769f, -0.717949f);
    glVertex2f(0.480769f, -0.713675f);
    glVertex2f(0.480769f, -0.709402f);
    glVertex2f(0.477564f, -0.705128f);
    glVertex2f(0.477564f, -0.700855f);
    glVertex2f(0.477564f, -0.696581f);
    glVertex2f(0.474359f, -0.692308f);
    glVertex2f(0.474359f, -0.688034f);
    glVertex2f(0.474359f, -0.683761f);
    glVertex2f(0.474359f, -0.679487f);
    glVertex2f(0.474359f, -0.675214f);
    glVertex2f(0.474359f, -0.670940f);
    glVertex2f(0.474359f, -0.666667f);
    glVertex2f(0.471154f, -0.662393f);
    glVertex2f(0.471154f, -0.658120f);
    glVertex2f(0.471154f, -0.653846f);
    glVertex2f(0.471154f, -0.649573f);
    glVertex2f(0.471154f, -0.645299f);
    glVertex2f(0.471154f, -0.641026f);
    glVertex2f(0.471154f, -0.636752f);
    glVertex2f(0.471154f, -0.632479f);
    glVertex2f(0.471154f, -0.628205f);
    glVertex2f(0.471154f, -0.623932f);
    glVertex2f(0.471154f, -0.619658f);
    glVertex2f(0.471154f, -0.615385f);
    glVertex2f(0.471154f, -0.611111f);
    glVertex2f(0.471154f, -0.606838f);
    glVertex2f(0.471154f, -0.602564f);
    glVertex2f(0.471154f, -0.598291f);
    glVertex2f(0.471154f, -0.594017f);
    glVertex2f(0.471154f, -0.589744f);
    glVertex2f(0.471154f, -0.585470f);
    glVertex2f(0.471154f, -0.581197f);
    glVertex2f(0.471154f, -0.576923f);
    glVertex2f(0.471154f, -0.572650f);
    glVertex2f(0.471154f, -0.568376f);
    glVertex2f(0.471154f, -0.564103f);
    glVertex2f(0.474359f, -0.559829f);
    glVertex2f(0.474359f, -0.555556f);
    glVertex2f(0.474359f, -0.551282f);
    glVertex2f(0.474359f, -0.547009f);
    glVertex2f(0.474359f, -0.542735f);
    glVertex2f(0.471154f, -0.538462f);
    glVertex2f(0.471154f, -0.534188f);
    glVertex2f(0.471154f, -0.529915f);
    glVertex2f(0.471154f, -0.525641f);
    glVertex2f(0.471154f, -0.521368f);
    glVertex2f(0.467949f, -0.517094f);
    glVertex2f(0.467949f, -0.512821f);
    glVertex2f(0.467949f, -0.508547f);
    glVertex2f(0.467949f, -0.504274f);
    glVertex2f(0.467949f, -0.500000f);
    glVertex2f(0.464744f, -0.495726f);
    glVertex2f(0.464744f, -0.491453f);
    glVertex2f(0.464744f, -0.487179f);
    glVertex2f(0.461538f, -0.482906f);
    glVertex2f(0.464744f, -0.478632f);
    glVertex2f(0.467949f, -0.478632f);
    glVertex2f(0.471154f, -0.474359f);
    glVertex2f(0.471154f, -0.470085f);
    glVertex2f(0.471154f, -0.465812f);
    glVertex2f(0.471154f, -0.461538f);
    glVertex2f(0.467949f, -0.457265f);
    glVertex2f(0.467949f, -0.452991f);
    glVertex2f(0.467949f, -0.448718f);
    glVertex2f(0.467949f, -0.444444f);
    glVertex2f(0.467949f, -0.440171f);
    glVertex2f(0.467949f, -0.435897f);
    glVertex2f(0.464744f, -0.431624f);
    glVertex2f(0.464744f, -0.427350f);
    glVertex2f(0.464744f, -0.423077f);
    glVertex2f(0.464744f, -0.418803f);
    glVertex2f(0.464744f, -0.414530f);
    glVertex2f(0.464744f, -0.410256f);
    glVertex2f(0.461538f, -0.405983f);
    glVertex2f(0.461538f, -0.401709f);
    glVertex2f(0.461538f, -0.397436f);
    glVertex2f(0.461538f, -0.393162f);
    glVertex2f(0.461538f, -0.388889f);
    glVertex2f(0.461538f, -0.384615f);
    glVertex2f(0.458333f, -0.380342f);
    glVertex2f(0.458333f, -0.376068f);
    glVertex2f(0.458333f, -0.371795f);
    glVertex2f(0.458333f, -0.367521f);
    glVertex2f(0.458333f, -0.363248f);
    glVertex2f(0.458333f, -0.358974f);
    glVertex2f(0.455128f, -0.354701f);
    glVertex2f(0.455128f, -0.350427f);
    glVertex2f(0.455128f, -0.346154f);
    glVertex2f(0.455128f, -0.341880f);
    glVertex2f(0.455128f, -0.337607f);
    glVertex2f(0.455128f, -0.333333f);
    glVertex2f(0.455128f, -0.329060f);
    glVertex2f(0.455128f, -0.324786f);
    glVertex2f(0.455128f, -0.320513f);
    glVertex2f(0.455128f, -0.316239f);
    glVertex2f(0.451923f, -0.311966f);
    glVertex2f(0.451923f, -0.307692f);
    glVertex2f(0.451923f, -0.303419f);
    glVertex2f(0.451923f, -0.299145f);
    glVertex2f(0.448718f, -0.294872f);
    glVertex2f(0.445513f, -0.290598f);
    glVertex2f(0.442308f, -0.286325f);
    glVertex2f(0.442308f, -0.282051f);
    glVertex2f(0.439103f, -0.277778f);
    glVertex2f(0.439103f, -0.273504f);
    glVertex2f(0.439103f, -0.269231f);
    glVertex2f(0.439103f, -0.264957f);
    glVertex2f(0.439103f, -0.260684f);
    glVertex2f(0.439103f, -0.256410f);
    glVertex2f(0.439103f, -0.252137f);
    glVertex2f(0.435897f, -0.247863f);
    glVertex2f(0.432692f, -0.247863f);
    glVertex2f(0.429487f, -0.243590f);
    glVertex2f(0.426282f, -0.239316f);
    glVertex2f(0.423077f, -0.235043f);
    glVertex2f(0.423077f, -0.230769f);
    glVertex2f(0.423077f, -0.226496f);
    glVertex2f(0.423077f, -0.222222f);
    glVertex2f(0.423077f, -0.217949f);
    glVertex2f(0.423077f, -0.213675f);
    glVertex2f(0.423077f, -0.209402f);
    glVertex2f(0.423077f, -0.205128f);
    glVertex2f(0.423077f, -0.200855f);
    glVertex2f(0.423077f, -0.196581f);
    glVertex2f(0.423077f, -0.192308f);
    glVertex2f(0.419872f, -0.188034f);
    glVertex2f(0.419872f, -0.183761f);
    glVertex2f(0.419872f, -0.179487f);
    glVertex2f(0.419872f, -0.175214f);
    glVertex2f(0.419872f, -0.170940f);
    glVertex2f(0.419872f, -0.166667f);
    glVertex2f(0.416667f, -0.162393f);
    glVertex2f(0.416667f, -0.158120f);
    glVertex2f(0.416667f, -0.153846f);
    glVertex2f(0.419872f, -0.149573f);
    glVertex2f(0.419872f, -0.145299f);
    glVertex2f(0.423077f, -0.141026f);
    glVertex2f(0.423077f, -0.136752f);
    glVertex2f(0.423077f, -0.132479f);
    glVertex2f(0.423077f, -0.128205f);
    glVertex2f(0.423077f, -0.123932f);
    glVertex2f(0.423077f, -0.119658f);
    glVertex2f(0.423077f, -0.115385f);
    glVertex2f(0.423077f, -0.111111f);
    glVertex2f(0.423077f, -0.106838f);
    glVertex2f(0.419872f, -0.102564f);
    glVertex2f(0.416667f, -0.098291f);
    glVertex2f(0.416667f, -0.094017f);
    glVertex2f(0.416667f, -0.089744f);
    glVertex2f(0.413462f, -0.085470f);
    glVertex2f(0.413462f, -0.081197f);
    glVertex2f(0.410256f, -0.076923f);
    glVertex2f(0.410256f, -0.072650f);
    glVertex2f(0.410256f, -0.068376f);
    glVertex2f(0.410256f, -0.064103f);
    glVertex2f(0.410256f, -0.059829f);
    glVertex2f(0.407051f, -0.055556f);
    glVertex2f(0.407051f, -0.051282f);
    glVertex2f(0.407051f, -0.047009f);
    glVertex2f(0.407051f, -0.042735f);
    glVertex2f(0.403846f, -0.038462f);
    glVertex2f(0.403846f, -0.034188f);
    glVertex2f(0.403846f, -0.029915f);
    glVertex2f(0.400641f, -0.025641f);
    glVertex2f(0.400641f, -0.021368f);
    glVertex2f(0.403846f, -0.017094f);
    glVertex2f(0.403846f, -0.012821f);
    glVertex2f(0.403846f, -0.008547f);
    glVertex2f(0.403846f, -0.004274f);
    glVertex2f(0.403846f, -0.000000f);
    glVertex2f(0.400641f, 0.004274f);
    glVertex2f(0.397436f, 0.004274f);
    glVertex2f(0.394231f, -0.000000f);
    glVertex2f(0.394231f, -0.004274f);
    glVertex2f(0.394231f, -0.008547f);
    glVertex2f(0.391026f, -0.012821f);
    glVertex2f(0.387821f, -0.008547f);
    glVertex2f(0.384615f, -0.004274f);
    glVertex2f(0.384615f, -0.000000f);
    glVertex2f(0.384615f, 0.004274f);
    glVertex2f(0.381410f, 0.008547f);
    glVertex2f(0.378205f, 0.008547f);
    glVertex2f(0.375000f, 0.004274f);
    glVertex2f(0.371795f, 0.004274f);
    glVertex2f(0.368590f, 0.004274f);
    glVertex2f(0.368590f, -0.000000f);
    glVertex2f(0.365385f, -0.004274f);
    glVertex2f(0.362179f, -0.008547f);
    glVertex2f(0.358974f, -0.012821f);
    glVertex2f(0.355769f, -0.017094f);
    glVertex2f(0.352564f, -0.017094f);
    glVertex2f(0.349359f, -0.017094f);
    glVertex2f(0.346154f, -0.012821f);
    glVertex2f(0.346154f, -0.008547f);
    glVertex2f(0.342949f, -0.004274f);
    glVertex2f(0.339744f, -0.000000f);
    glVertex2f(0.336538f, 0.004274f);
    glVertex2f(0.333333f, 0.004274f);
    glVertex2f(0.330128f, 0.004274f);
    glVertex2f(0.330128f, -0.000000f);
    glVertex2f(0.330128f, -0.004274f);
    glVertex2f(0.330128f, -0.008547f);
    glVertex2f(0.330128f, -0.012821f);
    glVertex2f(0.330128f, -0.017094f);
    glVertex2f(0.330128f, -0.021368f);
    glVertex2f(0.330128f, -0.025641f);
    glVertex2f(0.333333f, -0.029915f);
    glVertex2f(0.333333f, -0.034188f);
    glVertex2f(0.333333f, -0.038462f);
    glVertex2f(0.333333f, -0.042735f);
    glVertex2f(0.333333f, -0.047009f);
    glVertex2f(0.336538f, -0.051282f);
    glVertex2f(0.336538f, -0.055556f);
    glVertex2f(0.336538f, -0.059829f);
    glVertex2f(0.336538f, -0.064103f);
    glVertex2f(0.333333f, -0.068376f);
    glVertex2f(0.330128f, -0.072650f);
    glVertex2f(0.326923f, -0.076923f);
    glVertex2f(0.323718f, -0.081197f);
    glVertex2f(0.320513f, -0.085470f);
    glVertex2f(0.317308f, -0.085470f);
    glVertex2f(0.314103f, -0.089744f);
    glVertex2f(0.310897f, -0.089744f);
    glVertex2f(0.307692f, -0.094017f);
    glVertex2f(0.304487f, -0.098291f);
    glVertex2f(0.304487f, -0.102564f);
    glVertex2f(0.301282f, -0.106838f);
    glVertex2f(0.301282f, -0.111111f);
    glVertex2f(0.298077f, -0.115385f);
    glVertex2f(0.298077f, -0.119658f);
    glVertex2f(0.294872f, -0.123932f);
    glVertex2f(0.294872f, -0.128205f);
    glVertex2f(0.294872f, -0.132479f);
    glVertex2f(0.294872f, -0.136752f);
    glVertex2f(0.294872f, -0.141026f);
    glVertex2f(0.294872f, -0.145299f);
    glVertex2f(0.294872f, -0.149573f);
    glVertex2f(0.298077f, -0.153846f);
    glVertex2f(0.298077f, -0.158120f);
    glVertex2f(0.298077f, -0.162393f);
    glVertex2f(0.301282f, -0.166667f);
    glVertex2f(0.301282f, -0.170940f);
    glVertex2f(0.301282f, -0.175214f);
    glVertex2f(0.301282f, -0.179487f);
    glVertex2f(0.304487f, -0.183761f);
    glVertex2f(0.304487f, -0.188034f);
    glVertex2f(0.301282f, -0.192308f);
    glVertex2f(0.298077f, -0.196581f);
    glVertex2f(0.294872f, -0.200855f);
    glVertex2f(0.294872f, -0.205128f);
    glVertex2f(0.291667f, -0.209402f);
    glVertex2f(0.288462f, -0.213675f);
    glVertex2f(0.285256f, -0.217949f);
    glVertex2f(0.282051f, -0.217949f);
    glVertex2f(0.278846f, -0.217949f);
    glVertex2f(0.275641f, -0.222222f);
    glVertex2f(0.272436f, -0.222222f);
    glVertex2f(0.269231f, -0.222222f);
    glVertex2f(0.266026f, -0.222222f);
    glVertex2f(0.262821f, -0.226496f);
    glVertex2f(0.259615f, -0.222222f);
    glVertex2f(0.256410f, -0.222222f);
    glVertex2f(0.253205f, -0.222222f);
    glVertex2f(0.250000f, -0.217949f);
    glVertex2f(0.250000f, -0.213675f);
    glVertex2f(0.246795f, -0.209402f);
    glVertex2f(0.246795f, -0.205128f);
    glVertex2f(0.246795f, -0.200855f);
    glVertex2f(0.243590f, -0.196581f);
    glVertex2f(0.243590f, -0.192308f);
    glVertex2f(0.243590f, -0.188034f);
    glVertex2f(0.240385f, -0.183761f);
    glVertex2f(0.240385f, -0.179487f);
    glVertex2f(0.240385f, -0.175214f);
    glVertex2f(0.240385f, -0.170940f);
    glVertex2f(0.237179f, -0.166667f);
    glVertex2f(0.237179f, -0.162393f);
    glVertex2f(0.237179f, -0.158120f);
    glVertex2f(0.233974f, -0.153846f);
    glVertex2f(0.233974f, -0.149573f);
    glVertex2f(0.230769f, -0.145299f);
    glVertex2f(0.227564f, -0.141026f);
    glVertex2f(0.224359f, -0.136752f);
    glVertex2f(0.221154f, -0.136752f);
    glVertex2f(0.217949f, -0.136752f);
    glVertex2f(0.214744f, -0.136752f);
    glVertex2f(0.214744f, -0.141026f);
    glVertex2f(0.211538f, -0.145299f);
    glVertex2f(0.211538f, -0.149573f);
    glVertex2f(0.211538f, -0.153846f);
    glVertex2f(0.211538f, -0.158120f);
    glVertex2f(0.211538f, -0.162393f);
    glVertex2f(0.214744f, -0.166667f);
    glVertex2f(0.214744f, -0.170940f);
    glVertex2f(0.214744f, -0.175214f);
    glVertex2f(0.214744f, -0.179487f);
    glVertex2f(0.214744f, -0.183761f);
    glVertex2f(0.217949f, -0.188034f);
    glVertex2f(0.214744f, -0.192308f);
    glVertex2f(0.211538f, -0.192308f);
    glVertex2f(0.208333f, -0.188034f);
    glVertex2f(0.205128f, -0.183761f);
    glVertex2f(0.205128f, -0.179487f);
    glVertex2f(0.201923f, -0.175214f);
    glVertex2f(0.201923f, -0.170940f);
    glVertex2f(0.201923f, -0.166667f);
    glVertex2f(0.201923f, -0.162393f);
    glVertex2f(0.201923f, -0.158120f);
    glVertex2f(0.201923f, -0.153846f);
    glVertex2f(0.198718f, -0.149573f);
    glVertex2f(0.198718f, -0.145299f);
    glVertex2f(0.198718f, -0.141026f);
    glVertex2f(0.198718f, -0.136752f);
    glVertex2f(0.198718f, -0.132479f);
    glVertex2f(0.198718f, -0.128205f);
    glVertex2f(0.198718f, -0.123932f);
    glVertex2f(0.195513f, -0.119658f);
    glVertex2f(0.195513f, -0.115385f);
    glVertex2f(0.198718f, -0.111111f);
    glVertex2f(0.198718f, -0.106838f);
    glVertex2f(0.198718f, -0.102564f);
    glVertex2f(0.195513f, -0.102564f);
    glVertex2f(0.192308f, -0.098291f);
    glVertex2f(0.192308f, -0.094017f);
    glVertex2f(0.189103f, -0.089744f);
    glVertex2f(0.189103f, -0.085470f);
    glVertex2f(0.189103f, -0.081197f);
    glVertex2f(0.189103f, -0.076923f);
    glVertex2f(0.185897f, -0.072650f);
    glVertex2f(0.185897f, -0.068376f);
    glVertex2f(0.182692f, -0.064103f);
    glVertex2f(0.179487f, -0.059829f);
    glVertex2f(0.176282f, -0.055556f);
    glVertex2f(0.176282f, -0.051282f);
    glVertex2f(0.176282f, -0.047009f);
    glVertex2f(0.176282f, -0.042735f);
    glVertex2f(0.173077f, -0.038462f);
    glVertex2f(0.173077f, -0.034188f);
    glVertex2f(0.169872f, -0.029915f);
    glVertex2f(0.169872f, -0.025641f);
    glVertex2f(0.166667f, -0.021368f);
    glVertex2f(0.169872f, -0.017094f);
    glVertex2f(0.173077f, -0.017094f);
    glVertex2f(0.176282f, -0.012821f);
    glVertex2f(0.176282f, -0.008547f);
    glVertex2f(0.173077f, -0.004274f);
    glVertex2f(0.169872f, -0.004274f);
    glVertex2f(0.166667f, -0.000000f);
    glVertex2f(0.166667f, 0.004274f);
    glVertex2f(0.169872f, 0.008547f);
    glVertex2f(0.173077f, 0.012821f);
    glVertex2f(0.176282f, 0.012821f);
    glVertex2f(0.179487f, 0.012821f);
    glVertex2f(0.182692f, 0.017094f);
    glVertex2f(0.182692f, 0.021368f);
    glVertex2f(0.182692f, 0.025641f);
    glVertex2f(0.185897f, 0.029915f);
    glVertex2f(0.185897f, 0.034188f);
    glVertex2f(0.185897f, 0.038462f);
    glVertex2f(0.185897f, 0.042735f);
    glVertex2f(0.185897f, 0.047009f);
    glVertex2f(0.185897f, 0.051282f);
    glVertex2f(0.182692f, 0.055556f);
    glVertex2f(0.185897f, 0.059829f);
    glVertex2f(0.185897f, 0.064103f);
    glVertex2f(0.189103f, 0.068376f);
    glVertex2f(0.189103f, 0.072650f);
    glVertex2f(0.192308f, 0.076923f);
    glVertex2f(0.195513f, 0.081197f);
    glVertex2f(0.198718f, 0.085470f);
    glVertex2f(0.205128f, 0.085470f);
    glVertex2f(0.208333f, 0.085470f);
    glVertex2f(0.211538f, 0.089744f);
    glVertex2f(0.211538f, 0.094017f);
    glVertex2f(0.211538f, 0.098291f);
    glVertex2f(0.211538f, 0.102564f);
    glVertex2f(0.211538f, 0.106838f);
    glVertex2f(0.211538f, 0.111111f);
    glVertex2f(0.214744f, 0.115385f);
    glVertex2f(0.217949f, 0.119658f);
    glVertex2f(0.221154f, 0.119658f);
    glVertex2f(0.224359f, 0.119658f);
    glVertex2f(0.227564f, 0.119658f);
    glVertex2f(0.230769f, 0.119658f);
    glVertex2f(0.233974f, 0.115385f);
    glVertex2f(0.237179f, 0.115385f);
    glVertex2f(0.240385f, 0.115385f);
    glVertex2f(0.243590f, 0.115385f);
    glVertex2f(0.246795f, 0.115385f);
    glVertex2f(0.250000f, 0.115385f);
    glVertex2f(0.253205f, 0.115385f);
    glVertex2f(0.256410f, 0.115385f);
    glVertex2f(0.259615f, 0.115385f);
    glVertex2f(0.262821f, 0.119658f);
    glVertex2f(0.266026f, 0.123932f);
    glVertex2f(0.266026f, 0.128205f);
    glVertex2f(0.269231f, 0.132479f);
    glVertex2f(0.269231f, 0.136752f);
    glVertex2f(0.269231f, 0.141026f);
    glVertex2f(0.269231f, 0.145299f);
    glVertex2f(0.272436f, 0.149573f);
    glVertex2f(0.275641f, 0.145299f);
    glVertex2f(0.275641f, 0.141026f);
    glVertex2f(0.278846f, 0.136752f);
    glVertex2f(0.282051f, 0.132479f);
    glVertex2f(0.285256f, 0.132479f);
    glVertex2f(0.288462f, 0.132479f);
    glVertex2f(0.291667f, 0.136752f);
    glVertex2f(0.291667f, 0.141026f);
    glVertex2f(0.291667f, 0.145299f);
    glVertex2f(0.291667f, 0.149573f);
    glVertex2f(0.291667f, 0.153846f);
    glVertex2f(0.294872f, 0.158120f);
    glVertex2f(0.298077f, 0.158120f);
    glVertex2f(0.301282f, 0.158120f);
    glVertex2f(0.304487f, 0.158120f);
    glVertex2f(0.307692f, 0.153846f);
    glVertex2f(0.307692f, 0.149573f);
    glVertex2f(0.307692f, 0.145299f);
    glVertex2f(0.310897f, 0.141026f);
    glVertex2f(0.314103f, 0.136752f);
    glVertex2f(0.317308f, 0.136752f);
    glVertex2f(0.320513f, 0.136752f);
    glVertex2f(0.323718f, 0.136752f);
    glVertex2f(0.323718f, 0.141026f);
    glVertex2f(0.326923f, 0.145299f);
    glVertex2f(0.326923f, 0.149573f);
    glVertex2f(0.326923f, 0.153846f);
    glVertex2f(0.326923f, 0.158120f);
    glVertex2f(0.326923f, 0.162393f);
    glVertex2f(0.330128f, 0.166667f);
    glVertex2f(0.330128f, 0.170940f);
    glVertex2f(0.330128f, 0.175214f);
    glVertex2f(0.330128f, 0.179487f);
    glVertex2f(0.326923f, 0.183761f);
    glVertex2f(0.326923f, 0.188034f);
    glVertex2f(0.330128f, 0.192308f);
    glVertex2f(0.333333f, 0.192308f);
    glVertex2f(0.336538f, 0.188034f);
    glVertex2f(0.339744f, 0.188034f);
    glVertex2f(0.342949f, 0.188034f);
    glVertex2f(0.342949f, 0.192308f);
    glVertex2f(0.339744f, 0.196581f);
    glVertex2f(0.339744f, 0.200855f);
    glVertex2f(0.342949f, 0.205128f);
    glVertex2f(0.346154f, 0.205128f);
    glVertex2f(0.349359f, 0.200855f);
    glVertex2f(0.352564f, 0.200855f);
    glVertex2f(0.355769f, 0.200855f);
    glVertex2f(0.358974f, 0.200855f);
    glVertex2f(0.362179f, 0.200855f);
    glVertex2f(0.365385f, 0.205128f);
    glVertex2f(0.368590f, 0.205128f);
    glVertex2f(0.368590f, 0.209402f);
    glVertex2f(0.371795f, 0.213675f);
    glVertex2f(0.371795f, 0.217949f);
    glVertex2f(0.371795f, 0.222222f);
    glVertex2f(0.371795f, 0.226496f);
    glVertex2f(0.371795f, 0.230769f);
    glVertex2f(0.371795f, 0.235043f);
    glVertex2f(0.371795f, 0.239316f);
    glVertex2f(0.371795f, 0.243590f);
    glVertex2f(0.375000f, 0.247863f);
    glVertex2f(0.378205f, 0.252137f);
    glVertex2f(0.381410f, 0.256410f);
    glVertex2f(0.384615f, 0.260684f);
    glVertex2f(0.384615f, 0.264957f);
    glVertex2f(0.384615f, 0.269231f);
    glVertex2f(0.384615f, 0.273504f);
    glVertex2f(0.384615f, 0.277778f);
    glVertex2f(0.387821f, 0.282051f);
    glVertex2f(0.387821f, 0.286325f);
    glVertex2f(0.387821f, 0.290598f);
    glVertex2f(0.391026f, 0.294872f);
    glVertex2f(0.391026f, 0.299145f);
    glVertex2f(0.391026f, 0.303419f);
    glVertex2f(0.394231f, 0.307692f);
    glVertex2f(0.394231f, 0.311966f);
    glVertex2f(0.394231f, 0.316239f);
    glVertex2f(0.397436f, 0.320513f);
    glVertex2f(0.397436f, 0.324786f);
    glVertex2f(0.397436f, 0.329060f);
    glVertex2f(0.397436f, 0.333333f);
    glVertex2f(0.397436f, 0.337607f);
    glVertex2f(0.397436f, 0.341880f);
    glVertex2f(0.397436f, 0.346154f);
    glVertex2f(0.397436f, 0.350427f);
    glVertex2f(0.394231f, 0.354701f);
    glVertex2f(0.394231f, 0.358974f);
    glVertex2f(0.397436f, 0.363248f);
    glVertex2f(0.400641f, 0.363248f);
    glVertex2f(0.403846f, 0.363248f);
    glVertex2f(0.407051f, 0.363248f);
    glVertex2f(0.410256f, 0.363248f);
    glVertex2f(0.413462f, 0.358974f);
    glVertex2f(0.416667f, 0.354701f);
    glVertex2f(0.419872f, 0.354701f);
    glVertex2f(0.423077f, 0.350427f);
    glVertex2f(0.423077f, 0.346154f);
    glVertex2f(0.426282f, 0.346154f);
    glVertex2f(0.429487f, 0.346154f);
    glVertex2f(0.432692f, 0.346154f);
    glVertex2f(0.435897f, 0.350427f);
    glVertex2f(0.439103f, 0.350427f);
    glVertex2f(0.442308f, 0.350427f);
    glVertex2f(0.445513f, 0.354701f);
    glVertex2f(0.448718f, 0.354701f);
    glVertex2f(0.451923f, 0.358974f);
    glVertex2f(0.451923f, 0.363248f);
    glVertex2f(0.451923f, 0.367521f);
    glVertex2f(0.451923f, 0.371795f);
    glVertex2f(0.451923f, 0.376068f);
    glVertex2f(0.448718f, 0.380342f);
    glVertex2f(0.445513f, 0.384615f);
    glVertex2f(0.442308f, 0.388889f);
    glVertex2f(0.439103f, 0.388889f);
    glVertex2f(0.435897f, 0.393162f);
    glVertex2f(0.432692f, 0.397436f);
    glVertex2f(0.429487f, 0.401709f);
    glVertex2f(0.429487f, 0.405983f);
    glVertex2f(0.426282f, 0.410256f);
    glVertex2f(0.423077f, 0.410256f);
    glVertex2f(0.419872f, 0.410256f);
    glVertex2f(0.416667f, 0.414530f);
    glVertex2f(0.416667f, 0.418803f);
    glVertex2f(0.413462f, 0.418803f);
    glVertex2f(0.410256f, 0.423077f);
    glVertex2f(0.407051f, 0.423077f);
    glVertex2f(0.403846f, 0.423077f);
    glVertex2f(0.400641f, 0.423077f);
    glVertex2f(0.397436f, 0.423077f);
    glVertex2f(0.394231f, 0.427350f);
    glVertex2f(0.391026f, 0.431624f);
    glVertex2f(0.387821f, 0.435897f);
    glVertex2f(0.384615f, 0.440171f);
    glVertex2f(0.381410f, 0.440171f);
    glVertex2f(0.378205f, 0.440171f);
    glVertex2f(0.375000f, 0.440171f);
    glVertex2f(0.371795f, 0.444444f);
    glVertex2f(0.368590f, 0.448718f);
    glVertex2f(0.365385f, 0.452991f);
    glVertex2f(0.362179f, 0.452991f);
    glVertex2f(0.358974f, 0.452991f);
    glVertex2f(0.352564f, 0.452991f);
    glVertex2f(0.349359f, 0.452991f);
    glVertex2f(0.346154f, 0.452991f);
    glVertex2f(0.342949f, 0.452991f);
    glVertex2f(0.339744f, 0.452991f);
    glVertex2f(0.336538f, 0.452991f);
    glVertex2f(0.333333f, 0.452991f);
    glVertex2f(0.330128f, 0.452991f);
    glVertex2f(0.326923f, 0.452991f);
    glVertex2f(0.323718f, 0.452991f);
    glVertex2f(0.320513f, 0.452991f);
    glVertex2f(0.317308f, 0.452991f);
    glVertex2f(0.314103f, 0.448718f);
    glVertex2f(0.310897f, 0.448718f);
    glVertex2f(0.307692f, 0.448718f);
    glVertex2f(0.304487f, 0.448718f);
    glVertex2f(0.301282f, 0.448718f);
    glVertex2f(0.298077f, 0.448718f);
    glVertex2f(0.294872f, 0.448718f);
    glVertex2f(0.291667f, 0.448718f);
    glVertex2f(0.288462f, 0.448718f);
    glVertex2f(0.285256f, 0.444444f);
    glVertex2f(0.282051f, 0.444444f);
    glVertex2f(0.278846f, 0.444444f);
    glVertex2f(0.278846f, 0.440171f);
    glVertex2f(0.275641f, 0.435897f);
    glVertex2f(0.272436f, 0.435897f);
    glVertex2f(0.269231f, 0.435897f);
    glVertex2f(0.266026f, 0.435897f);
    glVertex2f(0.262821f, 0.440171f);
    glVertex2f(0.259615f, 0.444444f);
    glVertex2f(0.259615f, 0.448718f);
    glVertex2f(0.256410f, 0.448718f);
    glVertex2f(0.253205f, 0.448718f);
    glVertex2f(0.250000f, 0.444444f);
    glVertex2f(0.246795f, 0.444444f);
    glVertex2f(0.243590f, 0.440171f);
    glVertex2f(0.240385f, 0.440171f);
    glVertex2f(0.237179f, 0.440171f);
    glVertex2f(0.233974f, 0.440171f);
    glVertex2f(0.230769f, 0.440171f);
    glVertex2f(0.227564f, 0.440171f);
    glVertex2f(0.224359f, 0.444444f);
    glVertex2f(0.221154f, 0.444444f);
    glVertex2f(0.217949f, 0.444444f);
    glVertex2f(0.214744f, 0.448718f);
    glVertex2f(0.211538f, 0.448718f);
    glVertex2f(0.208333f, 0.448718f);
    glVertex2f(0.205128f, 0.452991f);
    glVertex2f(0.201923f, 0.452991f);
    glVertex2f(0.198718f, 0.452991f);
    glVertex2f(0.195513f, 0.457265f);
    glVertex2f(0.192308f, 0.457265f);
    glVertex2f(0.189103f, 0.461538f);
    glVertex2f(0.185897f, 0.461538f);
    glVertex2f(0.182692f, 0.457265f);
    glVertex2f(0.179487f, 0.457265f);
    glVertex2f(0.176282f, 0.457265f);
    glVertex2f(0.173077f, 0.457265f);
    glVertex2f(0.169872f, 0.457265f);
    glVertex2f(0.166667f, 0.457265f);
    glVertex2f(0.163462f, 0.457265f);
    glVertex2f(0.160256f, 0.457265f);
    glVertex2f(0.157051f, 0.452991f);
    glVertex2f(0.153846f, 0.452991f);
    glVertex2f(0.150641f, 0.452991f);
    glVertex2f(0.147436f, 0.452991f);
    glVertex2f(0.144231f, 0.452991f);
    glVertex2f(0.141026f, 0.452991f);
    glVertex2f(0.137821f, 0.452991f);
    glVertex2f(0.134615f, 0.448718f);
    glVertex2f(0.131410f, 0.448718f);
    glVertex2f(0.128205f, 0.448718f);
    glVertex2f(0.125000f, 0.444444f);
    glVertex2f(0.121795f, 0.444444f);
    glVertex2f(0.118590f, 0.444444f);
    glVertex2f(0.115385f, 0.444444f);
    glVertex2f(0.112179f, 0.444444f);
    glVertex2f(0.108974f, 0.444444f);
    glVertex2f(0.105769f, 0.444444f);
    glVertex2f(0.102564f, 0.440171f);
    glVertex2f(0.099359f, 0.444444f);
    glVertex2f(0.096154f, 0.444444f);
    glVertex2f(0.092949f, 0.444444f);
    glVertex2f(0.089744f, 0.448718f);
    glVertex2f(0.086538f, 0.448718f);
    glVertex2f(0.083333f, 0.448718f);
    glVertex2f(0.080128f, 0.448718f);
    glVertex2f(0.076923f, 0.444444f);
    glVertex2f(0.073718f, 0.444444f);
    glVertex2f(0.070513f, 0.448718f);
    glVertex2f(0.067308f, 0.448718f);
    glVertex2f(0.064103f, 0.448718f);
    glVertex2f(0.060897f, 0.448718f);
    glVertex2f(0.057692f, 0.448718f);
    glVertex2f(0.054487f, 0.448718f);
    glVertex2f(0.051282f, 0.448718f);
    glVertex2f(0.048077f, 0.448718f);
    glVertex2f(0.044872f, 0.448718f);
    glVertex2f(0.041667f, 0.448718f);
    glVertex2f(0.038462f, 0.448718f);
    glVertex2f(0.035256f, 0.448718f);
    glVertex2f(0.032051f, 0.448718f);
    glVertex2f(0.028846f, 0.448718f);
    glVertex2f(0.025641f, 0.448718f);
    glVertex2f(0.022436f, 0.448718f);
    glVertex2f(0.019231f, 0.444444f);
    glVertex2f(0.016026f, 0.444444f);
    glVertex2f(0.012821f, 0.444444f);
    glVertex2f(0.009615f, 0.444444f);
    glVertex2f(0.006410f, 0.444444f);
    glVertex2f(0.003205f, 0.444444f);
    glVertex2f(0.000000f, 0.448718f);
    glVertex2f(-0.003205f, 0.448718f);
    glVertex2f(-0.006410f, 0.452991f);
    glVertex2f(-0.009615f, 0.452991f);
    glVertex2f(-0.012821f, 0.452991f);
    glVertex2f(-0.016026f, 0.457265f);
    glVertex2f(-0.019231f, 0.457265f);
    glVertex2f(-0.022436f, 0.457265f);
    glVertex2f(-0.025641f, 0.457265f);
    glVertex2f(-0.028846f, 0.457265f);
    glVertex2f(-0.032051f, 0.461538f);
    glVertex2f(-0.035256f, 0.461538f);
    glVertex2f(-0.038462f, 0.461538f);
    glVertex2f(-0.041667f, 0.461538f);
    glVertex2f(-0.044872f, 0.465812f);
    glVertex2f(-0.048077f, 0.465812f);
    glVertex2f(-0.051282f, 0.470085f);
    glVertex2f(-0.054487f, 0.470085f);
    glVertex2f(-0.057692f, 0.470085f);
    glVertex2f(-0.060897f, 0.474359f);
    glVertex2f(-0.064103f, 0.474359f);
    glVertex2f(-0.067308f, 0.478632f);
    glVertex2f(-0.070513f, 0.478632f);
    glVertex2f(-0.076923f, 0.482906f);
    glVertex2f(-0.080128f, 0.482906f);
    glVertex2f(-0.083333f, 0.487179f);
    glVertex2f(-0.086538f, 0.487179f);
    glVertex2f(-0.089744f, 0.491453f);
    glVertex2f(-0.092949f, 0.491453f);
    glVertex2f(-0.096154f, 0.491453f);
    glVertex2f(-0.099359f, 0.487179f);
    glVertex2f(-0.102564f, 0.487179f);
    glVertex2f(-0.105769f, 0.487179f);
    glVertex2f(-0.108974f, 0.491453f);
    glVertex2f(-0.112179f, 0.495726f);
    glVertex2f(-0.112179f, 0.500000f);
    glVertex2f(-0.112179f, 0.504274f);
    glVertex2f(-0.112179f, 0.508547f);
    glVertex2f(-0.115385f, 0.512821f);
    glVertex2f(-0.112179f, 0.517094f);
    glVertex2f(-0.112179f, 0.521368f);
    glVertex2f(-0.112179f, 0.525641f);
    glVertex2f(-0.112179f, 0.529915f);
    glVertex2f(-0.108974f, 0.534188f);
    glVertex2f(-0.108974f, 0.538462f);
    glVertex2f(-0.108974f, 0.542735f);
    glVertex2f(-0.108974f, 0.547009f);
    glVertex2f(-0.108974f, 0.551282f);
    glVertex2f(-0.108974f, 0.555556f);
    glVertex2f(-0.108974f, 0.559829f);
    glVertex2f(-0.108974f, 0.564103f);
    glVertex2f(-0.108974f, 0.568376f);
    glVertex2f(-0.108974f, 0.572650f);
    glVertex2f(-0.105769f, 0.576923f);
    glVertex2f(-0.105769f, 0.581197f);
    glVertex2f(-0.105769f, 0.585470f);
    glVertex2f(-0.105769f, 0.589744f);
    glVertex2f(-0.105769f, 0.594017f);
    glVertex2f(-0.105769f, 0.598291f);
    glVertex2f(-0.105769f, 0.602564f);
    glVertex2f(-0.108974f, 0.606838f);
    glVertex2f(-0.108974f, 0.611111f);
    glVertex2f(-0.108974f, 0.615385f);
    glVertex2f(-0.112179f, 0.619658f);
    glVertex2f(-0.112179f, 0.623932f);
    glVertex2f(-0.112179f, 0.628205f);
    glVertex2f(-0.115385f, 0.632479f);
    glVertex2f(-0.115385f, 0.636752f);
    glVertex2f(-0.115385f, 0.641026f);
    glVertex2f(-0.115385f, 0.645299f);
    glVertex2f(-0.115385f, 0.649573f);
    glVertex2f(-0.115385f, 0.653846f);
    glVertex2f(-0.115385f, 0.658120f);
    glVertex2f(-0.112179f, 0.662393f);
    glVertex2f(-0.112179f, 0.666667f);
    glVertex2f(-0.108974f, 0.670940f);
    glVertex2f(-0.105769f, 0.675214f);
    glVertex2f(-0.105769f, 0.679487f);
    glVertex2f(-0.105769f, 0.683761f);
    glVertex2f(-0.105769f, 0.688034f);
    glVertex2f(-0.108974f, 0.692308f);
    glVertex2f(-0.105769f, 0.696581f);
    glVertex2f(-0.105769f, 0.700855f);
    glVertex2f(-0.108974f, 0.705128f);
    glVertex2f(-0.112179f, 0.705128f);
    glVertex2f(-0.115385f, 0.709402f);
    glVertex2f(-0.118590f, 0.713675f);
    glVertex2f(-0.121795f, 0.717949f);
    glVertex2f(-0.121795f, 0.722222f);
    glVertex2f(-0.121795f, 0.726496f);
    glVertex2f(-0.121795f, 0.730769f);
    glVertex2f(-0.125000f, 0.735043f);
    glVertex2f(-0.125000f, 0.739316f);
    glVertex2f(-0.128205f, 0.743590f);
    glVertex2f(-0.128205f, 0.747863f);
    glVertex2f(-0.128205f, 0.752137f);
    glVertex2f(-0.131410f, 0.756410f);
    glVertex2f(-0.134615f, 0.756410f);
    glVertex2f(-0.137821f, 0.756410f);
    glVertex2f(-0.141026f, 0.756410f);
    glVertex2f(-0.144231f, 0.760684f);
    glVertex2f(-0.144231f, 0.764957f);
    glVertex2f(-0.144231f, 0.769231f);
    glVertex2f(-0.144231f, 0.773504f);
    glVertex2f(-0.144231f, 0.777778f);
    glVertex2f(-0.147436f, 0.777778f);
    glVertex2f(-0.150641f, 0.777778f);
    glVertex2f(-0.153846f, 0.777778f);
    glVertex2f(-0.153846f, 0.773504f);
    glVertex2f(-0.153846f, 0.769231f);
    glVertex2f(-0.153846f, 0.764957f);
    glVertex2f(-0.157051f, 0.760684f);
    glVertex2f(-0.160256f, 0.760684f);
    glVertex2f(-0.163462f, 0.756410f);
    glVertex2f(-0.163462f, 0.752137f);
    glVertex2f(-0.163462f, 0.747863f);
    glVertex2f(-0.160256f, 0.743590f);
    glVertex2f(-0.163462f, 0.739316f);
    glVertex2f(-0.163462f, 0.735043f);
    glVertex2f(-0.160256f, 0.730769f);
    glVertex2f(-0.157051f, 0.726496f);
    glVertex2f(-0.160256f, 0.722222f);
    glVertex2f(-0.163462f, 0.717949f);
    glVertex2f(-0.163462f, 0.713675f);
    glVertex2f(-0.166667f, 0.709402f);
    glVertex2f(-0.166667f, 0.705128f);
    glVertex2f(-0.166667f, 0.700855f);
    glVertex2f(-0.169872f, 0.696581f);
    glVertex2f(-0.173077f, 0.700855f);
    glVertex2f(-0.176282f, 0.705128f);
    glVertex2f(-0.179487f, 0.709402f);
    glVertex2f(-0.182692f, 0.709402f);
    glVertex2f(-0.185897f, 0.705128f);
    glVertex2f(-0.189103f, 0.705128f);
    glVertex2f(-0.192308f, 0.705128f);
    glVertex2f(-0.195513f, 0.709402f);
    glVertex2f(-0.198718f, 0.713675f);
    glVertex2f(-0.201923f, 0.713675f);
    glVertex2f(-0.205128f, 0.709402f);
    glVertex2f(-0.208333f, 0.709402f);
    glVertex2f(-0.211538f, 0.709402f);
    glVertex2f(-0.214744f, 0.709402f);
    glVertex2f(-0.217949f, 0.713675f);
    glVertex2f(-0.221154f, 0.717949f);
    glVertex2f(-0.224359f, 0.722222f);
    glVertex2f(-0.227564f, 0.726496f);
    glVertex2f(-0.230769f, 0.726496f);
    glVertex2f(-0.233974f, 0.730769f);
    glVertex2f(-0.233974f, 0.735043f);
    glVertex2f(-0.237179f, 0.739316f);
    glVertex2f(-0.240385f, 0.743590f);
    glVertex2f(-0.243590f, 0.743590f);
    glVertex2f(-0.246795f, 0.747863f);
    glVertex2f(-0.250000f, 0.747863f);
    glVertex2f(-0.253205f, 0.752137f);
    glVertex2f(-0.256410f, 0.756410f);
    glVertex2f(-0.256410f, 0.760684f);
    glVertex2f(-0.256410f, 0.764957f);
    glVertex2f(-0.259615f, 0.769231f);
    glVertex2f(-0.259615f, 0.773504f);
    glVertex2f(-0.259615f, 0.777778f);
    glVertex2f(-0.259615f, 0.782051f);
    glVertex2f(-0.262821f, 0.786325f);
    glVertex2f(-0.262821f, 0.790598f);
    glVertex2f(-0.266026f, 0.794872f);
    glVertex2f(-0.266026f, 0.799145f);
    glVertex2f(-0.262821f, 0.803419f);
    glVertex2f(-0.259615f, 0.803419f);
    glVertex2f(-0.259615f, 0.807692f);
    glVertex2f(-0.259615f, 0.811966f);
    glVertex2f(-0.262821f, 0.811966f);
    glVertex2f(-0.266026f, 0.816239f);
    glVertex2f(-0.269231f, 0.820513f);
    glVertex2f(-0.269231f, 0.824786f);
    glVertex2f(-0.272436f, 0.829060f);
    glVertex2f(-0.275641f, 0.829060f);
    glVertex2f(-0.278846f, 0.833333f);
    glVertex2f(-0.282051f, 0.837607f);
    glVertex2f(-0.285256f, 0.837607f);
    glVertex2f(-0.288462f, 0.841880f);
    glVertex2f(-0.291667f, 0.846154f);
    glVertex2f(-0.294872f, 0.846154f);
    glVertex2f(-0.298077f, 0.841880f);
    glVertex2f(-0.301282f, 0.837607f);
    glVertex2f(-0.304487f, 0.833333f);
    glVertex2f(-0.304487f, 0.829060f);
    glVertex2f(-0.304487f, 0.824786f);
    glVertex2f(-0.304487f, 0.820513f);
    glVertex2f(-0.301282f, 0.816239f);
    glVertex2f(-0.298077f, 0.816239f);
    glVertex2f(-0.294872f, 0.811966f);
    glVertex2f(-0.291667f, 0.811966f);
    glVertex2f(-0.288462f, 0.807692f);
    glVertex2f(-0.288462f, 0.803419f);
    glVertex2f(-0.288462f, 0.799145f);
    glVertex2f(-0.285256f, 0.799145f);
    glVertex2f(-0.282051f, 0.794872f);
    glVertex2f(-0.282051f, 0.790598f);
    glVertex2f(-0.278846f, 0.790598f);
    glVertex2f(-0.275641f, 0.786325f);
    glVertex2f(-0.278846f, 0.782051f);
    glVertex2f(-0.282051f, 0.782051f);
    glVertex2f(-0.285256f, 0.777778f);
    glVertex2f(-0.288462f, 0.777778f);
    glVertex2f(-0.291667f, 0.782051f);
    glVertex2f(-0.294872f, 0.786325f);
    glVertex2f(-0.298077f, 0.790598f);
    glVertex2f(-0.301282f, 0.794872f);
    glVertex2f(-0.307692f, 0.794872f);
    glVertex2f(-0.310897f, 0.794872f);
    glVertex2f(-0.314103f, 0.790598f);
    glVertex2f(-0.314103f, 0.782051f);
    glVertex2f(-0.317308f, 0.777778f);
    glVertex2f(-0.320513f, 0.782051f);
    glVertex2f(-0.323718f, 0.786325f);
    glVertex2f(-0.323718f, 0.790598f);
    glVertex2f(-0.326923f, 0.794872f);
    glVertex2f(-0.330128f, 0.799145f);
    glVertex2f(-0.333333f, 0.799145f);
    glVertex2f(-0.336538f, 0.799145f);
    glVertex2f(-0.339744f, 0.799145f);
    glVertex2f(-0.342949f, 0.803419f);
    glVertex2f(-0.342949f, 0.807692f);
    glVertex2f(-0.342949f, 0.811966f);
    glVertex2f(-0.342949f, 0.816239f);
    glVertex2f(-0.346154f, 0.820513f);
    glVertex2f(-0.349359f, 0.824786f);
    glVertex2f(-0.349359f, 0.829060f);
    glVertex2f(-0.352564f, 0.833333f);
    glVertex2f(-0.352564f, 0.837607f);
    glVertex2f(-0.355769f, 0.837607f);
    glVertex2f(-0.358974f, 0.841880f);
    glVertex2f(-0.362179f, 0.846154f);
    glVertex2f(-0.365385f, 0.850427f);
    glVertex2f(-0.368590f, 0.854701f);
    glVertex2f(-0.375000f, 0.854701f);
    glVertex2f(-0.378205f, 0.854701f);
    glVertex2f(-0.381410f, 0.858974f);
    glVertex2f(-0.384615f, 0.863248f);
    glVertex2f(-0.387821f, 0.867521f);
    glVertex2f(-0.391026f, 0.871795f);
    glVertex2f(-0.394231f, 0.876068f);
    glVertex2f(-0.397436f, 0.876068f);
    glVertex2f(-0.400641f, 0.876068f);
    glVertex2f(-0.403846f, 0.880342f);
    glVertex2f(-0.407051f, 0.884615f);
    glVertex2f(-0.407051f, 0.888889f);
    glVertex2f(-0.407051f, 0.893162f);
    glVertex2f(-0.407051f, 0.897436f);
    glVertex2f(-0.407051f, 0.901709f);
    glVertex2f(-0.410256f, 0.901709f);
    glEnd();



    // Khulna Region
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.25, -0.5);
    glVertex2f(-0.22, -0.5);
    glVertex2f(-0.22, -0.55);
    glVertex2f(-0.25, -0.55);
    glEnd();

    // Dhaka Region
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.02, 0.14);
    glVertex2f(0.05, 0.14);
    glVertex2f(0.05, 0.09);
    glVertex2f(0.02, 0.09);
    glEnd();

    // Cox's Bazar Region
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.35, -0.60);
    glVertex2f(0.38, -0.60);
    glVertex2f(0.38, -0.65);
    glVertex2f(0.35, -0.65);
    glEnd();


    glFlush();
}































// Dhaka City:



// Function to draw a full circle
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}
void drawHalfCircles(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON); // Use GL_LINE_LOOP for outline only
    for (int i = 0; i <= num_segments; i++) {
        float theta = 3.1415926f * float(i) / float(num_segments); // 0 to PI
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Cloud styles
void drawCloud1(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.05f, 100);
    drawCircle(x + 0.05f, y + 0.02f, 0.06f, 100);
    drawCircle(x + 0.10f, y, 0.05f, 100);
}

void drawCloud2(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.05f, 100);
    drawCircle(x + 0.07f, y + 0.02f, 0.07f, 100);
    drawCircle(x + 0.15f, y, 0.05f, 100);
    drawCircle(x + 0.1f, y - 0.03f, 0.04f, 100);
}

void drawCloud3(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.06f, 100);
    drawCircle(x + 0.04f, y + 0.05f, 0.05f, 100);
    drawCircle(x - 0.04f, y + 0.05f, 0.05f, 100);
}

// Projection
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w > h)
        glOrtho(-1.0f * (w / float(h)), 1.0f * (w / float(h)), -1.0f, 1.0f, -1.0f, 1.0f);
    else
        glOrtho(-1.0f, 1.0f, -1.0f * (h / float(w)), 1.0f * (h / float(w)), -1.0f, 1.0f);
}

// Half circles
void drawHalfCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 3.1416f * float(i) / float(num_segments);
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawHalfCircle1(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 3.1416f * float(i) / float(num_segments);
        float x = r * cos(theta);
        float y = -r * sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawHalfCircle2(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i <= num_segments; i++) {
        float theta = -3.1416f / 2 + (3.1416f * float(i) / float(num_segments));
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawHalfCircle6(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 3.1416f * float(i) / float(num_segments);
        float x = r * cos(theta);
        float y = -r * sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawCloud4(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.08f, 100);
    drawCircle(x + 0.10f, y + 0.05f, 0.08f, 100);
    drawCircle(x - 0.10f, y + 0.05f, 0.08f, 100);
    drawCircle(x + 0.15f, y - 0.05f, 0.08f, 100);
}

void drawCloud5(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.05f, 100);
    drawCircle(x + 0.05f, y + 0.05f, 0.06f, 100);
    drawCircle(x + 0.12f, y + 0.02f, 0.05f, 100);
    drawCircle(x + 0.08f, y - 0.04f, 0.04f, 100);
    drawCircle(x - 0.05f, y + 0.03f, 0.04f, 100);
}

void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}
void drawWindow(float x, float y, float width, float height) {
    float frame = 2.0f;
    drawRectangle(x - frame, y - frame, width + 1.8f * frame, height + 2 * frame, 0.35f, 0.2f, 0.1f); // Frame
    drawRectangle(x, y, width, height, 0.85f, 0.95f, 1.0f); // Glass

    // Grid lines
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
        glVertex2f(x + width / 2, y); glVertex2f(x + width / 2, y + height); // vertical
        glVertex2f(x, y + height / 2); glVertex2f(x + width, y + height / 2); // horizontal
    glEnd();
}
void drawDoor(float x, float y, float width, float height) {
    float frame = 2.5f;
    drawRectangle(x - frame, y - frame, width + 2 * frame, height + 2 * frame,  0.2f, 0.2f, 0.2f); // Frame
    drawRectangle(x, y, width, height, 0.6f, 0.1f, 0.1f); // Door
}


void drawRect(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    const int WIDTH = 800;
const int HEIGHT = 700;
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Draw filled rectangle
void drawRect1(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}
void drawFramedWindow(float x, float y) {
// Frame stays same
drawRect(x - 8, y - 2, 38, 34, 1.0f, 1.0f, 1.0f);


// Adjust window to center within frame
drawRect(x - 4, y, 30, 30, 0.2f, 0.5f, 0.8f);
}



// Draw 2 columns of windows on a tower (5 rows)
void drawTowerWindows(float baseX, float baseY) {
    for (int i = 0; i < 5; ++i) {
        float y = baseY + i * 90; // More spacing
        drawFramedWindow(baseX + 30, y); // Left column
        drawFramedWindow(baseX + 90, y); // Right column
    }
}


// Center red strip windows remain fixed
void drawMiddleStripWindows() {
    for (int i = 0; i < 14; i++) {
        drawFramedWindow(390, 215 + i * 30);
    }
}

// Dual roof
void drawRoof() {
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(220, 640);
    glVertex2f(320, 740);
    glVertex2f(460, 640);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(340, 640);
    glVertex2f(480, 740);
    glVertex2f(581, 640);
    glEnd();
}

// Ground floor doors/garage
void drawGroundFloor() {
    drawRect1(225, 20, 350, 80, 0.4f, 0.1f, 0.1f); // base
    drawRect1(240, 20, 95, 60, 0.1f, 0.1f, 0.1f); // left
    drawRect1(352, 20, 95, 60, 0.1f, 0.1f, 0.1f); // center
    drawRect1(465, 20, 95, 60, 0.1f, 0.1f, 0.1f); // right
}

// Entire building
void drawBuilding() {
    drawRect1(230, 100, 200, 540, 1.0f, 0.8f, 0.6f); // Left tower
    drawRect1(370, 100, 200, 540, 1.0f, 0.8f, 0.6f); // Right tower
    drawRect1(370, 140, 60, 530, 0.8f, 0.2f, 0.2f);  // Center red strip

    drawTowerWindows(230, 200);   // Left windows
    drawTowerWindows(430, 200);   // Right windows
    drawMiddleStripWindows();     // Center windows
    drawRoof();                   // Roof
    drawGroundFloor();           // Base
}

void drawRectangle2(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}

void drawWindow2(float x, float y, float w, float h) {
    // Simulate gradient shading using vertex color interpolation
    glBegin(GL_QUADS);
        glColor3f(0.8f, 0.95f, 1.0f); // Top-left (light)
        glVertex2f(x, y + h);

        glColor3f(0.8f, 0.95f, 1.0f); // Top-right (light)
        glVertex2f(x + w, y + h);

        glColor3f(0.5f, 0.75f, 0.9f); // Bottom-right (darker)
        glVertex2f(x + w, y);

        glColor3f(0.5f, 0.75f, 0.9f); // Bottom-left (darker)
        glVertex2f(x, y);
    glEnd();

    // Optional border
    glColor3f(0.1f, 0.1f, 0.1f); // black border
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}


// Main door
void drawDoor2(float x, float y, float w, float h) {
    drawRectangle2(x, y, w, h, 0.2f, 0.2f, 0.2f);
    glColor3f(0.8f, 0.8f, 0.8f); // handle
    glPointSize(4.0f);
    glBegin(GL_POINTS);
        glVertex2f(x + w - 5, y + h / 2);
    glEnd();
}

// Stairs in front
void drawStairs(float x, float y, float width, int steps, float heightStep) {
    for (int i = 0; i < steps; ++i) {
        drawRectangle2(x - i * 5, y - i * heightStep, width + 2 * i * 5, heightStep, 0.6f - 0.05f * i, 0.6f - 0.05f * i, 0.6f - 0.05f * i);
    }
}

void drawHalfCircle3(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON); // Use GL_LINE_LOOP for outline only
    for (int i = 0; i <= num_segments; i++) {
        float theta = -3.1415926f * float(i) / float(num_segments); // 0 to PI
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawHalfCircle4(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON); // Use GL_LINE_LOOP for outline only
    for (int i = 0; i <= num_segments; i++) {
        float theta = 3.1415926f * float(i) / float(num_segments); // 0 to PI
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawHalfCircle8(float cx, float cy, float r, int num_segments, bool top) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center point

    for (int i = 0; i <= num_segments; ++i) {
        float theta = M_PI * (float(i) / num_segments); // [0, π]

        if (!top) // For bottom half-circle
            theta = -theta;

        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}


const float PI = 3.14159265358979323846f;


void drawCircle8(float cx, float cy, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * float(i) / float(segments); // Angle in radians
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void anglelips(float x,float y,float angle_degree)
{

    float angle = angle_degree * M_PI / 180.0f;
    float cosA = cos(angle);
    float sinA = sin(angle);
    float xx = cosA*x+(-sinA)*y;
    float yy = sinA*x+cosA*y;
    glVertex2d(xx,yy);
}

void drawHalfCircle9(float cx, float cy, float r, int num_segments, bool top) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center point

    for (int i = 0; i <= num_segments; ++i) {
        float theta = M_PI * (float(i) / num_segments); // [0, π]

        if (!top) // For bottom half-circle
            theta = -theta;

        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}

// Function to draw a filled circle at (cx, cy) with given radius
void drawCircle9(float cx, float cy, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * float(i) / float(segments); // Angle in radians
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void dora(float x1,float x2)
{
     glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.55f-x1, 0.37f-0.7f);
        glVertex2f(-0.55f-x1, -0.17f-0.7f);   // body
        glVertex2f(-0.57f-x2, -0.17f-0.7f);
        glVertex2f(-0.57f-x2, 0.37f-0.7f);
    glEnd();
}


// Display function
void Show() {
   if (isDay) {
        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.9f, 1.0f);  // Day sky - Light blue
        glVertex2f(-2.0f, 2.0f);
        glVertex2f(2.0f, 2.0f);
        glColor3f(0.1f, 0.3f, 0.7f);  // Darker blue at the bottom
        glVertex2f(2.0f, -2.0f);
        glVertex2f(-2.0f, -2.0f);
        glEnd();
    } else {
        glBegin(GL_QUADS);
        glColor3f(0.1f, 0.1f, 0.3f);  // Night sky - Dark blue
        glVertex2f(-2.0f, 2.0f);
        glVertex2f(2.0f, 2.0f);
        glColor3f(0.0f, 0.0f, 0.1f);  // Even darker blue at the bottom
        glVertex2f(2.0f, -2.0f);
        glVertex2f(-2.0f, -2.0f);
        glEnd();
    }

    // Drawing sun/moon based on the mode
    if (isDay) {
        glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color for sun
        drawCircle(1.5f, 0.8f, 0.1f, 100);  // Sun in the sky
    } else {
        glColor3f(0.8f, 0.8f, 0.8f);  // Light gray color for moon
        drawCircle(1.5f, 0.8f, 0.1f, 100);  // Moon in the sky
    }

    if (isDay) {
    } else {

        glPointSize(5);
        glBegin(GL_POINTS);
        glColor3f(0.8f, 0.8f, 0.8f);
         glScalef(0.2f, 0.2f, 1.0f);
        glVertex2f(1.f, 0.9f);
        glVertex2f(0.5f, 0.8f);
        glVertex2f(-1.f, 0.9f);
        glVertex2f(-0.5f, 0.8f);
        glVertex2f(0.1f, 0.9f);
        glVertex2f(0.0f, 0.7f);
        glVertex2f(1.8f, 0.85f);
        glVertex2f(-1.5f, 0.85f);
        glVertex2f(-1.8f, 0.7f);
        glVertex2f(-1.65f, 0.6f);
        glVertex2f(1.65f, 0.65f);
        glVertex2f(1.2f, 0.65f);
        glVertex2f(1.f, 0.6f);
        glVertex2f(-1.3f, 0.7f);
        glVertex2f(-1.05f, 0.65f);
        glVertex2f(-0.7f, 0.6f);
        glVertex2f(-.3f, 0.68f);
        glVertex2f(.4f, 0.63f);
         glEnd();
    }


    drawCircle(1.5f, 0.8f, 0.1f, 100);  // Position and radius of the sun

    glPushMatrix();

   glScalef(1.f, 0.7f, 1.0f);
    // Moving cloud
    drawCloud1(-0.8f + cloudOffsetX, 0.8f+0.5f);
    drawCloud2(-0.3f + cloudOffsetX, 0.7f+0.5f);
    drawCloud3(0.1f + cloudOffsetX, 0.85f+0.4f);
    drawCloud1(0.6f + cloudOffsetX, 0.75f+0.5f);
    drawCloud2(1.0f + cloudOffsetX, 0.8f+0.5f);
    drawCloud3(1.5f + cloudOffsetX, 0.7f+0.5f);
    drawCloud4(-1.4f + cloudOffsetX, 0.85f+0.4f); // New cloud shape 4
    drawCloud5(1.8f + cloudOffsetX, 0.85f+0.4f); // New cloud shape 5
    drawCloud2(1.5f + cloudOffsetX, 0.5f+0.5f);
    drawCloud2(0.1f + cloudOffsetX, 0.5f+0.5f);
    drawCloud2(-1.0f + cloudOffsetX, 0.5f+0.5f);
    // Plane


       glPopMatrix();


    glPushMatrix();

    glTranslatef(planeX, 0.65f, 1.0f);
 glScalef(0.2f, 0.2f, 1.0f);

    glBegin(GL_POLYGON); // Plane body
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.65f, -0.2f+0.5f); glVertex2f(-0.65f, -0.2f+0.5f);
    glVertex2f(-0.65f, 0.1f+0.5f); glVertex2f(0.65f, 0.1f+0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Front rectangle
    glVertex2f(0.60f, 0.04f+0.5f); glVertex2f(0.60f, -0.12f+0.5f);
    glVertex2f(0.745f, -0.12f+0.5f); glVertex2f(0.745f, 0.04f+0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Nose cone
    glVertex2f(0.86f, -0.047f+0.5f); glVertex2f(0.85f, -0.12f+0.5f);
    glVertex2f(0.745f, -0.12f+0.5f); glVertex2f(0.732f, 0.06f+0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Lower nose
    glVertex2f(0.85f, -0.107f+0.5f); glVertex2f(0.85f, -0.150f+0.5f);
    glVertex2f(0.70f, -0.20f+0.5f); glVertex2f(0.70f, -0.107f+0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Top tail wing
    glColor3f(.32f, .50f, .64f);
    glVertex2f(-0.65f, 0.1f+0.5f); glVertex2f(-0.95f, 0.08f+0.5f);
    glVertex2f(-1.f, 0.5f+0.5f); glVertex2f(-0.9f, 0.5f+0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Yellow stripe on tail
    glColor3f(.9f, .7f, 0.3f);
    glVertex2f(-0.73f, 0.22f+0.5f); glVertex2f(-0.97f, 0.25f+0.5f);
    glVertex2f(-0.985f, 0.37f+0.5f); glVertex2f(-0.81f, 0.35f+0.5f);
    glEnd();

    drawHalfCircle6(-0.65f, 0.1f+0.5f, 0.3f, 200); // Round tail

    glColor3f(.32f, .50f, .64f); // Windows
    float startX = -0.6f, centerY = 0.0f+0.5f, radius = 0.03f;
    for (int i = 0; i < 12; ++i)
        drawCircle(startX + i * 0.1f, centerY, radius, 100);

    drawHalfCircle(0.65f, 0.0f+0.5f, 0.1f, 200);
    drawHalfCircle1(0.65f, -0.1f+0.5f, 0.1f, 200);
    drawHalfCircle2(0.68f, -0.1f+0.5f, 0.1f, 200);
    drawHalfCircle2(0.70f, -0.1f+0.5f, 0.1f, 200);
    drawHalfCircle2(0.72f, -0.09f+0.5f, 0.1f, 200);
    drawHalfCircle2(0.85f, -0.1f+0.5f, 0.05f, 200);

    glBegin(GL_POLYGON); // Bottom stripe
    glColor3f(.9f, .7f, 0.3f);
    glVertex2f(0.55f, -0.06f+0.5f); glVertex2f(0.65f, -0.14f+0.5f);
    glVertex2f(-0.83f, -0.14f+0.5f); glVertex2f(-0.9f, -0.06f+0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Top windshield
    glColor3f(.32f, .50f, .64f);
    glVertex2f(0.65f, -0.04f+0.5f); glVertex2f(0.82f, -0.05f+0.5f);
    glVertex2f(0.7f, 0.04f+0.5f); glVertex2f(0.57f, 0.04f+0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Top fin
    glVertex2f(0.0f, .1f+0.5f); glVertex2f(-0.2f, .1f+0.5f);
    glVertex2f(-0.4f, 0.24f+0.5f); glVertex2f(-0.3f, 0.24f+0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Bottom fin
    glVertex2f(0.2f, -.1f+0.5f); glVertex2f(-0.2f, -.1f+0.5f);
    glVertex2f(-0.4f, -0.44f+0.5f); glVertex2f(-0.25f, -0.44f+0.5f);
    glEnd();

    glPopMatrix();



    ///////



    glPushMatrix();               // Save the current matrix
    glScalef(.008f, 0.008f, 2.0f);
glTranslatef(-235, -20, 0.0f);   // Translate the whole scene by (tx, ty)


glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(2, 0);
    glVertex2f(23, 0);
    glVertex2f(23, 90.0);
    glVertex2f(2, 80.0);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue

    glBegin(GL_POLYGON);
    glVertex2f(5, 0);
    glVertex2f(20, 0);
    glVertex2f(20, 82.0);
    glVertex2f(5, 75.0);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(5, 6);
    glVertex2f(20, 6);
    glVertex2f(20, 9);
    glVertex2f(5, 9);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 0);
    glVertex2f(9, 0);
    glVertex2f(9, 9);
    glVertex2f(8, 9);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(16, 0);
    glVertex2f(17, 0);
    glVertex2f(17, 9);
    glVertex2f(16, 9);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 12);
    glVertex2f(25, 12);
    glVertex2f(25, 14);
    glVertex2f(8, 14);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 17);
    glVertex2f(25, 17);
    glVertex2f(25, 19);
    glVertex2f(8, 19);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 22);
    glVertex2f(25, 22);
    glVertex2f(25, 24);
    glVertex2f(8, 24);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 27);
    glVertex2f(25, 27);
    glVertex2f(25, 29);
    glVertex2f(8, 29);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 32);
    glVertex2f(25, 32);
    glVertex2f(25, 34);
    glVertex2f(8, 34);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 37);
    glVertex2f(25, 37);
    glVertex2f(25, 39);
    glVertex2f(8, 39);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 42);
    glVertex2f(25, 42);
    glVertex2f(25, 44);
    glVertex2f(8, 44);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 47);
    glVertex2f(25, 47);
    glVertex2f(25, 49);
    glVertex2f(8, 49);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 52);
    glVertex2f(25, 52);
    glVertex2f(25, 54);
    glVertex2f(8, 54);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 57);
    glVertex2f(25, 57);
    glVertex2f(25, 59);
    glVertex2f(8, 59);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 62);
    glVertex2f(25, 62);
    glVertex2f(25, 64);
    glVertex2f(8, 64);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 67);
    glVertex2f(25, 67);
    glVertex2f(25, 73);
    glVertex2f(8, 69);
    glEnd();

glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(20, 75);
    glVertex2f(20, 77.0);
    glVertex2f(5, 74);
    glVertex2f(5, 71.0);
    glEnd();

    glPopMatrix();                // Restore the matrix




    //////

    glPushMatrix();
     glScalef(.008f, 0.008f, 2.0f);           // Save the current matrix
glTranslatef(80, -20, 0.0f);   // Translate the whole scene by (tx, ty)

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue
    glBegin(GL_POLYGON);
    glVertex2f(5, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 75.0);
    glVertex2f(5, 75.0);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 5);
    glVertex2f(32, 5);
    glVertex2f(32, 10.0);
    glVertex2f(3, 10.0);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 13);
    glVertex2f(32, 13);
    glVertex2f(32, 15.0);
    glVertex2f(3, 15.0);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 18);
    glVertex2f(32, 18);
    glVertex2f(32, 20.0);
    glVertex2f(3, 20.0);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 23);
    glVertex2f(32, 23);
    glVertex2f(32, 25.0);
    glVertex2f(3, 25.0);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 28);
    glVertex2f(32, 28);
    glVertex2f(32, 30.0);
    glVertex2f(3, 30.0);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 33);
    glVertex2f(32, 33);
    glVertex2f(32, 35);
    glVertex2f(3, 35);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 38);
    glVertex2f(32, 38);
    glVertex2f(32, 40);
    glVertex2f(3, 40);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 43);
    glVertex2f(32, 43);
    glVertex2f(32, 45);
    glVertex2f(3, 45);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 48);
    glVertex2f(32, 48);
    glVertex2f(32, 50);
    glVertex2f(3, 50);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 53);
    glVertex2f(32, 53);
    glVertex2f(32, 55);
    glVertex2f(3, 55);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 58);
    glVertex2f(32, 58);
    glVertex2f(32, 60);
    glVertex2f(3, 60);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 63);
    glVertex2f(32, 63);
    glVertex2f(32, 65);
    glVertex2f(3, 65);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 68);
    glVertex2f(32, 68);
    glVertex2f(32, 70);
    glVertex2f(3, 70);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(3, 73);
    glVertex2f(32, 73);
    glVertex2f(32, 77);
    glVertex2f(3, 77);
    glEnd();

    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex2f(2, 79);
    glVertex2f(33, 79);
    glVertex2f(33, 77);
    glVertex2f(2, 77);
    glEnd();

    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(11, 73);
    glVertex2f(15, 73);
    glVertex2f(15, 10);
    glVertex2f(11, 10);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 0);
    glVertex2f(11, 0);
    glVertex2f(11, 10);
    glVertex2f(8, 10);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(24, 0);
    glVertex2f(27, 0);
    glVertex2f(27, 10);
    glVertex2f(24, 10);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(17, 0);
    glVertex2f(18, 0);
    glVertex2f(18, 10);
    glVertex2f(17, 10);
    glEnd();


glPopMatrix();

//////

 glPushMatrix();
    glScalef(.008f, 0.008f, 2.0f);                 // Save the current matrix
glTranslatef(-123, -20, 0.0f);   // Translate the whole scene by (tx, ty)

    glColor3f(0.74f, 0.8f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(5, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 75.0);
    glVertex2f(5, 75.0);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue

    glBegin(GL_POLYGON);
    glVertex2f(3, 0);
    glVertex2f(32, 0);
    glVertex2f(32, 10.0);
    glVertex2f(3, 10.0);
    glEnd();
 glColor3f(0.64f, 0.7f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(3, 0);
    glVertex2f(5, 0);
    glVertex2f(5, 10.0);
    glVertex2f(3, 10.0);
    glEnd();

 glColor3f(0.64f, 0.7f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(3+5, 0);
    glVertex2f(5+5, 0);
    glVertex2f(5+5, 10.0);
    glVertex2f(3+5, 10.0);
    glEnd();

 glColor3f(0.64f, 0.7f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(30, 0);
    glVertex2f(32, 0);
    glVertex2f(32, 10.0);
    glVertex2f(30, 10.0);
    glEnd();
 glColor3f(0.64f, 0.7f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(30-5, 0);
    glVertex2f(32-5, 0);
    glVertex2f(32-5, 10.0);
    glVertex2f(30-5, 10.0);
    glEnd();

 glColor3f(0.64f, 0.7f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(3, 8);
    glVertex2f(32, 8);
    glVertex2f(32, 10.0);
    glVertex2f(3, 10.0);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue

    glBegin(GL_POLYGON);
    glVertex2f(14, 73);
    glVertex2f(21, 73);
    glVertex2f(21, 10.0);
    glVertex2f(14, 10.0);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 18);
    glVertex2f(29, 18);
    glVertex2f(29, 16.0);
    glVertex2f(6, 16.0);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 21);
    glVertex2f(29, 21);
    glVertex2f(29, 23);
    glVertex2f(6, 23);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 26);
    glVertex2f(29, 26);
    glVertex2f(29, 28);
    glVertex2f(6, 28);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 31);
    glVertex2f(29, 31);
    glVertex2f(29, 33);
    glVertex2f(6, 33);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 36);
    glVertex2f(29, 36);
    glVertex2f(29, 38);
    glVertex2f(6, 38);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 41);
    glVertex2f(29, 41);
    glVertex2f(29, 43);
    glVertex2f(6, 43);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(6, 46);
    glVertex2f(29, 46);
    glVertex2f(29, 48);
    glVertex2f(6, 48);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 51);
    glVertex2f(29, 51);
    glVertex2f(29, 53);
    glVertex2f(6, 53);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 56);
    glVertex2f(29, 56);
    glVertex2f(29, 58);
    glVertex2f(6, 58);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(6, 61);
    glVertex2f(29, 61);
    glVertex2f(29, 63);
    glVertex2f(6, 63);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 66);
    glVertex2f(29, 66);
    glVertex2f(29, 68);
    glVertex2f(6, 68);
    glEnd();



    glBegin(GL_POLYGON);
    glVertex2f(6, 71);
    glVertex2f(29, 71);
    glVertex2f(29, 73);
    glVertex2f(6, 73);
    glEnd();

 glColor3f(0.74f, 0.8f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(9, 73);
    glVertex2f(10, 73);
    glVertex2f(10, 10.0);
    glVertex2f(9, 10.0);
    glEnd();

 glColor3f(0.74f, 0.8f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(14, 73);
    glVertex2f(15, 73);
    glVertex2f(15, 10.0);
    glVertex2f(14, 10.0);
    glEnd();

 glColor3f(0.74f, 0.8f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(25, 73);
    glVertex2f(26, 73);
    glVertex2f(26, 10.0);
    glVertex2f(25, 10.0);
    glEnd();

 glColor3f(0.74f, 0.8f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(20, 73);
    glVertex2f(21, 73);
    glVertex2f(21, 10.0);
    glVertex2f(20, 10.0);
    glEnd();

  glColor3f(0.74f, 0.8f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(5, 80);
    glVertex2f(30,80);
    glVertex2f(30, 75.0);
    glVertex2f(5, 75.0);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue

    glBegin(GL_POLYGON);
    glVertex2f(6, 78);
    glVertex2f(29,78);
    glVertex2f(29, 75.0);
    glVertex2f(6, 75.0);
    glEnd();


 glColor3f(0.64f, 0.7f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(5, 80);
    glVertex2f(30,80);
    glVertex2f(30, 82);
    glVertex2f(5, 82);
    glEnd();
 glColor3f(0.64f, 0.7f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(7, 84);
    glVertex2f(28,84);
    glVertex2f(28, 82);
    glVertex2f(7, 82);
    glEnd();

     glColor3f(0.64f, 0.7f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(9, 84);
    glVertex2f(26,84);
    glVertex2f(26, 86);
    glVertex2f(9, 86);
    glEnd();


    glColor3f(1.f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(17.2, 100);
    glVertex2f(17.8,100);
    glVertex2f(17.8, 86);
    glVertex2f(17.2, 86);
    glEnd();

        glColor3f(0.0f, 0.4f, 0.7f); // blue-ish color
    drawHalfCircles(17.5, 86,5, 100); // center at (0,0), radius 0.5


glPopMatrix();

////

glPushMatrix();
   glScalef(.008f, 0.008f, 2.0f);                 // Save the current matrix
glTranslatef(50, -20, 0.0f);   // Translate the whole scene by (tx, ty)

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue


    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(30,0);
    glVertex2f(30, 75);
    glVertex2f(0, 75);
    glEnd();



 glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(30,0);
    glVertex2f(30, 75);
    glVertex2f(20, 75);
    glEnd();


glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 70.5);
    glVertex2f(30 ,70.5);
    glVertex2f(30,70);
    glVertex2f(0, 70);
    glEnd();

glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 66.5);
    glVertex2f(30 ,66.5);
    glVertex2f(30,66);
    glVertex2f(0, 66);
    glEnd();

glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 62.5);
    glVertex2f(30 ,62.5);
    glVertex2f(30,62);
    glVertex2f(0, 62);
    glEnd();

glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 58.5);
    glVertex2f(30 ,58.5);
    glVertex2f(30,58);
    glVertex2f(0, 58);
    glEnd();

glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 54.5);
    glVertex2f(30 ,54.5);
    glVertex2f(30,54);
    glVertex2f(0, 54);
    glEnd();

glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 54.5);
    glVertex2f(30 ,54.5);
    glVertex2f(30,54);
    glVertex2f(0, 54);
    glEnd();

glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 50.5);
    glVertex2f(30 ,50.5);
    glVertex2f(30,50);
    glVertex2f(0, 50);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 46.5);
    glVertex2f(30 ,46.5);
    glVertex2f(30,46);
    glVertex2f(0, 46);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 42.5);
    glVertex2f(30 ,42.5);
    glVertex2f(30,42);
    glVertex2f(0, 42);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 38.5);
    glVertex2f(30 ,38.5);
    glVertex2f(30,38);
    glVertex2f(0, 38);
    glEnd();

        glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 34.5);
    glVertex2f(30 ,34.5);
    glVertex2f(30,34);
    glVertex2f(0, 34);
    glEnd();


     glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 30.5);
    glVertex2f(30 ,30.5);
    glVertex2f(30,30);
    glVertex2f(0, 30);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 26.5);
    glVertex2f(30 ,26.5);
    glVertex2f(30,26);
    glVertex2f(0, 26);
    glEnd();


    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 22.5);
    glVertex2f(30 ,22.5);
    glVertex2f(30,22);
    glVertex2f(0, 22);
    glEnd();


     glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 18.5);
    glVertex2f(30 ,18.5);
    glVertex2f(30,18);
    glVertex2f(0, 18);
    glEnd();

      glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 14.5);
    glVertex2f(30 ,14.5);
    glVertex2f(30,14);
    glVertex2f(0, 14);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 10.5);
    glVertex2f(30 ,10.5);
    glVertex2f(30,10);
    glVertex2f(0, 10);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 6.5);
    glVertex2f(30 ,6.5);
    glVertex2f(30,6);
    glVertex2f(0, 6);
    glEnd();

glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(5, 75);
    glVertex2f(5.5,75);
    glVertex2f(5.5,2);
    glVertex2f(5, 2);
    glEnd();


         glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(16, 75);
    glVertex2f(16.5,75);
    glVertex2f(16.5,2);
    glVertex2f(16, 2);
    glEnd();

       glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(27, 75);
    glVertex2f(27.5,75);
    glVertex2f(27.5,2);
    glVertex2f(27, 2);
    glEnd();

     glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 73);
    glVertex2f(0 ,75);
    glVertex2f(30,75);
    glVertex2f(30, 73);
    glEnd();
           glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(23, 75);
    glVertex2f(23.5,75);
    glVertex2f(23.5,2);
    glVertex2f(23, 2);
    glEnd();



 glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(10, 0);
    glVertex2f(13,0);
    glVertex2f(13, 75);
    glVertex2f(10, 75);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(35, 0);
    glVertex2f(-20,0);
    glVertex2f(-20,2);
    glVertex2f(35, 2);
    glEnd();

        glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 73);
    glVertex2f(0 ,75);
    glVertex2f(30,75);
    glVertex2f(30, 73);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue
    glBegin(GL_POLYGON);
    glVertex2f(10, 30);
    glVertex2f(-13,30);
    glVertex2f(-13,57);
    glVertex2f(10, 57);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(10, 30);
    glVertex2f(-15,30);
    glVertex2f(-15,32);
    glVertex2f(10, 32);
    glEnd();

        glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(10, 35);
    glVertex2f(-15,35);
    glVertex2f(-15,37);
    glVertex2f(10, 37);
    glEnd();

            glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(10, 40);
    glVertex2f(-15,40);
    glVertex2f(-15,42);
    glVertex2f(10, 42);
    glEnd();

     glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(10, 45);
    glVertex2f(-15,45);
    glVertex2f(-15,47);
    glVertex2f(10, 47);
    glEnd();

     glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(10, 50);
    glVertex2f(-15,50);
    glVertex2f(-15,52);
    glVertex2f(10, 52);
    glEnd();

      glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(10, 55);
    glVertex2f(-15,55);
    glVertex2f(-15,57);
    glVertex2f(10, 57);
    glEnd();

          glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-11, 30);
    glVertex2f(-13,30);
    glVertex2f(-13,0);
    glVertex2f(-11, 0);
    glEnd();


glPopMatrix();


glPushMatrix();
   glScalef(.0015f, 0.001f, 2.0f);                 // Save the current matrix
glTranslatef(-1170, -220, 0.0f);   // Translate the whole scene by (tx, ty)

 drawRectangle(55, 100, 85, 280, 1.0f, 0.7f, 0.4f); // left wall (peach)

    // Windows (3 rows x 2 cols)
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 2; ++col)
            drawWindow(65 + col * 40, 170 + row * 70, 25, 43);

    // Door with frame
    drawDoor(83, 100, 30, 45);



    // ===== MIDDLE BUILDING =====
    drawRectangle(140, 60, 90, 220, 0.8f, 0.3f, 0.2f); // middle wall (red-orange)

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 2; ++col)
            drawWindow(150 + col * 40, 100 + row * 55, 30, 42);

     //gound Chimney
    drawRectangle(51, 70, 92, 30, 0.4f, 0.4f, 0.4f);

    //gound
    drawRectangle(51, 60, 92, 10, 0.8f, 0.8f, 0.8f);

    // Stairs (2 steps)
    drawRectangle(78, 90, 40, 10, 0.5f, 0.5f, 0.5f);
    drawRectangle(73, 80, 50, 10, 0.6f, 0.6f, 0.6f);
    drawRectangle(67, 70, 62, 10, 0.7f, 0.7f, 0.7f);

    // Chimney
    drawRectangle(150, 280, 13, 25, 0.5f, 0.2f, 0.2f);



    // ===== RIGHT TOWER =====
    drawRectangle(230, 60, 35, 265, 1.0f, 0.7f, 0.4f); // tower wall

    // Roof caps
    drawRectangle(225, 325, 45, 10, 0.35f, 0.2f, 0.1f); // tower cap
    drawRectangle(138, 280, 93, 5, 0.35f, 0.2f, 0.1f);  // middle cap
    drawRectangle(52, 380, 92, 5, 0.35f, 0.2f, 0.1f);   // left cap
    drawRectangle(147, 300, 19, 5, 0.35f, 0.2f, 0.1f);

    // Tower window with frame
    float tx = 238, ty = 260, tw = 20, th = 40;
    float frame = 2.0f;
    drawRectangle(tx - frame, ty - frame, tw + 1.5f * frame, th + 2 * frame, 0.35f, 0.2f, 0.1f); // frame
    drawRectangle(tx, ty, tw, th, 0.75f, 0.95f, 1.0f); // glass
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
        glVertex2f(tx + tw / 2, ty); glVertex2f(tx + tw / 2, ty + th);
        glVertex2f(tx, ty + th / 2); glVertex2f(tx + tw, ty + th / 2);
    glEnd();
glPopMatrix();


  /////
glPushMatrix();
   glScalef(.001f, 0.001f, 2.0f);                 // Save the current matrix
glTranslatef(-1610, -245, 0.0f);
   float frameColor[3] = {0.85f, 0.88f, 1.0f};   // Light purple-blue
    float glassColor[3] = {0.25f, 0.6f, 0.8f};    // Teal blue

    // ==== Right tower (Glass Grid) ====
    drawRect(400, 100, 220, 505, frameColor[0], frameColor[1], frameColor[2]); // Tower frame
    for (int row = 0; row < 18; row++) {
        for (int col = 0; col < 5; col++) {
            drawRect(400 + col * 27, 100 + row * 27.5, 25, 26, glassColor[0], glassColor[1], glassColor[2]);
        }
    }

    // double glass
    drawRect(534, 100, 85, 494, 0.1f, 0.24f, 0.32f);
    //glass

    for (int row = 0; row < 18; row++) {
        for (int col = 0; col < 4; col++) {
            drawRect(534 + col * 22, 100 + row * 27.5, 20, 25.5, 0.85f, 0.88f, 1.0f);
        }
    }


    // ==== Vertical blue stripe (between parts) ====
    drawRect(470, 100, 25, 505, 0.85f, 0.88f, 1.0f);

    // ==== Left structure with floors ====


    // Vertical line at far left
    drawRect(290, 100, 15, 300, frameColor[0], frameColor[1], frameColor[2]);

    // Entrance supports

    drawRect(250, 85, 400, 15, 0.85f, 0.88f, 1.0f); // base slab

    // Vertical blue glass panel below floors
    drawRect(290, 235, 180, 250, 0.25f, 0.6f, 0.8f);

    for (int i = 0; i < 7; ++i) {
        drawRect(275, 230 + i * 40, 200, 15, 0.85f, 0.88f, 1.0f); // floors
    }
glPopMatrix();

glPushMatrix();
   glScalef(.001f, 0.001f, 2.0f);                 // Save the current matrix
glTranslatef(1300, -190, 0.0f);   // Translate the whole scene by (tx, ty)
    drawBuilding();
    glPopMatrix();



    glPushMatrix();
   glScalef(.001f, 0.001f, 2.0f);                 // Save the current matrix
glTranslatef(1180, -240, 0.0f);
     drawRectangle2(50, 65, 80, 245, 0.85f, 0.85f, 0.9f);

    // Windows left wing
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 2; ++col)
            drawWindow2(52 + col * 37, 67 + row * 80, 39, 78);

    // === RIGHT WING ===
    drawRectangle2(270, 65, 80, 245, 0.85f, 0.85f, 0.9f);

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 2; ++col)
            drawWindow2(272 + col * 37, 67 + row * 80, 39, 78);

    // === CENTER TOWER ===
    drawRectangle2(130, 65, 140, 315, 0.75f, 0.75f, 0.85f);

    // Windows center
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            drawWindow2(132 + col * 45, 67 + row * 104, 45, 102);

    // === MAIN DOOR ===
    drawDoor2(175, 70, 50, 60);

    // === STAIRS ===
    drawStairs(175, 70, 50, 3, 7);
  glPopMatrix();



  glPushMatrix();
   glScalef(.0015f, 0.0015f, 2.0f);                 // Save the current matrix
glTranslatef(-550, -170, 0.0f);


   drawRectangle(110, 60, 140, 470, 1.0f, 0.6f, 0.3f);
    drawRectangle(250, 60, 80, 380, 0.94f, 0.87f, 0.75f);
    drawRectangle(70, 60, 40, 450, 0.8f, 0.35f, 0.0f);

    drawRectangle(128, 110, 103, 14, 1.0f, 1.0f, 1.0f); drawRectangle(221, 60, 07, 55, 1.0f, 1.0f, 1.0f);
    drawRectangle(132, 60, 07, 55, 1.0f, 1.0f, 1.0f); drawRectangle(146, 60, 68, 44, 0.6f, 0.2f, 0.0f);
    drawRectangle(150, 60, 60, 40, 1.0f, 0.9f, 0.8f); drawRectangle(178, 60, 02, 40, 0.8f, 0.35f, 0.0f);
    drawRectangle(153, 77, 20, 20, 0.0f, 0.5f, 0.7f); drawRectangle(187, 77, 20, 20, 0.0f, 0.5f, 0.7f);

    float winWidt = 20, winHeigh = 15, frameThick = 2;
    float sX = 120, sY = 140;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 6; ++j) {
            float x = sX + j * 20, y = sY + i * 38;
            drawRectangle(x - frameThick, y - frameThick, winWidt + 2 * frameThick, winHeigh + 2 * frameThick, 1.0f, 1.0f, 1.0f);
            drawRectangle(x, y, winWidt, winHeigh, 0.0f, 0.6f, 0.9f);
        }

    for (int i = 0; i < 8; ++i) {
        float y = 140 + i * 38;
        drawRectangle(260 - frameThick, y - frameThick, winWidt + 2 * frameThick, winHeigh + 2 * frameThick, 1.0f, 1.0f, 1.0f);
        drawRectangle(260, y, winWidt, winHeigh, 0.0f, 0.6f, 0.9f);
        drawRectangle(300 - frameThick, y - frameThick, winWidt + 2 * frameThick, winHeigh + 2 * frameThick, 1.0f, 1.0f, 1.0f);
        drawRectangle(300, y, winWidt, winHeigh, 0.0f, 0.6f, 0.9f);
    }

    for (int i = 0; i < 10; ++i) {
        float y = 140 + i * 38;
        drawRectangle(80 - frameThick, y - frameThick, winWidt + 2 * frameThick, winHeigh + 2 * frameThick, 1.0f, 1.0f, 1.0f);
        drawRectangle(80, y, winWidt, winHeigh, 0.03f, 0.6f, 0.9f);
    }
    glPopMatrix();


     glPushMatrix();               // Save the current matrix
    glScalef(.008f, 0.008f, 2.0f);
glTranslatef(-43, -20, 0.0f);   // Translate the whole scene by (tx, ty)


glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(2, 0);
    glVertex2f(23, 0);
    glVertex2f(23, 90.0);
    glVertex2f(2, 80.0);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue

    glBegin(GL_POLYGON);
    glVertex2f(5, 0);
    glVertex2f(20, 0);
    glVertex2f(20, 82.0);
    glVertex2f(5, 75.0);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(5, 6);
    glVertex2f(20, 6);
    glVertex2f(20, 9);
    glVertex2f(5, 9);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 0);
    glVertex2f(9, 0);
    glVertex2f(9, 9);
    glVertex2f(8, 9);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(16, 0);
    glVertex2f(17, 0);
    glVertex2f(17, 9);
    glVertex2f(16, 9);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 12);
    glVertex2f(25, 12);
    glVertex2f(25, 14);
    glVertex2f(8, 14);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 17);
    glVertex2f(25, 17);
    glVertex2f(25, 19);
    glVertex2f(8, 19);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 22);
    glVertex2f(25, 22);
    glVertex2f(25, 24);
    glVertex2f(8, 24);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 27);
    glVertex2f(25, 27);
    glVertex2f(25, 29);
    glVertex2f(8, 29);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 32);
    glVertex2f(25, 32);
    glVertex2f(25, 34);
    glVertex2f(8, 34);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 37);
    glVertex2f(25, 37);
    glVertex2f(25, 39);
    glVertex2f(8, 39);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 42);
    glVertex2f(25, 42);
    glVertex2f(25, 44);
    glVertex2f(8, 44);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 47);
    glVertex2f(25, 47);
    glVertex2f(25, 49);
    glVertex2f(8, 49);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 52);
    glVertex2f(25, 52);
    glVertex2f(25, 54);
    glVertex2f(8, 54);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 57);
    glVertex2f(25, 57);
    glVertex2f(25, 59);
    glVertex2f(8, 59);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 62);
    glVertex2f(25, 62);
    glVertex2f(25, 64);
    glVertex2f(8, 64);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(8, 67);
    glVertex2f(25, 67);
    glVertex2f(25, 73);
    glVertex2f(8, 69);
    glEnd();

glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(20, 75);
    glVertex2f(20, 77.0);
    glVertex2f(5, 74);
    glVertex2f(5, 71.0);
    glEnd();

    glPopMatrix();                // Restore the matrix



     glPushMatrix();
   glScalef(.0015f, 0.0015f, 2.0f);                 // Save the current matrix
glTranslatef(-160, -170, 0.0f);


   drawRectangle(110, 60, 140, 470, 0.2f, 0.3f, 0.4f);
    drawRectangle(250, 60, 80, 380, 0.94f, 0.6f, 0.7f);
    drawRectangle(70, 60, 40, 450, 0.7f, 0.2f, 0.0f);

    drawRectangle(128, 110, 103, 14, 1.0f, 1.0f, 1.0f); drawRectangle(221, 60, 07, 55, 1.0f, 1.0f, 1.0f);
    drawRectangle(132, 60, 07, 55, 1.0f, 1.0f, 1.0f); drawRectangle(146, 60, 68, 44, 0.6f, 0.2f, 0.0f);
    drawRectangle(150, 60, 60, 40, 1.0f, 0.9f, 0.8f); drawRectangle(178, 60, 02, 40, 0.8f, 0.35f, 0.0f);
    drawRectangle(153, 77, 20, 20, 0.0f, 0.5f, 0.7f); drawRectangle(187, 77, 20, 20, 0.0f, 0.5f, 0.7f);

    float winWidta = 20, winHeigha = 15, frameThicka = 2;
    float sXa = 120, sYa = 140;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 6; ++j) {
            float x = sXa + j * 20, y = sYa + i * 38;
            drawRectangle(x - frameThicka, y - frameThick, winWidta + 2 * frameThicka, winHeigha + 2 * frameThicka, 1.0f, 1.0f, 1.0f);
            drawRectangle(x, y, winWidta, winHeigha, 0.0f, 0.6f, 0.9f);
        }

    for (int i = 0; i < 8; ++i) {
        float y = 140 + i * 38;
        drawRectangle(260 - frameThicka, y - frameThicka, winWidta + 2 * frameThicka, winHeigha + 2 * frameThicka, 1.0f, 1.0f, 1.0f);
        drawRectangle(260, y, winWidta, winHeigha, 0.0f, 0.6f, 0.9f);
        drawRectangle(300 - frameThicka, y - frameThicka, winWidta + 2 * frameThicka, winHeigha + 2 * frameThicka, 1.0f, 1.0f, 1.0f);
        drawRectangle(300, y, winWidta, winHeigha, 0.0f, 0.6f, 0.9f);
    }

    for (int i = 0; i < 10; ++i) {
        float y = 140 + i * 38;
        drawRectangle(80 - frameThicka, y - frameThicka, winWidta + 2 * frameThicka, winHeigha + 2 * frameThicka, 1.0f, 1.0f, 1.0f);
        drawRectangle(80, y, winWidta, winHeigha, 0.03f, 0.6f, 0.9f);
    }
    glPopMatrix();
 glPushMatrix();
    glScalef(.009f, 0.009f, 2.0f);                 // Save the current matrix
glTranslatef(97, -18, 0.0f);   // Translate the whole scene by (tx, ty)

    glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(5, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 75.0);
    glVertex2f(5, 75.0);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue

    glBegin(GL_POLYGON);
    glVertex2f(3, 0);
    glVertex2f(32, 0);
    glVertex2f(32, 10.0);
    glVertex2f(3, 10.0);
    glEnd();
glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(3, 0);
    glVertex2f(5, 0);
    glVertex2f(5, 10.0);
    glVertex2f(3, 10.0);
    glEnd();

 glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(3+5, 0);
    glVertex2f(5+5, 0);
    glVertex2f(5+5, 10.0);
    glVertex2f(3+5, 10.0);
    glEnd();

 glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(30, 0);
    glVertex2f(32, 0);
    glVertex2f(32, 10.0);
    glVertex2f(30, 10.0);
    glEnd();
glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(30-5, 0);
    glVertex2f(32-5, 0);
    glVertex2f(32-5, 10.0);
    glVertex2f(30-5, 10.0);
    glEnd();

glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(3, 8);
    glVertex2f(32, 8);
    glVertex2f(32, 10.0);
    glVertex2f(3, 10.0);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue

    glBegin(GL_POLYGON);
    glVertex2f(14, 73);
    glVertex2f(21, 73);
    glVertex2f(21, 10.0);
    glVertex2f(14, 10.0);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 18);
    glVertex2f(29, 18);
    glVertex2f(29, 16.0);
    glVertex2f(6, 16.0);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 21);
    glVertex2f(29, 21);
    glVertex2f(29, 23);
    glVertex2f(6, 23);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 26);
    glVertex2f(29, 26);
    glVertex2f(29, 28);
    glVertex2f(6, 28);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 31);
    glVertex2f(29, 31);
    glVertex2f(29, 33);
    glVertex2f(6, 33);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 36);
    glVertex2f(29, 36);
    glVertex2f(29, 38);
    glVertex2f(6, 38);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 41);
    glVertex2f(29, 41);
    glVertex2f(29, 43);
    glVertex2f(6, 43);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(6, 46);
    glVertex2f(29, 46);
    glVertex2f(29, 48);
    glVertex2f(6, 48);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 51);
    glVertex2f(29, 51);
    glVertex2f(29, 53);
    glVertex2f(6, 53);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 56);
    glVertex2f(29, 56);
    glVertex2f(29, 58);
    glVertex2f(6, 58);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(6, 61);
    glVertex2f(29, 61);
    glVertex2f(29, 63);
    glVertex2f(6, 63);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(6, 66);
    glVertex2f(29, 66);
    glVertex2f(29, 68);
    glVertex2f(6, 68);
    glEnd();



    glBegin(GL_POLYGON);
    glVertex2f(6, 71);
    glVertex2f(29, 71);
    glVertex2f(29, 73);
    glVertex2f(6, 73);
    glEnd();

glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(9, 73);
    glVertex2f(10, 73);
    glVertex2f(10, 10.0);
    glVertex2f(9, 10.0);
    glEnd();

glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(14, 73);
    glVertex2f(15, 73);
    glVertex2f(15, 10.0);
    glVertex2f(14, 10.0);
    glEnd();

glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(25, 73);
    glVertex2f(26, 73);
    glVertex2f(26, 10.0);
    glVertex2f(25, 10.0);
    glEnd();

glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(20, 73);
    glVertex2f(21, 73);
    glVertex2f(21, 10.0);
    glVertex2f(20, 10.0);
    glEnd();

glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(5, 80);
    glVertex2f(30,80);
    glVertex2f(30, 75.0);
    glVertex2f(5, 75.0);
    glEnd();

if (isYellow)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.0f, 0.6f, 0.7f); // Original Light Blue

    glBegin(GL_POLYGON);
    glVertex2f(6, 78);
    glVertex2f(29,78);
    glVertex2f(29, 75.0);
    glVertex2f(6, 75.0);
    glEnd();


 glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(5, 80);
    glVertex2f(30,80);
    glVertex2f(30, 82);
    glVertex2f(5, 82);
    glEnd();
glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(7, 84);
    glVertex2f(28,84);
    glVertex2f(28, 82);
    glVertex2f(7, 82);
    glEnd();

 glColor3f(1.f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(9, 84);
    glVertex2f(26,84);
    glVertex2f(26, 86);
    glVertex2f(9, 86);
    glEnd();


glColor3f(0.0f, 0.4f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(17.2, 100);
    glVertex2f(17.8,100);
    glVertex2f(17.8, 86);
    glVertex2f(17.2, 86);
    glEnd();

        glColor3f(0.7f, 0.8f, 0.8f); // blue-ish color
    drawHalfCircles(17.5, 86,5, 100); // center at (0,0), radius 0.5


glPopMatrix();


glPushMatrix(); // Save current matrix
    glTranslatef(trainPosX, 0.0f, 0.0f); // Move train
  glScalef(.5f, 0.5f, 2.0f);

glColor3f(1.0f, 1.0f, 1.0f); // blue-ish color
    drawHalfCircle4(-1.535f, 0.0f, 0.3f, 100); // center at (0,0), radius 0.5
 drawHalfCircle4(1.535f+0.65f, 0.0f, 0.3f, 100);

 glColor3f(0.3f, 0.3f, 0.3f);
 drawHalfCircle4(-1.665f, 0.25f, 0.01f, 100);


drawHalfCircle4(-1.55f, 0.0f, 0.28f, 100); // center at (0,0), radius 0.5
drawHalfCircle4(2.2f, 0.0f, 0.28f, 100);
 glColor3f(0.0f, 0.8f, 0.0f);
 drawHalfCircle4(-1.635f, 0.26f, 0.02f, 100);
  drawHalfCircle4(1.635f+0.65f, 0.26f, 0.02f, 100);

 glColor3f(1.0f, 1.0f, 1.0f);
 drawHalfCircle4(-1.5f, 0.1f, 0.1f, 100);
 drawHalfCircle4(1.5f+0.65f, 0.1f, 0.1f, 100);


        glBegin(GL_POLYGON);             // front head
    glColor3f(1.0f,1.0f, 1.0f);
    glVertex2f(-1.535f,0.0);
    glVertex2f(-1.535f,0.1);
     glVertex2f(-1.81f,0.1);
  glVertex2f(-1.825f,0.06);
    glVertex2f(-1.83f,0.0);


    glEnd();

    glBegin(GL_POLYGON);             // front head
    glColor3f(1.0f,1.0f, 1.0f);
    glVertex2f(.535f+0.65f,0.0);
    glVertex2f(1.535f+0.65f,0.1);
     glVertex2f(1.81f+0.65f,0.1);
  glVertex2f(1.825f+0.65f,0.06);
    glVertex2f(1.83f+0.65f,0.0);


    glEnd();


    glBegin(GL_POLYGON);            //train body
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-1.535f,0.0);
    glVertex2f(-1.535f,0.3);
    glVertex2f(2.2f,0.3);
    glVertex2f(2.2f,0.0);
    glEnd();


    glBegin(GL_POLYGON);             // body  1st top
    glColor3f(0.0f,0.8f, 0.0f);
    glVertex2f(-1.625f,0.28);
    glVertex2f(-1.625f,0.26);
    glVertex2f(2.25f,0.26);
    glVertex2f(2.3f,0.28);
    glEnd();


    glBegin(GL_POLYGON);              //body 2nd top
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(-1.67f,0.25);
    glVertex2f(-1.67f,0.26);
    glVertex2f(2.3f,0.26);
    glVertex2f(2.3f,0.25);
    glEnd();


    glBegin(GL_POLYGON);               // 10th window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(.09f+1.5f,0.23);
    glVertex2f(0.09f+1.5f,0.09);
    glVertex2f(0.31f+1.5f,0.09);
    glVertex2f(0.31f+1.5f,0.23);
    glEnd();



    glBegin(GL_POLYGON);              //  9th window
   if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.1f+1.5f,0.22);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.1f+1.5f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.3f+1.5f,0.1);
  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.3f+1.5f,0.22);
    glEnd();

    glBegin(GL_POLYGON);               // 9th window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(.34f+1.5f,0.23);
    glVertex2f(0.34f+1.5f,0.09);
    glVertex2f(0.56f+1.5f,0.09);
    glVertex2f(0.56f+1.5f,0.23);
    glEnd();

    glBegin(GL_POLYGON);              //  10th window
  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.35f+1.5f,0.22);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.35f+1.5f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.55f+1.5f,0.1);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.55f+1.5f,0.22);
    glEnd();


    glBegin(GL_POLYGON);               // 8th window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(.09f,0.23);
    glVertex2f(0.09f,0.09);
    glVertex2f(0.31f,0.09);
    glVertex2f(0.31f,0.23);
    glEnd();



    glBegin(GL_POLYGON);              //  8th window
  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.1f,0.22);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.1f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.3f,0.1);
 if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.3f,0.22);
    glEnd();

    glBegin(GL_POLYGON);               // 7th window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(.34f,0.23);
    glVertex2f(0.34f,0.09);
    glVertex2f(0.56f,0.09);
    glVertex2f(0.56f,0.23);
    glEnd();

    glBegin(GL_POLYGON);              //  7th window
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.35f,0.22);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.35f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.55f,0.1);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.55f,0.22);
    glEnd();


    glBegin(GL_POLYGON);               // 1st door cover
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(.6f,0.26);
    glVertex2f(0.6f,0.0);
    glVertex2f(0.8f,0.0);
    glVertex2f(0.8f,0.26);
    glEnd();

     glBegin(GL_POLYGON);               // 3rd door cover red line
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(.62f,0.25);
    glVertex2f(0.62f,0.0);
    glVertex2f(0.75f,0.0);
    glVertex2f(0.75f,0.25);
    glEnd();

 glBegin(GL_POLYGON);               // 1st door left
    glColor3f(1.f, 1.0f, 1.0f);
    glVertex2f(.62f,0.25);
    glVertex2f(0.62f,0.0);
    glVertex2f(0.695f,0.0);
    glVertex2f(0.695f,0.25);
    glEnd();

glBegin(GL_POLYGON);               // 1st door right
    glColor3f(1.f, 1.0f, 1.0f);
    glVertex2f(.705f,0.25);
    glVertex2f(0.705f,0.0);
    glVertex2f(0.78f,0.0);
    glVertex2f(0.78f,0.25);
    glEnd();

  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    drawHalfCircle4(0.658f, 0.20f, 0.03f, 100); // center at (0,0), radius 0.5
    drawHalfCircle4(0.744f, 0.20f, 0.03f, 100);
    glColor3f(0.8f, 0.8f, 0.8f);
    drawHalfCircle3(0.658f, 0.12f, 0.03f, 100);
    drawHalfCircle3(0.744f, 0.12f, 0.03f, 100);

glBegin(GL_POLYGON);               // 1st door left
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(.628f,0.202);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.6875f,0.202);
    glColor3f(0.8f, 0.8f, 0.8f);
     glVertex2f(0.6875f,0.12);
       glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.628f,0.12);

    glEnd();

    glBegin(GL_POLYGON);               // 1st door right
  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(.712f,0.202);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.774f,0.202);
    glColor3f(0.8f, 0.8f, 0.8f);
     glVertex2f(0.774f,0.12);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.712f,0.12);

    glEnd();

      glBegin(GL_POLYGON);               // 6th window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(.84f,0.23);
    glVertex2f(0.84f,0.09);
    glVertex2f(1.06f,0.09);
    glVertex2f(1.06f,0.23);
    glEnd();

    glBegin(GL_POLYGON);              //  6th window
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.85f,0.22);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.85f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(1.05f,0.1);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(1.05f,0.22);
    glEnd();

    glBegin(GL_POLYGON);               // 5th window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(1.31f,0.23);
    glVertex2f(1.31f,0.09);
    glVertex2f(1.09f,0.09);
    glVertex2f(1.09f,0.23);
    glEnd();

    glBegin(GL_POLYGON);              //  5th window
 if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(1.30f,0.22);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(1.30f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(1.10f,0.1);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(1.10f,0.22);
    glEnd();



    glBegin(GL_POLYGON);               // 4th door cover
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(1.55f,0.26);
    glVertex2f(1.55f,0.0);
    glVertex2f(1.35f,0.0);
    glVertex2f(1.35f,0.26);
    glEnd();

     glBegin(GL_POLYGON);               // 4th door cover red line
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(.62f+0.75f,0.25);
    glVertex2f(0.62f+0.75f,0.0);
    glVertex2f(0.75f+0.75f,0.0);
    glVertex2f(0.75f+0.75f,0.25);
    glEnd();

 glBegin(GL_POLYGON);               // 4th door left
    glColor3f(1.f, 1.0f, 1.0f);
    glVertex2f(0.62f+0.75f,0.25);
    glVertex2f(0.62f+0.75f,0.0);
    glVertex2f(0.695f+0.75f,0.0);
    glVertex2f(0.695f+0.75f,0.25);
    glEnd();

glBegin(GL_POLYGON);               // 4th door right
    glColor3f(1.f, 1.0f, 1.0f);
    glVertex2f(.705f+0.75f,0.25);
    glVertex2f(0.705f+0.75f,0.0);
    glVertex2f(0.78f+0.75f,0.0);
    glVertex2f(0.78f+0.75f,0.25);
    glEnd();

  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    drawHalfCircle4(0.658f+0.75f, 0.20f, 0.03f, 100); // center at (0,0), radius 0.5
    drawHalfCircle4(0.743f+0.75f, 0.20f, 0.03f, 100);
    glColor3f(0.8f, 0.8f, 0.8f);
    drawHalfCircle3(0.658f+0.75f, 0.12f, 0.03f, 100);
    drawHalfCircle3(0.744f+0.75f, 0.12f, 0.03f, 100);

glBegin(GL_POLYGON);               // 4th door left
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(.628f+0.75f,0.202);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.6875f+0.75f,0.202);
    glColor3f(0.8f, 0.8f, 0.8f);
     glVertex2f(0.6875f+0.75f,0.12);
       glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.628f+0.75f,0.12);

    glEnd();

    glBegin(GL_POLYGON);               // 4th door right
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(.712f+0.75f,0.202);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.774f+0.75f,0.202);
    glColor3f(0.8f, 0.8f, 0.8f);
     glVertex2f(0.774f+0.75f,0.12);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.712f+0.75f,0.12);

    glEnd();

     glBegin(GL_POLYGON);               // 4th window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(.09f-0.75f,0.23);
    glVertex2f(0.09f-0.75f,0.09);
    glVertex2f(0.31f-0.75f,0.09);
    glVertex2f(0.31f-0.75f,0.23);
    glEnd();


    glBegin(GL_POLYGON);              //   4th window
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.1f-0.75f,0.22);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.1f-0.75f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.3f-0.75f,0.1);
  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.3f-0.75f,0.22);
    glEnd();

    glBegin(GL_POLYGON);               // 3rd window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(.34f-0.75f,0.23);
    glVertex2f(0.34f-0.75f,0.09);
    glVertex2f(0.56f-0.75f,0.09);
    glVertex2f(0.56f-0.75f,0.23);
    glEnd();

    glBegin(GL_POLYGON);              //  3rd window
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.35f-0.75f,0.22);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.35f-0.75f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.55f-0.75f,0.1);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.55f-0.75f,0.22);
    glEnd();



     glBegin(GL_POLYGON);               // 2nd window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(.09f-0.75f-0.75f,0.23);
    glVertex2f(0.09f-0.75f-0.75f,0.09);
    glVertex2f(0.31f-0.75f-0.75f,0.09);
    glVertex2f(0.31f-0.75f-0.75f,0.23);
    glEnd();


    glBegin(GL_POLYGON);              //  2nd window
 if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.1f-0.75f-0.75f,0.22);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.1f-0.75f-0.75f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.3f-0.75f-0.75f,0.1);
  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.3f-0.75f-0.75f,0.22);
    glEnd();

    glBegin(GL_POLYGON);               // 1st window cover
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(0.34f-0.75f-0.75f,0.23);
    glVertex2f(0.34f-0.75f-0.75f,0.09);
    glVertex2f(0.56f-0.75f-0.75f,0.09);
    glVertex2f(0.56f-0.75f-0.75f,0.23);
    glEnd();



    glBegin(GL_POLYGON);              //  1st window
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.35f-0.75f-0.75f,0.22);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.35f-0.75f-0.75f,0.1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.55f-0.75f-0.75f,0.1);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.55f-0.75f-0.75f,0.22);
    glEnd();

 glBegin(GL_POLYGON);               // 2nd door cover
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(.6f-0.75f,0.26);
    glVertex2f(0.6f-0.75f,0.0);
    glVertex2f(0.8f-0.75f,0.0);
    glVertex2f(0.8f-0.75f,0.26);
    glEnd();

    glBegin(GL_POLYGON);               // 2nd door cover red line
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(.62f-0.75f,0.25);
    glVertex2f(0.62f-0.75f,0.0);
    glVertex2f(0.75f-0.75f,0.0);
    glVertex2f(0.75f-0.75f,0.25);
    glEnd();



 glBegin(GL_POLYGON);               // 2nf door left
    glColor3f(1.f, 1.0f, 1.0f);
    glVertex2f(.62f-0.75f,0.25);
    glVertex2f(0.62f-0.75f,0.0);
    glVertex2f(0.695f-0.75f,0.0);
    glVertex2f(0.695f-0.75f,0.25);
    glEnd();

glBegin(GL_POLYGON);               // 2nd door right
    glColor3f(1.f, 1.0f, 1.0f);
    glVertex2f(.705f-0.75f,0.25);
    glVertex2f(0.705f-0.75f,0.0);
    glVertex2f(0.78f-0.75f,0.0);
    glVertex2f(0.78f-0.75f,0.25);
    glEnd();

if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    drawHalfCircle4(0.658f-0.75f, 0.20f, 0.03f, 100); // center at (0,0), radius 0.5
    drawHalfCircle4(0.744f-0.75f, 0.20f, 0.03f, 100);
    glColor3f(0.8f, 0.8f, 0.8f);
    drawHalfCircle3(0.658f-0.75f, 0.12f, 0.03f, 100);
    drawHalfCircle3(0.744f-0.75f, 0.12f, 0.03f, 100);

glBegin(GL_POLYGON);               //  2nd door left
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(.628f-0.75f,0.202);
  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.6875f-0.75f,0.202);
    glColor3f(0.8f, 0.8f, 0.8f);
     glVertex2f(0.6875f-0.75f,0.12);
       glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.628f-0.75f,0.12);

    glEnd();

    glBegin(GL_POLYGON);               // 2nd door right
 if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(.712f-0.75f,0.202);
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.774f-0.75f,0.202);
    glColor3f(0.8f, 0.8f, 0.8f);
     glVertex2f(0.774f-0.75f,0.12);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.712f-0.75f,0.12);

    glEnd();

    glBegin(GL_POLYGON);               // 1st door cover
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(.6f-0.75f-0.75f,0.26);
    glVertex2f(0.6f-0.75f-0.75f,0.0);
    glVertex2f(0.8f-0.75f-0.75f,0.0);
    glVertex2f(0.8f-0.75f-0.75f,0.26);
    glEnd();

    glBegin(GL_POLYGON);               // 1st door cover red line
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(.62f-0.75f-0.75f,0.25);
    glVertex2f(0.62f-0.75f-0.75f,0.0);
    glVertex2f(0.75f-0.75f-0.75f,0.0);
    glVertex2f(0.75f-0.75f-0.75f,0.25);
    glEnd();

 glBegin(GL_POLYGON);               // 1st door left
    glColor3f(1.f, 1.0f, 1.0f);
    glVertex2f(.62f-0.75f-0.75f,0.25);
    glVertex2f(0.62f-0.75f-0.75f,0.0);
    glVertex2f(0.695f-0.75f-0.75f,0.0);
    glVertex2f(0.695f-0.75f-0.75f,0.25);
    glEnd();

glBegin(GL_POLYGON);               // 1st door right
    glColor3f(1.f, 1.0f, 1.0f);
    glVertex2f(.705f-0.75f-0.75f,0.25);
    glVertex2f(0.705f-0.75f-0.75f,0.0);
    glVertex2f(0.78f-0.75f-0.75f,0.0);
    glVertex2f(0.78f-0.75f-0.75f,0.25);
    glEnd();

 if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    drawHalfCircle4(0.658f-0.75f-0.75f, 0.20f, 0.03f, 100); // center at (0,0), radius 0.5
    drawHalfCircle4(0.744f-0.75f-0.75f, 0.20f, 0.03f, 100);
    glColor3f(0.8f, 0.8f, 0.8f);
    drawHalfCircle3(0.658f-0.75f-0.75f, 0.12f, 0.03f, 100);
    drawHalfCircle3(0.744f-0.75f-0.75f, 0.12f, 0.03f, 100);

glBegin(GL_POLYGON);               // 1st door left
if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(.628f-0.75f-0.75f,0.202);
 if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.6875f-0.75f-0.75f,0.202);
    glColor3f(0.8f, 0.8f, 0.8f);
     glVertex2f(0.6875f-0.75f-0.75f,0.12);
       glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.628f-0.75f-0.75f,0.12);

    glEnd();

    glBegin(GL_POLYGON);               // 1st door right
  if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(.712f-0.75f-0.75f,0.202);
 if (changeColor)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
else
    glColor3f(0.1f, 0.4f, 0.6f); // Original Blue
    glVertex2f(0.774f-0.75f-0.75f,0.202);
    glColor3f(0.8f, 0.8f, 0.8f);
     glVertex2f(0.774f-0.75f-0.75f,0.12);
     glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.712f-0.75f-0.75f,0.12);

    glEnd();

  glPopMatrix();


     glBegin(GL_POLYGON);               //foothpath
glColor3f(0.9569f, 0.6431f, 0.3765f);

    glVertex2f(3,-0.16);
    glVertex2f(-3,-0.16);
    glVertex2f(-3,-0.2);
    glVertex2f(3,-.2);
    glEnd();





glBegin(GL_POLYGON);                  // road
glColor3f(0.3f, 0.3f, 0.3f);

    glVertex2f(3,-0.9);
    glVertex2f(-3,-0.9);
    glVertex2f(-3,-0.2);
    glVertex2f(3,-.2);
    glEnd();



         glBegin(GL_POLYGON);
glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2f(3,-0.21);
    glVertex2f(-3,-0.21);
    glVertex2f(-3,-0.2);
    glVertex2f(3,-.2);
    glEnd();

            glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(2,-0.21);
    glVertex2f(1.8,-0.21);
    glVertex2f(1.8,-0.2);
    glVertex2f(2,-.2);
    glEnd();

             glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1.6,-0.21);
    glVertex2f(1.4,-0.21);
    glVertex2f(1.4,-0.2);
    glVertex2f(1.6,-.2);
    glEnd();


                 glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1.2,-0.21);
    glVertex2f(1.0,-0.21);
    glVertex2f(1.0,-0.2);
    glVertex2f(1.2,-.2);
    glEnd();

                     glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.8,-0.21);
    glVertex2f(0.6,-0.21);
    glVertex2f(0.6,-0.2);
    glVertex2f(0.8,-.2);
    glEnd();


                         glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.4,-0.21);
    glVertex2f(0.2,-0.21);
    glVertex2f(0.2,-0.2);
    glVertex2f(0.4,-.2);
    glEnd();

                             glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.4,-0.21);
    glVertex2f(0.2,-0.21);
    glVertex2f(0.2,-0.2);
    glVertex2f(0.4,-.2);
    glEnd();

                             glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.0,-0.21);
    glVertex2f(-0.2,-0.21);
    glVertex2f(-0.2,-0.2);
    glVertex2f(0.0,-.2);
    glEnd();

                                 glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.4,-0.21);
    glVertex2f(-0.6,-0.21);
    glVertex2f(-0.6,-0.2);
    glVertex2f(-0.4,-.2);
    glEnd();

                                     glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.8,-0.21);
    glVertex2f(-1.0,-0.21);
    glVertex2f(-1.0,-0.2);
    glVertex2f(-0.8,-.2);
    glEnd();


                                         glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-1.2,-0.21);
    glVertex2f(-1.4,-0.21);
    glVertex2f(-1.4,-0.2);
    glVertex2f(-1.2,-.2);
    glEnd();

glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-1.6,-0.21);
    glVertex2f(-1.8,-0.21);
    glVertex2f(-1.8,-0.2);
    glVertex2f(-1.6,-.2);
    glEnd();




glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-1.57,-0.32);
    glVertex2f(-1.8,-0.32);
    glVertex2f(-1.83,-0.34);
    glVertex2f(-1.6,-0.34);
    glEnd();

glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-1.37,-0.32);
    glVertex2f(-1.1,-0.32);
    glVertex2f(-1.13,-0.34);
    glVertex2f(-1.4,-0.34);
    glEnd();

    glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.57,-0.32);
    glVertex2f(-0.9,-0.32);
    glVertex2f(-0.93,-0.34);
    glVertex2f(-0.6,-0.34);
    glEnd();

glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.37,-0.32);
    glVertex2f(-0.1,-0.32);
    glVertex2f(-0.13,-0.34);
    glVertex2f(-0.4,-0.34);
    glEnd();


    glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.4,-0.32);
    glVertex2f(0.13,-0.32);
    glVertex2f(0.1,-0.34);
    glVertex2f(0.37,-0.34);
    glEnd();


        glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.6,-0.32);
    glVertex2f(0.93,-0.32);
    glVertex2f(0.9,-0.34);
    glVertex2f(0.57,-0.34);
    glEnd();


    glBegin(GL_POLYGON);                  // foothpath down
glColor3f(0.333f, 0.4196f, 0.1843f);;

    glVertex2f(3,-0.9);
    glVertex2f(-3,-0.9);
    glVertex2f(-3,-1.0);
    glVertex2f(3,-1.0);
    glEnd();


    glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1.6,-0.32);
    glVertex2f(1.83,-0.32);
    glVertex2f(1.8,-0.34);
    glVertex2f(1.57,-0.34);
    glEnd();

glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1.4,-0.32);
    glVertex2f(1.13,-0.32);
    glVertex2f(1.1,-0.34);
    glVertex2f(1.37,-0.34);
    glEnd();



glPushMatrix();
glTranslatef(0.0f, -0.3f, 0.0f);
glScalef(1.0f, 1.2f, 2.0f);

glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-1.57,-0.32);
    glVertex2f(-1.8,-0.32);
    glVertex2f(-1.83,-0.34);
    glVertex2f(-1.6,-0.34);
    glEnd();

glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-1.37,-0.32);
    glVertex2f(-1.1,-0.32);
    glVertex2f(-1.13,-0.34);
    glVertex2f(-1.4,-0.34);
    glEnd();

    glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.57,-0.32);
    glVertex2f(-0.9,-0.32);
    glVertex2f(-0.93,-0.34);
    glVertex2f(-0.6,-0.34);
    glEnd();

glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.37,-0.32);
    glVertex2f(-0.1,-0.32);
    glVertex2f(-0.13,-0.34);
    glVertex2f(-0.4,-0.34);
    glEnd();


    glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.4,-0.32);
    glVertex2f(0.13,-0.32);
    glVertex2f(0.1,-0.34);
    glVertex2f(0.37,-0.34);
    glEnd();


        glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.6,-0.32);
    glVertex2f(0.93,-0.32);
    glVertex2f(0.9,-0.34);
    glVertex2f(0.57,-0.34);
    glEnd();


    glBegin(GL_POLYGON);                  // foothpath down
glColor3f(0.333f, 0.4196f, 0.1843f);;

    glVertex2f(3,-0.9);
    glVertex2f(-3,-0.9);
    glVertex2f(-3,-1.0);
    glVertex2f(3,-1.0);
    glEnd();


    glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1.6,-0.32);
    glVertex2f(1.83,-0.32);
    glVertex2f(1.8,-0.34);
    glVertex2f(1.57,-0.34);
    glEnd();

glBegin(GL_POLYGON);               // middle dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1.4,-0.32);
    glVertex2f(1.13,-0.32);
    glVertex2f(1.1,-0.34);
    glVertex2f(1.37,-0.34);
    glEnd();

      glPopMatrix();


      glPushMatrix();
    glTranslatef(bus, 0.0f, -0.8f); // Move the entire airplane
 glScalef(0.25f, 0.25f, 1.0f);

    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawCircle8(1.5f, 0.3f-0.8f, 0.1f, 100); // Draw circle at origin with radius 0.3
    drawCircle8(1.5f, -0.3f-0.8f, 0.1f, 100); // Draw circle at origin with radius 0.3
    drawCircle8(-1.5f, 0.3f-0.8f, 0.1f, 100);
    drawCircle8(-1.6f, -0.35f-0.8f, 0.05f, 100);
    // Plane body
    glColor3f(1.0f, 0.0f, 0.0f); // red
    glBegin(GL_POLYGON);
        glVertex2f(-1.5f, 0.4f-0.8f);
        glVertex2f(-1.5f, -0.4f-0.8f);
        glVertex2f(1.5f, -0.4f-0.8f);
        glVertex2f(1.5f, 0.4f-0.8f);
    glEnd();

     glColor3f(1.0f, 0.0f, 0.0f); // red
    glBegin(GL_POLYGON);
        glVertex2f(1.5f, 0.3f-0.8f);
        glVertex2f(1.5f, -0.3f-0.8f);
        glVertex2f(1.6f, -0.3f-0.8f);
        glVertex2f(1.6f, 0.3f-0.8f);
    glEnd();

     glColor3f(1.0f, 0.0f, 0.0f); // red
    glBegin(GL_POLYGON);
        glVertex2f(-1.5f, -0.3f-0.8f);
        glVertex2f(-1.5f, -0.4f-0.8f);
        glVertex2f(-1.6f, -0.4f-0.8f);
        glVertex2f(-1.6f, -0.3f-0.8f);
    glEnd();

     glColor3f(1.0f, 0.0f, 0.0f); // red
    glBegin(GL_POLYGON);
        glVertex2f(-1.5f, 0.3f-0.8f);
        glVertex2f(-1.5f, -0.4f-0.8f);
        glVertex2f(-1.65f, -0.35f-0.8f);
        glVertex2f(-1.6f, 0.3f-0.8f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);    //head
    glVertex2f(-1.52f, 0.3f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.54f, -0.05f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.62f, -0.05f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.59f, 0.3f-0.8f);
      glEnd();

 glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.60f, 0.3f-0.8f);
    glVertex2f(-1.70f, 0.3f-0.8f);
    glVertex2f(-1.70f, 0.27f-0.8f);
    glVertex2f(-1.60f, 0.27f-0.8f);
     glEnd();

     glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(-1.75f, 0.3f-0.8f);
    glVertex2f(-1.70f, 0.3f-0.8f);
    glVertex2f(-1.70f, 0.2f-0.8f);
    glVertex2f(-1.75f, 0.2f-0.8f);
     glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.f, 0.0f);    // 1 head light
    glVertex2f(-1.57f, -0.3f-0.8f);
    glVertex2f(-1.57f, -0.2f-0.8f);
    glVertex2f(-1.63f, -0.2f-0.8f);
    glVertex2f(-1.63f, -0.3f-0.8f);
      glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.8f, 0.9f);    // 2 head light
    glVertex2f(-1.59f, -0.3f-0.8f);
    glVertex2f(-1.59f, -0.2f-0.8f);
    glVertex2f(-1.63f, -0.2f-0.8f);
    glVertex2f(-1.64f, -0.3f-0.8f);
      glEnd();


      glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.f, 0.0f);    // back light
    glVertex2f(1.59f, -0.3f-0.8f);
    glVertex2f(1.59f, -0.2f-0.8f);
    glVertex2f(1.55f, -0.2f-0.8f);
    glVertex2f(1.55f, -0.3f-0.8f);
      glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f-0.1f, 0.3f-0.8f);            // 1 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f-0.1f, 0.1f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f-0.1f, 0.1f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f-0.1f, 0.3f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f-0.1f, 0.3f-0.8f);            // 2 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f-0.1f, 0.3f-0.8f);
      glEnd();
       glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f, 0.3f-0.8f);            // 3 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f, 0.3f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);            // 4 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);            // 5 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);            // 6 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);            // 7 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);            // 6 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f);
      glEnd();

glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.15f-0.1f, 0.25f-0.8f);            // 2 head
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.15f-0.1f, 0.05f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.42f-0.1f, -0.05f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.4f-0.1f, 0.25f-0.8f);
      glEnd();




    glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle8(-1.0f, -0.4f-0.8f, 0.17f, 100, true); //1 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle8(-1.0f, -0.4f-0.8f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle8(-1.0f, -0.4f-0.8f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle8(-1.0f, -0.4f-0.8f, 0.025f, 100);


     glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle8(1.0f, -0.4f-0.8f, 0.17f, 100, true); // 3 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle8(1.0f, -0.4f-0.8f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle8(1.0f, -0.4f-0.8f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle8(1.0f, -0.4f-0.8f, 0.025f, 100);

 glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle8(0.6f, -0.4f-0.8f, 0.17f, 100, true); // 2 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle8(0.6f, -0.4f-0.8f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle8(0.6f, -0.4f-0.8f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle8(0.6f, -0.4f-0.8f, 0.025f, 100);

glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);
  glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.77f, -0.4f-0.8f);            // black border
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.77f, -0.18f-0.8f);
     glVertex2f(-0.8f+0.35f+0.35f-0.1f+0.63f, -0.18f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+0.63f, -0.4f-0.8f);

      glEnd();
glBegin(GL_POLYGON);
    glColor3f(1.f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f, -0.39f-0.8f);            // 1 box red
    glVertex2f(-1.1f+0.35f+0.35f-0.1f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f, -0.39f-0.8f);
      glEnd();



       glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.14f, -0.39f-0.8f);           // 2 box red
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.14f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.14f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.14f, -0.39f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.765f, -0.39f-0.8f);            // 3 box red
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.765f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.765f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.765f, -0.39f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+0.62f, -0.39f-0.8f);            // 4 red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+0.62f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+0.62f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+0.62f, -0.39f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.20f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.19f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.20f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.22f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.21f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.21f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.22f-0.8f);
      glEnd();


      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.24f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.23f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.23f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.24f-0.8f);
      glEnd();

        glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.26f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.25f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.25f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.26f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.28f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.27f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.27f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.28f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.30f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.29f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.29f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.30f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.32f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.31f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.31f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.32f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.34f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.33f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.33f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.34f-0.8f);
      glEnd();

       glPopMatrix();





       glPushMatrix();
    glTranslatef(cargo, 0.0f, 0.0f); // Move the entire
 glScalef(0.3f, 0.3f, 1.0f);


     glColor3f(1.0f, 0.8f, 0.f);
    drawCircle9(-1.28f, -0.35f-0.7f, 0.04f, 100);
    drawCircle9(1.28f, -0.35f-0.7f, 0.04f, 100);

      glColor3f(1.0f, 0.8f, 0.f);
      drawCircle9(-1.28f, -0.2f-0.7f, 0.04f, 100);

    // Plane body
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, 0.4f-0.7f);
        glVertex2f(-0.7f, -0.2f-0.7f);   // body
        glVertex2f(1.4f, -0.2f-0.7f);
        glVertex2f(1.4f, 0.4f-0.7f);
    glEnd();


    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, 0.37f-0.7f);
        glVertex2f(-0.65f, -0.17f-0.7f);   // body
        glVertex2f(-0.63f, -0.17f-0.7f);
        glVertex2f(-0.63f, 0.37f-0.7f);
    glEnd();

     glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.55f, 0.37f-0.7f);
        glVertex2f(-0.55f, -0.17f-0.7f);   // body
        glVertex2f(-0.57f, -0.17f-0.7f);
        glVertex2f(-0.57f, 0.37f-0.7f);
    glEnd();

dora(-0.09,-0.08);
dora(-0.19,-0.18);
dora(-0.29,-0.28);
dora(-0.39,-0.38);
dora(-0.49,-0.48);
dora(-0.59,-0.58);
dora(-0.69,-0.68);
dora(-0.79,-0.78);
dora(-0.89,-0.88);
dora(-0.99,-0.98);
dora(-1.09,-1.08);
dora(-1.19,-1.18);
dora(-1.29,-1.28);
dora(-1.39,-1.38);
dora(-1.49,-1.48);
dora(-1.59,-1.58);
dora(-1.69,-1.68);
dora(-1.79,-1.78);
dora(-1.89,-1.88);


glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-1.3f, -0.3f-0.7f);
        glVertex2f(-1.3f, -0.4f-0.7f);  // black layer
        glVertex2f(1.3f, -0.4f-0.7f);
        glVertex2f(1.3f, -0.3f-0.7f);
    glEnd();


 glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.85f, -0.27f-0.7f);
        glVertex2f(-0.85f, -0.2f-0.7f);   // gray layer
        glVertex2f(1.35f, -0.2f-0.7f);
        glVertex2f(1.35f, -0.27f-0.7f);
    glEnd();

    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.85f, -0.27f-0.7f);
        glVertex2f(-0.85f, -0.3f-0.7f);   // gray layer
        glVertex2f(1.35f, -0.3f-0.7f);
        glVertex2f(1.35f, -0.27f-0.7f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.1f, 0.3f-0.7f);
        glVertex2f(-0.85f, 0.3f-0.7f);
        glVertex2f(-0.85f, -0.3f-0.7f);   // body
        glVertex2f(-1.3f, -0.3f-0.7f);
        glVertex2f(-1.3f, -0.1f-0.7f);
    glEnd();


    glBegin(GL_POLYGON);
        glColor3f(0.1f, 0.4f, 0.9f);
        glVertex2f(-1.11f, 0.2f-0.7f);
        glColor3f(0.1f, 0.4f, 0.9f);
        glVertex2f(-0.9f, 0.2f-0.7f);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(-0.9f, -0.07f-0.7f);   // body
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(-1.25f, -0.07f-0.7f);
    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle9(-1.0f, -0.4f-0.7f, 0.17f, 100, true); //1 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle9(-1.0f, -0.4f-0.7f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle9(-1.0f, -0.4f-0.7f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle9(-1.0f, -0.4f-0.7f, 0.025f, 100);


     glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle9(1.0f, -0.4f-0.7f, 0.17f, 100, true); // 3 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle9(1.0f, -0.4f-0.7f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle9(1.0f, -0.4f-0.7f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle9(1.0f, -0.4f-0.7f, 0.025f, 100);

 glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle9(0.6f, -0.4f-0.7f, 0.17f, 100, true); // 2 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle9(0.6f, -0.4f-0.7f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle9(0.6f, -0.4f-0.7f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle9(0.6f, -0.4f-0.7f, 0.025f, 100);


      glPopMatrix();


glBegin(GL_POLYGON);                  // foothpath middle
glColor3f(0.333f, 0.4196f, 0.1843f);;

    glVertex2f(3,-0.45);
    glVertex2f(-3,-0.45);
    glVertex2f(-3,-0.55);
    glVertex2f(3,-0.55);
    glEnd();

    glPushMatrix();
glTranslatef(0.0f, 0.07f, 0.0f);
glScalef(1.0f, 3.0f, 2.0f);

             glBegin(GL_POLYGON);
glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2f(3,-0.21);
    glVertex2f(-3,-0.21);
    glVertex2f(-3,-0.2);
    glVertex2f(3,-.2);
    glEnd();

            glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(2,-0.21);
    glVertex2f(1.8,-0.21);
    glVertex2f(1.8,-0.2);
    glVertex2f(2,-.2);
    glEnd();

             glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1.6,-0.21);
    glVertex2f(1.4,-0.21);
    glVertex2f(1.4,-0.2);
    glVertex2f(1.6,-.2);
    glEnd();


                 glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1.2,-0.21);
    glVertex2f(1.0,-0.21);
    glVertex2f(1.0,-0.2);
    glVertex2f(1.2,-.2);
    glEnd();

                     glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.8,-0.21);
    glVertex2f(0.6,-0.21);
    glVertex2f(0.6,-0.2);
    glVertex2f(0.8,-.2);
    glEnd();


                         glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.4,-0.21);
    glVertex2f(0.2,-0.21);
    glVertex2f(0.2,-0.2);
    glVertex2f(0.4,-.2);
    glEnd();

                             glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.4,-0.21);
    glVertex2f(0.2,-0.21);
    glVertex2f(0.2,-0.2);
    glVertex2f(0.4,-.2);
    glEnd();

                             glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.0,-0.21);
    glVertex2f(-0.2,-0.21);
    glVertex2f(-0.2,-0.2);
    glVertex2f(0.0,-.2);
    glEnd();

                                 glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.4,-0.21);
    glVertex2f(-0.6,-0.21);
    glVertex2f(-0.6,-0.2);
    glVertex2f(-0.4,-.2);
    glEnd();

                                     glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.8,-0.21);
    glVertex2f(-1.0,-0.21);
    glVertex2f(-1.0,-0.2);
    glVertex2f(-0.8,-.2);
    glEnd();


                                         glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-1.2,-0.21);
    glVertex2f(-1.4,-0.21);
    glVertex2f(-1.4,-0.2);
    glVertex2f(-1.2,-.2);
    glEnd();

glBegin(GL_POLYGON);               //dora
glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-1.6,-0.21);
    glVertex2f(-1.8,-0.21);
    glVertex2f(-1.8,-0.2);
    glVertex2f(-1.6,-.2);
    glEnd();

      glPopMatrix();


           glPushMatrix();
    glTranslatef(bus2, 0.0f, -0.8f); // Move the entire airplane
 glScalef(-0.3f, 0.3f, 1.0f);

  glColor3f(0.0f, 0.5f, 0.5f); // Red color
    drawCircle8(1.5f, 0.3f-0.8f-0.8f-0.8f, 0.1f, 100); // Draw circle at origin with radius 0.3
    drawCircle8(1.5f, -0.3f-0.8f-0.8f-0.8f, 0.1f, 100); // Draw circle at origin with radius 0.3
    drawCircle8(-1.5f, 0.3f-0.8f-0.8f-0.8f, 0.1f, 100);
    drawCircle8(-1.6f, -0.35f-0.8f-0.8f-0.8f, 0.05f, 100);
    // Plane body
    glColor3f(0.0f, 0.5f, 0.5f); // red
    glBegin(GL_POLYGON);
        glVertex2f(-1.5f, 0.4f-0.8f-0.8f-0.8f);
        glVertex2f(-1.5f, -0.4f-0.8f-0.8f-0.8f);
        glVertex2f(1.5f, -0.4f-0.8f-0.8f-0.8f);
        glVertex2f(1.5f, 0.4f-0.8f-0.8f-0.8f);
    glEnd();

     glColor3f(0.0f, 0.5f, 0.5f); // red
    glBegin(GL_POLYGON);
        glVertex2f(1.5f, 0.3f-0.8f-0.8f-0.8f);
        glVertex2f(1.5f, -0.3f-0.8f-0.8f-0.8f);
        glVertex2f(1.6f, -0.3f-0.8f-0.8f-0.8f);
        glVertex2f(1.6f, 0.3f-0.8f-0.8f-0.8f);
    glEnd();

     glColor3f(0.0f, 0.5f, 0.5f);// red
    glBegin(GL_POLYGON);
        glVertex2f(-1.5f, -0.3f-0.8f-0.8f-0.8f);
        glVertex2f(-1.5f, -0.4f-0.8f-0.8f-0.8f);
        glVertex2f(-1.6f, -0.4f-0.8f-0.8f-0.8f);
        glVertex2f(-1.6f, -0.3f-0.8f-0.8f-0.8f);
    glEnd();

     glColor3f(0.0f, 0.5f, 0.5f); // red
    glBegin(GL_POLYGON);
        glVertex2f(-1.5f, 0.3f-0.8f-0.8f-0.8f);
        glVertex2f(-1.5f, -0.4f-0.8f-0.8f-0.8f);
        glVertex2f(-1.65f, -0.35f-0.8f-0.8f-0.8f);
        glVertex2f(-1.6f, 0.3f-0.8f-0.8f-0.8f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);    //head
    glVertex2f(-1.52f, 0.3f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.54f, -0.05f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.62f, -0.05f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.59f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();

 glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.60f, 0.3f-0.8f-0.8f-0.8f);
    glVertex2f(-1.70f, 0.3f-0.8f-0.8f-0.8f);
    glVertex2f(-1.70f, 0.27f-0.8f-0.8f-0.8f);
    glVertex2f(-1.60f, 0.27f-0.8f-0.8f-0.8f);
     glEnd();

     glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(-1.75f, 0.3f-0.8f-0.8f-0.8f);
    glVertex2f(-1.70f, 0.3f-0.8f-0.8f-0.8f);
    glVertex2f(-1.70f, 0.2f-0.8f-0.8f-0.8f);
    glVertex2f(-1.75f, 0.2f-0.8f-0.8f-0.8f);
     glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.f, 0.0f);    // 1 head light
    glVertex2f(-1.57f, -0.3f-0.8f-0.8f-0.8f);
    glVertex2f(-1.57f, -0.2f-0.8f-0.8f-0.8f);
    glVertex2f(-1.63f, -0.2f-0.8f-0.8f-0.8f);
    glVertex2f(-1.63f, -0.3f-0.8f-0.8f-0.8f);
      glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.8f, 0.9f);    // 2 head light
    glVertex2f(-1.59f, -0.3f-0.8f-0.8f-0.8f);
    glVertex2f(-1.59f, -0.2f-0.8f-0.8f-0.8f);
    glVertex2f(-1.63f, -0.2f-0.8f-0.8f-0.8f);
    glVertex2f(-1.64f, -0.3f-0.8f-0.8f-0.8f);
      glEnd();


      glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.f, 0.0f);    // back light
    glVertex2f(1.59f, -0.3f-0.8f-0.8f-0.8f);
    glVertex2f(1.59f, -0.2f-0.8f-0.8f-0.8f);
    glVertex2f(1.55f, -0.2f-0.8f-0.8f-0.8f);
    glVertex2f(1.55f, -0.3f-0.8f-0.8f-0.8f);
      glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f-0.1f, 0.3f-0.8f-0.8f-0.8f);            // 1 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f-0.1f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);            // 2 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();
       glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);            // 3 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);            // 4 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);            // 5 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);            // 6 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);            // 7 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);            // 6 window
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.1f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f+0.35f-0.1f, 0.3f-0.8f-0.8f-0.8f);
      glEnd();

glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.15f-0.1f, 0.25f-0.8f-0.8f-0.8f);            // 2 head
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.15f-0.1f, 0.05f-0.8f-0.8f-0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-1.42f-0.1f, -0.05f-0.8f-0.8f-0.8f);
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-1.4f-0.1f, 0.25f-0.8f-0.8f-0.8f);
      glEnd();




    glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle8(-1.0f, -0.4f-0.8f-0.8f-0.8f, 0.17f, 100, true); //1 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle8(-1.0f, -0.4f-0.8f-0.8f-0.8f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle8(-1.0f, -0.4f-0.8f-0.8f-0.8f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle8(-1.0f, -0.4f-0.8f-0.8f-0.8f, 0.025f, 100);


     glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle8(1.0f, -0.4f-0.8f-0.8f-0.8f, 0.17f, 100, true); // 3 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle8(1.0f, -0.4f-0.8f-0.8f-0.8f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle8(1.0f, -0.4f-0.8f-0.8f-0.8f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle8(1.0f, -0.4f-0.8f-0.8f-0.8f, 0.025f, 100);

 glColor3f(0.0f, 0.0f, 0.0f); // Set color
    drawHalfCircle8(0.6f, -0.4f-0.8f-0.8f-0.8f, 0.17f, 100, true); // 2 wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle8(0.6f, -0.4f-0.8f-0.8f-0.8f, 0.15f, 100);
     glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle8(0.6f, -0.4f-0.8f-0.8f-0.8f, 0.1f, 100);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle8(0.6f, -0.4f-0.8f-0.8f-0.8f, 0.025f, 100);

glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);
  glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.77f, -0.4f-0.8f-0.8f-0.8f);            // black border
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.77f, -0.18f-0.8f-0.8f-0.8f);
     glVertex2f(-0.8f+0.35f+0.35f-0.1f+0.63f, -0.18f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+0.63f, -0.4f-0.8f-0.8f-0.8f);

      glEnd();
glBegin(GL_POLYGON);
   glColor3f(0.0f, 0.5f, 0.5f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f, -0.39f-0.8f-0.8f-0.8f);            // 1 box red
    glVertex2f(-1.1f+0.35f+0.35f-0.1f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f, -0.39f-0.8f-0.8f-0.8f);
      glEnd();



       glBegin(GL_POLYGON);
   glColor3f(0.0f, 0.5f, 0.5f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.14f, -0.39f-0.8f-0.8f-0.8f);           // 2 box red
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.14f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.14f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.14f, -0.39f-0.8f-0.8f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.5f);
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.765f, -0.39f-0.8f-0.8f-0.8f);            // 3 box red
    glVertex2f(-1.1f+0.35f+0.35f+0.35f-0.765f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.765f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f+0.35f-0.765f, -0.39f-0.8f-0.8f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
   glColor3f(0.0f, 0.5f, 0.5f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+0.62f, -0.39f-0.8f-0.8f-0.8f);            // 4 red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+0.62f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+0.62f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+0.62f, -0.39f-0.8f-0.8f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.20f-0.8f-0.8f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.19f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.20f-0.8f-0.8f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.22f-0.8f-0.8f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.21f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.21f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.22f-0.8f-0.8f-0.8f);
      glEnd();


      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.24f-0.8f-0.8f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.23f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.23f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.24f-0.8f-0.8f-0.8f);
      glEnd();

        glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.26f-0.8f-0.8f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.25f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.25f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.26f-0.8f-0.8f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.28f-0.8f-0.8f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.27f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.27f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.28f-0.8f-0.8f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.30f-0.8f-0.8f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.29f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.29f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.30f-0.8f-0.8f-0.8f);
      glEnd();

       glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.32f-0.8f-0.8f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.31f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.31f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.32f-0.8f-0.8f-0.8f);
      glEnd();

      glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.34f-0.8f-0.8f-0.8f);            // last red box
    glVertex2f(-1.1f+0.35f+0.35f-0.1f+1.7f, -0.33f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.33f-0.8f-0.8f-0.8f);
    glVertex2f(-0.8f+0.35f+0.35f-0.1f+1.7f, -0.34f-0.8f-0.8f-0.8f);
      glEnd();

       glPopMatrix();


glPushMatrix(); // Save current matrix

  glScalef(.5f, 0.3f, 2.0f);

  glBegin(GL_POLYGON);               // train base
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(4.f,0.0f);
    glVertex2f(4.0f,-0.1f);
    glVertex2f(-4.0f,-0.1f);
    glVertex2f(-4.0f,0.0f);
    glEnd();

    glBegin(GL_POLYGON);               // 1st up pilar
    glColor3f(0.5f, 0.55f, 0.52f);
    glVertex2f(1.0f-3.0f,-0.2f);
    glVertex2f(1.2f-3.0f,-0.1f);
    glVertex2f(-.2f-3.0f,-0.1f);
    glVertex2f(.0f-3.0f,-0.2f);
    glEnd();

    glBegin(GL_POLYGON);               // 1st down pilar
   glColor3f(0.5f, 0.55f, 0.52f);
    glVertex2f(0.6f-3.0f,-0.2f);
    glVertex2f(0.6f-3.0f,-1.6f);
    glVertex2f(.4f-3.0f,-1.6f);
    glVertex2f(.4f-3.0f,-0.2f);
    glEnd();

     glBegin(GL_POLYGON);               // 2nd up pilar
   glColor3f(0.5f, 0.55f, 0.52f);
    glVertex2f(1.0f-0.5f,-0.2f);
    glVertex2f(1.2f-0.5f,-0.1f);
    glVertex2f(-.2f-0.5f,-0.1f);
    glVertex2f(.0f-0.5f,-0.2f);
    glEnd();

     glBegin(GL_POLYGON);               // 2nd down pilar
 glColor3f(0.5f, 0.55f, 0.52f);
    glVertex2f(0.6f-0.5f,-0.2f);
    glVertex2f(0.6f-0.5f,-1.6f);
    glVertex2f(.4f-0.5f,-1.6f);
    glVertex2f(.4f-0.5f,-0.2f);
    glEnd();


    glBegin(GL_POLYGON);               // 3rd up pilar
 glColor3f(0.5f, 0.55f, 0.52f);
    glVertex2f(1.0f+2.0f,-0.2f);
    glVertex2f(1.2f+2.0f,-0.1f);
    glVertex2f(-.2f+2.0f,-0.1f);
    glVertex2f(.0f+2.0f,-0.2f);
    glEnd();

     glBegin(GL_POLYGON);               // 3rd down pilar
 glColor3f(0.5f, 0.55f, 0.52f);

    glVertex2f(0.6f+2.0f,-0.2f);
    glVertex2f(0.6f+2.0f,-1.6f);
    glVertex2f(.4f+2.0f,-1.6f);
    glVertex2f(.4f+2.0f,-0.2f);
    glEnd();

  glPopMatrix();


   glPushMatrix();
    glTranslatef(0.0f, -0.8f, -0.8f); // Move the entire airplane
 glScalef(0.006f, 0.006f, 1.0f);

   glColor3f(0.0, 0.5, 0.0);
    // Top Fish (vertical)
    glBegin(GL_POLYGON);
    glVertex2f(1.50, 0);
    glVertex2f(-1.50, 0);
    glVertex2f(-1.50, -30.0);
    glVertex2f(1.50, -30.0);

    glEnd();

 glColor3f(1.0, 0.75, 0.8);
    // Left Fish
    glBegin(GL_POLYGON);
    glVertex2f(-40, 0);
    glVertex2f(-35, 5);
    glVertex2f(-30, 7.5);
    glVertex2f(-25, 8.5);
    glVertex2f(-20, 9);
    glVertex2f(-15, 8.5);
    glVertex2f(-10, 7.5);
    glVertex2f(-5, 5);
    glVertex2f(0, 0);
    glVertex2f(-5, -5);
    glVertex2f(-10, -7.5);
    glVertex2f(-15, -8.5);
    glVertex2f(-20, -9);
    glVertex2f(-25, -8.5);
    glVertex2f(-30, -7.5);
    glVertex2f(-35, -5);
    glVertex2f(-40, 0);
    glEnd();

    // Right Fish
    glBegin(GL_POLYGON);
    glVertex2f(40, 0);
    glVertex2f(35, 5);
    glVertex2f(30, 7.5);
    glVertex2f(25, 8.5);
    glVertex2f(20, 9);
    glVertex2f(15, 8.5);
    glVertex2f(10, 7.5);
    glVertex2f(5, 5);
    glVertex2f(0, 0);
    glVertex2f(5, -5);
    glVertex2f(10, -7.5);
    glVertex2f(15, -8.5);
    glVertex2f(20, -9);
    glVertex2f(25, -8.5);
    glVertex2f(30, -7.5);
    glVertex2f(35, -5);
    glVertex2f(40, 0);
    glEnd();



glBegin(GL_POLYGON);
 glColor3f(1.0, 0.08, 0.58);


  anglelips(0, 40,30);
    anglelips(5, 35,30);
    anglelips(7.5, 30,30);
    anglelips(8.5, 25,30);
    anglelips(9, 20,30);
    anglelips(8.5, 15,30);
   anglelips(7.5, 10,30);
    anglelips(5, 5,30);
    anglelips(0, 0,30);
    anglelips(-5, 5,30);
  anglelips(-7.5, 10,30);
    anglelips(-8.5, 15,30);
   anglelips(-9, 20,30);
    anglelips(-8.5, 25,30);
   anglelips(-7.5, 30,30);
    anglelips(-5, 35,30);
    anglelips(0, 40,30);
      glEnd();


      glBegin(GL_POLYGON);

  anglelips(0, 40,-30);
    anglelips(5, 35,-30);
    anglelips(7.5, 30,-30);
    anglelips(8.5, 25,-30);
    anglelips(9, 20,-30);
    anglelips(8.5, 15,-30);
   anglelips(7.5, 10,-30);
    anglelips(5, 5,-30);
    anglelips(0, 0,-30);
    anglelips(-5, 5,-30);
  anglelips(-7.5, 10,-30);
    anglelips(-8.5, 15,-30);
   anglelips(-9, 20,-30);
    anglelips(-8.5, 25,-30);
   anglelips(-7.5, 30,-30);
    anglelips(-5, 35,-30);
    anglelips(0, 40,-30);
      glEnd();


      glBegin(GL_POLYGON);

  glColor3f(1.0f, 0.4f, 0.7f);
  anglelips(0, 40,-60);
    anglelips(5, 35,-60);
    anglelips(7.5, 30,-60);
    anglelips(8.5, 25,-60);
    anglelips(9, 20,-60);
    anglelips(8.5, 15,-60);
   anglelips(7.5, 10,-60);
    anglelips(5, 5,-60);
    anglelips(0, 0,-60);
    anglelips(-5, 5,-60);
  anglelips(-7.5, 10,-60);
    anglelips(-8.5, 15,-60);
   anglelips(-9, 20,-60);
    anglelips(-8.5, 25,-60);
   anglelips(-7.5, 30,-60);
    anglelips(-5, 35,-60);
    anglelips(0, 40,-60);
      glEnd();

       glBegin(GL_POLYGON);

  anglelips(0, 40,60);
    anglelips(5, 35,60);
    anglelips(7.5, 30,60);
    anglelips(8.5, 25,60);
    anglelips(9, 20,60);
    anglelips(8.5, 15,60);
   anglelips(7.5, 10,60);
    anglelips(5, 5,60);
    anglelips(0, 0,60);
    anglelips(-5, 5,60);
  anglelips(-7.5, 10,60);
    anglelips(-8.5, 15,60);
   anglelips(-9, 20,60);
    anglelips(-8.5, 25,60);
   anglelips(-7.5, 30,60);
    anglelips(-5, 35,60);
    anglelips(0, 40,60);
      glEnd();

       glColor3f(1.0, 0.0, 0.5);
    // Top Fish (vertical)
    glBegin(GL_POLYGON);
    glVertex2f(0, 40);
    glVertex2f(5, 35);
    glVertex2f(7.5, 30);
    glVertex2f(8.5, 25);
    glVertex2f(9, 20);
    glVertex2f(8.5, 15);
    glVertex2f(7.5, 10);
    glVertex2f(5, 5);
    glVertex2f(0, 0);
    glVertex2f(-5, 5);
    glVertex2f(-7.5, 10);
    glVertex2f(-8.5, 15);
    glVertex2f(-9, 20);
    glVertex2f(-8.5, 25);
    glVertex2f(-7.5, 30);
    glVertex2f(-5, 35);
    glVertex2f(0, 40);
    glEnd();



  glPopMatrix();




  glutSwapBuffers();
    glFlush();
}

// Timer for animation
void update(int value) {

    planeX +=  0.015f;
    if (planeX > 2.5f)
    {planeX = -2.5f;}

    cloudOffsetX -= 0.0005f;
    if (cloudOffsetX < -3.5f)
    {cloudOffsetX = 3.5f;}

     trainPosX -= 0.02f; // Move train to the right

    if (trainPosX <=- 3.3f)  // Reset position when off-screen right
        {trainPosX = 3.0f;}

    bus -= 0.01f; // Adjust speed here

    if (bus <-3.5f) { // Reset position when off-screen
        bus = 3.0f;
    }

     bus2 += 0.01f;
    if (bus2 > 2.5f) { // Reset position when off-screen
        bus2 = -2.5f;
    }

    cargo -= 0.01f; // Adjust speed here

    if (cargo < -3.5f) { // Reset position when off-screen
        cargo = 3.0f;
    }

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(32, update, 0); // Call again after ~16 ms (~60 FPS)


}
void toggleDayNight(unsigned char key, int x, int y) {
    if (key == 32) {  // Space key to toggle day/night
        isDay = !isDay;  // Toggle the mode
        glutPostRedisplay();  // Redraw the scene with the new mode
    }

    if (key == 'a' || key == 'A') {
        isYellow = !isYellow; // Toggle color state
        glutPostRedisplay();  // Redraw the scene
    }
     if (key == 's' || key == 'S') {

        changeColor = !changeColor;
        glutPostRedisplay(); // Redraw the screen
    }

}




















 // New Scenario









void updateHelicopter(int value) {

    if (movingUp==true) {
        heliY += 0.0001f;
        if (heliY >= 3.f) {
            movingUp = false;
        }
    } else {
        heliX += 0.0001f;
        if (heliX >= 1.2f) {
            movingUp = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(600, updateHelicopter, 0);
}






void animateRotors(int value) {
    rotorAngle += 5.0f;
    if (rotorAngle >= 360.0f)
        rotorAngle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(4, animateRotors, 0);
}


void drawHelicopter() {


    glPushMatrix();
    glTranslatef(-1.3f, -0.6f, 0.0f);
    glScalef(0.15f, 0.7f, 1.0f);


    // Body
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.2);
    glVertex2f(0.5, -0.2);
    glVertex2f(0.5, 0.2);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.0, 0.5);
    glVertex2f(-0.3, 0.2);
    glVertex2f(-0.5, 0.2);
    glEnd();


    // Tail boom
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-1.2, 0.0);
    glVertex2f(-1.2, 0.1);
    glVertex2f(-0.5, 0.1);
    glEnd();


    // Tail rotor hub
    glColor3f(0.8, 0.9, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(-1.22, -0.02); glVertex2f(-1.28, -0.02);
    glVertex2f(-1.28, 0.12); glVertex2f(-1.22, 0.12);
    glEnd();


    // Rotating Tail Rotor Blades
    glPushMatrix();
    glTranslatef(-1.25f, 0.05f, 0.0f); // center of tail rotor
    glRotatef(rotorAngle * 5, 0.0f, 0.0f, 1.0f); // Faster spin for small rotor

    glColor3f(0.1f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.19f, -0.019f);
    glVertex2f(0.19f, 0.019f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f); glVertex2f(-0.15f, -0.015f);
    glVertex2f(-0.15f, 0.015f);
    glEnd();
    glPopMatrix();


    // Main rotor hub
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180.0f;
        glVertex2f(0.1f * cos(theta), 0.1f * sin(theta) + 0.5f);
    }
    glEnd();


    // Main rotor blades (rotating)
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glRotatef(rotorAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.8f, -0.1f);
    glVertex2f(0.8f, 0.1f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.8f, -0.1f);
    glVertex2f(-0.8f, 0.1f);
    glEnd();
    glPopMatrix();


    // Landing skids
    glColor3f(0.2, 0.1, 0.1);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.32, -0.2); glVertex2f(-0.28, -0.2);
    glVertex2f(-0.28, -0.4); glVertex2f(-0.32, -0.4);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.28, -0.2); glVertex2f(0.32, -0.2);
    glVertex2f(0.32, -0.4); glVertex2f(0.28, -0.4);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.36, -0.41); glVertex2f(0.36, -0.41);
    glVertex2f(0.36, -0.39); glVertex2f(-0.36, -0.39);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.37, -0.42); glVertex2f(-0.33, -0.42);
    glVertex2f(-0.33, -0.40); glVertex2f(-0.37, -0.40);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.33, -0.42); glVertex2f(0.37, -0.42);
    glVertex2f(0.37, -0.40); glVertex2f(0.33, -0.40);
    glEnd();
    glLineWidth(1.0);

    // Windows
    glColor3f(0.7, 0.9, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.0); glVertex2f(-0.2, 0.0);
    glVertex2f(-0.2, 0.15); glVertex2f(-0.4, 0.15);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.1, 0.0); glVertex2f(0.1, 0.0);
    glVertex2f(0.1, 0.15); glVertex2f(-0.1, 0.15);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.2, 0.0); glVertex2f(0.4, 0.0);
    glVertex2f(0.4, 0.15); glVertex2f(0.2, 0.15);
    glEnd();


    glPopMatrix();
}








void update_s1(int value) {

    cloudX += 0.000003f;
    if (cloudX > 2.0f) cloudX = -2.0f;


    glutPostRedisplay();
    glutTimerFunc(100, update_s1, 0);
}




void Road_brick_horizontal() {

    glTranslatef(-0.09f, 0.71f, 0.0f);
    glScalef(1.0f, 0.71f, 1.0f);

    // Road base (light brick color)
    glColor3f(0.8f, 0.5f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-1.5f, -0.05f);
    glVertex2f( 1.5f, -0.05f);
    glVertex2f( 1.5f,  0.05f);
    glVertex2f(-1.5f,  0.05f);
    glEnd();
}






void Road_first() {


     glTranslatef(-0.09f, -0.6f, 0.0f);
     glScalef(1.0f, 0.79f, 1.0f);

    // Road base (light gray)
    glColor3f(0.7f, 0.7f, 0.7f);  // Light gray
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.05f);
    glVertex2f(1.2f, -0.05f);
    glVertex2f(1.2f, 0.05f);
    glVertex2f(-0.4f, 0.05f);
    glEnd();

    // Center dashed line (3 white dashes)
    glColor3f(1.0f, 1.0f, 1.0f);

    // Dash 1
    glBegin(GL_QUADS);
    glVertex2f(-0.35f, -0.005f);
    glVertex2f(-0.3f, -0.005f);
    glVertex2f(-0.3f,  0.005f);
    glVertex2f(-0.35f,  0.005f);
    glEnd();

    // Dash 2
    glBegin(GL_QUADS);
    glVertex2f(-0.25f, -0.005f);
    glVertex2f(-0.2f, -0.005f);
    glVertex2f(-0.2f,  0.005f);
    glVertex2f(-0.25f,  0.005f);
    glEnd();

    // Dash 3
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.005f);
    glVertex2f(-0.1f, -0.005f);
    glVertex2f(-0.1f,  0.005f);
    glVertex2f(-0.15f,  0.005f);
    glEnd();

     // Dash 4
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, -0.005f);
    glVertex2f(0.0f, -0.005f);
    glVertex2f(0.0f,  0.005f);
    glVertex2f(-0.05f,  0.005f);
    glEnd();

    // Dash 5
    glBegin(GL_QUADS);
    glVertex2f(0.05f, -0.005f);
    glVertex2f(0.1f, -0.005f);
    glVertex2f(0.1f,  0.005f);
    glVertex2f(0.05f,  0.005f);
    glEnd();

    // Dash 6
    glBegin(GL_QUADS);
    glVertex2f(0.15f, -0.005f);
    glVertex2f(0.2f, -0.005f);
    glVertex2f(0.2f,  0.005f);
    glVertex2f(0.15f,  0.005f);
    glEnd();

    // Dash 7
    glBegin(GL_QUADS);
    glVertex2f(0.25f, -0.005f);
    glVertex2f(0.3f, -0.005f);
    glVertex2f(0.3f,  0.005f);
    glVertex2f(0.25f,  0.005f);
    glEnd();

    // Dash 8
    glBegin(GL_QUADS);
    glVertex2f(0.35f, -0.005f);
    glVertex2f(0.4f, -0.005f);
    glVertex2f(0.4f,  0.005f);
    glVertex2f(0.35f,  0.005f);
    glEnd();

    // Dash 9
    glBegin(GL_QUADS);
    glVertex2f(0.45f, -0.005f);
    glVertex2f(0.5f, -0.005f);
    glVertex2f(0.5f,  0.005f);
    glVertex2f(0.45f,  0.005f);
    glEnd();

        // Dash 10
    glBegin(GL_QUADS);
    glVertex2f(0.55f, -0.005f);
    glVertex2f(0.6f, -0.005f);
    glVertex2f(0.6f,  0.005f);
    glVertex2f(0.55f,  0.005f);
    glEnd();

    // Dash 11
    glBegin(GL_QUADS);
    glVertex2f(0.65f, -0.005f);
    glVertex2f(0.7f, -0.005f);
    glVertex2f(0.7f,  0.005f);
    glVertex2f(0.65f,  0.005f);
    glEnd();

    // Dash 12
    glBegin(GL_QUADS);
    glVertex2f(0.75f, -0.005f);
    glVertex2f(0.8f, -0.005f);
    glVertex2f(0.8f,  0.005f);
    glVertex2f(0.75f,  0.005f);
    glEnd();

    // Dash 13
    glBegin(GL_QUADS);
    glVertex2f(0.85f, -0.005f);
    glVertex2f(0.9f, -0.005f);
    glVertex2f(0.9f,  0.005f);
    glVertex2f(0.85f,  0.005f);
    glEnd();


        // Dash 14
    glBegin(GL_QUADS);
    glVertex2f(0.95f, -0.005f);
    glVertex2f(1.0f, -0.005f);
    glVertex2f(1.0f,  0.005f);
    glVertex2f(0.95f,  0.005f);
    glEnd();

    // Dash 15
    glBegin(GL_QUADS);
    glVertex2f(1.05f, -0.005f);
    glVertex2f(1.1f, -0.005f);
    glVertex2f(1.1f,  0.005f);
    glVertex2f(1.05f,  0.005f);
    glEnd();

    // Dash 16
    glBegin(GL_QUADS);
    glVertex2f(1.15f, -0.005f);
    glVertex2f(1.2f, -0.005f);
    glVertex2f(1.2f,  0.005f);
    glVertex2f(1.15f,  0.005f);
    glEnd();



}







void Road_second() {

    glTranslatef(0.2f, -0.09f, 0.0f);
    glScalef(0.79f, 0.7f, 1.0f);

    // Road base (light gray)
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f,  0.2f);
    glVertex2f( 0.05f,  0.2f);
    glVertex2f( 0.05f,  0.7f);
    glVertex2f(-0.05f,  0.7f);
    glEnd();

    // Center dashed line (white)
    glColor3f(1.0f, 1.0f, 1.0f);



    // Dash 1
    glBegin(GL_QUADS);
    glVertex2f(-0.005f, 0.15f);
    glVertex2f( 0.005f, 0.15f);
    glVertex2f( 0.005f, 0.2f);
    glVertex2f(-0.005f, 0.2f);
    glEnd();

    // Dash 2
    glBegin(GL_QUADS);
    glVertex2f(-0.005f, 0.25f);
    glVertex2f( 0.005f, 0.25f);
    glVertex2f( 0.005f, 0.3f);
    glVertex2f(-0.005f, 0.3f);
    glEnd();

    // Dash 3
    glBegin(GL_QUADS);
    glVertex2f(-0.005f, 0.35f);
    glVertex2f( 0.005f, 0.35f);
    glVertex2f( 0.005f, 0.4f);
    glVertex2f(-0.005f, 0.4f);
    glEnd();

    // Dash 4
    glBegin(GL_QUADS);
    glVertex2f(-0.005f, 0.45f);
    glVertex2f( 0.005f, 0.45f);
    glVertex2f( 0.005f, 0.5f);
    glVertex2f(-0.005f, 0.5f);
    glEnd();

    // Dash 5
    glBegin(GL_QUADS);
    glVertex2f(-0.005f, 0.55f);
    glVertex2f( 0.005f, 0.55f);
    glVertex2f( 0.005f, 0.6f);
    glVertex2f(-0.005f, 0.6f);
    glEnd();

    // Dash 6
    glBegin(GL_QUADS);
    glVertex2f(-0.005f, 0.65f);
    glVertex2f( 0.005f, 0.65f);
    glVertex2f( 0.005f, 0.7f);
    glVertex2f(-0.005f, 0.7f);
    glEnd();


}








void drawFilledCircle(float x, float y, float radius, int segments) {

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}




//  Helipad Drawing

void drawHelipad() {

    // Draw oval base
    glPushMatrix();
    glTranslatef(-0.61f, -0.6f, 0.0f);  // Position on screen
    glScalef(1.5f, 1.0f, 1.0f);      // Oval effect
    glColor3f(0.6f, 0.3f, 0.2f);     // Brick color
    drawFilledCircle(0.0f, 0.0f, 0.09f, 100);
    glPopMatrix();


    // Draw "H" on top (rotated 180 degrees)
    glPushMatrix();
    glTranslatef(-0.61f, -0.6f, 0.0f);  // Same center as oval
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);  // Rotate H upside down
    glColor3f(1.0f, 1.0f, 1.0f);     // White H

    float hWidth = 0.02f;
    float hHeight = 0.08f;

    // Left bar
    glBegin(GL_QUADS);
    glVertex2f(-0.04f, -hHeight);
    glVertex2f(-0.02f, -hHeight);
    glVertex2f(-0.02f, hHeight);
    glVertex2f(-0.04f, hHeight);
    glEnd();

    // Right bar
    glBegin(GL_QUADS);
    glVertex2f(0.02f, -hHeight);
    glVertex2f(0.04f, -hHeight);
    glVertex2f(0.04f, hHeight);
    glVertex2f(0.02f, hHeight);
    glEnd();

    // Middle bar
    glBegin(GL_QUADS);
    glVertex2f(-0.04f, -0.01f);
    glVertex2f(0.04f, -0.01f);
    glVertex2f(0.04f, 0.01f);
    glVertex2f(-0.04f, 0.01f);
    glEnd();

    glPopMatrix();
}





void Sky_Drawing() {

    glBegin(GL_QUADS);

        glColor3f(0.58f, 0.86f, 0.98f); // Sky blue (Top)
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);

        // Bottom (darker blue)
        glColor3f(0.16f, 0.55f, 0.81f);
        glVertex2f(1.0f, -0.25f);
        glVertex2f(-1.0f, -0.25f);
    glEnd();
}





// Sun :

void DrawDaystar (float cx, float cy, float r) {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // center
    int seg = 50;
    for (int i = 0; i <= seg; i++) {
        float theta = 2.0f * 3.14159f * i / seg;
        float x = cx + r * cosf(theta);
        float y = cy + r * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}






void plotRoundCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}



void drawCloud(float x, float y, float scale) {

     glPushMatrix();
     glTranslatef(cloudX, 0.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f); // White cloud

    // Draw multiple overlapping circles
    plotRoundCircle(x, y, 0.08f * scale, 100);
    plotRoundCircle(x + 0.07f * scale, y + 0.03f * scale, 0.09f * scale, 100);
    plotRoundCircle(x + 0.14f * scale, y, 0.08f * scale, 100);
    plotRoundCircle(x + 0.05f * scale, y - 0.04f * scale, 0.06f * scale, 100);
    plotRoundCircle(x + 0.11f * scale, y - 0.04f * scale, 0.06f * scale, 100);

    glPopMatrix();
}



void GrassField() {
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.5f, 0.0f); // Grass green

        glVertex2f(-1.0f, -0.25f); // Middle left
        glVertex2f(1.0f, -0.25f);  // Middle right
        glVertex2f(1.0f, -1.0f); // Bottom right
        glVertex2f(-1.0f, -1.0f); // Bottom left
    glEnd();
}






// === Tree Type 1 ===
void T1() {

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, -0.24f);
        glVertex2f(0.02f, -0.24f);
        glVertex2f(0.02f, 0.06f);
        glVertex2f(-0.02f, 0.06f);
    glEnd();


    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.08f, 0.06f);
        glVertex2f(0.08f, 0.06f);
        glVertex2f(0.0f, 0.18f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.06f, 0.12f);
        glVertex2f(0.06f, 0.12f);
        glVertex2f(0.0f, 0.24f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.04f, 0.18f);
        glVertex2f(0.04f, 0.18f);
        glVertex2f(0.0f, 0.30f);
    glEnd();
}







// === Tree Type 2 ===
void T2() {
    // Left Circle
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f, 0.10f);
        glVertex2f(-0.12f, 0.17f);
        glVertex2f(-0.05f, 0.20f);
        glVertex2f(0.00f, 0.17f);
        glVertex2f(-0.02f, 0.10f);
        glVertex2f(-0.08f, 0.05f);
        glVertex2f(-0.12f, 0.05f);
    glEnd();

    // Center Circle
    glColor3f(0.0f, 0.7f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.10f, 0.12f);
        glVertex2f(-0.04f, 0.18f);
        glVertex2f(0.04f, 0.18f);
        glVertex2f(0.10f, 0.12f);
        glVertex2f(0.08f, 0.04f);
        glVertex2f(0.00f, 0.00f);
        glVertex2f(-0.08f, 0.04f);
    glEnd();

    // Right Circle
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.00f, 0.10f);
        glVertex2f(0.05f, 0.20f);
        glVertex2f(0.12f, 0.20f);
        glVertex2f(0.16f, 0.14f);
        glVertex2f(0.14f, 0.05f);
        glVertex2f(0.08f, 0.02f);
    glEnd();

    // Trunk
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON); // Main trunk
        glVertex2f(-0.02f, -0.20f);
        glVertex2f( 0.02f, -0.20f);
        glVertex2f( 0.01f,  0.00f);
        glVertex2f(-0.01f,  0.00f);
    glEnd();

    glBegin(GL_POLYGON); // Left branch
        glVertex2f(-0.01f, 0.00f);
        glVertex2f(-0.03f, 0.05f);
        glVertex2f(-0.01f, 0.05f);
        glVertex2f(0.00f, 0.01f);
    glEnd();

    glBegin(GL_POLYGON); // Right branch
        glVertex2f(0.01f, 0.00f);
        glVertex2f(0.03f, 0.05f);
        glVertex2f(0.01f, 0.05f);
        glVertex2f(0.00f, 0.01f);
    glEnd();
}




void TreeDrawing() {



    glPushMatrix();
    glTranslatef(-0.98f, -0.19f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, -0.21f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.35f, -0.21f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, -0.19f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, -0.21f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T2();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.27f, -0.21f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T2();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.35f, -0.19f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T1();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.57f, -0.21f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.77f, -0.21f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.96f, -0.19f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, -0.21f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    T2();
    glPopMatrix();



}






void TreeDrawing_2() {



    glPushMatrix();
    glTranslatef(-0.98f, -0.19f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, -0.21f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.35f, -0.21f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, -0.19f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, -0.21f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T2();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.27f, -0.21f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T2();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.35f, -0.19f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T1();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.57f, -0.21f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.77f, -0.21f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.96f, -0.19f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, -0.21f, 0.0f);
    glScalef(0.5f, 0.6f, 1.0f);
    T2();
    glPopMatrix();

}



void TreeDrawing_3() {


    glPushMatrix();
    glTranslatef(-0.78f, -0.39f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4f, -0.41f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.15f, -0.41f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, -0.39f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.015f, -0.41f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.47f, -0.41f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55f, -0.39f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.77f, -0.41f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.97f, -0.41f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.16f, -0.39f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9f, -0.41f, 0.0f);
    glScalef(0.5f, 0.65f, 1.0f);
    T2();
    glPopMatrix();



}










void B1() {


    glPushMatrix();
    glTranslatef(-0.4f, 0.1f, 0.0f);
    glScalef(0.58f, 0.48f, 1.0f);

    //  Left  Building
    glColor3f(0.58f, 0.0f, 0.83f);
    glBegin(GL_QUADS);
    glVertex2f(-0.95f, -0.8f);
    glVertex2f(-0.75f, -0.8f);
    glVertex2f(-0.75f, -0.3f);
    glVertex2f(-0.95f, -0.3f);
    glEnd();


    // Top trim
    glColor3f(0.1f, 0.2f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-0.96f, -0.3f);
    glVertex2f(-0.74f, -0.3f);
    glVertex2f(-0.74f, -0.27f);
    glVertex2f(-0.96f, -0.27f);
    glEnd();

    // Windows on left building
    glColor3f(0.8f, 0.95f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.93f, -0.76f);
    glVertex2f(-0.87f, -0.76f);
    glVertex2f(-0.87f, -0.68f);
    glVertex2f(-0.93f, -0.68f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.85f, -0.76f);
    glVertex2f(-0.79f, -0.76f);
    glVertex2f(-0.79f, -0.68f);
    glVertex2f(-0.85f, -0.68f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.93f, -0.64f);
    glVertex2f(-0.87f, -0.64f);
    glVertex2f(-0.87f, -0.56f);
    glVertex2f(-0.93f, -0.56f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.85f, -0.64f);
    glVertex2f(-0.79f, -0.64f);
    glVertex2f(-0.79f, -0.56f);
    glVertex2f(-0.85f, -0.56f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.93f, -0.52f);
    glVertex2f(-0.87f, -0.52f);
    glVertex2f(-0.87f, -0.44f);
    glVertex2f(-0.93f, -0.44f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.85f, -0.52f);
    glVertex2f(-0.79f, -0.52f);
    glVertex2f(-0.79f, -0.44f);
    glVertex2f(-0.85f, -0.44f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.93f, -0.40f);
    glVertex2f(-0.87f, -0.40f);
    glVertex2f(-0.87f, -0.32f);
    glVertex2f(-0.93f, -0.32f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.85f, -0.40f);
    glVertex2f(-0.79f, -0.40f);
    glVertex2f(-0.79f, -0.32f);
    glVertex2f(-0.85f, -0.32f);
    glEnd();

    // --- Middle  Building ---
   glColor3f(0.38f, 0.19f, 0.61f);
    glBegin(GL_QUADS);
    glVertex2f(-0.75f, -0.8f);
    glVertex2f(-0.49f, -0.8f);
    glVertex2f(-0.49f, -0.4f);
    glVertex2f(-0.75f, -0.4f);
    glEnd();

    // Windows
    glColor3f(0.8f, 0.95f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.73f, -0.76f);
    glVertex2f(-0.67f, -0.76f);
    glVertex2f(-0.67f, -0.68f);
    glVertex2f(-0.73f, -0.68f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.65f, -0.76f);
    glVertex2f(-0.59f, -0.76f);
    glVertex2f(-0.59f, -0.68f);
    glVertex2f(-0.65f, -0.68f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.57f, -0.76f);
    glVertex2f(-0.51f, -0.76f);
    glVertex2f(-0.51f, -0.68f);
    glVertex2f(-0.57f, -0.68f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.73f, -0.6f);
    glVertex2f(-0.67f, -0.6f);
    glVertex2f(-0.67f, -0.52f);
    glVertex2f(-0.73f, -0.52f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.65f, -0.6f);
    glVertex2f(-0.59f, -0.6f);
    glVertex2f(-0.59f, -0.52f);
    glVertex2f(-0.65f, -0.52f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.57f, -0.6f);
    glVertex2f(-0.51f, -0.6f);
    glVertex2f(-0.51f, -0.52f);
    glVertex2f(-0.57f, -0.52f);
    glEnd();

    //   Right  Tower
    glColor3f(0.58f, 0.0f, 0.83f);
    glBegin(GL_QUADS);
    glVertex2f(-0.52f, -0.8f);
    glVertex2f(-0.42f, -0.8f);
    glVertex2f(-0.42f, -0.1f);
    glVertex2f(-0.52f, -0.1f);
    glEnd();

    // Top trim
    glColor3f(0.1f, 0.2f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-0.53f, -0.1f);
    glVertex2f(-0.41f, -0.1f);
    glVertex2f(-0.41f, -0.07f);
    glVertex2f(-0.53f, -0.07f);
    glEnd();

    // Tall window
    glColor3f(0.8f, 0.95f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.49f, -0.3f);
    glVertex2f(-0.44f, -0.3f);
    glVertex2f(-0.44f, -0.12f);
    glVertex2f(-0.49f, -0.12f);
    glEnd();

     glPopMatrix();      // scaling and translation will work till here;

}





void B2() {
    glPushMatrix();
    glTranslatef(-0.2f, 0.1f, 0.0f);  // Move right
    glScalef(0.28f, 0.49f, 1.0f);


    glColor3f(0.82f, 0.71f, 0.55f);
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, -0.8f);
    glVertex2f( 0.2f, -0.8f);
    glVertex2f( 0.2f,  0.0f);
    glVertex2f(-0.2f,  0.0f);
    glEnd();

    // Windows
    glColor3f(0.94f, 0.98f, 0.91f);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.65f);
    glVertex2f(-0.05f, -0.65f);
    glVertex2f(-0.05f, -0.55f);
    glVertex2f(-0.15f, -0.55f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.45f);
    glVertex2f(-0.05f, -0.45f);
    glVertex2f(-0.05f, -0.35f);
    glVertex2f(-0.15f, -0.35f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.25f);
    glVertex2f(-0.05f, -0.25f);
    glVertex2f(-0.05f, -0.15f);
    glVertex2f(-0.15f, -0.15f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.05f, -0.65f);
    glVertex2f(0.15f, -0.65f);
    glVertex2f(0.15f, -0.55f);
    glVertex2f(0.05f, -0.55f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.05f, -0.45f);
    glVertex2f(0.15f, -0.45f);
    glVertex2f(0.15f, -0.35f);
    glVertex2f(0.05f, -0.35f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.05f, -0.25f);
    glVertex2f(0.15f, -0.25f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(0.05f, -0.15f);
    glEnd();

    // Top trim
    glColor3f(0.6f, 0.4f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, 0.0f);
    glVertex2f( 0.22f, 0.0f);
    glVertex2f( 0.22f, 0.04f);
    glVertex2f(-0.22f, 0.04f);
    glEnd();

    glPopMatrix();
}


    // --- Purple Building ---

 void B5() {


    glPushMatrix();
    glTranslatef(0.5f, 0.1f, 0.0f);
    glScalef(0.3f, 0.48f, 1.0f);



    glColor3f(0.96f, 0.64f, 0.38f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.8f);
        glVertex2f(0.3f, -0.8f);
        glVertex2f(0.3f, 0.4f);
        glVertex2f(-0.2f, 0.4f);
    glEnd();


    // Windows
    glColor3f(0.9f, 0.95f, 1.0f);

    // Row 1
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.6f);
        glVertex2f(-0.15f, -0.6f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.7f);
        glVertex2f(0.1f, -0.7f);
        glVertex2f(0.1f, -0.6f);
        glVertex2f(0.0f, -0.6f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.7f);
        glVertex2f(0.25f, -0.7f);
        glVertex2f(0.25f, -0.6f);
        glVertex2f(0.15f, -0.6f);
    glEnd();


    // Row 2
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.55f);
        glVertex2f(-0.05f, -0.55f);
        glVertex2f(-0.05f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.55f);
        glVertex2f(0.1f, -0.55f);
        glVertex2f(0.1f, -0.45f);
        glVertex2f(0.0f, -0.45f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.55f);
        glVertex2f(0.25f, -0.55f);
        glVertex2f(0.25f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();


    // Row 3
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.05f, -0.4f);
        glVertex2f(-0.05f, -0.3f);
        glVertex2f(-0.15f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.4f);
        glVertex2f(0.1f, -0.4f);
        glVertex2f(0.1f, -0.3f);
        glVertex2f(0.0f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.25f, -0.4f);
        glVertex2f(0.25f, -0.3f);
        glVertex2f(0.15f, -0.3f);
    glEnd();


    // Row 4
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.25f);
        glVertex2f(-0.05f, -0.25f);
        glVertex2f(-0.05f, -0.15f);
        glVertex2f(-0.15f, -0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.25f);
        glVertex2f(0.1f, -0.25f);
        glVertex2f(0.1f, -0.15f);
        glVertex2f(0.0f, -0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.25f);
        glVertex2f(0.25f, -0.25f);
        glVertex2f(0.25f, -0.15f);
        glVertex2f(0.15f, -0.15f);
    glEnd();


    // Row 5
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.05f, -0.1f);
        glVertex2f(-0.05f, 0.0f);
        glVertex2f(-0.15f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(0.1f, 0.0f);
        glVertex2f(0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.25f, -0.1f);
        glVertex2f(0.25f, 0.0f);
        glVertex2f(0.15f, 0.0f);
    glEnd();


    // Row 6
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.05f);
        glVertex2f(-0.05f, 0.05f);
        glVertex2f(-0.05f, 0.15f);
        glVertex2f(-0.15f, 0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, 0.15f);
        glVertex2f(0.0f, 0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, 0.05f);
        glVertex2f(0.25f, 0.05f);
        glVertex2f(0.25f, 0.15f);
        glVertex2f(0.15f, 0.15f);
    glEnd();



    // Top trim
    glColor3f(0.3f, 0.15f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-0.22f, 0.4f);
        glVertex2f(0.32f, 0.4f);
        glVertex2f(0.32f, 0.44f);
        glVertex2f(-0.22f, 0.44f);
    glEnd();

    glPopMatrix();
}






      // Building - 4

 void B6() {


    glPushMatrix();
    glTranslatef(0.85f, 0.1f, 0.0f);
    glScalef(0.3f, 0.48f, 1.0f);


    glColor3f(0.6f, 0.3f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.8f);
        glVertex2f(0.3f, -0.8f);
        glVertex2f(0.3f, 0.4f);
        glVertex2f(-0.2f, 0.4f);
    glEnd();


    // Windows
    glColor3f(0.9f, 0.95f, 1.0f);

    // Row 1
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.6f);
        glVertex2f(-0.15f, -0.6f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.7f);
        glVertex2f(0.1f, -0.7f);
        glVertex2f(0.1f, -0.6f);
        glVertex2f(0.0f, -0.6f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.7f);
        glVertex2f(0.25f, -0.7f);
        glVertex2f(0.25f, -0.6f);
        glVertex2f(0.15f, -0.6f);
    glEnd();


    // Row 2
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.55f);
        glVertex2f(-0.05f, -0.55f);
        glVertex2f(-0.05f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.55f);
        glVertex2f(0.1f, -0.55f);
        glVertex2f(0.1f, -0.45f);
        glVertex2f(0.0f, -0.45f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.55f);
        glVertex2f(0.25f, -0.55f);
        glVertex2f(0.25f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();


    // Row 3
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.05f, -0.4f);
        glVertex2f(-0.05f, -0.3f);
        glVertex2f(-0.15f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.4f);
        glVertex2f(0.1f, -0.4f);
        glVertex2f(0.1f, -0.3f);
        glVertex2f(0.0f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.25f, -0.4f);
        glVertex2f(0.25f, -0.3f);
        glVertex2f(0.15f, -0.3f);
    glEnd();


    // Row 4
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.25f);
        glVertex2f(-0.05f, -0.25f);
        glVertex2f(-0.05f, -0.15f);
        glVertex2f(-0.15f, -0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.25f);
        glVertex2f(0.1f, -0.25f);
        glVertex2f(0.1f, -0.15f);
        glVertex2f(0.0f, -0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.25f);
        glVertex2f(0.25f, -0.25f);
        glVertex2f(0.25f, -0.15f);
        glVertex2f(0.15f, -0.15f);
    glEnd();


    // Row 5
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.05f, -0.1f);
        glVertex2f(-0.05f, 0.0f);
        glVertex2f(-0.15f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(0.1f, 0.0f);
        glVertex2f(0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.25f, -0.1f);
        glVertex2f(0.25f, 0.0f);
        glVertex2f(0.15f, 0.0f);
    glEnd();


    // Row 6
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.05f);
        glVertex2f(-0.05f, 0.05f);
        glVertex2f(-0.05f, 0.15f);
        glVertex2f(-0.15f, 0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, 0.15f);
        glVertex2f(0.0f, 0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, 0.05f);
        glVertex2f(0.25f, 0.05f);
        glVertex2f(0.25f, 0.15f);
        glVertex2f(0.15f, 0.15f);
    glEnd();



    // Top trim
    glColor3f(0.3f, 0.15f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-0.22f, 0.4f);
        glVertex2f(0.32f, 0.4f);
        glVertex2f(0.32f, 0.44f);
        glVertex2f(-0.22f, 0.44f);
    glEnd();

    glPopMatrix();
}








      // Building - 5

 void B3() {


    glPushMatrix();
    glTranslatef(-0.45f, 0.1f, 0.0f);
    glScalef(0.3f, 0.48f, 1.0f);


    // --- Purple Building ---
    glColor3f(0.70f, 0.56f, 0.42f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.8f);
        glVertex2f(0.3f, -0.8f);
        glVertex2f(0.3f, 0.4f);
        glVertex2f(-0.2f, 0.4f);
    glEnd();


    // Windows
    glColor3f(0.9f, 0.95f, 1.0f);

    // Row 1
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.6f);
        glVertex2f(-0.15f, -0.6f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.7f);
        glVertex2f(0.1f, -0.7f);
        glVertex2f(0.1f, -0.6f);
        glVertex2f(0.0f, -0.6f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.7f);
        glVertex2f(0.25f, -0.7f);
        glVertex2f(0.25f, -0.6f);
        glVertex2f(0.15f, -0.6f);
    glEnd();


    // Row 2
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.55f);
        glVertex2f(-0.05f, -0.55f);
        glVertex2f(-0.05f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.55f);
        glVertex2f(0.1f, -0.55f);
        glVertex2f(0.1f, -0.45f);
        glVertex2f(0.0f, -0.45f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.55f);
        glVertex2f(0.25f, -0.55f);
        glVertex2f(0.25f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();


    // Row 3
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.05f, -0.4f);
        glVertex2f(-0.05f, -0.3f);
        glVertex2f(-0.15f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.4f);
        glVertex2f(0.1f, -0.4f);
        glVertex2f(0.1f, -0.3f);
        glVertex2f(0.0f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.25f, -0.4f);
        glVertex2f(0.25f, -0.3f);
        glVertex2f(0.15f, -0.3f);
    glEnd();


    // Row 4
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.25f);
        glVertex2f(-0.05f, -0.25f);
        glVertex2f(-0.05f, -0.15f);
        glVertex2f(-0.15f, -0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.25f);
        glVertex2f(0.1f, -0.25f);
        glVertex2f(0.1f, -0.15f);
        glVertex2f(0.0f, -0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.25f);
        glVertex2f(0.25f, -0.25f);
        glVertex2f(0.25f, -0.15f);
        glVertex2f(0.15f, -0.15f);
    glEnd();


    // Row 5
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.05f, -0.1f);
        glVertex2f(-0.05f, 0.0f);
        glVertex2f(-0.15f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(0.1f, 0.0f);
        glVertex2f(0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.25f, -0.1f);
        glVertex2f(0.25f, 0.0f);
        glVertex2f(0.15f, 0.0f);
    glEnd();


    // Row 6
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.05f);
        glVertex2f(-0.05f, 0.05f);
        glVertex2f(-0.05f, 0.15f);
        glVertex2f(-0.15f, 0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, 0.15f);
        glVertex2f(0.0f, 0.15f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15f, 0.05f);
        glVertex2f(0.25f, 0.05f);
        glVertex2f(0.25f, 0.15f);
        glVertex2f(0.15f, 0.15f);
    glEnd();



    // Top trim
    glColor3f(0.3f, 0.15f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-0.22f, 0.4f);
        glVertex2f(0.32f, 0.4f);
        glVertex2f(0.32f, 0.44f);
        glVertex2f(-0.22f, 0.44f);
    glEnd();

    glPopMatrix();
}




void B4()
{
    glPushMatrix();
    glTranslatef(0.67f, 0.43f, 0.0f);
    glScalef(0.99f, 0.9f, 1.0f);

    glColor3f(0.00f, 0.50f, 0.50f);
    glBegin(GL_QUADS);
        glVertex2f(-0.75f, -0.8f);
        glVertex2f(-0.41f, -0.8f);
        glVertex2f(-0.41f, -0.4f);
        glVertex2f(-0.75f, -0.4f);
    glEnd();

    // --- Windows (Upper Row) ---
    glColor3f(0.8f, 0.95f, 1.0f);

    glBegin(GL_QUADS);
        glVertex2f(-0.73f, -0.76f);
        glVertex2f(-0.67f, -0.76f);
        glVertex2f(-0.67f, -0.68f);
        glVertex2f(-0.73f, -0.68f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-0.65f, -0.76f);
        glVertex2f(-0.59f, -0.76f);
        glVertex2f(-0.59f, -0.68f);
        glVertex2f(-0.65f, -0.68f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-0.57f, -0.76f);
        glVertex2f(-0.51f, -0.76f);
        glVertex2f(-0.51f, -0.68f);
        glVertex2f(-0.57f, -0.68f);
    glEnd();

    glBegin(GL_QUADS);  // 4th upper window
        glVertex2f(-0.49f, -0.76f);
        glVertex2f(-0.43f, -0.76f);
        glVertex2f(-0.43f, -0.68f);
        glVertex2f(-0.49f, -0.68f);
    glEnd();

    // --- Windows (Lower Row) ---
    glBegin(GL_QUADS);
        glVertex2f(-0.73f, -0.6f);
        glVertex2f(-0.67f, -0.6f);
        glVertex2f(-0.67f, -0.52f);
        glVertex2f(-0.73f, -0.52f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-0.65f, -0.6f);
        glVertex2f(-0.59f, -0.6f);
        glVertex2f(-0.59f, -0.52f);
        glVertex2f(-0.65f, -0.52f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-0.57f, -0.6f);
        glVertex2f(-0.51f, -0.6f);
        glVertex2f(-0.51f, -0.52f);
        glVertex2f(-0.57f, -0.52f);
    glEnd();

    glBegin(GL_QUADS);  // 4th lower window
        glVertex2f(-0.49f, -0.6f);
        glVertex2f(-0.43f, -0.6f);
        glVertex2f(-0.43f, -0.52f);
        glVertex2f(-0.49f, -0.52f);
    glEnd();


     //top trim
     glColor3f(0.00f, 0.35f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-0.76f, -0.4f);
    glVertex2f(-0.40f, -0.4f);
    glVertex2f(-0.40f, -0.37f);
    glVertex2f(-0.76f, -0.37f);
    glEnd();


    glPopMatrix();
}









void display_3()
{

    Show();

}






void display_1_show() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    Sky_Drawing();
    GrassField();
    B1();
    B2();
    B3();
    B4();
    B5();
    B6();
    TreeDrawing();


    DrawDaystar (-0.1f, 0.8f, 0.1f);   // sun


    drawCloud(-0.7f, 0.6f, 0.8f);  // Big cloud left
    drawCloud(0.3f, 0.7f, 1.0f);   // Bigger cloud right
    drawCloud(0.6f, 0.7f, 0.4f);   // Smaller cloud right
    drawCloud(-0.8f, 0.75f, 0.3f); // Small cloud left
    glutTimerFunc(0, update_s1, 0);

    drawHelipad();

    Road_first();
    Road_second();

    Road_brick_horizontal();
    TreeDrawing_2();
    TreeDrawing_3();


    glTranslatef(0.0f, heliY, 0.0f);
    glTranslatef(heliX, 0.0f, 0.0f);
    glutTimerFunc(0, updateHelicopter, 0);


    glTranslatef(0.5f, 0.0f, 0.0f);
    drawHelicopter();
    glutTimerFunc(0, animateRotors, 0);




    glFlush();

}




bool showFirstWindow = true;
bool showSecondWindow = true;
bool showThirdWindow = true;
bool showFourthWindow = true;





void display_1()
{
    if(showSecondWindow)
    {
        display_1_show();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}







void createFourthWindow() {

    glutInitWindowSize(width_S, height_S);
    glutCreateWindow("Sundarban project  AIUB");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutKeyboardFunc(handleKeypress);
    initRain();
    initBirds();
    glutDisplayFunc(display);


    glutReshapeFunc(reshape_S);
    glutTimerFunc(0, update_S, 0);

}



void handleKeypress_ThirdWindow(unsigned char key, int x, int y) {
    if (key == 'g' && showThirdWindow) {
        showThirdWindow = false;
        glutPostRedisplay();
        createFourthWindow();
    }
}




void createThirdWindow() {

    glutInitWindowSize(800, 600);
    glutCreateWindow(" Dhaka City");
    glutDisplayFunc(display_3);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);

    glutKeyboardFunc(handleKeypress_ThirdWindow);

}



void handleKeypress_SecondWindow(unsigned char key, int x, int y) {
    if (key == 'f' && showSecondWindow) {
        showSecondWindow = false;
        glutPostRedisplay();
        createThirdWindow();
    }
}


// Function to create the second window
void createSecondWindow() {

    glutInitWindowSize(800, 500);
    glutCreateWindow("Canvas Of Bangladesh - Start");
    glutDisplayFunc(display_1);
    glutKeyboardFunc(handleKeypress_SecondWindow);

}




void handleKeypress_FirstWindow(unsigned char key, int x, int y) {
    if (key == 'd' && showFirstWindow) {
        showFirstWindow = false;
        glutPostRedisplay();
        createSecondWindow();
    }
}





// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // First window
    glutInitWindowSize(420, 420);
    glutCreateWindow("Canvas Of Bangladesh - Map");
    init();
    glutDisplayFunc(display_2);
    glutKeyboardFunc(handleKeypress_FirstWindow);  // For first window


    glutMainLoop();
    return 0;
}
