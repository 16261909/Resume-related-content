#include<windows.h>
#include<gl\glut.h>
#include<bits/stdc++.h>
#include<stddef.h>
#define MAX_OBJECTS 10000
#define DEFAULT_POINT_SIZE 10
#define DEFAULT_LINE_WIDTH 5
#define DEFAULT_BEZIER_CONTROL_POINTS_NUM 4
#define MAX_BEZIER_CONTROL_POINTS_NUM 13
#define DEFAULT_PICK_BUFFER_SIZE 32
#define DEFAULT_PICK_WINDOW_SIZE 10
#define PI 3.141592652528979323846
enum GLState{MoveObject,MakePoint};
struct GLColor;
struct GLTransform;
class GLObject;
class GLWorld;
class GLPoint;
class GLBezier;
GLsizei winWidth=600,winHeight=600;
class wcPt3D
{
	public:
		GLfloat x,y,z;
};
void plotPoint(wcPt3D bezCurvePt)
{
	glBegin(GL_POINTS);
		glVertex2f(bezCurvePt.x,bezCurvePt.y);
	glEnd();
}
void binomialCoeffs(GLint n,GLint *C)
{
	for(int k=0;k<=n;k++)
	{
		C[k]=1;
		for(int j=n;j>=k+1;j--)C[k]*=j;
		for(int j=n-k;j>=2;j--)C[k]/=j;
	}
}
void computeBezPt(GLfloat u,wcPt3D* bezPt,GLint nCtrlPts,wcPt3D * ctrlPts,GLint *C)
{
	GLint n=nCtrlPts-1;
	GLfloat bezBlendFcn;
	bezPt->x=bezPt->y=bezPt->z=0.0;
	for(int k=0;k<nCtrlPts;k++)
	{
		bezBlendFcn=(C[k]*pow(u,k)*pow(1-u,n-k));
		bezPt->x+=ctrlPts [k].x*bezBlendFcn;
		bezPt->y+=ctrlPts [k].y*bezBlendFcn;
		bezPt->z+=ctrlPts [k].z*bezBlendFcn;
	}
}

struct GLColor
{
	GLfloat r=0,g=0,b=0;
};
struct GLTransform
{
	GLdouble x=0,y=0,z=0,rx=0,ry=0,rz=0,sx=1,sy=1,sz=1;
};
class GLObject
{
	public:
		GLint id=0;
		GLColor color;
		GLTransform transform;
		bool movable=0,visible=1;
		GLWorld* parentWorld;
		virtual void Draw(GLenum RenderMode=GL_RENDER){}
		virtual void MakePoint(GLdouble x,GLdouble y,GLdouble z){}
		void SetPosition(GLdouble x,GLdouble y,GLdouble z)
		{
			transform.x=x;transform.y=y;transform.z=z;
		}
};
class GLWorld
{
	public:
		GLObject* objects[MAX_OBJECTS];
		GLint count=0;
		GLWorld()=default;
		~GLWorld()
		{
			for(int i=count-1;i>=0;i--)delete objects[i];
		}
		template<typename T>
		T* NewObject()
		{
			if(count<MAX_OBJECTS)
			{
				T* ret=new T;
				objects[count]=(GLObject*)ret;
				objects[count]->parentWorld=this;
				objects[count]->id=count;
				++count;
				return ret;
			}
			else return nullptr;
		}
		void DeleteObject(GLint id);
		void Empty();
		void DrawObjects(GLenum RenderMode=GL_RENDER)
		{
			for(int i=0;i<count;i++)objects[i]->Draw(RenderMode);
		}
		GLint pickedObjectId=-1;
		void PickObject(GLint xMouse,GLint yMouse)
		{
			pickRects(GLUT_LEFT_BUTTON,GLUT_DOWN,xMouse,yMouse);
		}
	private:
		void pickRects(GLint button,GLint action,GLint xMouse,GLint yMouse);
		void processPicks(GLint nPicks,GLuint pickBuffer[]);
};
extern GLfloat xwcMin,xwcMax,ywcMin,ywcMax;
void GLWorld::pickRects(GLint button,GLint action,GLint xMouse,GLint yMouse)
{
	GLuint pickBuffer[DEFAULT_PICK_BUFFER_SIZE];
	GLint nPicks,vpArray[4];
	if(button!=GLUT_LEFT_BUTTON||action!=GLUT_DOWN)return;
	glSelectBuffer(DEFAULT_PICK_BUFFER_SIZE,pickBuffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(MAX_OBJECTS);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glGetIntegerv(GL_VIEWPORT,vpArray);
	gluPickMatrix(GLdouble (xMouse),GLdouble(vpArray[3]-yMouse),DEFAULT_PICK_WINDOW_SIZE,DEFAULT_PICK_WINDOW_SIZE,vpArray);
	gluOrtho2D(xwcMin,xwcMax,ywcMin,ywcMax);
	this->DrawObjects(GL_SELECT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	nPicks=glRenderMode(GL_RENDER);
	processPicks(nPicks,pickBuffer);
	glutPostRedisplay();
}
void GLWorld::processPicks(GLint nPicks,GLuint pickBuffer[])
{
	if(nPicks==0)pickedObjectId=-1;
	else
	{
		int chunkId=4*(nPicks-1);
		pickedObjectId=pickBuffer[chunkId+3];
	}
	return;
}
class GLPoint:public GLObject
{
	public:
		GLPoint(){color.r=1;}
		virtual void Draw(GLenum RenderMode=GL_RENDER)
		{
			if(!visible)return;
			if(RenderMode==GL_SELECT)glLoadName((GLuint)id);
			glColor3f(color.r,color.g,color.b);
			glPointSize(DEFAULT_POINT_SIZE);
			glBegin(GL_POINTS);
			glVertex3d(transform.x,transform.y,transform.z);
			glEnd();
		}
};
void bezier(wcPt3D *ctrlPts,GLint nCtrlPts,GLint nBezCurvePts)
{
	wcPt3D bezCurvePt;
	GLfloat u;
	GLint *C;
	C=new GLint [nCtrlPts];
	binomialCoeffs (nCtrlPts-1,C);
	for(int k=0;k<=nBezCurvePts;k++)
	{
		u=GLfloat(k)/GLfloat(nBezCurvePts);
		computeBezPt(u,&bezCurvePt,nCtrlPts,ctrlPts,C);
		plotPoint(bezCurvePt);
	}
	delete []C;
} 
class GLBezier:public GLObject
{
	public:GLPoint* ctrlPoints[MAX_BEZIER_CONTROL_POINTS_NUM];
	int count=0;
	GLint nBezCurvePoints=1000;
	virtual void MakePoint(GLdouble x,GLdouble y,GLdouble z)
	{
		if(count>=MAX_BEZIER_CONTROL_POINTS_NUM)return;
		ctrlPoints[count]=parentWorld->NewObject<GLPoint>();
		ctrlPoints[count]->SetPosition(x,y,z);
		ctrlPoints[count]->movable=1;
		count++;
	}
	virtual void Draw(GLenum RenderMode=GL_RENDER)
	{
		if(count==0)return;
		for(int i=0;i<count;i++)
		{
			if(!ctrlPoints[i])return;
		}
		if(RenderMode==GL_SELECT)glLoadName((GLuint)id);
		glColor3f(color.r,color.g,color.b);
		glPointSize(DEFAULT_LINE_WIDTH);
//		bezier(ctrlPoints,nBezCurvePoints);
	}
private:
	void bezier(GLPoint* ctrlPoints,GLint nBezCurvePoints)
	{
		
	}
};
int main()
{
	return 0;
}
