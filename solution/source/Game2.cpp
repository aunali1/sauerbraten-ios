#ifdef GAME2
#ifdef WIN32
#include <GLES/gl.h>
#else
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif
#include "Game2.h"

Game::~Game()
{
	RotX = 0;
	RotY = 0;
	RotZ = 0;
}

void Game::initGame()
{
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
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	//
	// Our dwarf
	//
	string Name;
	Name = GetBaseAppPath() + "ninja_blue.ms3d";
	ModelManagerf::getModelf(Name.c_str(), model);
	Name = GetBaseAppPath() + "ninja_idle.esad";
	AnimationLoaderf::loadAnimationf(Name.c_str(), model);
	//ModelManagerf::getModelf("cube.ms3d", model);
	model.setNextAnimationf(0, GL_TRUE, GL_TRUE);
	model.createBoundingSpheref(4);
	//
	// Texture for a simple ground
	//
	Name = GetBaseAppPath() + "ground.tga";
	TextureManager::getTextureName(Name.c_str(), groundTextureName);
}

void Game::reshapeGame(GLsizei width, GLsizei height)
{
	if (width == 0 || height == 0)
	{
		return;
	}
	// Set the viewport to maximum screen size
	glViewport(0, 0, width, height);
	// Set the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GluSubsetf::perspectivef(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 400.0f);
	// Restore the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Game::updateGame(GLuint time)
{
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
	// Smooth shading
	glShadeModel(GL_SMOOTH);
	// Enable the matrix mode
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();
	// Look from the origin to the negative z axis
	GluSubsetf::lookAtf(0.0f, 0.0f, 150.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	glMultMatrixf((GLfloat*)Trackball.getRotMatrix());
	/*glRotatef(RotX, 1, 0, 0);
	glRotatef(RotY, 0, 1, 0);
	glRotatef(RotZ, 0, 0, 1);*/
	//
	// Our ground
	//
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTextureName);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ground);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, groundTexture);
	glEnable(GL_TEXTURE_2D);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
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
	// Line
	if (model.intersectsBoundingSpheref(0, 0, 0, hit, start, end, GL_TRUE, -1))
	{
		Primitivesf::colorf(1.0f, 0.0f, 0.0f, 1.0f);
		Primitivesf::linef(start, hit);
		scanTime = 100.0f;
	}
	else
	{
		Primitivesf::colorf(0.0f, 1.0f, 0.0f, 1.0f);
		Primitivesf::linef(start, end);
		scanTime = 20.0f;
	}
	// Change line
	end[0] += xdirection * time / scanTime;
	end[2] += zdirection * time / scanTime;
	if (end[0] < -40.0f)
	{
		end[0] = -40.0f;
		xdirection = 0.0f;
		zdirection = 1.0f;
	}
	else if (end[2] > 40.0f)
	{
		end[2] = 40.0f;
		zdirection = -1.0f;

		end[1] += ydirection;
	}
	else if (end[2] < -40.0f)
	{
		end[2] = -40.0f;

		xdirection = 1.0f;
		zdirection = 0.0f;
	}
	else if (end[0] > 40.0f)
	{
		end[0] = 40.0f;

		xdirection = -1.0f;

		end[1] += ydirection;
	}

	if (end[1] > 20.0f)
	{
		end[1] = 20.0f;
		ydirection = -1.0f;
	}
	else if (end[1] < -20.0f)
	{
		end[1] = -20.0f;
		ydirection = 1.0f;
	}

	// Flush
	glFlush();
}

void Game::destroyGame(void)
{
	// Clean up model
	model.resetf();

	TextureManager::deleteAllTextures();
	ModelManagerf::deleteAllModelCoresf();
}

void Game::Touch(int OldX, int OldY, int NewX, int NewY) {
	if (abs(NewX - OldX) > abs(NewY - OldY)) {
		if (NewX > OldX) {
			RotY = RotY + 5;
		} else {
			RotY = RotY - 5;
		}
	} else {
		if (NewY > OldY) {
			RotX = RotX + 5;
		} else {
			RotX = RotX - 5;
		}
	}
}
#endif