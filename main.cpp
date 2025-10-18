
#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>

//////water
int waterStatus = 0;
float waterX = 0;
float waterY = 0;
float shipx=0;
float shipy=0;

//////cloud
int meghmegh = 1;
int meghStatus = 0;
float meghX = 0;
float meghY = 0;
/////sun
int sunStatus = 0;
float sunX = 0;
float sunY = 0;

//////
float shipX = 0;
float shipY =0;

int springstatus=0;
int lightstatus = 0;

int  ships1 =1;
GLfloat cloudSpeed=0.05f;
GLfloat Position3= 330;

int currentScene = 0;  // 0 for river, 1 for beach
GLfloat skyColorR = 102.0f / 255.0f;
GLfloat skyColorG = 212.0f / 255.0f;
GLfloat skyColorB = 238.0f / 255.0f;
void drawQuad(GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3)
{ glBegin(GL_QUADS);
  glVertex2f(x0,y0);glVertex2f(x1,y1);glVertex2f(x2,y2);glVertex2f(x3,y3);
  glEnd();
}

void drawTriangle(GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2)
{   glBegin(GL_TRIANGLES);
    glVertex2f(x0,y0);glVertex2f(x1,y1);glVertex2f(x2,y2);
    glEnd();
}
void DrawCircle(float cx, float cy, float r, int num_segments) {

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get current angle

		float x = r * cosf(theta);//calculate x
		float y = r * sinf(theta);//calculate y

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
	glFlush();
}

void update3(int value){
    if(Position3<-300)
    {
        Position3=+30.0f;
    }
    if(Position3>300)
       {
           Position3=3;
       }
      Position3 -= cloudSpeed;
      glutPostRedisplay();
      glutTimerFunc(400, update3, 0);////snow spped increase/decrease
}

////////////////// sun movement
float position2 = 0.0f;
float speed2 = 0.6f;

void update2(int value){
    if(position2 > 300)
    position2 = +1500;
    position2 += speed2;
    glutPostRedisplay();
    glutTimerFunc(130, update2, 0);//sun spped increase/decrease
}
void sky(){
    glColor3ub (102, 212, 238);
    glBegin(GL_QUADS);
    glVertex2f(0, 480);
    glVertex2f(0, 255);
    glVertex2f(640, 255);
    glVertex2f(640, 480);
    glEnd();
}

void hills(){
//from left 1st hill
glColor3ub (150, 129, 117);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 250);
    glVertex2f(0, 300);
    glVertex2f(55, 250);

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 250);
    glVertex2f(0, 400);
    glVertex2f(0, 400);
    glVertex2f(55, 255);
    glEnd();


    glColor3ub (150, 129, 117);
    glBegin(GL_TRIANGLES);
    glVertex2f(20, 255);
    glVertex2f(120, 340);
    glVertex2f(200, 255);

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(30, 275);
    glVertex2f(120, 340);

    glVertex2f(120, 340);
    glVertex2f(200, 255);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(20, 255);
    glVertex2f(120, 340);

    glVertex2f(120, 340);
    glVertex2f(200, 255);
    glEnd();

    glColor3ub (150, 129, 117);
    glBegin(GL_TRIANGLES);
    glVertex2f(20, 255);
    glVertex2f(120, 340);
    glVertex2f(200, 255);

    glColor3ub (150, 129, 117);
    glBegin(GL_TRIANGLES);
    glVertex2f(180, 255);
    glVertex2f(270, 320);
    glVertex2f(360, 255);
    glEnd();
    //////line shape
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(180, 255);
    glVertex2f(270, 320);

    glVertex2f(270, 320);
    glVertex2f(360, 255);
    glEnd();

    glColor3ub (150, 129, 117);
    glBegin(GL_TRIANGLES);
    glVertex2f(260, 255);
    glVertex2f(340, 360);
    glVertex2f(450, 255);
    glEnd();
    //////line shape
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(293, 299);
    glVertex2f(340, 360);
    glVertex2f(340, 360);
    glVertex2f(450, 255);
    glEnd();
    //right last hills
    glColor3ub (150, 129, 117);
    glBegin(GL_TRIANGLES);
    glVertex2f(440, 255);
    glVertex2f(535, 385);
    glVertex2f(650, 250);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(440, 255);
    glVertex2f(535, 385);
    glVertex2f(535, 385);
    glVertex2f(650, 250);
    glEnd();

    glFlush();
}
void drawWaves() {
    glColor3ub(47, 136, 220);  // Set wave color (same as water)

    glBegin(GL_TRIANGLE_STRIP);
    float waveAmplitude = 10.0f;  // Amplitude of the waves
    float waveFrequency = 0.05f;  // Frequency of the waves
    float waveSpeed = 0.05f;      // Speed at which the waves move

    for (float x = 0; x <= 640; x += 1.0f) {  // Iterate over the width of the screen
        float y = waveAmplitude * sin(waveFrequency * x + waveSpeed);  // Sine wave for smooth oscillation
        glVertex2f(x, 255 + y);  // Position waves just above the river's surface
        glVertex2f(x, 255);  // Create a filled area between the wave and the river
    }
    glEnd();
}
float waveOffset = 0.0f;

