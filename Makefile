ifeq ($(shell uname -s), Darwin)
LDFLAGS=-L/opt/ports/lib -framework OpenGL -lglfw -lGLEW -lm
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lGLEW -lglfw -lm
endif

CC = g++
CFLAGS=-g -I/opt/ports/include
CXXFLAGS+=-g -Wall -I/opt/ports/include
INIT_SHADER = initshader.o
SOURCES= boid.c vecs.cpp mats.cpp
OBJECTS=$(SOURCES:.c=.o)
OBJECTS+=$(SOURCES:.cpp=.o)
DEPS=common.h boid.h mats.hpp vecs.hpp
EXECUTABLE=boid mats vecs

boid: boid.o $(INITSHADER) common.h
	$(CC) $@.o $(INITSHADER) $(LDFLAGS) -o $@

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(CXX) -c $(CXXFLAGS) $<

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

clean:
	rm *o $(EXECUTABLE)

# example1: example1.o $(INIT_SHADER) common.h
# 	$(CC) $@.o $(INIT_SHADER) $(LDFLAGS) -o $@
#
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@
#
#
# clean:
# 	-rm -r example1 *.o core *.dSYM

# ifeq ($(shell uname -s), Darwin)
# LDFLAGS+=-L/opt/ports/lib -framework OpenGL -lglfw3 -lm -lGLEW
# else
# LDFLAGS+=-lX11 -lGL -lGLU -lglfw -lGLEW -lm -lgsl -lgslcblas -lglut
# endif
# # CC = gcc
# CC = g++
# CFLAGS+=-g -Wall -I/opt/ports/include
# INIT_SHADER = initshader.o
# CXXFLAGS+=-g -Wall -I/opt/ports/include
# #-I/usr/local/Cellar/glfw3/3.2.1/include


	# ifeq ($(shell uname -s), Darwin)
	# LDFLAGS=-L/opt/local/lib -framework OpenGL -lglfw -lGLEW -lm
	# else
	# LDFLAGS=-lX11 -lGL -lGLU -lglfw -lGLEW -lm
	# endif
	# CC = gcc
	# CFLAGS=-g -Wall -I/opt/local/include
	# all: $@
	# $@: $a.
