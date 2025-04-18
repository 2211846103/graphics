#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>

#include <renderer/window.hpp>

using namespace engine::rendering;

#ifdef ENGINE_COMPILE_METAL

MetalWindow::MetalWindow(int width, int height, const char* name)
: _width(width), _height(height), _windowName(name), _window(nil), _contentView(nil), _metalLayer(nil) {}

MetalWindow::~MetalWindow() {
    if (_window) {
        [_window close];
        _window = nil;
    }
}

void MetalWindow::initWindow() {
    @autoreleasepool {

        NSApplication* app = [NSApplication sharedApplication];


        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];


        NSRect frame = NSMakeRect(0, 0, _width, _height);
        _window = [[NSWindow alloc] initWithContentRect:frame
                                               styleMask:(NSWindowStyleMaskTitled |
                                                          NSWindowStyleMaskClosable |
                                                          NSWindowStyleMaskResizable)
                                                 backing:NSBackingStoreBuffered
                                                   defer:NO];
        [_window setTitle:[NSString stringWithUTF8String:_windowName]];
        [_window makeKeyAndOrderFront:nil];

        _contentView = [_window contentView];
        _metalLayer = [CAMetalLayer layer];
        _metalLayer.device = MTLCreateSystemDefaultDevice();
        _metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        _metalLayer.framebufferOnly = YES;
        _metalLayer.drawableSize = CGSizeMake(_width, _height);
        _metalLayer.contentsScale = [[NSScreen mainScreen] backingScaleFactor];


        _contentView.wantsLayer = YES;
        _contentView.layer = _metalLayer;


        [NSApp finishLaunching];
        [NSApp activateIgnoringOtherApps:YES];
    }
}

bool MetalWindow::shouldClose() {
    return !_window || ![_window isVisible];
}

float MetalWindow::update() {
    @autoreleasepool {

        NSEvent* event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                             untilDate:[NSDate dateWithTimeIntervalSinceNow:0.01]
                                                inMode:NSDefaultRunLoopMode
                                               dequeue:YES])) {
            [NSApp sendEvent:event];
        }
        [NSApp updateWindows];
    }

    return 0.016f;
}

#endif
