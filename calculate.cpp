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


/* 子階層の座標を求め、格納する関数 */
void calculate(node_t* node)
{
  int n = count_dir( node );
  int i = 0;
  node_t* tmp = node->child;
  node_t* tmp1 = tmp;
  if (n == 1){
    tmp1->x = node->x;
    tmp1->y = node->y - H;
    tmp1->z = node->z;
  }
  else{
    for ( i = 0;i < n ;i++ ){
      tmp1->x = n * R * cos( 2 * i * M_PI / n ) + node->x;
      tmp1->y = node->y - H;
      tmp1->z = n * R * sin( 2 * i * M_PI / n ) + node->z;
      if ( tmp1-> next == NULL )
	break;
      tmp1 = tmp1->next;
    }
  }
  if ( node->next != NULL ){
    calculate ( node->next );
  }
  if ( node->child != NULL ){
    calculate ( node-> child );
  }
}

/* 子ファイルの座標を求め、格納する関数 */
void calculate_f(node_t* node)
{
  int n = count_file( node );
  int i = 0;
  node_f* tmp = node->file;
  node_f* tmp1 = tmp;
  for ( i = 0;i < n ;i++ ){
    tmp1->x = R_f * cos(M_PI/n) * cos( 2 * i * M_PI / n ) + node->x;
    tmp1->y = node->y;
    tmp1->z = R_f * cos(M_PI/n) * sin( 2 * i * M_PI / n ) + node->z;
    if ( tmp1-> next == NULL )
      break;
    tmp1 = tmp1->next;
  }
}
