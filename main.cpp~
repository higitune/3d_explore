#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <unistd.h>
#include "textureio.h"
#include "filer.h"
#include "draw.h"
#include "moji.h"

#define WINDOW_NAME "3D Explorer"

void init(void);
void glut_display(void);
void glut_keyboard(unsigned char key, int x, int y);
void glut_mouse(int button, int state, int x, int y);
void glut_motion( int x, int y);
void glut_idle( void );


double Angle1 = 0.0;
double Angle2 = 0.0;
double Distance = D, Distance_temp = D;
bool LeftButtonOn = false;
bool RightButtonOn = false;
bool OpenKey = false;
bool flag_dist = false;
bool ForwardKey = false;
bool BackKey = false;
bool UpKey = false;
bool DownKey = false;
int num = 0;
GLfloat light_pos[] = { 0.0, 3.0, 5.0, 1.0 };
GLuint TextureHandle[MAX_];

/* currentdirectory */
node_t* cd;
node_f* Current= NULL, *Before=NULL;
void set_texture();
int main(int argc, char *argv[])
{
  /* ディレクトリ構造を取得する */
  printdir(".",0);
  cd = root;
  show_tree_dfs(root,0);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(500,500);
  glutCreateWindow(WINDOW_NAME);
  init();
  glutDisplayFunc(glut_display);
  glutKeyboardFunc(glut_keyboard);
  glutMouseFunc(glut_mouse);
  glutMotionFunc(glut_motion);
  glutPassiveMotionFunc(glut_motion);
  glutIdleFunc(glut_idle);
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(1.0,1.0,1.0,1.0);
  glColor3d(1.0,0.8 ,0.8 );

  GLubyte texture[TEXHEIGHT][TEXWIDTH][3];

  glGenTextures(MAX_, TextureHandle);
  int i;
  for(int i = 0; i < MAX_ ; i++ ){

    glBindTexture(GL_TEXTURE_2D, TextureHandle[i]);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1 );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXWIDTH,TEXHEIGHT,0 ,GL_RGB, GL_UNSIGNED_BYTE,NULL);
    glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXWIDTH,TEXHEIGHT,0 ,GL_RGB, GL_UNSIGNED_BYTE,NULL);
    //    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEXWIDTH, TEXHEIGHT,GL_RGB, GL_UNSIGNED_BYTE, texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

  }
}


void glut_keyboard(unsigned char key, int x, int y){

  switch(key){

  case 'q':
  case 'Q':
  case '\033':
    exit(0);
  case 'o':
    flag_dist = true;
    if ( OpenKey == false ){
      Distance_temp = Distance;
      OpenKey = true;
    }
   else
     OpenKey = false;
   break;
  case 'f':
    if (cd != root){
      ForwardKey = true;
    }
    break;
  case 'b':
    if (cd != root){
      BackKey = true;
    }
    break;
  case 'u':
    if (cd != root){
      UpKey = true;
    }
    break;
  case 'd':
    if ( cd->child != NULL ){
      DownKey = true;
    }
    break;
  }
  glutPostRedisplay();
}

void glut_mouse( int button , int state, int x, int y ){

  if (button == GLUT_LEFT_BUTTON){
    if(state == GLUT_UP ){
      LeftButtonOn = false;
    }else if (state == GLUT_DOWN ){
      LeftButtonOn = true;
    }
  }
  if (button == GLUT_RIGHT_BUTTON){
    if(state == GLUT_UP){
      RightButtonOn = false;
    }
    else if (state == GLUT_DOWN){
      RightButtonOn = true;
    }
  }

}

