#include "model.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include <obj/load.h>
#include <obj/draw.h>

void init_object(Object* object, int x, int z, int y)
{
	object->position.x = x;
	object->position.y = y;
	object->position.z = z;

	object->material_ambient[0] = 0.75;
	object->material_ambient[1] = 0.75;
	object->material_ambient[2] = 0.75;
	object->material_ambient[3] = 0.5;
}

/**
 * Loads the texture file with SOIL
 */
GLuint load_texture(const char* filename) {
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	GLuint texture_name;
	Pixel* image;
	glGenTextures(1, &texture_name);

	int width;
	int height;

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

	glBindTexture(GL_TEXTURE_2D, texture_name);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGBA,GL_UNSIGNED_BYTE,(Pixel*)image);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// SOIL_free_image_data(image);

	return texture_name;
}

void init_entities(World* world) {
	move_chair_id = -1;

	// Chair
	load_model(&world->chairs[0].model, "assets/models/19799_Zig_Zag_Chair_v1.obj");
	world->chairs[0].texture = load_texture("assets/textures/chair.jpg");
	init_object(&world->chairs[0], -120, -60, -13);
	world->chairs[0].rotation = -270.0f;

	// Chair
	world->chairs[1].model = world->chairs[0].model;
	world->chairs[1].texture = world->chairs[0].texture;
	init_object(&world->chairs[1], -120, 45, -13);
	world->chairs[1].rotation = 270.0f;

	// Chair
	world->chairs[2].model = world->chairs[0].model;
	world->chairs[2].texture = world->chairs[0].texture;
	init_object(&world->chairs[2], 1840, -5, -13);
	world->chairs[2].rotation = 180.0f;

	// Table
	load_model(&world->table1.model, "assets/models/table.obj");
	world->table1.texture = load_texture("assets/textures//Wood_Table_C_2.jpg");
	init_object(&world->table1, -120, 20, 25);

	// Table
	world->table2.model = world->table1.model;
	world->table2.texture = world->table1.texture;
	init_object(&world->table2, 1900, 20, 15);

	// Door
	load_model(&world->door.model, "assets/models/door2_v2.obj");
	world->door.texture = load_texture("assets/textures//door.jpg");
	init_object(&world->door, -120, 170, 0);

	// Corridor
	world->corridor.ground = load_texture("assets/textures/ground.jpg");
    world->corridor.ceiling = load_texture("assets/textures/ceiling.jpg");
	world->corridor.back = load_texture("assets/textures//wall.jpg");
	world->corridor.front = world->corridor.back;
	world->corridor.left = world->corridor.back;
	world->corridor.right = world->corridor.back;

	// Help
	world->helpTexture = load_texture("assets/textures//help.png");
}