void updateWaves(int value) {
    waveOffset += 0.1f;  // Adjust wave speed by changing this value
    if (waveOffset > 360.0f) waveOffset -= 360.0f;  // Reset the offset after a full cycle

    glutPostRedisplay();  // Request a redraw of the window
    glutTimerFunc(30, updateWaves, 0);  // Repeat the function after 30 ms
}


void river() {
    glColor3ub(47, 136, 220);  // River color
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(640, 0);
    glVertex2f(640, 255);
    glVertex2f(0, 255);
    glEnd();

    // Draw animated waves on top of the river
    drawWaves();
}

////////////////ship///////////////
void ship()
{

    glTranslated(0,110,0);
    glScaled(20,15,0);

    glBegin(GL_POLYGON);
    glColor3ub(16,58,65);
    glVertex2f(1,5.5);
    glColor3ub(0,49,57);
    glVertex2f(3,1);
    glColor3ub(0,49,57);
    glVertex2f(19,1);
    glColor3ub(16,58,65);
    glVertex2f(21,5.5);
    glEnd();

    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(3.5,5.5);
    glVertex2f(3.5,7);
    glVertex2f(19.5,7);
    glVertex2f(19.5,5.5);
    glEnd();

    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(4.5,8);
    glVertex2f(4.5,7);
    glVertex2f(18.5,7);
    glVertex2f(18.5,8);
    glEnd();

    // Windows
    glColor3f(0.9,0.9,0.9);
    glBegin(GL_POLYGON);
    glVertex2f(6,7);
    glVertex2f(6,7.5);
    glVertex2f(8,7.5);
    glVertex2f(8,7);
    glEnd();

    glTranslated(3,-0.5,0);

    glBegin(GL_POLYGON);
    glVertex2f(6,7.5);
    glVertex2f(6,8);
    glVertex2f(8,8);
    glVertex2f(8,7.5);
    glEnd();

    glTranslated(3,0,0);

    glBegin(GL_POLYGON);
    glVertex2f(6,7.5);
    glVertex2f(6,8);
    glVertex2f(8,8);
    glVertex2f(8,7.5);
    glEnd();

    glTranslated(3,0,0);

    glBegin(GL_POLYGON);
    glVertex2f(6,7.5);
    glVertex2f(6,8);
    glVertex2f(8,8);
    glVertex2f(8,7.5);
    glEnd();

    // Steam Pipes
    glColor3ub(21,21,21);
    glTranslated(-8,-1.6,0);
    glBegin(GL_POLYGON);
    glVertex2f(4.1,10);
    glVertex2f(4,12.9);
    glVertex2f(5.6,12.9);
    glVertex2f(5.7,10);
    glEnd();

    glColor3ub(69,21,0);
    glBegin(GL_POLYGON);
    glVertex2f(4,12.9);
    glVertex2f(3.9,13.5);
    glVertex2f(5.5,13.5);
    glVertex2f(5.6,12.9);
    glEnd();

    glTranslated(3,0,0);

    glColor3ub(21,21,21);
    glBegin(GL_POLYGON);
    glVertex2f(4.1,10);
    glVertex2f(4,12.9);
    glVertex2f(5.6,12.9);
    glVertex2f(5.7,10);
    glEnd();

    glColor3ub(69,21,0);
    glBegin(GL_POLYGON);
    glVertex2f(4,12.9);
    glVertex2f(3.9,13.5);
    glVertex2f(5.5,13.5);
    glVertex2f(5.6,12.9);
    glEnd();

    glTranslated(3,0,0);

    glColor3ub(21,21,21);
    glBegin(GL_POLYGON);
    glVertex2f(4.1,10);
    glVertex2f(4,12.9);
    glVertex2f(5.6,12.9);
    glVertex2f(5.7,10);
    glEnd();

    glColor3ub(69,21,0);
    glBegin(GL_POLYGON);
    glVertex2f(4,12.9);
    glVertex2f(3.9,13.5);
    glVertex2f(5.5,13.5);
    glVertex2f(5.6,12.9);
    glEnd();
}
//////////////Ship end////////////////////