void glut_motion( int x, int y){

  static int px = -1, py = -1;

  if(LeftButtonOn == true){

    if(px >= 0 && py >= 0 ){
      Angle1 += (double)-(x - px )/ 20;
      Angle2 += (double)-(y - py )/ 20;
    }

    px = x;
    py = y;
  }
  else if ( RightButtonOn == true ){
    if ( px >= 0&& py >= 0){
      Distance += (double)(y - py )/20 ;
    }
    px = x;
    py = y;

  }
  else{
    px = -1;
    py = -1;
  }

  glutPostRedisplay();

}
float x, y, z,x00,y00,z00;
void glut_idle(void)
{
  static int counter1 = 0, counter2 = 0,counter3 = 0, counter4 = 0;
  node_t* tempo;
  if (OpenKey == true && flag_dist == true){
    if ( Distance >= R_s * 5 ){
      Distance = Distance/1.1;
    }
    else if (Distance > R_s)
       Distance -= 1;
    else{
      Distance = R_s;
      flag_dist = false;
    }
  }
  if (OpenKey == false && flag_dist == true){
    if ( Distance_temp > Distance * 2 )
      Distance *= 1.1;
    else if ( Distance_temp > Distance )
      Distance *= 1.01;
    else{
      Distance = Distance_temp;
      flag_dist = false;
    }
  }
  if (UpKey == true){
    if ( counter1 == 0 ){
      x00 = x_0;
      y00 = y_0;
      z00 = z_0;
      x= (cd->x -cd->parent->x);
      y= (cd->y -cd->parent->y);
      z= (cd->z -cd->parent->z);
    }
    x_0 += x/50;
    y_0 += y/50;
    z_0 += z/50;
    counter1++;

    if ( counter1 == 50 ){
      counter1 = 0;
      x_0 = x00 + x;
      y_0 = y00 + y;
      z_0 = z00 + z;
      cd = cd->parent;
      UpKey = false;
    }
  }
  if (DownKey == true){
    if ( counter2 == 0 ){
      x00 = x_0;
      y00 = y_0;
      z00 = z_0;
      x= (cd->x -cd->child->x);
      y= (cd->y -cd->child->y);
      z= (cd->z -cd->child->z);
    }
    x_0 += x/50;
    y_0 += y/50;
    z_0 += z/50;
    counter2++;

    if ( counter2 == 50 ){
      counter2 = 0;
      x_0 = x00 + x;
      y_0 = y00 + y;
      z_0 = z00 + z;
      cd = cd->child;
      DownKey = false;
    }
  }
  else if (ForwardKey == true){
    if ( counter3 == 0 ){
      x00 = x_0;
      y00 = y_0;
      z00 = z_0;
      if ( cd-> next != NULL ){
	x= (cd->x -cd->next->x);
	y= (cd->y -cd->next->y);
	z= (cd->z -cd->next->z);
      }
      else{
	x= (cd->x -cd->parent->child->x);
	y= (cd->y -cd->parent->child->y);
	z= (cd->z -cd->parent->child->z);
      }
    }
    x_0 += x/50;
    y_0 += y/50;
    z_0 += z/50;
    counter3++;

    if ( counter3 == 50 ){
      counter3 = 0;
      x_0 = x00 + x;
      y_0 = y00 + y;
      z_0 = z00 + z;
      if (cd->next !=NULL) cd = cd->next;
      else cd = cd->parent->child;
      ForwardKey = false;
    }
  }
  else if (BackKey == true){
    tempo = cd;
    while ( tempo->next != NULL )
      tempo = tempo->next;
    if ( counter4 == 0 ){
      x00 = x_0;
      y00 = y_0;
      z00 = z_0;
      if ( cd-> before != NULL ){
	x= (cd->x -cd->before->x);
	y= (cd->y -cd->before->y);
	z= (cd->z -cd->before->z);
      }
      else{
	x= (cd->x -tempo->x);
	y= (cd->y -tempo->y);
	z= (cd->z -tempo->z);
      }
    }
    x_0 += x/50;
    y_0 += y/50;
    z_0 += z/50;
    counter4++;

    if ( counter4 == 50 ){
      counter4 = 0;
      x_0 = x00 + x;
      y_0 = y00 + y;
      z_0 = z00 + z;
      if (cd->before !=NULL) cd = cd->before;
      else cd = tempo;
      BackKey = false;
    }
  }
  glutPostRedisplay();

}


void glut_display(void)
{
  set_texture();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(300.0,1.0,0.1,10000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(Distance * cos(Angle2) * sin(Angle1),
	    Distance * sin(Angle2),
	    Distance * cos(Angle2)* cos(Angle1),
	    0.0,0.0,0.0,0.0,-1.0,0.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  draw_tree(root,OpenKey);
  glFlush();
  glDisable(GL_DEPTH_TEST);
  BuildList( cd->name );
  DISPLAY_TEXT();

  glutSwapBuffers();
}

void set_texture(void){
  node_f* temp = Current;
  int i = 0,j;
  if ( Current != Before ){
    char inputfile[256];
    chdir(cd->name);
    for ( temp = Current; ;temp = temp->next ){
      for ( j = 0; temp->name[j] != '\0'; j++ )
	inputfile[j] = temp->name[j];
      inputfile[j] = '\0';
      printf("%s\n",inputfile);
      printf("%d\n",CheckExtention(inputfile,".jpg"));
      if( true == CheckExtention(inputfile,".jpg")){
	TextureRGBImage Input;
	Input.ReadImagefromFile(inputfile);
	glBindTexture(GL_TEXTURE_2D,TextureHandle[i]);
	glTexSubImage2D(GL_TEXTURE_2D,0,
			(TEXWIDTH - Input.width)/2,
			(TEXHEIGHT - Input.height)/2,
			Input.width, Input.height,
			GL_RGB, GL_UNSIGNED_BYTE, Input.imageData);
	i++;
      }
      if ( temp->next == NULL )break;
    }
    Before = Current;
  }
}
