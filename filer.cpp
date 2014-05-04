#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/param.h>
#include "filer.h"
#define N 10000

using namespace std;

// typedef struct node {
//   char name[255];
//   struct node * child;
//   struct node * next;
// } node_t;
node_t* node0[N];

node_t*  search ( node_t* node );

int n = 0, i, flag = 0;
node_t* tmp1,*tmp2,*tmp3, *root;
node_t* tmp,*temp;
char buf[255];
char*
Getcwd(char *buf, size_t size){
  char* p = getcwd(buf, size);
  if(!p){
    perror("getcwd");
  }
  return(p);
}
void printdir(char *dir, int depth)
{
  DIR *dp;
  struct dirent *entry;
  struct stat statbuf;
  if ((dp = opendir(dir)) == NULL) {
    fprintf(stderr,"cannot open directory: %s\n", dir);
    return;
  }
  chdir(dir);
  if ( n == 0 ){
    root = create(Getcwd(buf, sizeof(buf)));
    tmp1 = root;
    tmp2 = root;
  }
  else{
    append ( tmp1 , tmp2 = create ( Getcwd(buf, sizeof(buf) )));
    tmp1 = tmp2;
  }
  n++;
  while((entry = readdir(dp)) != NULL) {
    lstat(entry->d_name, &statbuf);
    if(S_ISDIR(statbuf.st_mode)) {
      if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0) {
        continue;
      }
      printf("%*s%s/\n",depth,"",entry->d_name);
      printdir(entry->d_name,depth+4);
    } else {
      append_f ( tmp1 ,createf( entry->d_name ));
      printf("%*s%s\n",depth,"",entry->d_name);
    }

  }
  flag = 0;
  chdir("..");
  /* 親ディレクトリを確定する */
  tmp1 = search(root);
  /* ディレクトリの個数を確定する */
  
  closedir(dp);
}
node_t*  search ( node_t* node )
{
  if ( strcmp ( Getcwd( buf, sizeof(buf)), node->name ) == 0 ){
    return node;
  }
  if ( node->next != NULL ){
    return search( node->next );
  }
  if ( node->child != NULL ){
    return search( node->child);
  }

}

int count_dir( node_t *dir )
{
  node_t* tmp;
  int num = 0;
  if( dir->child != NULL ){
    for ( tmp = dir->child; ; tmp = tmp->next ){
      num++;
      if ( tmp->next == NULL )
	break;
    }
  }
  return num;
}
int count_file( node_t *dir )
{
  node_f* tmp;
  int num = 0;
  if( dir->file != NULL ){
    for ( tmp = dir->file; ; tmp = tmp->next ){
      num++;
      if ( tmp->next == NULL )
	break;
    }
  }
  return num;
}




// int main(int argc, char* argv[])
// {
//   if (argc == 2) {
//     //    printf("directory scan of %s\n", argv[1]);
//     printdir(argv[1],0);
//     //    printf("done.\n");
//   }
// }

node_t* create(char* name)
{
  node_t* node = (node_t*)malloc( sizeof(node_t) );
  if ( node == NULL ) exit( EXIT_FAILURE );
  int i;
  for ( i = 0; name[i] != '\0' ; i++)
    node->name[i] = name[i];
  node->x = node->y = node->z = 0;
  node->parent = NULL;
  node->child = NULL;
  node->next = NULL;
  node->before = NULL;
}

node_f* createf(char* name)
{
  node_f* node = (node_f*)malloc(sizeof(node_f));
  if ( node == NULL )exit(EXIT_FAILURE);
  int i;
  for ( i = 0; name[i] != '\0'; i++ )
    node->name[i] = name[i];
  node->parent = NULL;
  node->before = NULL;
  node->next = NULL;
}

void destroy(node_t* node)
{
  free(node);
  node = NULL;
}

void destroy_tree(node_t* node)
{
  if (node == NULL) return;
  destroy_tree(node->child);
  destroy_tree(node->next);
  destroy(node);
}
void append(node_t* parent, node_t* node)
{
  node->parent = parent;
  if (parent->child == NULL)
  {
    parent->child = node;
  }
  else
  {
    node_t* last = parent->child;
    while (last->next != NULL) last = last->next;
    last->next = node;
    node->before = last;
  }
}

void append_f( node_t* parent, node_f* node)
{
  node->parent = parent;
  if ( parent->file == NULL )
    parent->file = node;
  else{
      node_f* last = parent->file;
      while ( last->next != NULL) last = last->next;
      last->next = node;
      node->before = last;
  }
}

void display(node_t* node, int depth)
{
  int i;
  for (i=0;i<depth;i++)
  {
    printf(" ");
  }
  printf("+ %s\t%d\n",node->name,count_dir(node));
}
void display_f( node_f* node, int depth)
{
  int i;
  for ( i = 0; i < depth; i++) printf(" ");
  printf("- %s\n", node->name);
}
void show_file( node_f* node , int depth)
{
  if( node != NULL ){
    display_f( node ,depth);
    show_file( node->next, depth );
  }
}

void show_tree_dfs(node_t* node, int depth)
{
  if (node != NULL){
    display(node, depth);
    if (node->file != NULL )
      show_file ( node->file, depth );
    show_tree_dfs(node->child, depth + 1);
    show_tree_dfs(node->next, depth);
  }
}
