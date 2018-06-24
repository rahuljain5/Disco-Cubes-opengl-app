#include <iostream>
#include <string.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
using namespace std;
GLfloat vertices[][3] = {{-4.15, -4.15, -4.15}, {4.15, -4.15, -4.15}, {4.15, 4.15, -4.15}, {-4.15, 4.15, -4.15}, {-4.15, -4.15, 4.15}, {4.15, -4.15, 4.15}, {4.15, 4.15, 4.15}, {-4.15, 4.15, 4.15}};
GLfloat vertices_small[][3] = {{-2.0, -2.0, -2.0}, {2.0, -2.0, -2.0}, {2.0, 2.0, -2.0}, {-2.0, 2.0, -2.0}, {-2.0, -2.0, 2.0}, {2.0, -2.0, 2.0}, {2.0, 2.0, 2.0}, {-2.0, 2.0, 2.0}};
GLfloat _positions[][3] = {{-28, -4, 8}, {-37, -4, -37}, {28, -4, 10}, {37, -4, -37}};
GLchar images[][25] = {"./images/a41.jpg", "./images/images__1_.jpg", "./images/a7.jpg", "./images/d3.jpg", "./images/a8.jpg", "./images/a6.jpg", "./images/download.jpg", "./images/d4.jpg", "./images/a14.jpg", "./images/1.jpg", "./images/a9.jpg", "./images/a10.jpg", "./images/a11.jpg", "./images/a12.jpg", "./images/a13.jpg"};
GLchar img[25];
GLfloat slack = 0.0;
GLfloat _angle1 = 0.0;
const float BOX_POS = 7.1f;     //The height of the box off of the ground
const float FLOOR_SIZE = 90.0f; //The length of each side of the floor
GLuint tex_2d;
int num = 0;
float zoom = -40.0f;
float yoom = 0.0f;
float xoom = 0.0f;
//Draws the faces of cube with image
void polygon(int a, int b, int c, int d)
{
    int i;
    num = rand();
    num = num % 15;
    strcpy(img, images[num]);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    tex_2d = SOIL_load_OGL_texture(
        img,
        SOIL_LOAD_RGB,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_NTSC_SAFE_RGB);
    for (i = 0; i < 2000; i++)
        for (int j = 0; j < 1000; j++)
        {
            ;
        }
    glBindTexture(GL_TEXTURE_2D, tex_2d);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(vertices[d]);
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(vertices[a]);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(vertices[b]);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(vertices[c]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glFlush();
}
//Draws the cube
void drawCube(float angle)
{
    glPushMatrix();
    glRotatef(-angle, 1.0f, 1.0f, 0.0f);
    polygon(0, 3, 2, 1);
    polygon(2, 3, 7, 6);
    polygon(0, 4, 7, 3);
    polygon(4, 5, 6, 7);
    polygon(0, 1, 5, 4);
    polygon(1, 5, 6, 2);
    glPopMatrix();
}

//Draws mini cube faces
void mini_polygon(int a, int b, int c, int d)
{
    glBegin(GL_QUADS);
    glColor3ub(rand() % 255, rand() % 255, rand() % 255);
    glVertex3fv(vertices_small[a]);
    glVertex3fv(vertices_small[b]);
    glVertex3fv(vertices_small[c]);
    glVertex3fv(vertices_small[d]);
    glEnd();
    glFlush();
}
//Draws mini cube
void draw_mini_Cube(float angle1)
{
    int i;
    glColor3f(1.0, 1.0, 1.0);
    for (i = 0; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(_positions[i][0], _positions[i][1], _positions[i][2]);
        glRotatef(-angle1, 1.0f, 1.0f, 0.0f);
        mini_polygon(0, 3, 2, 1);
        mini_polygon(2, 3, 7, 6);
        mini_polygon(0, 4, 7, 3);
        mini_polygon(4, 5, 6, 7);
        mini_polygon(0, 1, 5, 4);
        mini_polygon(1, 5, 6, 2);
        glPopMatrix();
    }
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(37, -4, -37);
    glVertex3f(-37, -4, -37);
    glVertex3f(-28, -4, 8);
    glVertex3f(28, -4, 10);
    glEnd();
}
//Draws the floor
void drawFloor()
{
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-FLOOR_SIZE / 2, 0, FLOOR_SIZE / 2);
    glVertex3f(-FLOOR_SIZE / 2, 0, -FLOOR_SIZE / 2);
    glVertex3f(FLOOR_SIZE / 2, 0, -FLOOR_SIZE / 2);
    glVertex3f(FLOOR_SIZE / 2, 0, FLOOR_SIZE / 2);
    glEnd();
}
float _angle = 0;
//Keyboard Function
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
        break;
    case 32: //space bar
        slack = 0.0;
        break;
    case 13: //enter key
        slack = 6.0;
        break;
    case 8: //Backspace
        slack = -6.0;
        break;
    case 'z': //zoom in
        zoom--;
        break;
    case 'x': //zoom out
        zoom++;
        break;
    case 'a': //move left
        xoom++;
        break;
    case 's': //move right
        xoom--;
        break;
    case 'q': //move down
        yoom++;
        break;
    case 'w': //move up
        yoom--;
        break;
    }
}
//Print Text on Screen
void distring(const GLfloat sx, const GLfloat sy, const GLfloat sz, const char *s)
{
    int l = 0, i;
    l = strlen(s);
    glLoadIdentity();
    glRasterPos3f(sx, sy, sz);
    glColor3f(1, 1, 1);
    for (i = 0; i < l; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
} // Function END
void initRendering()
{
    glClearColor(0.0393, 0.5, 0.486, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
//Handles Screen Resize
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(58.0, (float)w / (float)h, 1.0, 150.0);
}
//Display function
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(xoom, yoom, zoom);
    glRotatef(20, 1, 0, 0);
    GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    GLfloat lightColor[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat lightPos[] = {-2 * BOX_POS, BOX_POS, 4 * BOX_POS, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glPushMatrix();
    glTranslatef(0, BOX_POS, 0);
    drawCube(_angle);
    draw_mini_Cube(_angle1);
    distring(-7, 10, -20, " ");
    distring(7.5, 8.7, -20, "- Rahul Jain");
    distring(-3, 10, -20, "-Disco Cubes-");
    glPopMatrix();
    glEnable(GL_STENCIL_TEST);      //Enable using the stencil buffer
    glColorMask(0, 0, 0, 0);        //Disable drawing colors to the screen
    glDisable(GL_DEPTH_TEST);       //Disable depth testing
    glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
    //Make pixels in the stencil buffer be set to 1 when the stencil test passes
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //Set all of the pixels covered by the floor to be 1 in the stencil buffer
    drawFloor();
    glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
    glEnable(GL_DEPTH_TEST); //Enable depth testing
    //Make the stencil test pass only when the pixel is 1 in the stencil buffer
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
    //Draw the cube, reflected vertically, at all pixels where the stencil
    //buffer is 1
    glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(0, BOX_POS, 0);
    drawCube(_angle);
    draw_mini_Cube(_angle1);
    glPopMatrix();
    glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
    //Blend the floor onto the screen
    glEnable(GL_BLEND);
    glColor4f(0.0, 0.0, 0.0, 0.85f);
    drawFloor();
    glDisable(GL_BLEND);
    glutSwapBuffers();
}
//Mouse Function
void mouse(int btn, int state, int x, int y)
{

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        slack = 6.0;
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        slack = 0.0;
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        slack = -6.0;
}
//Redraw Screen with rotated cube
void update(int value)
{
    _angle += slack;
    if (_angle > 360)
    {
        _angle -= 360;
    }
    else if (_angle < -360)
        _angle += 360;
    glutPostRedisplay();
    glutTimerFunc(1, update, 0);
}
//Rotate mini cubes
void update_mini(int value)
{
    _angle1 += 10.0;
    if (_angle1 > 360)
    {
        _angle1 -= 360;
    }
    else if (_angle1 < -360)
        _angle1 += 360;
    glutPostRedisplay();
    glutTimerFunc(5, update_mini, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(1080, 920);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CG");
    initRendering();
    glutMouseFunc(mouse);
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(1, update, 0);
    glutTimerFunc(5, update_mini, 0);
    glutMainLoop();
    return 0;
}
