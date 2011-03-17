//
//  EAGLView.m
//
//  Created by Seth Robinson on 3/6/09.
//  For license info, check the license.txt file that should have come with this.
//


#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import "EAGLView.h"
#include "App.h"

#define USE_DEPTH_BUFFER 1

// A class extension to declare private methods
@interface EAGLView ()

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) NSTimer *animationTimer;

- (BOOL) createFramebuffer;
- (void) destroyFramebuffer;

@end


@implementation EAGLView

@synthesize context;
@synthesize animationTimer;
@synthesize animationInterval;


// You must implement this
+ (Class)layerClass {
	return [CAEAGLLayer class];
}

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder {

	if ((self = [super initWithCoder:coder]))
	{
		// Get the layer
		CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
		
		eaglLayer.opaque = YES;
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
		   [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
		
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		
		if (!context || ![EAGLContext setCurrentContext:context])
		{
			[self release];
			return nil;
		}
		
		animationInterval = 1.0 / 60.0;
	}
	
	
	if (!g_App.Init())
	{
		
		NSLog(@"Couldn't init app");
		[self release];
		return nil;
	}
	return self;
}


- (void)drawView 
{
		
	if (!viewRenderbuffer) return;
		
	[EAGLContext setCurrentContext:context];

	glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
	glViewport(0, 0, 320, 480);
	
	g_App.Update();
	g_App.Draw();
	
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	[context presentRenderbuffer:GL_RENDERBUFFER_OES];
}


- (void)layoutSubviews
{
	[EAGLContext setCurrentContext:context];
	[self destroyFramebuffer];
	[self createFramebuffer];
	[self drawView];
}


- (BOOL)createFramebuffer 
{
	
	glGenFramebuffersOES(1, &viewFramebuffer);
	glGenRenderbuffersOES(1, &viewRenderbuffer);
	
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	[context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
	
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
	
	if (USE_DEPTH_BUFFER) {
		glGenRenderbuffersOES(1, &depthRenderbuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
		glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
	}

	if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
		NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
		return NO;
	}
	
	return YES;
}


- (void)destroyFramebuffer {
	
	glDeleteFramebuffersOES(1, &viewFramebuffer);
	viewFramebuffer = 0;
	glDeleteRenderbuffersOES(1, &viewRenderbuffer);
	viewRenderbuffer = 0;
	
	if(depthRenderbuffer) {
		glDeleteRenderbuffersOES(1, &depthRenderbuffer);
		depthRenderbuffer = 0;
	}
}


- (void)startAnimation {
	self.animationTimer = [NSTimer scheduledTimerWithTimeInterval:animationInterval target:self selector:@selector(drawView) userInfo:nil repeats:YES];
}


- (void)stopAnimation {
	self.animationTimer = nil;
}


- (void)setAnimationTimer:(NSTimer *)newTimer {
	[animationTimer invalidate];
	animationTimer = newTimer;
}


- (void)setAnimationInterval:(NSTimeInterval)interval {
	
	animationInterval = interval;
	if (animationTimer) {
		[self stopAnimation];
		[self startAnimation];
	}
}


- (void)dealloc {
	
	[self stopAnimation];
	
	if ([EAGLContext currentContext] == context) {
		[EAGLContext setCurrentContext:nil];
	}
	
	[context release];	
	[super dealloc];
}

// Handles the start of a touch
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
  	// Enumerate through all the touch objects.
	NSUInteger touchCount = 0;
	for (UITouch *touch in touches)
	{
		CGPoint pt =[touch locationInView:self];
		ConvertCoordinatesIfRequired(pt.x, pt.y);
		GetMessageManager()->AddGUI(touchCount, MESSAGE_TYPE_GUI_CLICK_START,pt.x, pt.y);			
		touchCount++;  
	}	
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
  	// Enumerate through all the touch objects.
	NSUInteger touchCount = 0;
	for (UITouch *touch in touches)
	{
		CGPoint pt =[touch locationInView:self];
		ConvertCoordinatesIfRequired(pt.x, pt.y);
		GetMessageManager()->AddGUI(touchCount, MESSAGE_TYPE_GUI_CLICK_END,pt.x, pt.y);
		touchCount++;  
	}	
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
   // Enumerate through all the touch objects.
	NSUInteger touchCount = 0;
	for (UITouch *touch in touches)
	{
		CGPoint pt =[touch locationInView:self];
		ConvertCoordinatesIfRequired(pt.x, pt.y);
		GetMessageManager()->AddGUI(touchCount, MESSAGE_TYPE_GUI_CLICK_MOVE,pt.x, pt.y);
		touchCount++;  
	}	
}


@end
