#pragma once
#ifndef GUIVIDEO_H
#define GUIVIDEO_H
#include <memory>
#include <basetsd.h>
#include <string>
#include <iostream>
//#include "SDL_thread.h"

#include "structure.h"
using namespace std;

extern "C"
{
#include "libavcodec/avcodec.h"
#include "SDL.h"
};


class GuiVideo 
{
public:
	GuiVideo(Rect &rect);
	GuiVideo(UINT32 width,UINT32 height);
	//GuiVideo(UINT32 width,UINT32 height);
	~GuiVideo();
	void displayVideo(AVFrame *frame);
	void displayVideo1(const uint8_t *pSrcStream, UINT32 streamLength);

private:
	void Init(const string &strTitle, const Rect &rect, Uint32 format);

	void InitAudio();
	SDL_Window* create_window(const string &strTitle, const Rect &rect);
	SDL_Renderer*	create_Renderer(SDL_Window *pWindow);
	bool create_Texture(SDL_Renderer *pRenderer, Uint32 format,const Rect &rect);
private:
	bool							m_createSuccess = true;
	SDL_Rect						m_rect;
	std::shared_ptr<SDL_Window>		m_window;	//要在这个区域显示帧
	std::shared_ptr<SDL_Renderer>	m_renderer;	//把m_texture渲染到SDL_Window
	std::shared_ptr<SDL_Texture>	m_texture;	//显示yuv，rgb
	SDL_Rect						m_rect1;
};



#endif
