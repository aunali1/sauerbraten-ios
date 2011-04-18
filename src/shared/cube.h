#ifndef __CUBE_H__
#define __CUBE_H__

#ifdef __GNUC__
#define gamma __gamma
#endif

#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#ifdef __GNUC__
#undef gamma
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <assert.h>
#ifdef __GNUC__
#include <new>
#else
#include <new.h>
#endif
#include <time.h>

#ifdef WIN32
  #define WIN32_LEAN_AND_MEAN
  #include "windows.h"
  #ifndef _WINDOWS
    #define _WINDOWS
  #endif
  #ifndef __GNUC__
    #include <eh.h>
    #include <dbghelp.h>
  #endif
  #define ZLIB_DLL
#endif

#ifndef STANDALONE
#include "SDL.h"
#include "SDL_image.h"

#define SCREENW 480
#define SCREENH 320
#define ESCAPEX 32
#define ESCAPEY 32
#define TOUCHMOVEX 64
#define TOUCHMOVEY 256
#define TOUCHFIREX 416
#define TOUCHFIREY 256
#define TOUCHSWAPX 448
#define TOUCHSWAPY 32
#define TOUCHSIZE 64
#define TOUCHRANGE 16
#define TOUCHSIZE2 32
#define TOUCHRANGE2 16

#define SUPPORTONSCREENBUTTON
//#define SUPPORTSOUND
//#define SUPPORTVBO
//#define SUPPORTSHADER
//#define SUPPORTCUBEMAP
//#define SUPPORTOCCLUSION
//#define SUPPORTFBO
//#define SUPPORTDRAWRANGE
//#define SUPPORTBLENDCOLOR
//#define SUPPORTRESCALE
#define GL_TEXTURE_RECTANGLE_ARB_ GL_TEXTURE_2D

#ifdef WIN32
#define GL_GLEXT_LEGACY
#define __glext_h__
#define NO_SDL_GLEXT
#include <SDL_opengl.h>
#undef __glext_h__
#include "gl/glext.h"
#elif WEBOS
#include "SDL.h"
#include "PDL.h"
#include <GLES/gl.h>
#else
#include "SDL_opengles.h"
#include <OpenGLES/es1/gl.h>
#include <OpenGLES/es1/glext.h>
#endif
#if WEBOS | __IPHONEOS__
#define glGenBuffers_ glGenBuffers
#define glBindBuffer_ glBindBuffer
#define glMapBuffer_ glMapBuffer
#define glUnmapBuffer_ glUnmapBuffer
#define glBufferData_ glBufferData
#define glBufferSubData_ glBufferSubData
#define glDeleteBuffers_ glDeleteBuffers
#define glGetBufferSubData_ glGetBufferSubData
#define glActiveTexture_ glActiveTexture
#define glClientActiveTexture_ glClientActiveTexture
#define glCheckFramebufferStatus_ glCheckFramebufferStatusOES
#define glFramebufferTexture2D_ glFramebufferTexture2DOES
#define glCheckFramebufferStatus_ glCheckFramebufferStatusOES
#define glGenRenderbuffers_ glGenRenderbuffersOES
#define glBindRenderbuffer_ glBindRenderbufferOES
#define glBindFramebuffer_ glBindFramebufferOES
#define glRenderbufferStorage_ glRenderbufferStorageOES
#define glDeleteRenderbuffers_ glDeleteRenderbuffersOES
#define glDeleteFramebuffers_ glDeleteFramebuffersOES
#define glActiveTexture_ glActiveTexture
#define glClientActiveTexture_ glClientActiveTexture
#define glGenFramebuffers_ glGenFramebuffersOES
#define glFramebufferRenderbuffer_ glFramebufferRenderbufferOES
#define glGenQueries_ glGenQueries
#define glBeginQuery_ glBeginQuery
#define glEndQuery_ glEndQuery
#define glClearDepth glClearDepthf
#define glDepthRange glDepthRangef
#define glBlitFramebuffer_ glBlitFramebuffer
#define glCompressedTexImage2D_ glCompressedTexImage2D

#define GL_ELEMENT_ARRAY_BUFFER_ARB GL_ELEMENT_ARRAY_BUFFER
#define GL_STATIC_DRAW_ARB GL_STATIC_DRAW
#define GL_ARRAY_BUFFER_ARB GL_ARRAY_BUFFER
#define GL_TEXTURE0_ARB GL_TEXTURE0
#define GL_TEXTURE1_ARB GL_TEXTURE1
#define GL_TEXTURE2_ARB GL_TEXTURE2
#define GL_TEXTURE3_ARB GL_TEXTURE3
#define GL_TEXTURE4_ARB GL_TEXTURE4
#define GL_TEXTURE_CUBE_MAP_ARB GL_TEXTURE_2D
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB GL_TEXTURE_2D
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB GL_TEXTURE_2D
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB GL_TEXTURE_2D
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB GL_TEXTURE_2D
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB GL_TEXTURE_2D
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB GL_TEXTURE_2D
#define GL_NONE GL_NONE_OES
#define GL_FRAMEBUFFER_EXT GL_FRAMEBUFFER_OES
#define GL_RENDERBUFFER_EXT GL_RENDERBUFFER_OES
#define GL_COLOR_ATTACHMENT0_EXT GL_COLOR_ATTACHMENT0_OES
#define GL_FRAMEBUFFER_COMPLETE_EXT GL_FRAMEBUFFER_COMPLETE_OES
#define GL_DEPTH_ATTACHMENT_EXT GL_DEPTH_ATTACHMENT_OES
#define GL_FRAMEBUFFER_COMPLETE_EXT GL_FRAMEBUFFER_COMPLETE_OES
#define GL_STENCIL_ATTACHMENT_EXT GL_STENCIL_ATTACHMENT_OES
#define GL_COMPRESSED_RGB_ARB GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
#define GL_COMPRESSED_RGBA_ARB GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
#define GL_REFLECTION_MAP_ARB GL_REFLECTION_MAP
#define GL_RESCALE_NORMAL_EXT GL_RESCALE_NORMAL
#define GL_DEPTH_COMPONENT16 GL_DEPTH_COMPONENT16_OES
#define GL_DEPTH_COMPONENT24 GL_DEPTH_COMPONENT24_OES
#define GL_DEPTH_COMPONENT GL_DEPTH_COMPONENT16_OES
#define GL_DEPTH_COMPONENT32 GL_DEPTH_COMPONENT32_OES
#define GL_RGB8 GL_RGB8_OES
#define GL_RGBA8 GL_RGBA8_OES
#endif
#endif

#include "enet.h"
#include <zlib.h>

#ifdef __sun__
#undef sun
#undef MAXNAMELEN
#ifdef queue
  #undef queue
#endif
#define queue __squeue
#endif

#include "tools.h"
#include "geom.h"
#include "ents.h"
#include "command.h"
#include "iengine.h"
#include "igame.h"
#endif