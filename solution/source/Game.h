#ifndef GAME2
#ifndef GAME_H_
#define GAME_H_
//#include "ES3Df.h"
//#include "Button.h"

#define MAXSIZE 6
#define WHOLESIZE 60
#define MAXTYPE 8
#define STATEMENU 1
#define STATEPLAY 2
#define STATEOVER 3

class Game : public GameBase {
public:
	GLuint elapsedTime, OldTime;
	int State;

public:
	virtual void initGame(void);
	virtual void reshapeGame(GLsizei width, GLsizei height);
	virtual void updateGame(GLuint time, unsigned int Tick);
	virtual void updateGameMenu(GLuint time, unsigned int Tick);
	virtual void updateGamePlay(GLuint time, unsigned int Tick);
	virtual void updateGameOver(GLuint time, unsigned int Tick);
	virtual void destroyGame(void);
	virtual void Load(std::string Name, TextureObject& TO);
	virtual ~Game();	
};
#endif
#endif