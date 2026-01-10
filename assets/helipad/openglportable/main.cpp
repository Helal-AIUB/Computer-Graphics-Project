// Scenario  : HeliPad
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


void updateHelicopter(int value) {

    if (movingUp==true) {
        heliY += 0.0001f;
        if (heliY >= 3.f) {
            movingUp = false;

        }
    } else {
        heliX -= 0.0001f;
        if (heliX >= -1.2f) {
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




//  Heliipad Drawing

void drawHelipad() {

    // Draw oval base
    glPushMatrix();
    glTranslatef(-0.61f, -0.6f, 0.0f);  // Position on screen
    glScalef(1.5f, 1.0f, 1.0f);      // Oval effect
    glColor3f(0.6f, 0.3f, 0.2f);     // Brick color
    drawFilledCircle(0.0f, 0.0f, 0.09f, 100);
    glPopMatrix();


    // Draw "H" on top
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




void display_1_show() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    Sky_Drawing();
    GrassField();


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


    glTranslatef(0.0f, heliY, 0.0f);
    glTranslatef(heliX, 0.0f, 0.0f);
    glutTimerFunc(0, updateHelicopter, 0);


    glTranslatef(0.5f, 0.0f, 0.0f);
    drawHelicopter();
    glutTimerFunc(0, animateRotors, 0);




    glFlush();

}




void display_1()
{
        display_1_show();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}


// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // First window
    glutInitWindowSize(800, 500);
    glutCreateWindow("Canvas Of Bangladesh");
    init();
    glutDisplayFunc(display_1);

    glutMainLoop();
    return 0;
}
