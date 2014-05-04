#include <GL/glut.h>
/* ヘッダファイル draw.h */

#ifndef _draw_h
#define _draw_h

#define TEXHEIGHT 1024
#define TEXWIDTH 1024
/*半径*/
#define R 50
/*ファイル配置の半径*/
#define R_f 9.7
/* 球の半径 */
#define R_s 10
/* 高さ */
#define H 200
/* 視点の遠さ */
#define D 800.0
/* 読み込む画像の最大数 */
#define MAX_ 15
extern float x_0;
extern float y_0;
extern float z_0;

extern GLuint TextureHandle[MAX_];

void calculate( node_t* node);
void calculate_f( node_t* node);
void draw_tree( node_t* node, bool Key);
void draw(bool Key);
char *getFileName(char *lpszPath);
bool CheckExtention( char* filename, const char* ext );




#endif
