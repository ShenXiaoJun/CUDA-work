#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#define W 600
#define H 600
#define DELTA 5
#define TITLE_STRING "4_5_1: distance image display app"
int2 Aloc = {W/2, H/2};
int2 Bloc = {0, 0};

void keyboard(unsigned char key, int x, int y){
	if(key == 27) exit(0);
	glutPostRedisplay();
}

void mouseMove(int x,int y){
	Bloc.x = x;
	Bloc.y = y;
	glutPostRedisplay();
}

void mouseDrag(int x,int y){
	return;
}

void handleSpecialKeypress(int key, int x, int y){
	if(key == GLUT_KEY_LEFT) 	Aloc.x -= DELTA;
	if(key == GLUT_KEY_RIGHT) 	Aloc.x += DELTA;
	if(key == GLUT_KEY_UP) 		Aloc.y -= DELTA;
	if(key == GLUT_KEY_DOWN) 	Aloc.y += DELTA;
	glutPostRedisplay();
}

void printInstructions(){
	printf("4_5_1 interactions\n");
	printf("arrow keys: move A locations\n");
	printf("mouse move: move B locations\n");
	printf("esc: close graphics window\n");
}

#endif
