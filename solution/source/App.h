#pragma once
#include "BaseApp.h"
#include "MessageManager.h"
//#include "TextureManager.h"
//#include "TextureLoader.h"
//#include "Loader.h"
//#include "Game.h"
//#include "Game2.h"
#include <vector>

class App: public BaseApp {
public:
	App();
	virtual ~App();
	virtual bool Init();
	virtual void Kill();
	virtual void Draw();
	virtual void Update();
	virtual void Reshape(GLsizei width, GLsizei height);
	virtual void OnScreenSizeChange();
	virtual void OnMessage(Message &m);

private:
	int OldX, OldY, NewX, NewY;
	bool inCube;
};

extern App g_App;
App * GetApp();