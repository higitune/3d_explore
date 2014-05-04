#include <cstring>
#include <cstdio>
#include "filer.h"
#include "draw.h"

bool CheckExtention( char* filename, const char* ext )
{
  if (strrchr(filename,'.') ==NULL) return false;
  else if ( filename && ext )
    {
      return  0 == std::strcmp(std::strrchr(filename, '.'), ext);
    }
  else return false;
}


char *getFileName(char *lpszPath)
{
    char    *lpszPtr=lpszPath;

    while(*lpszPtr != '\0')
    {
      //[\],[/],[:]を見つけたら現在地+1のポインタを保存
      if((*lpszPtr == '\\') || (*lpszPtr == '/') || (*lpszPtr == ':'))
	{
	  lpszPath=lpszPtr+1;
	}
      //        }
      //次の文字へ
      lpszPtr++;
    }
    return lpszPath;
}
