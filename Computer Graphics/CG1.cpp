#include<windows.h>
#include<gl/glut.h>
HGLRC hRC=0;
HDC hDC=0;
HWND hWnd=0;
HINSTANCE hInstance;
bool keys[256];
bool active=1;
GLfloat sum1=0.0004f,sum2=0.0004f;
GLfloat rtri,trisum;
GLfloat rquad,quadsum;
void ResizeGLScene(GLsizei width,GLsizei height)//
{
	if(height==0)height=1;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_ACTIVATE:{active=!HIWORD(wParam);return 0;}
		case WM_SYSCOMMAND:
		{
			switch(wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;
		}
		case WM_CLOSE:{PostQuitMessage(0);return 0;}
		case WM_KEYDOWN:{keys[wParam]=1;return 0;}
		case WM_KEYUP:{keys[wParam]=0;return 0;}
		case WM_SIZE:{ResizeGLScene(LOWORD(lParam),HIWORD(lParam));return 0;}
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
int InitGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	return 1;
}
int DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-1.5f,0.0f,-6.0f);
	
	glRotatef(rtri,0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);
	
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	
	glEnd();
	
	glLoadIdentity();
	glTranslatef(1.5f,0.0f,-7.0f);
	glRotatef(rquad,1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
	
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	
	glColor3f(1.0f,0.5f,0.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	
	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	
	glColor3f(1.0f,0.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	
	glEnd();
	
	trisum+=sum1;
	quadsum+=sum2;
	if(trisum>0.50f||trisum<-0.50f)sum1*=-1.0f;
	if(quadsum>0.50f||quadsum<-0.50f)sum2*=-1.0f;
//	rtri+=trisum;
//	rquad-=quadsum;
	return 1;
}
void KillGLWindow()
{
	if(hRC)
	{
		wglMakeCurrent(0,0);
		wglDeleteContext(hRC);
	}
	ReleaseDC(hWnd,hDC);
	DestroyWindow(hWnd);
	UnregisterClass("OpenGL",hInstance);
}

BOOL CreateGLWindow(char *title,int width,int height,int bits)
{
	GLuint PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)height;
	hInstance=GetModuleHandle(0);
	wc.style=CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	wc.lpfnWndProc=WndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(0,IDI_WINLOGO);
	wc.hCursor=LoadCursor(0,IDC_ARROW);
	wc.hbrBackground=0;
	wc.lpszMenuName=0;
	wc.lpszClassName="OPenGL";
	RegisterClass(&wc);
	dwExStyle=WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;
	dwStyle=WS_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&WindowRect,dwStyle,FALSE,dwExStyle);
	LONG nX=(::GetSystemMetrics(SM_CXSCREEN-width))/2,nY=(::GetSystemMetrics(SM_CYSCREEN)-height)/2;
	if(!(hWnd=CreateWindowEx(dwExStyle,"OpenGL",title,WS_CLIPSIBLINGS|WS_CLIPCHILDREN|dwStyle,nX,nY,WindowRect.right-WindowRect.left,WindowRect.bottom-WindowRect.top,0,0,hInstance,0)))
	{
		KillGLWindow();
		MessageBox(0,"Cannot create a window device description table","Error",MB_OK|MB_ICONEXCLAMATION);
		return 0;
	}
	static PIXELFORMATDESCRIPTOR pfd={sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,bits,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,PFD_MAIN_PLANE,0,0,0,0};
	if(!(hDC=GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(0,"Cannot create a matched pixel format","Error",MB_OK|MB_ICONEXCLAMATION);
		return 0;
	}
	if(!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
	{
		KillGLWindow();
		MessageBox(0,"Cannot set pixel format","Error",MB_OK|MB_ICONEXCLAMATION);                
		return 0;
	}
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		KillGLWindow();
		MessageBox(0,"Cannot set pixel format","Error",MB_OK|MB_ICONEXCLAMATION);                
		return 0;
	}
	if(!(hRC=wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL,"Cannot create OpebGL render description table","Error",MB_OK|MB_ICONEXCLAMATION);
		return 0;
	}
	if(!wglMakeCurrent(hDC,hRC))
	{
		KillGLWindow();
		MessageBox(NULL,"Cannot active the current OpebGL render description table","Error",MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	ShowWindow(hWnd,SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ResizeGLScene(width,height);
	if(!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL,"Initialization","Error",MB_OK|MB_ICONEXCLAMATION);
		return 0;
	}
	return 1;
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	BOOL done=0;
	CreateGLWindow("OpenGL 3D Figure of 3D item",640,480,16);
	while(!done)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			if(msg.message==WM_QUIT)done=1;
			else TranslateMessage(&msg),DispatchMessage(&msg);
		}
		else
		{
			if(active)
			{
				if(keys[VK_ESCAPE])done=1;
				else DrawGLScene(),SwapBuffers(hDC);
			}
			if(keys[VK_F1])
			{
				keys[VK_F1]=0;
				KillGLWindow();
				if(!CreateGLWindow("OpenGL 3D Figure of rotation",640,480,16))
					return 0;
			}
		}
	}
	KillGLWindow();
	return (msg.wParam);
}
