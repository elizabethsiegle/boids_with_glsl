ifeq ($(shell uname -s), Darwin)
LDFLAGS=-L/opt/ports/lib -framework OpenGL -lX11 -lglfw -lGL -lGLU -lglut -lGLEW -lm -lXcursor -lXxf86vm -lXrandr -lXinerama -lstdc++
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lGLEW -lglfw -lXcursor -lXxf86vm -lXrandr -lXinerama -lm
endif

CC = g++
CPLUS = -x c++ -std=c++11
CFLAGS=-g -I/opt/ports/include
CXXFLAGS =-g -I/opt/ports/include
INIT_SHADER = initshader.o
SOURCES= mats.cpp vecs.cpp hw4.c initshader.c boid.h
#SOURCES= hw4.c
OBJECTS=$(SOURCES:.c=.o)
# OBJECTS+=$(SOURCES:.cpp=.o) //???
#DEPS=common.hpp mats.hpp vecs.hpp boid.h hw4.h
DEPS=hw4.h
#EXECUTABLE= hw4 boids mats vecs
EXECUTABLE=hw4

%.o: %.c $(DEPS)
	$(CC) $(CPLUS) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

clean:
	rm *.o $(EXECUTABLE) core. dSYM
