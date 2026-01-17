#include <GL/glut.h>
#include <cmath>

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
void display() {
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


}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Moving Plane and Clouds - OpenGL"); //start
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