///////////////////moving ship
void moveship(int xx){

if(ships1==1)

    {

        shipx+=0.05;//change left or right

    }

    glPushMatrix();
    glTranslatef(shipx, shipy, 0);
    if(xx==1)
        {

    ship();
    }
    else{
       ship();
    }
    glPopMatrix();
    glFlush();

}

void megh(){
     glColor3ub (200, 220, 220);
	DrawCircle(20, 450, 25, 2000);
	DrawCircle(50, 450, 35, 2000);
	DrawCircle(80, 450, 25, 2000);

    glColor3ub (200, 220, 220);
	DrawCircle(220, 400, 25, 2000);
	DrawCircle(250, 400, 35, 2000);
	DrawCircle(280, 400, 25, 2000);

    glColor3ub (200, 220, 220);
	DrawCircle(300, 420, 25, 2000);
	DrawCircle(330, 420, 35, 2000);
	DrawCircle(360, 420, 25, 2000);

    glColor3ub (200, 220, 220);
	DrawCircle(400, 400, 25, 2000);
	DrawCircle(430, 400, 35, 2000);
	DrawCircle(460, 400, 25, 2000);
	glFlush();

	glColor3ub (200, 220, 220);
	DrawCircle(580, 480, 25, 2000);
	DrawCircle(510, 480, 35, 2000);
	DrawCircle(540, 480, 25, 2000);
	glFlush();
}




void drawSun(){

    // Set the position of the sun on the left side
    float sunPosX = 100.0f; // Adjust this value to change the position
    float sunPosY = 400.0f; // Adjust this value to change the position
    float sunRadius = 50.0f;

    glColor3ub(255, 255, 0); // Yellow color for the sun
    DrawCircle(sunPosX, sunPosY, sunRadius, 2000);

}




