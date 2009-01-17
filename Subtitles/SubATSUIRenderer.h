//
//  SubATSUIRenderer.h
//  SSARender2
//
//  Created by Alexander Strange on 7/30/07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#import "SubRenderer.h"

@interface SubATSUIRenderer : SubRenderer {
	SubContext *context;
	unichar *ubuffer;
	UniCharArrayOffset *breakbuffer;
	ATSUTextLayout layout;
	float screenScaleX, screenScaleY, videoWidth, videoHeight;
	@public;
	CGColorSpaceRef srgbCSpace;
	TextBreakLocatorRef breakLocator;
}
-(SubATSUIRenderer*)initWithVideoWidth:(float)width videoHeight:(float)height;
-(SubATSUIRenderer*)initWithSSAHeader:(NSString*)header videoWidth:(float)width videoHeight:(float)height;
-(void)renderPacket:(NSString *)packet inContext:(CGContextRef)c width:(float)cWidth height:(float)cHeight;
@end

typedef SubATSUIRenderer *SubtitleRendererPtr;

#else
#include <QuickTime/QuickTime.h>

typedef void *SubtitleRendererPtr;

#endif

extern SubtitleRendererPtr SubInitForSSA(char *header, size_t headerLen, int width, int height);
extern SubtitleRendererPtr SubInitNonSSA(int width, int height);
extern CGColorSpaceRef SubGetColorSpace(SubtitleRendererPtr s);
extern void SubRenderPacket(SubtitleRendererPtr s, CGContextRef c, CFStringRef str, int cWidth, int cHeight);
extern void SubPrerollFromHeader(char *header, int headerLen);
extern void SubDisposeRenderer(SubtitleRendererPtr s);

#ifdef __cplusplus
}
#endif