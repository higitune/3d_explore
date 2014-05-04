#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <unistd.h>
#include <math.h>
#include <GL/glut.h>
#include "global.h"
#include "filer.h"
#include "draw.h"
#include "moji.h"
#include <string.h>
#include "uglyfont.h"
#include <GL/gl.h>
#include <GL/glu.h>


GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
node_t* aaa;
float x_0 = 0.0;
float y_0 = 0.0;
float z_0 = 0.0;
/* 階層が変わったことを表す変数 */
int flag0 = 1;

double color[7][3] = {{0,0,1},{0,1,0},{0,1,1},{0,0.5,0.5},{0.1,0.8,0.2},{0.2,0.7,0.9},{0.3,0.5,0.5}};

void draw_floor( node_t* node );
void draw_plain();
void draw_circle(node_t* node);

void draw_tree( node_t* node , bool Key){
  root->x = x_0;
  root->y = y_0;
  root->z = z_0;
  calculate(root);
  glPushMatrix();
  /* 階層ごとに色を変化させる */
  if ( flag0 == 1 ){
    glColor3d(color[strlen(node->name)%7][0],color[strlen(node->name)%7][1],color[strlen(node->name)%7][2]);
  }
  /* 普通のノードを描画する。 */
  if ( cd != node ){
    glTranslatef( node->x,node->y ,node->z );
    glutSolidSphere(R_s,16,16);
    glPopMatrix();

    /* ディレクトリ名を表示する */
    glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);  //色、Zバッファの退避
    glDisable(GL_DEPTH_TEST);
    glColor3d(0.5,0.5,0.5);
    DrawString3( getFileName(node->name),GLUT_BITMAP_HELVETICA_18,node->x,node->y,node->z);
    glPopAttrib();//色、Zバッファを戻す

  }

  /* OpenKeyが押されている時の描画 */
  else if ( Key == true )
    {
      if ( node-> file  != NULL){
	//ファイルの座標を計算
	Current = cd->file;
	calculate_f( node );
	draw_floor( node );
      }
    }
  /* CurrentDirectory の描画 */
  else
    {
      /* 平面を描画する */
      glPushMatrix();
      glTranslatef( root->x,node->y ,root->z );
      draw_plain();
      glPopMatrix();
      glPushMatrix();
      /* 円を描画する。 */
      draw_circle(node);
      glPopMatrix();
      glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);
      glColor3d(1.0,0.0,0.0);
      glTranslatef( node->x,node->y ,node->z );
      glutSolidSphere(R_s,16,16);
      glPopAttrib();
      glPopMatrix();
    }
  /* そのフロアの描画 */
  if ( node->next != NULL ){
    flag0 = 0; /* 同じ階層を描画するのでflagを倒す */
    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3d(1.0,0.8 ,0.8 );
    glBegin(GL_LINES);
    glVertex3f(aaa->x,aaa->y,aaa->z );
    glVertex3f(node->next->x,node->next->y,node->next->z);
    glEnd();
    glPopAttrib();
    glPopMatrix();
    draw_tree ( node->next, Key );
  }
  /* 子階層の描画 */
  if ( node->child != NULL ){
    flag0 = 1; /* 階層が変更されたのでflagを立てる */
    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3d(1.0,0.8 ,0.8 );
    glBegin(GL_LINES);
    glVertex3f(node->x,node->y,node->z );
    glVertex3f(node->child->x,node->child->y,node->child->z);
    glEnd();
    glPopAttrib();
    glPopMatrix();
    aaa = node;
    draw_tree ( node-> child,Key );
  }
}

void draw(bool Key){

  int i;
  if ( Key == true ){
    for ( i = 0; i < 10; i ++ ) {
      glPushMatrix();
      glTranslatef( 10 * cos(2* i *  3.141592/10), 0.0, 10 *  sin(2* i *  3.141592/10) );
      glutSolidSphere(R_s,16,16);
      glPopMatrix();
    }
  }
  else{
    glPushMatrix();
    glTranslatef (0,0.0,0);
    glutSolidSphere(2.0,16,16);
    glPopMatrix();
  }
}


