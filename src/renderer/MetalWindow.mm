#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>

#include <renderer/window.hpp>
#include <iostream>


using namespace engine::rendering;

#ifdef ENGINE_COMPILE_METAL

MetalWindow::MetalWindow(int width, int height, const char* name)
: _width(width), _height(height), _windowName(name), _window(nil), _contentView(nil),
  _metalLayer(nil), _device(nil), _commandQueue(nil), _shaderLibrary(nil), _pipelineState(nil), shaderLoaded(false) {}

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

        _device = MTLCreateSystemDefaultDevice();
        _commandQueue = [_device newCommandQueue];

        _metalLayer = [CAMetalLayer layer];
        _metalLayer.device = _device;
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

void MetalWindow::loadShader(const std::string& source) {
    if (shaderLoaded) return;

    std::cout << "Loading MetalShader" << std::endl;

    @autoreleasepool {
        NSError* error = nil;

        NSString* shaderSrc = [NSString stringWithUTF8String:source.c_str()];
        _shaderLibrary = [_device newLibraryWithSource:shaderSrc options:nil error:&error];

        if (!_shaderLibrary) {
            std::cout << "ERROR::METAL::SHADER::COMPILATION_FAILED\n" << error.localizedDescription.UTF8String << std::endl;
            return;
        }

        id<MTLFunction> vertexFunction = [_shaderLibrary newFunctionWithName:@"vertex_main"];
        id<MTLFunction> fragmentFunction = [_shaderLibrary newFunctionWithName:@"fragment_main"];

        if (!vertexFunction || !fragmentFunction) {
            std::cout << "ERROR::METAL::SHADER::FUNCTION_NOT_FOUND" << std::endl;
            return;
        }

        MTLRenderPipelineDescriptor* pipelineDesc = [[MTLRenderPipelineDescriptor alloc] init];
        pipelineDesc.vertexFunction = vertexFunction;
        pipelineDesc.fragmentFunction = fragmentFunction;
        pipelineDesc.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;

        _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineDesc error:&error];

        if (!_pipelineState) {
            std::cout << "ERROR::METAL::PIPELINE_STATE::FAILED\n" << error.localizedDescription.UTF8String << std::endl;
            return;
        }

        shaderLoaded = true;
    }
}

void MetalWindow::useShader(id<MTLRenderCommandEncoder> encoder) {
    if (_pipelineState && encoder) {
        [encoder setRenderPipelineState:_pipelineState];
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
