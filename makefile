OBJS = main.cpp ShaderProgram.cpp Texture.cpp
CC = clang++
FLAGS = -std=c++11
LINKER =  -I/include -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLEW
OBJ_NAME = game

all:
	$(CC) $(OBJS) $(LINKER) $(FLAGS) -o $(OBJ_NAME)
