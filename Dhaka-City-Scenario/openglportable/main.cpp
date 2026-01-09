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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Moving Plane and Clouds - OpenGL"); //start

    glutMainLoop();
    return 0;
}

