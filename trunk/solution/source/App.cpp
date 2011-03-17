#include "App.h"

#define BUTTONSHOWX 30
#define BUTTONSHOWY 440

MessageManager g_messageManager;
//static TextureManager TM;
//static Game game;

MessageManager * GetMessageManager() {
	return &g_messageManager;
}

App g_App;

BaseApp * GetBaseApp() {
	return &g_App;
}

App::App() {
}

App::~App() {
}

bool App::Init() {
	if (m_bInitted)	 {
		return true;
	}
	//game.init();
	if (!BaseApp::Init()) return false;
	glDisable(GL_CULL_FACE);
	GetBaseApp()->SetFPSVisible(true);
	//Reshape(GetScreenSizeX(), GetScreenSizeY());
	return true;
}

void App::Reshape(GLsizei width, GLsizei height) {
	//game.reshape(width,height);
}

void App::Kill() {
	BaseApp::Kill();
}

void App::Draw() {
	//game.update(GetGameTick());
	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();
	//if (GetOrientation() != ORIENTATION_PORTRAIT)
	//{
	//	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	//}
	//glRotatef(float( (GetGameTick()/10) %360) , 0, 1, 0); //rotate it
	//RenderGLTriangle();
	//glPopMatrix();
	//draw our game stuff
	//the base handles actually drawing the GUI stuff over everything else
	BaseApp::Draw();
}

void App::Update() {
	BaseApp::Update();
}

void App::OnScreenSizeChange() {
	BaseApp::OnScreenSizeChange();
}

void App::OnMessage(Message &m) {
	switch (m.GetType()) {
	case MESSAGE_TYPE_GUI_CLICK_START: {
			CPoint Mouse;
			Mouse.x = m.GetParm1();
			Mouse.y = m.GetParm2();
			CPoint WndSize;
#ifndef GLES2
			WndSize.x = GetScreenSizeX();
			WndSize.y = GetScreenSizeY();
#endif
			int X = m.GetParm1();
			int Y = m.GetParm2();
			break;
									   }
	case MESSAGE_TYPE_GUI_CLICK_END: {
			int X = m.GetParm1();
			int Y = m.GetParm2();
			break;
									 }
	case MESSAGE_TYPE_GUI_CLICK_MOVE: {
			CPoint Mouse;
			Mouse.x = m.GetParm1();
			Mouse.y = m.GetParm2();
			CPoint WndSize;
#ifndef GLES2
			WndSize.x = GetScreenSizeX();
			WndSize.y = GetScreenSizeY();
#endif
			break;		
									  }
	}
	BaseApp::OnMessage(m);
}

App * GetApp() {
	return &g_App;
}