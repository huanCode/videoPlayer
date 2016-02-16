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
	//��SDL_Init�ɶ�
	SDL_Quit();	
}




void GuiVideo::displayVideo(AVFrame *frame)
{
	//ˢ��
	//const void *data = (const void *)frame->data;
	SDL_UpdateTexture(m_texture.get(), 
					NULL,//�������صľ�����������ΪNULL��ʱ�������������
					frame->data[0], //��������
					frame->linesize[0]);	//һ���������ݵ��ֽ�����



	//SDL_RenderClear(m_renderer.get());
	//����
	SDL_RenderCopy(m_renderer.get(), m_texture.get(),
					NULL, //ѡ�����������һ�����������Ϊ���롣����ΪNULL��ʱ������������Ϊ����
					&m_rect); //ѡ����ȾĿ���һ�����������Ϊ���������ΪNULL��ʱ��������ȾĿ����Ϊ���
	
	//SDL_RenderCopy(m_renderer.get(), m_texture.get(),
	//	NULL, //ѡ�����������һ�����������Ϊ���롣����ΪNULL��ʱ������������Ϊ����
	//	&m_rect1); //ѡ����ȾĿ���һ�����������Ϊ���������ΪNULL��ʱ��������ȾĿ����Ϊ���


	//��ʾ
	SDL_RenderPresent(m_renderer.get());
}


void GuiVideo::displayVideo1(const uint8_t *pSrcStream, UINT32 dataLength)
{
	if (pSrcStream == nullptr)
	{
		return;
	}
	//ˢ��
	//const void *data = (const void *)frame->data;
	SDL_UpdateTexture(m_texture.get(),
		NULL,//�������صľ�����������ΪNULL��ʱ�������������
		pSrcStream, //��������
		m_rect.w);	//һ���������ݵ��ֽ�����



								//SDL_RenderClear(m_renderer.get());
								//����
	SDL_RenderCopy(m_renderer.get(), m_texture.get(),
		NULL, //ѡ�����������һ�����������Ϊ���롣����ΪNULL��ʱ������������Ϊ����
		&m_rect); //ѡ����ȾĿ���һ�����������Ϊ���������ΪNULL��ʱ��������ȾĿ����Ϊ���

				  //SDL_RenderCopy(m_renderer.get(), m_texture.get(),
				  //	NULL, //ѡ�����������һ�����������Ϊ���롣����ΪNULL��ʱ������������Ϊ����
				  //	&m_rect1); //ѡ����ȾĿ���һ�����������Ϊ���������ΪNULL��ʱ��������ȾĿ����Ϊ���


				  //��ʾ
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

	SDL_Window *pResult = SDL_CreateWindow(strTitle.c_str(),		//���ڱ���
						10,	//x
						10,	//y
						rect.width, rect.height,	//width,height
						SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);	//����

	
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
			-1, //�����ʼ������Ⱦ�豸�����������á� - 1�����ʼ��Ĭ�ϵ���Ⱦ�豸��
			SDL_RENDERER_ACCELERATED);	//ʹ��Ӳ������

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
									format, //YUV420,RGB24��
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

