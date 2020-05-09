#ifndef INCLUDE_MODEL_H
#define INCLUDE_MODEL_H

#include <stdio.h>
#include <GL/glut.h>
#include "SOIL/SOIL.h"

#include <obj/model.h>

#define TRUE 1
#define FALSE 0

#define CHAIR_LENGTH 3

typedef GLubyte Pixel[3];

typedef struct {
    Model model;
    float material_ambient[4];
    int texture;
    struct Vertex position;
    float rotation;
}Object;

typedef struct {
    int front, back, left, right, ground, ceiling;
}Corridor;

typedef struct {
	Corridor corridor;
	int helpTexture;
    Object door;
    Object table1;
    Object table2;
    Object chairs[CHAIR_LENGTH];
}World;

World world;

void init_object(Object* object, int x, int z, int y);

// Loads the texture file with SOIL
GLuint load_texture(const char* filename);

// Initialize my entities
void init_entities(World* world);

#endif // MODEL_H
