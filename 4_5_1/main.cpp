/*
 * 修改flashlight 程序，使其变为一个“更冷/更热”游戏，
 * 为玩家A提供一个选择目标像素的接口，
 * 玩家B根据点的颜色寻找目标像素。
 * 其中，随着点远离目标，点的颜色会变蓝(或红)
 * */
#include "kernel.h"
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include "interactions.h"

GLuint pbo = 0;
GLuint tex = 0;
struct cudaGraphicsResource *cuda_pbo_resource;

void render(){
	uchar4 *d_out = 0;
	cudaGraphicsMapResources(1, &cuda_pbo_resource, 0);
	cudaGraphicsResourceGetMappedPointer((void **)&d_out, NULL, cuda_pbo_resource);
	kernelLauncher(d_out, W, H, Aloc, Bloc);
	cudaGraphicsUnmapResources(1, &cuda_pbo_resource, 0);
	char title[64];
	sprintf(title, "4_5_1:Aloc.x=%d, Aloc.y=%d, Bloc.x=%d, bloc.y=%d", Aloc.x, Aloc.y, Bloc.x, Bloc.y);
	glutSetWindowTitle(title);
}

void drawTexture(){
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0,0);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0,H);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(W,H);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(W,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void display(){
	render();
	drawTexture();
	glutSwapBuffers();
}

void initGLUT(int *argc, char **argv){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutCreateWindow(TITLE_STRING);
	glewInit();
}

void initPixelBuffer(){
	glGenBuffers(1,&pbo);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, 4*W*H*sizeof(GLubyte), 0, GL_STREAM_DRAW);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D,tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	cudaGraphicsGLRegisterBuffer(&cuda_pbo_resource, pbo, cudaGraphicsMapFlagsWriteDiscard);
}

void exitFunc(){
	if(pbo){
		cudaGraphicsUnregisterResource(cuda_pbo_resource);
		glDeleteBuffers(1, &pbo);
		glDeleteTextures(1, &tex);
	}
}

int main(int argc, char **argv){
	printInstructions();
	initGLUT(&argc, argv);
	gluOrtho2D(0, W, H, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(handleSpecialKeypress);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseDrag);
	glutDisplayFunc(display);
	initPixelBuffer();
	glutMainLoop();
	atexit(exitFunc);
	return 0;
}
