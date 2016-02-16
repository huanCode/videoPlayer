#include "stdafx.h"
#include "GuiVideo.hpp"



GuiVideo::GuiVideo(Rect &rect)
{


	Init(string("live video"),rect, SDL_PIXELFORMAT_IYUV);

	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = rect.width;
	m_rect.h = rect.height;

	m_rect1.x = 110;
	m_rect1.y = 110;
	m_rect1.w = rect.width;
	m_rect1.h = rect.height;
}


GuiVideo::GuiVideo(UINT32 width, UINT32 height)
{
	Rect rect;
	rect.width = width;
	rect.height = height;

	Init(string("live video"), rect, SDL_PIXELFORMAT_IYUV);

	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = rect.width;
	m_rect.h = rect.height;

	m_rect1.x = 110;
	m_rect1.y = 110;
	m_rect1.w = rect.width;
	m_rect1.h = rect.height;
}


//GuiVideo::GuiVideo(UINT32 width, UINT32 height)
//{
//	m_rect.x = 0;
//	m_rect.y = 0;
//	m_rect.w = width;
//	m_rect.h = height;
//
//	Init(string("live video"), rect, SDL_PIXELFORMAT_IYUV);
//}

GuiVideo::~GuiVideo()
{
	//和SDL_Init成对
	SDL_Quit();	
}




void GuiVideo::displayVideo(AVFrame *frame)
{
	//刷新
	//const void *data = (const void *)frame->data;
	SDL_UpdateTexture(m_texture.get(), 
					NULL,//更新像素的矩形区域。设置为NULL的时候更新整个区域
					frame->data[0], //像素数据
					frame->linesize[0]);	//一行像素数据的字节数。



	//SDL_RenderClear(m_renderer.get());
	//复制
	SDL_RenderCopy(m_renderer.get(), m_texture.get(),
					NULL, //选择输入纹理的一块矩形区域作为输入。设置为NULL的时候整个纹理作为输入
					&m_rect); //选择渲染目标的一块矩形区域作为输出。设置为NULL的时候整个渲染目标作为输出
	
	//SDL_RenderCopy(m_renderer.get(), m_texture.get(),
	//	NULL, //选择输入纹理的一块矩形区域作为输入。设置为NULL的时候整个纹理作为输入
	//	&m_rect1); //选择渲染目标的一块矩形区域作为输出。设置为NULL的时候整个渲染目标作为输出


	//显示
	SDL_RenderPresent(m_renderer.get());
}


void GuiVideo::displayVideo1(const uint8_t *pSrcStream, UINT32 dataLength)
{
	if (pSrcStream == nullptr)
	{
		return;
	}
	//刷新
	//const void *data = (const void *)frame->data;
	SDL_UpdateTexture(m_texture.get(),
		NULL,//更新像素的矩形区域。设置为NULL的时候更新整个区域
		pSrcStream, //像素数据
		m_rect.w);	//一行像素数据的字节数。



								//SDL_RenderClear(m_renderer.get());
								//复制
	SDL_RenderCopy(m_renderer.get(), m_texture.get(),
		NULL, //选择输入纹理的一块矩形区域作为输入。设置为NULL的时候整个纹理作为输入
		&m_rect); //选择渲染目标的一块矩形区域作为输出。设置为NULL的时候整个渲染目标作为输出

				  //SDL_RenderCopy(m_renderer.get(), m_texture.get(),
				  //	NULL, //选择输入纹理的一块矩形区域作为输入。设置为NULL的时候整个纹理作为输入
				  //	&m_rect1); //选择渲染目标的一块矩形区域作为输出。设置为NULL的时候整个渲染目标作为输出


				  //显示
	SDL_RenderPresent(m_renderer.get());

}


void GuiVideo::Init(const string &strTitle, const Rect &rect, Uint32 format)
{
	SDL_Window *pWindow = create_window(strTitle, rect);
	SDL_Renderer *pRenderer = create_Renderer(pWindow);
	bool success = create_Texture(pRenderer,format,rect);
	if (!success)
	{
	}

}

void GuiVideo::InitAudio()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return;
	}
}

SDL_Window* GuiVideo::create_window(const string &strTitle, const Rect &rect)
{

	SDL_Window *pResult = SDL_CreateWindow(strTitle.c_str(),		//窗口标题
						10,	//x
						10,	//y
						rect.width, rect.height,	//width,height
						SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);	//属性

	
	if (pResult)
	{
		m_window.reset(pResult,[](SDL_Window *p) {});	
	}
	else
	{
		cout <<"SDL_CreateWindow is error!"<< endl;
		m_createSuccess = false;
	}
	return pResult;
}

SDL_Renderer* GuiVideo::create_Renderer(SDL_Window *pWindow)
{


	SDL_Renderer	*pResult = NULL;
	if (m_createSuccess)
	{
		pResult = SDL_CreateRenderer(pWindow,
			-1, //打算初始化的渲染设备的索引。设置“ - 1”则初始化默认的渲染设备。
			SDL_RENDERER_ACCELERATED);	//使用硬件加速

		if (pResult)
		{
			m_renderer.reset(pResult, [](SDL_Renderer *p) {});
		}
		else
		{
			cout << "SDL_CreateRenderer() is error!" << endl;
			m_createSuccess = false;
		}
	}
	return pResult;
}

bool GuiVideo::create_Texture(SDL_Renderer *pRenderer, Uint32 format, const Rect &rect)
{
	
	if (m_createSuccess)
	{
		SDL_Texture	*pResult = NULL;
		pResult = SDL_CreateTexture(pRenderer,
									format, //YUV420,RGB24等
									SDL_TEXTUREACCESS_STREAMING, 
									rect.width, rect.height);

		if (pResult)
		{
			m_texture.reset(pResult, [](SDL_Texture *p) {});
		}
		else
		{
			cout << "SDL_CreateTexture is error!" << endl;
			m_createSuccess = false;
		}

	}
	return true;
}

