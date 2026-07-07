#include "macOS.hpp"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

void* getNSWindowHandle()
{
    NSArray<NSWindow*>* windows = [NSApplication sharedApplication].windows;
    return windows[0];
}