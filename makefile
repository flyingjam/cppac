OBJS = main.cpp Vertex.cpp ShaderProgram.cpp Texture.cpp glad.c
CC = clang++
FLAGS = -std=c++11 -Wall
LINKER =  -I/include -lsfml-graphics -lsfml-window -lsfml-system -lGL -ldl
OBJ_NAME = game

all:
	$(CC) $(OBJS) $(LINKER) $(FLAGS) -o $(OBJ_NAME)
