#ifdef GAME2
#ifndef GAME_H_
#define GAME_H_
#include "ES3Df.h"
#include "TrackBall.h"

using namespace ES3D;

class Game : public GameBase {
public:
	Modelf model;
	WTrackball Trackball;
	GLuint groundTextureName;
	GLfloat RotX, RotY, RotZ;

protected:
	virtual void initGame(void);
	virtual void reshapeGame(GLsizei width, GLsizei height);
	virtual void updateGame(GLuint time);
	virtual void destroyGame(void);

public:
	void Touch(int OldX, int OldY, int NewX, int NewY);
	virtual ~Game();	
};
#endif
#endif