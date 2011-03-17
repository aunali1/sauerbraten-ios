//
//  RTAppAppDelegate.m
//  Created by Seth Robinson on 3/6/09.
//  For license info, check the license.txt file that should have come with this.
//


#import "RTAppAppDelegate.h"
#import "EAGLView.h"

@implementation RTAppAppDelegate

@synthesize window;
@synthesize viewController;
@synthesize glView;

- (void)applicationDidFinishLaunching:(UIApplication *)application {
	
	[window addSubview:viewController.view];
	[window makeKeyAndVisible];
}


- (void)applicationWillResignActive:(UIApplication *)application {
	glView.animationInterval = 1.0 / 5.0;
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
	glView.animationInterval = 1.0 / 60.0;
}

- (void)dealloc {
	[window release];
	[super dealloc];
}

@end
