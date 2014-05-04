#include <cstring>
#include <cstdio>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "moji.h"
#include <iostream>


void display();
void reshape(int w, int h);
void timer(int value);


using namespace std;


// inline void GLUT_INIT()
// {
// glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
// }

// inline void GLUT_CALL_FUNC()
// {
// glutDisplayFunc(display);
// glutReshapeFunc(reshape);
// glutTimerFunc(1,timer,0);
// }

// inline void MY_INIT()
// {
// glClearColor(1.0, 1.0, 1.0, 1.0);
// glEnable(GL_LIGHTING);
// glEnable(GL_LIGHT0);
// BuildList(); 
// }


// int main(int argc, char **argv)
// {
// glutInit(&argc,argv);
// GLUT_INIT();
// glutCreateWindow("window name");
// GLUT_CALL_FUNC();
// MY_INIT();
// glutMainLoop();

// return 0;
// }



/********[ここから各種コールバック]***********************************/
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
int list;

void display()
{
static int r = 0;
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();
gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);


glEnable(GL_DEPTH_TEST);

glPushMatrix();
glRotated((double)r, 0.0, 1.0, 0.0);
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
glutSolidCube(1);
glPopMatrix();


glDisable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
glDisable(GL_LIGHT0);

DISPLAY_TEXT(); 

glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);

glutSwapBuffers();

r = r + 1;
if(r > 360)
{
r= 0;
}
}


void reshape(int w, int h)
{
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
glMatrixMode(GL_MODELVIEW);

}

void timer(int value)
{
glutPostRedisplay();
glutTimerFunc(1,timer,0); 
}



void BuildList(char* name)
{

list=glGenLists(1);
glNewList(list,GL_COMPILE);
DRAW_STRING(0, 0, name ,GLUT_BITMAP_TIMES_ROMAN_24);
glEndList();

}


inline void DISPLAY_TEXT()
{
glPushAttrib(GL_ENABLE_BIT);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity(); 
gluOrtho2D(0, 200, 0, 200); 
glMatrixMode(GL_MODELVIEW); 
glPushMatrix(); 
glLoadIdentity(); 
glColor3f(1,0,1);
glCallList(list);
glPopMatrix(); 
glMatrixMode(GL_PROJECTION); 
glPopMatrix(); 
glPopAttrib(); 
glMatrixMode(GL_MODELVIEW); 
}


void DRAW_STRING(int x, int y, char *string, void *font)
{

int len, i;
y += 5; //位置補正
glRasterPos2f(x, y);
len = (int) strlen(string);
for (i = 0; i < len; i++)
{
glutBitmapCharacter(font, string[i]);
}

}
void DrawString3(const char *str,void *font,float x,float y,float z)
{
	glRasterPos3f(x,y,z);
	while(*str){
		glutBitmapCharacter(font, *str);
		++str;
	}
}







// //------------- OpenGLの初期設定 ----------------//
// void GLUT_INIT()
// {
// 	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
// 	glutInitWindowSize(300,300);
// 	glutCreateWindow("Stroke Font");
// }

// void GLUT_CALL_FUNC()
// {
// 	glutDisplayFunc(display);
// 	glutReshapeFunc(reshape);
// 	glutTimerFunc(0,timer,17);
// }

// void MY_INIT()
// {
// 	glClearColor(1.0, 1.0, 1.0, 1.0);
// 	glEnable(GL_DEPTH_TEST);  //Zバッファ有効化
// }


// //------------ メイン関数 ---------------//
// int main(int argc, char **argv)
// {
// 	glutInit(&argc,argv);
	
// 	GLUT_INIT();
// 	GLUT_CALL_FUNC();
// 	MY_INIT();

// 	glutMainLoop();

// 	return 0;
// }

//------------ ここからコールバック ---------------//
// void display()
// {
// 	static int r = 0;
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
// 	DRAW_XYZ();  //XYZ軸の描画

// 	//ポリゴンの描画
// 	glPushMatrix();   
// 	glRotated(double(r), 0.0, 1.0, 0.0);
// 	glTranslated(1,0,0);
// 	glColor3d(0,1,0);
// 	DRAW_TRI();
// 	glPopMatrix();


// 	glPushMatrix();
// 	glScalef(0.005,0.005,0.005);
// 	glColor3d(1,0,1);
// 	DrawString3D("Hello",font,3); //フォントの描画
// 	glPopMatrix();


// 	glutSwapBuffers();

// 	if(++r > 360){
// 		r= 0;
// 	}
// }

// void reshape(int w, int h)
// {
// 	glViewport(0, 0, w, h);

// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// 	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

// }

// void timer(int t)
// {
// 	glutPostRedisplay();
// 	glutTimerFunc(t,timer,17); //タイマー関数
// }

//------------- ここから各種関数 ------------------//
void DRAW_XYZ()
{
	glBegin(GL_LINES);

	glColor3d(0,1,0);//x
	glVertex2d(-100,0);
	glVertex2d(100, 0);

	glColor3d(1,0,0);//y
	glVertex2d(0,0);
	glVertex2d(0,100);

	glColor3d(0,0,1);//z
	glVertex3d(0,0,-100);
	glVertex3d(0,0, 100);
	glEnd();

}

void DRAW_TRI()
{
	glBegin(GL_TRIANGLES);
	glVertex2d(0,1);
	glVertex2d(-0.5, 0);
	glVertex2d(0.5, 0);
	glEnd();
}

//---------- フォントの描画 ------------//
void DrawString3D(const char *str,void *font,float Width)
{
	glPushAttrib(GL_LINE_BIT);
	glLineWidth(Width);
	while(*str){
		glutStrokeCharacter(font, *str);
		++str;
	}
	glPopAttrib();
}