void moveMegh(int x){

            if(meghStatus ==0){
            meghX +=0.5;//move megh right or left
            }
    if (meghX>400)
        {
            meghX =-100;
        }
    glPushMatrix();
    glTranslatef(meghX, meghY, 0);


      if(x==1)
    {
       megh();

    }


    glPopMatrix();
    glFlush();
}
void drawPerson(float x, float y) {
    // Draw head
    glColor3ub(0, 0, 0);  // Skin color
    DrawCircle(x, y + 20, 10, 1000);  // Head circle

    // Draw body
    glColor3ub(0, 128, 255);  // Shirt color
    glBegin(GL_QUADS);
    glVertex2f(x - 10, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 10, y - 20);
    glVertex2f(x - 10, y - 20);
    glEnd();

    // Draw legs
    glColor3ub(0, 212, 0);  // Pants color
    glBegin(GL_QUADS);
    glVertex2f(x - 5, y - 20);
    glVertex2f(x + 5, y - 20);
    glVertex2f(x + 5, y - 40);
    glVertex2f(x - 5, y - 40);
    glEnd();

    // Draw arms
    glColor3ub(255, 224, 0);  // Skin color for arms
    glBegin(GL_QUADS);
    glVertex2f(x - 15, y - 5);
    glVertex2f(x - 5, y - 5);
    glVertex2f(x - 5, y - 15);
    glVertex2f(x - 15, y - 15);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x + 5, y - 5);
    glVertex2f(x + 15, y - 5);
    glVertex2f(x + 15, y - 15);
    glVertex2f(x + 5, y - 15);
    glEnd();
}
void drawHalfSun(float sunPosX, float sunPosY, float sunRadius) {
    int numSegments = 100; // Number of segments used to draw the circle
    float angle;

    glColor3ub(255, 69, 0); // Orange color for sunset

    // Start drawing a fan of triangles for the top half of the sun
    glBegin(GL_TRIANGLE_FAN);

    // Center of the sun
    glVertex2f(sunPosX, sunPosY);

    // Draw the upper half of the sun (180 degrees, from left to right)
    for (int i = 0; i <= numSegments / 2; i++) {
        angle = 2.0f * M_PI * float(i) / float(numSegments); // Angle for each segment
        float x = sunRadius * cos(angle);
        float y = sunRadius * sin(angle);
        glVertex2f(sunPosX + x, sunPosY + y);
    }

    glEnd();
}
void drawPalmTree(float x, float y) {
    // Draw the trunk
    glColor3ub(139, 69, 19);  // Brown color for the trunk
    glBegin(GL_QUADS);
    glVertex2f(x - 5, y);
    glVertex2f(x + 5, y);
    glVertex2f(x + 5, y + 50);  // Height of the trunk
    glVertex2f(x - 5, y + 50);
    glEnd();

    // Draw the leaves (fan-like shape)
    glColor3ub(34, 139, 34);  // Green color for the leaves
    glBegin(GL_TRIANGLES);

    // Upper left leaf
    glVertex2f(x, y + 50);
    glVertex2f(x - 30, y + 70);
    glVertex2f(x, y + 60);

    // Upper right leaf
    glVertex2f(x, y + 50);
    glVertex2f(x + 30, y + 70);
    glVertex2f(x, y + 60);

    // Left middle leaf
    glVertex2f(x, y + 50);
    glVertex2f(x - 40, y + 40);
    glVertex2f(x, y + 60);


    // Right middle leaf
    glVertex2f(x, y + 50);
    glVertex2f(x + 40, y + 40);
    glVertex2f(x, y + 60);

    // Lower left leaf
    glVertex2f(x, y + 50);
    glVertex2f(x - 30, y + 30);
    glVertex2f(x, y + 60);

    // Lower right leaf
    glVertex2f(x, y + 50);
    glVertex2f(x + 30, y + 30);
    glVertex2f(x, y + 60);

    glEnd();
}



void drawSunbed(float x, float y) {
    // Draw the main part of the sunbed (the mattress)
    glColor3ub(210, 140, 140); // Light brown color for the mattress
    glBegin(GL_QUADS);
    glVertex2f(x, y);           // Bottom left
    glVertex2f(x + 60, y);      // Bottom right
    glVertex2f(x + 60, y + 10); // Top right
    glVertex2f(x, y + 10);      // Top left
    glEnd();

    // Draw the legs of the sunbed
    glColor3ub(139, 69, 19); // Darker brown color for the legs
    glBegin(GL_QUADS);
    glVertex2f(x, y - 10);       // Left leg
    glVertex2f(x + 5, y - 10);
    glVertex2f(x + 5, y);        // Top of the left leg
    glVertex2f(x, y);            // Bottom of the left leg

    glVertex2f(x + 55, y - 10);  // Right leg
    glVertex2f(x + 60, y - 10);
    glVertex2f(x + 60, y);       // Top of the right leg
    glVertex2f(x + 55, y);       // Bottom of the right leg
    glEnd();
}

float person1X = 100;
float person1Y = 50;

float person2X = 200;
float person2Y = 270;

float person3X = 400;
float person3Y = 240;

