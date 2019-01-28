#ifndef INTERACTIONS_H
#define INTERACTIONS_H
#include "kernel.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector_types.h>

#define W 600
#define H 600
#define DELTA 5
#define NX 128
#define NY 128
#define NZ 128

int id = 1;
int method = 2;
const int3 volumeSize = {NX, NY, NZ};
const float4 params = {NX/4.f, NY/6.f, NZ/16.f, 1.f};
float *d_vol;
float zs = NZ;
float dist = 0.f, theta = 0.f, threshold = 0.f;

void mymenu(int value){
	switch(value){
	case 0: return;
		case 1: id = 0;break;//sphere
		case 2: id = 1;break;//torus
		case 3: id = 2;break;//block
	}
	volumeKernelLauncher(d_vol, volumeSize, id, params);
	glutPostRedisplay();
}

void createMenu(){
	glutCreateMenu(mymenu);
	glutAddMenuEntry("Object Selector", 0);
	glutAddMenuEntry("Sphere", 1);
	glutAddMenuEntry("Torus", 2);
	glutAddMenuEntry("Block", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboard(unsigned char key, int x, int y){
	if(key == '+') zs -= DELTA;
	if(key == '-') zs += DELTA;
	if(key == 'd') --dist;
	if(key == 'D') ++dist;
	if(key == 'z') zs = NZ, theta = 0.f, dist = 0.f;
	if(key == 'v') method = 0;
	if(key == 'f') method = 1;
	if(key == 'r') method = 2;
	if(key == 27) exit(0);
	glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y){
	if(key == GLUT_KEY_LEFT) theta -= 0.1f;
	if(key == GLUT_KEY_RIGHT) theta += 0.1f;
	if(key == GLUT_KEY_UP) threshold += 0.1f;
	if(key == GLUT_KEY_DOWN) threshold -= 0.1f;
	glutPostRedisplay();
}

void printInstructions(){
	printf("3D Volume Visualizer\n"
			"Controls:\n"
			"Volume render mode                          : v\n"
			"Slice render mode                           : f\n"
			"Raycast mode                                : r\n"
			"Zoom out/in                                 : -/+\n"
			"Rotate view                                 : left/right\n"
			"Decr./Incr. Offset (intensity in slice mode): down/up\n"
			"Decr./Incr. distance (only in slice mode)   : d/D\n"
			"Reset parameters                            : z\n"
			"Right-click for object selection menu\n");
}

#endif
