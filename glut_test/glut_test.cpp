// glut_test.cpp : Defines the entry point for the console application.
//

#include "simOBJ.h"
#include "glut.h"

#pragma comment(lib, "glut32.lib")

//Globals
OBJ_Model *miku, *cube, *shit;
void *font = GLUT_BITMAP_TIMES_ROMAN_24;
float rotation;
float theta = 0;
float zoom;
float trans_y;
float scale;
int width, height, ratio;
GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };
GLfloat sLightPosition[]=	{ 0.0f, 10.0f,0.0f, 1.0f };

inline void pushScreenCoordinateMatrix() {
    glPushAttrib(GL_TRANSFORM_BIT);
    GLint   viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(viewport[0],viewport[2],viewport[1],viewport[3]);
    glPopAttrib();
}
 
inline void popProjectionMatrix() {
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void renderText(float x, float y, void *font, char *string) 
{
	char *c;
	glRasterPos2f(x, y);
	
	glDisable(GL_LIGHTING);
		
	for(c=string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);

	glEnable(GL_LIGHTING);
}

void rKeyboardListener(unsigned char key, int x, int y)
{
	int mod = glutGetModifiers();

	if(key == 27)
		return;

	if(key == 'a')
	{
		if(rotation + 6 >= 360)
			rotation = (rotation + 6) - 360;
		else
			rotation += 6;
	}
	else if(key == 'd')
	{
		if(rotation-6 <= 0)
			rotation = 360 + (rotation - 6);
		else
			rotation -= 6;
	}
	else if(key == 'w')
		zoom += 5;
	else if(key == 's')
		zoom -= 5;
	else if(key == 'r')
		trans_y += 1;
	else if(key == 'f')
		trans_y -= 1;
	else if(key == '1')
		scale /= .95;
	else if(key == '2')
		scale *= .95;
}

void sKeyboardListener(int key, int x, int y)
{
	int mod = glutGetModifiers();
}

void render(void) 
{
	char buffer[1024];
	AABoundingBox* bb;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	//Reset transformations
	glLoadIdentity();

	//Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,
				0.0f, 0.0f,  0.0f,
				0.0f, 1.0f,  0.0f);

	//Enable lighting and smoothing
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_SMOOTH);

	//Draw Miku
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0.0f, -12.0f+trans_y, -100.0f+zoom);
		glRotatef(rotation, 0.0f, 1.0f, 0.0f);
		glScalef(0.025f, scale*0.025f, 0.025f);
		miku->Draw(INTERNAL_MATERIALS);
	glPopMatrix();
	//Draw shit
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(25.0f, 0.0f+trans_y, -100.0f+zoom);
		glRotatef(theta, 1, 0, 1);
		glScalef(0.25, 0.25, 0.25);
		shit->DrawGroup("Left_Arm", INTERNAL_MATERIALS);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(25.0f, 0.0f+trans_y, -100.0f+zoom);
		glRotatef(theta+180, 1, 1, 0);
		glScalef(0.25, 0.25, 0.25);
		shit->DrawGroup("Right_Arm", INTERNAL_MATERIALS);
	glPopMatrix();
	//Draw textured cube
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glTranslatef(0.0f, -12.0f+trans_y, -50.0f+zoom);
		glRotatef(theta, 0, 1, 0);
		glScalef(.25f, .25f, .25f);
		cube->Draw(INTERNAL_TEXTURES | INTERNAL_MATERIALS);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);
	sprintf(buffer, "theta: %f degrees", rotation);
	renderText(-4, 3.5, font, buffer);

	glutSwapBuffers();
}

void idle(void)
{
	theta += 1;
	render();
}

void reshape(int w, int h)
{
	width = w;
	height = h;

	if(height == 0)
		height = 1;
	ratio = 1.0* width / height;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

    // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// Set the correct perspective.
	gluPerspective(45,ratio,0.1,100000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void initialize()
{
	//Initialize glut
	glutInitWindowPosition(-1,-1);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("This Sure is a Game!");

	//Initialize OpenGL
	glShadeModel(GL_SMOOTH);                
    glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL); 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_POSITION,sLightPosition);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0f);
 
	//Initialize variables
	rotation = 0;
	zoom = 0;
	trans_y = 0;
	scale = 1;

	//Load the models
	miku = new OBJ_Model("miku.obj");
	miku->PrintDetails();
	cube = new OBJ_Model("cube.obj");
	cube->PrintDetails();
	shit = new OBJ_Model("shit.obj");
	shit->PrintDetails();

	//Callbacks
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(rKeyboardListener);
	glutSpecialFunc(sKeyboardListener);
}

int main(int argc, char* argv[])
{
	//Initialization
	glutInit(&argc, argv);
	initialize();

	glutMainLoop();

	return 0;
}

