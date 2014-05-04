#include <stdio.h>

class TextureRGBImage{

 public:
  int width;
  int height;
  unsigned char *imageData;

  TextureRGBImage(void);
  ~TextureRGBImage();
  void ReadImagefromFile(char *filename);

};
