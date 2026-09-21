// videosdl.cpp (Versión Segura para WebAssembly / Multihilo)
#include "pch.h"
#include <SDL.h>
#include "video_shared.h"

RGB* video_buffer = nullptr;
int xfb_width = 0;
int xfb_height = 0;
bool xfb_frame_ready = false;;

using namespace Debug;

bool VideoOutOpen(HWConfig* config, int width, int height, RGB** gfxbuf)
{
    xfb_width = width;
    xfb_height = height;

    if (video_buffer != nullptr) {
        delete[] video_buffer;
    }

    video_buffer = new RGB[width * height];
    memset(video_buffer, 0, sizeof(RGB) * width * height);

    *gfxbuf = video_buffer;
    return true;
}

void VideoOutClose()
{
    if (video_buffer != nullptr) {
        delete[] video_buffer;
        video_buffer = nullptr;
    }
    xfb_frame_ready = false;
}

void VideoOutRefresh()
{   
    xfb_frame_ready = true;
}

void VideoOutResize(int width, int height)
{
    if (width != xfb_width || height != xfb_height) 
    {
        xfb_width = width;
        xfb_height = height;
		
		printf("Debug XFB -> width: %d, height: %d\n", xfb_width, xfb_height);
        fflush(stdout);
        
        if (video_buffer != nullptr) {
            delete[] video_buffer;
        }
        video_buffer = new RGB[width * height];
        memset(video_buffer, 0, sizeof(RGB) * width * height);
    }
}