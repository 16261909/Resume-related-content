#include<windows.h>
#include<GL\glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
GLfloat mynear=-30.0,myfar=30.0,viewxform_z=-5.0,Time=0.0,deltaTime=0.01,ang,dang=0.01;
bool drawLines=0;
GLfloat vertices[][3]=
{
	{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0},
	{-1.0,-1.0,1.0},{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0}
};
GLfloat colors[][3]=
{
	{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}
};
GLfloat objectXform[4][4]=
{
	{1.0,0.0,0.0,0.0},{0.0,1.0,0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,0.0,0.0,1.0}
};
void polygon(int a,int b,int c,int d,int face)
{
	if(drawLines)
	{
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINE_LOOP);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
		glEnd();
	}
	else
	{
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
}
void colorcube()
{
	polygon(1,0,3,2,0);
	polygon(3,7,6,2,1);
	polygon(7,3,0,4,2);
	polygon(2,6,5,1,3);
	polygon(4,5,6,7,4);
	polygon(5,4,0,1,5);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0,0.0,viewxform_z);
	
	glPushMatrix();
	glLoadIdentity();
	GLfloat deltaHeight=(GLfloat)(sin(Time+deltaTime)-sin(Time))*2.0;
	glTranslatef(0,deltaHeight,0);
	ang+=dang;
	printf("%lf %lf\n",dang,ang);
	if(((fabs(ang)>3)||((rand()%5>4)&&fabs(ang)>0.8))&&ang*dang>0.0)dang*=-1.0;
//	glScalef(ang*(rand()%2),ang*(rand()%2),ang*(rand()%2));
	glRotatef(ang,-0.7,1,0.7);
	glMultMatrixf((GLfloat *)objectXform);
	glGetFloatv(GL_MODELVIEW_MATRIX,(GLfloat *)objectXform);
	glPopMatrix();
	
	
	glPushMatrix();
	glMultMatrixf((GLfloat *)objectXform);
	colorcube();
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
	
	Sleep(deltaTime*1000);
	Time+=deltaTime;
	glutPostRedisplay();
}
void init()
{
	glLineWidth(3.0);
	glEnable(GL_DEPTH_TEST);
}
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)glOrtho(-5.0,5.0,-5.0*(GLfloat)h/(GLfloat)w,5.0*(GLfloat)h/(GLfloat)w,mynear,myfar);
	else glOrtho(-5.0*(GLfloat)w/(GLfloat)h,5.0*(GLfloat)w/(GLfloat)h,-5.0,5.0,mynear,myfar);
	viewxform_z=-5.0;
	glMatrixMode(GL_MODELVIEW);
	
}
int main(int argc,char** argv)
{
	srand(time(NULL));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("Obj");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	display();
	glutMainLoop();
	return 0;
}
