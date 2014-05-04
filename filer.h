/* ヘッダファイル filer.h */

#ifndef _filer_h
#define _filer_h

struct node {
  char name[255];
  /* 座標 */
  float x;
  float y;
  float z;
  struct node *parent;
  struct node * child;
  struct node * before;
  struct node * next;
  struct f_node * file;
};

typedef struct node node_t;

struct f_node{
  char name[255];
  float x;
  float y;
  float z;
  struct node *parent;
  struct f_node *before;
  struct f_node *next;
  
};
typedef struct f_node node_f;

extern node_t* root, *cd;
extern node_f* Current;

/* 二分木のノードを作成する */
extern node_t* create(char* name);
/* ファイルのノードを作成する */
extern node_f* createf(char* name);
/* 二分木のノードを削除する */
void destroy(node_t* node);
/* 二分木そのものを削除する */
void destroy_tree(node_t* node);
/* 二分木のノードを連結する */
void append(node_t* parent, node_t* node);
/* ファイルノードを連結する */
void append_f( node_t* parent, node_f* node);
/* rootディレクトリを指定して二分木を作成する */
void printdir(char *dir, int depth);
/* ノード下の子ディレクトリの数を取得する */
int count_dir( node_t *dir );
/* ノード下の子ファイルの数を取得する */
int count_file( node_t *dir );

void display(node_t* node, int depth);
/* 木構造を表示する */
void show_tree_dfs(node_t* node, int depth);

#endif

