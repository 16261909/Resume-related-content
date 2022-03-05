#include<windows.h>
#include<GL\glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
enum TransMode{Translate,Rotate,Scale};
TransMode transModeSelected =Rotate;
GLfloat angle=0.0,axis[3];
GLfloat mynear=-30.0,myfar=30.0,viewxform_z=-5.0;
GLfloat Time=0.0,deltaTime=0.01,ang,dang=0.01;
bool drawLines=0;
int lastX,lastY,winWidth,winHeight;
GLfloat vertices[][3]=
{
	{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0},
	{-1.0,-1.0,1.0},{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0},
	{-2.0,-1.0,1.0},{-2.0,-1.0,-1.0},{-2.0,1.0,-1.0},{-2.0,1.0,1.0},{-3.0,0.0,0.0}
};
GLfloat colors[][3]=
{
	{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0},
	{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,1.0,1.0},{0.0,0.0,1.0},
	{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,1.0,1.0},{0.0,0.0,1.0},
};
GLfloat objectXform[4][4]=
{
	{1.0,0.0,0.0,0.0},{0.0,1.0,0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,0.0,0.0,1.0}
};
struct menuEntryStruct
{
	const char *label;
	char key;
};
static menuEntryStruct mainMenu[]={"Reset",'0',"Rotate",'r',"Translate",'t',"Scale",'s',"Lines/Polygons",'1',"quit",27};
int mainMenuEntries=sizeof(mainMenu)/sizeof(menuEntryStruct);
void startMotion(int x,int y){lastX=x;lastY=y;}
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
void polygon1(int a,int b,int c)
{
	if(drawLines)
	{
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINE_LOOP);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
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
	polygon(8,9,10,11,0);
	polygon1(8,9,12);
	polygon1(9,10,12);
	polygon1(10,11,12);
	polygon1(11,8,12);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0,0.0,viewxform_z);
	if(transModeSelected==Translate)
	{
		glPushMatrix();
		glLoadIdentity();
		GLfloat deltaHeight=(GLfloat)(sin(Time+deltaTime)-sin(Time))*2.0;
		glTranslatef(0,deltaHeight,0);
		glMultMatrixf((GLfloat *)objectXform);
		glGetFloatv(GL_MODELVIEW_MATRIX,(GLfloat *)objectXform);
		glPopMatrix();
	}
	else if(transModeSelected==Rotate)
	{
		glPushMatrix();
		glLoadIdentity();
		ang+=dang;
		if(((fabs(ang)>3)||((rand()%5>4)&&fabs(ang)>0.8))&&ang*dang>0.0)dang*=-1.0;
		glRotatef(ang,-0.7,1,0.7);
		glMultMatrixf((GLfloat *)objectXform);
		glGetFloatv(GL_MODELVIEW_MATRIX,(GLfloat *)objectXform);
		glPopMatrix();
	}
	else if(transModeSelected==Scale)
	{
		glPushMatrix();
		glLoadIdentity();
		GLfloat delta1=50.0/49.0,delta2=49.0/50.0,sx,sy,sz;
		if(rand()%2==0)sx=delta1;else sx=delta2;
		if(rand()%2==0)sy=delta1;else sy=delta2;
		if(rand()%2==0)sz=delta1;else sz=delta2;
		glScalef(sx,sx,sx);
		glMultMatrixf((GLfloat *)objectXform);
		glGetFloatv(GL_MODELVIEW_MATRIX,(GLfloat *)objectXform);
		glPopMatrix();
	}
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
void myReshape(int w,int h)
{
	winWidth=w;
	winHeight=h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)glOrtho(-5.0,5.0,-5.0*(GLfloat)h/(GLfloat)w,5.0*(GLfloat)h/(GLfloat)w,mynear,myfar);
	else glOrtho(-5.0*(GLfloat)w/(GLfloat)h,5.0*(GLfloat)w/(GLfloat)h,-5.0,5.0,mynear,myfar);
	viewxform_z=-5.0;
	glMatrixMode(GL_MODELVIEW);
	
}
void stopMotion(int x,int y)
{
	angle=0.0f;
	memset(axis,0,sizeof axis);
	printf("objectXform:\n");
	for(int i=0;i<4;i++)
	{
		printf("\t");
		for(int j=0;j<4;j++)
		{
			printf("%.2f\t",objectXform[i][j]);
		}
		puts("");
	}
}
void mouseButton(int button,int state,int x,int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:break;
		default:return;
	}
	switch(state)
	{
		case GLUT_DOWN:startMotion(x,y);break;
		case GLUT_UP:stopMotion(x,y);break;
	}
}
void mouseMotion(int x,int y)
{
	float dx=x-lastX,dy=y-lastY;
	if(!dx&&!dy)return;
	if(transModeSelected==Translate)
	{
		axis[0]=dx*(10.0f/winWidth);
		axis[1]=-dy*(10.0f/winHeight);
		axis[2]=0;
	}
	else if(transModeSelected==Rotate)
	{
		angle=3.0;
		axis[0]=dy*(360.0/winHeight);
		axis[1]=dx*(360.0/winWidth);
		axis[2]=0;
	}
	else if(transModeSelected==Scale)
	{
		axis[0]=dx*(4.0/winWidth);
		axis[1]=-dy*(4.0/winHeight);
		axis[2]=0;
	}
	lastX=x,lastY=y;
	glutPostRedisplay();
}
void userEventAction(int key)
{
	switch(key)
	{
		case '0':
			angle=0.0f;
			memset(axis,0,sizeof axis);
			memset(objectXform,0,sizeof objectXform);
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
					if(i==j)objectXform[i][j]=1.0f;
			break;
		case 'r':
			transModeSelected=Rotate;
			break;
		case 't':
			transModeSelected=Translate;
			break;
		case 's':
			transModeSelected=Scale;
			break;
		case '1':
			drawLines^=1;
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
void selectMain(int choice){userEventAction(mainMenu[choice].key);}
void keyboard(unsigned char key,int x,int y)
{
	userEventAction(key);
}
void init()
{
	glLineWidth(3.0);
	glEnable(GL_DEPTH_TEST);
	glutCreateMenu(selectMain);
	for(int i=0;i<mainMenuEntries;i++)glutAddMenuEntry(mainMenu[i].label,i);
	glutAttachMenu(GLUT_RIGHT_BUTTON); 
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
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
