CC=g++
CFLAGS=`pkg-config opencv --cflags` 
LIBS=-lglut -lGL -lGLU -lm `pkg-config opencv --libs`
main: main.o draw.o filer.o moji.o calculate.o etc.o textureio.o uglyfont.o
	$(CC) main.o draw.o filer.o moji.o calculate.o etc.o textureio.o uglyfont.o -o main $(LIBS)


moji: moji.o
	$(CC) moji.o -o moji $(LIBS)

moji2: moji2.o
	$(CC) moji2.o -o moji2 $(LIBS)


draw: draw.o
	$(CC) draw.o -o draw $(LIBS)

filer: filer.o
	$(CC) filer.o -o  filer $(LIBS)


sphere: sphere.o
	$(CC) sphere.o -o sphere $(LIBS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)
