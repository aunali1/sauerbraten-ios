/*
 *  MakUtils.mm
 *  Created by Seth Robinson on 3/6/09.
 *  For license info, check the license.txt file that should have come with this.
 *
 */

#import <cstdarg>
#include <string>
#include <sys/time.h>
#include <Foundation/Foundation.h>
#include <CoreFoundation/CoreFoundation.h>
//#include "BaseApp.h"

using namespace std;

void LogMsg(const char *lpFormat, ...)
{
	/*std::va_list argPtr ;
	va_start( argPtr, lpFormat ) ;
	NSLogv([NSString stringWithCString:lpFormat], argPtr) ;
	
	const int logSize = 4096;
	char buffer[logSize];
	memset ( (void*)buffer, 0, logSize );
	vsnprintf( buffer, logSize,  lpFormat, argPtr );
	GetBaseApp()->GetConsole()->AddLine(buffer);
	va_end(argPtr) ;*/
}


string GetBaseAppPath()
{
	
	CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        LogMsg("Can't change to Resources directory; something's seriously wrong\n");
		return "";
    }
    CFRelease(resourcesURL);

	return string(path)+"/";
	
	/*
	CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
	CFStringRef str = CFURLCopyF00ileSystemPath( resourcesURL, kCFURLPOSIXPathStyle );
	CFRelease(resourcesURL);
	char path[PATH_MAX];
	
	CFStringGetCString( str, path, FILENAME_MAX, kCFStringEncodingASCII );
	CFRelease(str);
	*/
}

string GetSavePath()
{

	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES); 
	return string([ [paths objectAtIndex:0] cStringUsingEncoding:NSUTF8StringEncoding])+"/";
	}

/*	
	+ (void) DeleteDocumentFile:(NSString*)filename
	{
			// deletes a file
			NSFileManager* FM = [NSFileManager defaultManager];
			NSString* path = [self MakeDocumentFile:filename];
			if (path) [FM removeItemAtPath:path error:NULL];
		}	
*/	
	
unsigned int GetSystemTimeTick()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec/1000 + tv.tv_sec*1000;
}

unsigned int timeGetTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec/1000 + tv.tv_sec*1000;
}


int GetYOffset()
{
	return 0;
}

#import <mach/mach.h>
#import <mach/mach_host.h>
 
//Snippet from http://landonf.bikemonkey.org/2008/12/06

unsigned int GetFreeMemory ()
 {
    mach_port_t host_port;
    mach_msg_type_number_t host_size;
    vm_size_t pagesize;
    
    host_port = mach_host_self();
    host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_page_size(host_port, &pagesize);        
 
    vm_statistics_data_t vm_stat;
              
    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS)
        LogMsg("Failed to fetch vm statistics");
 
    /* Stats in bytes */ 
	 natural_t mem_free = vm_stat.free_count * pagesize;
	 //natural_t mem_total = mem_used + mem_free;
	 //natural_t mem_used = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;
	 // LogMsg("Mem used: %u free: %u total: %u", mem_used, mem_free, mem_total);
   return mem_free;
}

