#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
int winWidth, winHeight;
float angle = 0.0, axis[3], trans[3];
bool trackingMouse = false;
bool redrawContinue = false;
bool trackballMove = false;
GLfloat vertices[][3] = {
	{-1.0,-1.0,-1.0}, {1.0,-1.0,-1.0}, {1.0,1.0,-1.0}, {-1.0,1.0,-1.0},
	{-1.0,-1.0,1.0}, {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}
};
GLfloat colors[][3] = {
	{0.0,0.0,0.0}, {1.0,0.0,0.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0},
	{0.0,0.0,1.0}, {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}
};
void polygon(int a, int b, int c , int d, int face) {
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}
void colorcube(void) {
	polygon(1,0,3,2,0);
	polygon(3,7,6,2,1);
	polygon(7,3,0,4,2);
	polygon(2,6,5,1,3);
	polygon(4,5,6,7,4);
	polygon(5,4,0,1,5);
}
float lastPos[3] = {0.0F, 0.0F, 0.0F};
int curx, cury;
int startX, startY;
void trackball_ptov(int x, int y, int width, int height, float v[3]) {
	float d, a;
	v[0] = (2.0F*x - width) / width;
	v[1] = (height - 2.0F*y) / height;
	d = (float) sqrt(v[0]*v[0] + v[1]*v[1]);
	v[2] = (float) cos((3.1415926/2.0F) * ((d < 1.0F) ? d : 1.0F));
	a = 1.0F / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	v[0] *= a;
	v[1] *= a;
	v[2] *= a;
}
void mouseMotion(int x, int y) {
	float curPos[3], dx, dy, dz;
	trackball_ptov(x, y, winWidth, winHeight, curPos);
	if(trackingMouse) {
		dx = curPos[0] - lastPos[0];
		dy = curPos[1] - lastPos[1];
		dz = curPos[2] - lastPos[2];
		if (dx || dy || dz) {
			angle = 90.0F * sqrt(dx*dx + dy*dy + dz*dz);
			axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1];
			axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
			axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0];
			lastPos[0] = curPos[0];
			lastPos[1] = curPos[1];
			lastPos[2] = curPos[2];
		}
	}
	glutPostRedisplay();
}
void startMotion(int x, int y) {
	trackingMouse = true;
	redrawContinue = false;
	startX = x;
	startY = y;
	curx = x;
	cury = y;
	trackball_ptov(x, y, winWidth, winHeight, lastPos);
	trackballMove=true;
}
void stopMotion(int x, int y) {
	trackingMouse = false;
	if (startX != x || startY != y) {
		redrawContinue = true;
	} else {
		angle = 0.0F;
		redrawContinue = false;
		trackballMove = false;
	}
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if (trackballMove) {
		glRotatef(angle, axis[0], axis[1], axis[2]);
	}
	colorcube();
	glutSwapBuffers();
}
void mouseButton(int button, int state, int x, int y) {
	if(button==GLUT_RIGHT_BUTTON) exit(0);
	if(button==GLUT_LEFT_BUTTON) switch(state) {
			case GLUT_DOWN:
				y=winHeight-y;
				startMotion(x,y);
				break;
			case GLUT_UP:
				stopMotion(x,y);
				break;
		}
}
void myReshape(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
		        2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
		        2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}
void spinCube() {
	if (redrawContinue) glutPostRedisplay();
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
