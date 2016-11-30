ifeq ($(shell uname -s), Darwin)
LDFLAGS=-L/opt/ports/lib -framework OpenGL -lX11 -lglfw -lGL -lGLU -lglut -lGLEW -lm -lXcursor -lXxf86vm -lXrandr -lXinerama -lstdc++
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lGLEW -lglfw -lXcursor -lXxf86vm -lXrandr -lXinerama -lm
endif

CC = g++
CFLAGS=-g -I/opt/ports/include
CXX = g++
CXXFLAGS =-g -I/opt/ports/include
LIBS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr
INIT_SHADER = initshader.o

hw4: hw4.o $(INIT_SHADER)
	$(CC) $@.o $(INIT_SHADER) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -r lab6 *.o core *.dSYM

# ifeq ($(shell uname -s), Darwin)
# LDFLAGS=-L/opt/ports/lib -framework OpenGL -lglfw -lGLEW -lm
# else
# LDFLAGS=-lX11 -lGL -lGLU -lglut -lGLEW -lglfw -lm
# endif
#
# CC = g++
# CPLUS = -x c++ -std=c++11
# CFLAGS=-g -I/opt/ports/include
# #CXXFLAGS+=-g -Wall -I/opt/ports/include
# INIT_SHADER = initshader.o
# SOURCES= mats.cpp vecs.cpp hw4.c initshader.c boid.c list.c
# OBJECTS=$(SOURCES:.c=.o)
# # OBJECTS+=$(SOURCES:.cpp=.o) //???
# DEPS=common.hpp mats.hpp vecs.hpp boid.h list.h hw4.h
# EXECUTABLE= hw4 boids mats vecs list
#
# %.o: %.c $(DEPS)
# 	$(CC) $(CPLUS) -c -o $@ $< $(CFLAGS)
#
# $(EXECUTABLE): $(OBJECTS)
# 	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)
#
# clean:
# 	rm *.o $(EXECUTABLE) core. dSYM
