#include "header2.h"

int main (int argc, char ** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(300,300);
	glutCreateWindow("My First GL program Homework");
	glutIdleFunc(idle);
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}