/* nodeのベクトルを法線ベクトルとしてそれを中心とした3*4長方形に、JPGファイルをマッピングして描画する。 */
void draw_rect_img(node_f* node){
  float a;
  /* 画像の横の長さ */
  float l;
  l = R_f * sin( M_PI /count_file(cd) );
  a = sqrt(l*l/((node->x)*(node->x)+(node->z)*(node->z)));
  GLfloat pointA[] = {node->x + a * node->z, l*27/64, node->z - a * node->x };
  GLfloat pointB[] = {node->x - a * node->z, l*27/64, node->z + a * node->x };
  GLfloat pointC[] = {node->x + a * node->z, -l*27/64, node->z - a * node->x };
  GLfloat pointD[] = {node->x - a * node->z, -l*27/64, node->z + a * node->x };
  glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  glColor3f( 1.0,1.0,1.0 );
  /* テクスチャマッピング */
  glEnable(GL_TEXTURE_2D);

  glBegin( GL_POLYGON );
  glTexCoord2f(1.0,0.0);
  glVertex3fv(pointA);
  glTexCoord2f(0.0,0.0);
  glVertex3fv(pointB);
  glTexCoord2f(0.0,1.0);
  glVertex3fv(pointD);
  glTexCoord2f(1.0,1.0);
  glVertex3fv(pointC);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
  glPopAttrib();
}
void draw_rect_name(node_f* node, int i){
  float a;
  /* 画像の横の長さ */
  float l;
  l = R_f * sin( M_PI /count_file(cd) );
  a = sqrt(l*l/4/((node->x)*(node->x)+(node->z)*(node->z)));
  GLdouble pointA[] = {node->x + a * node->z, l*27/64, node->z - a * node->x };
  GLdouble pointB[] = {node->x - a * node->z, l*27/64, node->z + a * node->x };
  GLdouble pointC[] = {node->x + a * node->z, -l*27/64, node->z - a * node->x };
  GLdouble pointD[] = {node->x - a * node->z, -l*27/64, node->z + a * node->x };
  glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  glColor3f( 0.8,0.8,0.8 );
  glBegin( GL_POLYGON );
  glVertex3dv(pointA);
  glVertex3dv(pointB);
  glVertex3dv(pointD);
  glVertex3dv(pointC);
  glEnd();

  glPopMatrix();
  glPushMatrix();
  glColor3f( 0.0,0.0,0.0);
  glBegin(GL_LINES);
  glVertex3dv(pointA);
  glVertex3dv(pointB);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor3f( 0.0,0.0,0.0);
  glBegin(GL_LINES);
  glVertex3dv(pointD);
  glVertex3dv(pointB);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor3f( 0.0,0.0,0.0);
  glBegin(GL_LINES);
  glVertex3dv(pointA);
  glVertex3dv(pointC);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor3f( 0.0,0.0,0.0);
  glBegin(GL_LINES);
  glVertex3dv(pointD);
  glVertex3dv(pointC);
  glEnd();
  glPopMatrix();

  glPopAttrib();
  /* ディレクトリ名を表示する */
  float ratio;
  ratio = l / strlen(node->name) /2;
  glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);  //色、Zバッファの退避
  glPushMatrix();
  glColor3d(0.0,0.0,0.0);
  glTranslated(1.005*node->x,node->y,1.005*node->z);
  //  glRotated(90-360.0 * i/ count_file(node->parent) , 0, 1, 0);
  glRotated ( atan2 ( node->x , node->z ) * 180/M_PI, 0, 1, 0);
  glScaled(ratio,ratio,ratio);
  YsDrawUglyFont(node->name,1,1);
  glPopMatrix();
  glPopAttrib();//色、Zバッファを戻す
}


/* nodeのディレクトリの内部を描画する */
void draw_floor( node_t *node ){
    int i = 0,j = 0;
    node_f* temp;
    if (node->file != NULL ){
      for ( temp = node->file; ; temp = temp->next){
	if (CheckExtention(temp->name,".jpg")){
	  glBindTexture(GL_TEXTURE_2D,TextureHandle[i]);
	  i++;
	  draw_rect_img( temp );
	}
	else draw_rect_name( temp,j++ );
	if (temp->next == NULL ) break;
      }
    }
}
/* xz平面を描画する関数 */
void draw_plain(){
  int i;
  for (i = -10000; i < 10000; i=i+200){
    //    glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);
    //    glColor3f( 0.88,0.88 ,0.88 );
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3f(i,0,-10000);
    glVertex3f(i,0,10000);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3f(-10000,0,i);
    glVertex3f(10000,0,i);
    glEnd();
    glPopMatrix();
    //    glPopAttrib();
  }
}

void draw_circle(node_t* node){
  if ( node != root )
    {
      int radius = count_dir(node->parent) * R;
      if (radius != R ){
	for (float th1 = 0.0;  th1 <= 360.0;  th1 = th1 + 1.0)
	  {
	    float th2 = th1 + 10.0;
	    float th1_rad = th1 / 180.0 * M_PI;
	    float th2_rad = th2 / 180.0 * M_PI;
	    float x1 = radius * cos(th1_rad);
	    float z1 = radius * sin(th1_rad);
	    float x2 = radius * cos(th2_rad);
	    float z2 = radius * sin(th2_rad);
	    glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);  //色、Zバッファの退避
	    glBegin(GL_LINES);
	    glColor3d(1.0,0.8 ,0.8 );
	    glVertex3f( x1+node->parent->x,node->y ,z1+node->parent->z );     
	    glVertex3f( x2+node->parent->x,node->y ,z2+node->parent->z );
	    glEnd();
	    glPopAttrib();}
      }
    }
}
