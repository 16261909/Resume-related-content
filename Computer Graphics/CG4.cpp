#include<windows.h>
#include<GL/glut.h>
#include<bits/stdc++.h>
GLsizei winWidth=500,winHeight=500;
GLint MAXITER;
GLfloat xComplexMin=-2.00,xComplexMax=0.50;
GLfloat yComplexMin=-1.25,yComplexMax=1.25;
GLfloat complexWidth=xComplexMax-xComplexMin;
GLfloat complexHeight=yComplexMax-yComplexMin;
class complexNum{
	public:
		GLfloat x,y;
};
struct color{GLfloat r,g,b;};
void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
}
void plotPoint(complexNum z)
{
	glBegin(GL_POINTS);
		glVertex2f(z.x,z.y);
	glEnd();
}
complexNum complexSquare(complexNum z)
{
	complexNum zSquare;
	zSquare.x=z.x*z.x-z.y*z.y;
	zSquare.y=2*z.x*z.y;
	return zSquare;
}
GLint mandelSqTransf(complexNum z0,GLint maxIter)
{
	complexNum z=z0;
	GLint count=0;
	while((z.x*z.x+z.y*z.y<=4.0)&&(count<maxIter))
	{
		z=complexSquare(z);
		z.x+=z0.x;
		z.y+=z0.y;
		count++;
	}
	return count;
}
void mandelbrot(GLint nx,GLint ny,GLint maxIter)
{
	complexNum z,zIncr;
	color ptColor;
	GLint iterCount;
	zIncr.x=complexWidth/GLfloat(nx);
	zIncr.y=complexHeight/GLfloat(ny);
	for(z.x=xComplexMin;z.x<xComplexMax;z.x+=zIncr.x)
	{
		for(z.y=yComplexMin;z.y<yComplexMax;z.y+=zIncr.y)
		{
			iterCount=mandelSqTransf(z,maxIter);
			if(iterCount>=maxIter)
			{
				ptColor.r=0.0;
				ptColor.g=0.0;
				ptColor.b=0.0;
			}
			else 
			{
				GLfloat value=(GLfloat)iterCount/maxIter;
				ptColor.r=(GLfloat)(sin(value*2+0.1)/2+0.5);
				ptColor.g=(GLfloat)(sin(value*3+0.3)/2+0.5);
				ptColor.b=(GLfloat)(sin(value*5+0.5)/2+0.5);
				
			}
			glColor3f(ptColor.r,ptColor.g,ptColor.b);
			plotPoint(z);
		}
	}
}
void winReshapeFcn(GLint newWidth,GLint newHeight)
{
	glViewport(0,0,newWidth,newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xComplexMin,xComplexMax,yComplexMin,yComplexMax);
	glClear(GL_COLOR_BUFFER_BIT);
}
GLint newX=0,newY=0;
void zoom()
{
	GLdouble winx=(GLdouble)newX,winy=(GLdouble)winHeight-(GLdouble)newY,winz=0;
//	objx=winx;
//	objy=winy;
//	objz=winz;
//	unProject(winx,winy,winz,&objx,&objy,&objz);
//	gluLookAt(winx,winy,winz,0.0,0.0,0.0,0.0,0.0,0.0); 
	winx=winx/winWidth*complexWidth+xComplexMin;
	winy=winy/winHeight*complexHeight+yComplexMin;
//	printf("%lf %lf\n",winx,winy);
//	printf("%f %f %f %f\n",xComplexMin,xComplexMax,yComplexMin,yComplexMax);
	xComplexMin+=(winx-xComplexMin)/2;
	xComplexMax+=(winx-xComplexMax)/2;
	yComplexMin+=(winy-yComplexMin)/2;
	yComplexMax+=(winy-yComplexMax)/2;
	complexWidth=xComplexMax-xComplexMin;
	complexHeight=yComplexMax-yComplexMin;
	glutPostRedisplay();
}
void displayFcn()
{
	GLint nx=winWidth,ny=winHeight,maxIter=MAXITER;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xComplexMin,xComplexMax,yComplexMin,yComplexMax);
	glMatrixMode(GL_MODELVIEW);
	mandelbrot(nx,ny,maxIter);
	glFlush();
	printf("Zoom:%.2f\n",2.5/complexHeight);
}
void mouseButton(int button,int state,int x,int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:break;
		case GLUT_RIGHT_BUTTON:
			xComplexMin=-2.00,xComplexMax=0.50;
			yComplexMin=-1.25,yComplexMax=1.25;
			complexWidth=xComplexMax-xComplexMin;
			complexHeight=yComplexMax-yComplexMax;
			glutPostRedisplay();
			return;
		default:return;
	}
	switch(state)
	{
		case GLUT_DOWN:
			newX=x,newY=y;
			glutIdleFunc(zoom);
			break;
		case GLUT_UP:
			newX=0,newY=0;;
			glutIdleFunc(NULL);
			break;
	}
}
void mouseMotion(int x,int y){newX=x,newY=y;}

int main(int argc,char** argv)
{
	puts("PLEASE INPUT THE TIMES OF ITERATIONS:");
	scanf("%d",&MAXITER);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(500,200);
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("Mandelbrot Set");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutMainLoop();
	return 0;
}
