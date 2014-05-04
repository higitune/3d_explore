/* ヘッダファイル moji.h*/
/* quoted from OpenGL de プログラミング */

#ifndef _moji_h
#define _moji_h

void BuildList( char* name);
void DISPLAY_TEXT();
void DRAW_STRING(int x, int y, char *string, void *font);
void DrawString3(const char *str,void *font,float x,float y,float z);


void reshape(int w, int h);
void timer(int value);
void DRAW_XYZ();
void DRAW_TRI();
void DrawString3D(const char *str,void *font,float Width);

#endif
