#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>
#include "textureio.h"



TextureRGBImage::TextureRGBImage(void){
  this->width = 0;
  this->height = 0;
  this->imageData = NULL;
}



TextureRGBImage::~TextureRGBImage(void){
  if(this->imageData != NULL) free(this->imageData);
}

void TextureRGBImage::ReadImagefromFile(char * filename){

  IplImage * cvImage = cvLoadImage(filename,1);
  if(cvImage == NULL){
    printf("cannot read %s\n", filename);
  }
  cvCvtColor(cvImage, cvImage, CV_BGR2RGB);

  this->width = cvImage->width;
  this->height =cvImage->height;
  int memory_size = this->width* this->height * 3;
  this->imageData = (unsigned char *) malloc (memory_size);
  memcpy(this->imageData,cvImage->imageData, memory_size);

  cvReleaseImage(&cvImage);
}

