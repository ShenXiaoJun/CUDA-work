//未完成
//范德尔堡限制环在param=0.1时近似为圆形。修改stability程序，使阴影决定于
//最终距离和一个新参数rad之间的差值。实现对rad的交互控制，并且运行修改的应用程序来确定限制环的大小
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
	kernelLauncher(d_out, W, H, param, sys);
	cudaGraphicsUnmapResources(1, &cuda_pbo_resource, 0);
	char title[64];
	sprintf(title, "Stability: param = %.1f, sys = %d", param, sys);
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
