//
//  MyViewController.m
//  Created by Seth Robinson on 3/6/09.
//  For license info, check the license.txt file that should have come with this.
//

//#define C_FORCE_LANDSCAPE_MODE 1

#import "MyViewController.h"
#import "EAGLView.h"
#include "App.h"

@implementation MyViewController

@synthesize glView;
@synthesize window;

// Implement viewDidLoad to do additional setup after loading the view.
- (void)viewDidLoad {
	glView.animationInterval = 1.0 / 60.0;
	[glView startAnimation];
    [super viewDidLoad];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
	
#ifdef C_FORCE_LANDSCAPE_MODE
	SetupScreenInfo(480, 320, 3); //3 is landscape, don't make me go find the real define
	return false;
#endif
	if (interfaceOrientation == 1 || interfaceOrientation == 3)
	{
		
		if (interfaceOrientation == 1 && m_latestOrientation == 3)
		{
			//they want to switch from landscape to portrait, prepare so the rotation effect look sright
			//glView.transform = CGAffineTransformIdentity;
			glView.transform = CGAffineTransformMakeRotation(3.14159/2);
			window.bounds = CGRectMake(0.0, 0.0, 320.0, 480.0);
			window.center = CGPointMake (160.0, 240.0);
			SetupScreenInfo(320, 480, 1);
			[glView drawView];

		}
			m_latestOrientation = interfaceOrientation;
		return YES;
	} else
	{
		return NO;
	}
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
	
	if (fromInterfaceOrientation == m_latestOrientation)
	{
		//special case at the start, when we force landscape mode
		window.bounds = CGRectMake(0.0, 0.0, 320.0, 480.0);
		window.center = CGPointMake (160.0, 240.0);
		
		glView.transform = CGAffineTransformIdentity;
		glView.bounds = CGRectMake(0.0, 0.0, 320.0, 480.0);
		glView.center = CGPointMake (160.0, 240.0);
		SetupScreenInfo(480, 320, m_latestOrientation);
		return;
		fromInterfaceOrientation = UIInterfaceOrientation(1);
	}

	if (fromInterfaceOrientation == 3)
	{
		LogMsg("Setting up for portrait");
		glView.transform = CGAffineTransformIdentity;
		window.bounds = CGRectMake(0.0, 0.0, 320.0, 480.0);
		window.center = CGPointMake (160.0, 240.0);
		SetupScreenInfo(window.bounds.size.width, window.bounds.size.height, m_latestOrientation);
		
	} else
	{
		glView.transform = CGAffineTransformIdentity;
		window.bounds = CGRectMake(0.0, 0.0, 320.0, 480.0);
		window.center = CGPointMake (160.0, 240.0);
		glView.bounds = CGRectMake(0.0, 0.0, 320.0, 480.0);
		glView.center = CGPointMake (160.0, 240.0);
		SetupScreenInfo(480, 320, m_latestOrientation);
		}
	
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
    // Release anything that's not essential, such as cached data
}


- (void)dealloc {
    [super dealloc];
}


@end
