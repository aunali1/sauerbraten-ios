#ifndef GAME2
#ifdef WIN32
#include <GLES2/gl2.h>
#else
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif
#include "RenderUtils.h"
#include "Game.h"
#include "GLU.h"

Game::~Game() {
}

void Game::initGame() {
	State = STATEMENU;
	//
	//
	//
	GLfloat lightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// Set the clear color to plain black
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	// Set the clear depth to 1.0
	glClearDepthf(1.0f);
	// Enable the depth test when rendering
	glEnable(GL_DEPTH_TEST);
	// Enable backface culling
	glEnable(GL_CULL_FACE);
	// Enable the light0
#ifndef GLES2
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
#endif
}

void Game::Load(std::string Name, TextureObject& TO) {
	Name = GetBaseAppPath() + Name;
	TextureManager::getTexture(Name.c_str(), TO);
}

void Game::reshapeGame(GLsizei width, GLsizei height) {
	if (width == 0 || height == 0) {
		return;
	}
	// Set the viewport to maximum screen size
	glViewport(0, 0, width, height);
#ifndef GLES2
	// Set the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#endif
	GluSubsetf::perspectivef(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 400.0f);
#ifndef GLES2
	// Restore the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
#endif
}

void Game::updateGame(GLuint time, unsigned int Tick) {
	switch (State) {
		case (STATEMENU): 
			updateGameMenu(time, Tick);
			break;
		case (STATEPLAY): 
			updateGamePlay(time, Tick);
			break;
		case (STATEOVER): 
			updateGameOver(time, Tick);
			break;
	}
}

void Game::updateGameMenu(GLuint time, unsigned int Tick) {
	static GLuint elapsedTime = 0;
	// update the elapsed time
	elapsedTime += time;
	static GLfloat	ground[] = { -40.0f, -20.0f, 40.0f,
					  			  40.0f, -20.0f, 40.0f,
								 -40.0f, -20.0f, -40.0f, 
					 			  40.0f, -20.0f, -40.0f};
	static GLfloat	groundTexture[] = { 0.0f, 0.0f,
						 				4.0f, 0.0f,
						 				0.0f, 4.0f,
						 				4.0f, 4.0f};
	static GLfloat start[3] = {40.0f, 0.0f, 40.0f};
	static GLfloat end[3] = {40.0f, -20.0f, -40.0f};
	static GLfloat hit[3];
	static GLfloat xdirection = -1.0f;
	static GLfloat ydirection = 1.0f;
	static GLfloat zdirection = 0.0f;
	static GLfloat scanTime = 20.0f;
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifndef GLES2
	// Smooth shading
	glShadeModel(GL_SMOOTH);
	// Enable the matrix mode
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();
#endif
	// Look from the origin to the negative z axis
	GluSubsetf::lookAtf(0.0f, 0.0f, 150.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	//glMultMatrixf((GLfloat*)Trackball.getRotMatrix());
	/*glRotatef(RotX, 1, 0, 0);
	glRotatef(RotY, 0, 1, 0);
	glRotatef(RotZ, 0, 0, 1);*/
	//
	// Our dwarf
	//
	model.position[0] = 0.0f;
	model.position[1] = -20.0f;
	model.position[2] = 0.0f;
	model.orientation[0] = 0.0f;
	model.orientation[1] = -135.0f;
	model.orientation[2] = 0.0f;
	model.scale[0] = 4.0f;
	model.scale[1] = 4.0f;
	model.scale[2] = 4.0f;
	// update ...
	model.updatef(time);
	// ... and render the model
	model.renderf();
	glFlush();
}

void Game::updateGameOver(GLuint time, unsigned int Tick) {
	static GLuint elapsedTime = 0;
	elapsedTime += time;
	if (OldTime + 10 < Tick) {
		OldTime = Tick;
	}	
}

void Game::updateGamePlay(GLuint time, unsigned int Tick) {
	static GLuint elapsedTime = 0;
	elapsedTime += time;
	if (OldTime + 10 < Tick) {
		OldTime = Tick;
	}	

}

void Game::destroyGame(void) {
	TextureManager::deleteAllTextures();
	ModelManagerf::deleteAllModelCoresf();
}
#endif