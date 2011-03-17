//
//  RTAppAppDelegate.h
//  Created by Seth Robinson on 3/6/09.
//  For license info, check the license.txt file that should have come with this.
//


#import <UIKit/UIKit.h>

@class EAGLView;

@interface RTAppAppDelegate : NSObject <UIApplicationDelegate> {
	IBOutlet UIWindow *window;
	IBOutlet EAGLView *glView;
	IBOutlet UIViewController *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) EAGLView *glView;
@property (nonatomic, retain) UIViewController *viewController;


@end