float person4X = 450;
float person4Y = 60;

void beach() {
    // Sky
    glColor3ub(255, 140,0); // Light blue
    glBegin(GL_QUADS);
    glVertex2f(0, 480);
    glVertex2f(0, 255);
    glVertex2f(640, 255);
    glVertex2f(640, 480);
    glEnd();

    // Sand
    glColor3ub(237, 201, 175); // Sandy color
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(640, 0);
    glVertex2f(640, 255);
    glVertex2f(0, 255);
    glEnd();

    // Draw waves or water (ocean)
    glColor3ub(47, 136, 220); // Ocean color
    glBegin(GL_QUADS);
    glVertex2f(0, 100);
    glVertex2f(640, 100);
    glVertex2f(640, 200);
    glVertex2f(0, 200);
    glEnd();

    // Draw people with updated positions
    drawPerson(person1X, person1Y);
    drawPerson(person2X, person2Y);
    drawPerson(person3X, person3Y);
    drawPerson(person4X, person4Y);

    // Draw palm trees
    drawPalmTree(100, 200);  // Place the first palm tree
    drawPalmTree(300, 50);  // Place the second palm tree
    drawPalmTree(500, 220);  // Place the third palm tree



    // Draw sunbeds
    drawSunbed(200, 40);     // Place a sunbed
    drawSunbed(400, 40);     // Place another sunbed
}
void updateClouds(int value){
    if (meghStatus == 0) {  // If the clouds should move
        meghX += 0.00005f;  // Adjust this value for speed
    }
    if (meghX > 640) { // If clouds move off the screen (right boundary)
        meghX = -100;  // Reset position to the left of the screen
    }

    glutPostRedisplay();  // Request redisplay to update the scene
    glutTimerFunc(30, updateClouds, 0); // Continuously call the function every 30 ms
}


void myDisplay(void) {
    if (currentScene == 0) {
        // River scene
        if (position2 >= -250.0f) {
            sky();
            hills();
            drawSun();
            river();
            moveMegh(1);
            moveship(1);
        } else {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Add your night-time rendering code here if you have it.
            moveMegh(2);
            moveship(1);
        }
    } else if (currentScene == 1) {
        // Beach scene
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        beach();
        // Draw the half sun at the horizon
        drawHalfSun(320.0f, 255.0f, 50.0f); // Position the half sun at the horizon
        moveMegh(1);  // Optionally, clouds in beach scene
        moveship(1);  // Optionally, a ship near the beach
    }

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
    glutTimerFunc(30, updateClouds, 0);
}

void mykeyboard(unsigned char key, int x, int y) {
    if (key == 'C' || key == 'c') {
        meghStatus = 1;  // Move clouds
    } else if (key == 'V' || key == 'v') {
        meghStatus = 0;  // Stop clouds
        }if (key == 'M' || key == 'm') {
        ships1 = 1;  // Move clouds
    } else if (key == 'N' || key == 'n') {
        ships1 = 0;  // Stop clouds
    } else if (key == 'S' || key == 's') {
        // Change the sky color (e.g., sunset)
        skyColorR = 255.0f / 255.0f;  // Red
        skyColorG = 140.0f / 255.0f;  // Orange
        skyColorB = 0.0f;             // No blue
    } else if (key == 'B' || key == 'b') {
        // Reset the sky color (back to day time)
        skyColorR = 102.0f / 255.0f;
        skyColorG = 212.0f / 255.0f;
        skyColorB = 238.0f / 255.0f;
        currentScene = 1;  // Switch to beach scene
    } else if (key == 'R' || key == 'r') {
        currentScene = 0;  // Switch back to river scene
    }
}

void myInit(void){
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glColor3f(.0f,.0f,.0f);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Ship on the River");

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(mykeyboard);


    myInit();

    glutTimerFunc(30, update2, 0);  // Timer for sun
    glutTimerFunc(5, update3, 0);   // Timer for clouds
    glutTimerFunc(30, updateWaves, 0);  // Timer for waves (new!)

    glutMainLoop();
    return 0;
}
