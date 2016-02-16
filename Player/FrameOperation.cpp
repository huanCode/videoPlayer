#include "stdafx.h"
#include "FrameOperation.hpp"
FrameOperation::FrameOperation(UINT32 width, UINT32 height, AVPixelFormat format)
{
	m_dstFrameProperty.rect.width  = width;
	m_dstFrameProperty.rect.height = height;
	m_dstFrameProperty.format	   = format;

	m_srcFrameProperty = m_dstFrameProperty;
	create_SwsContext(m_dstFrameProperty);
}



FrameOperation::FrameOperation(UINT32 width, UINT32 height, AVPixelFormat srcFormat, AVPixelFormat dstFormat)
{
	m_dstFrameProperty.rect.width = width;
	m_dstFrameProperty.rect.height = height;
	m_dstFrameProperty.format = srcFormat;

	m_srcFrameProperty = m_dstFrameProperty;
	m_srcFrameProperty.format = dstFormat;
	create_SwsContext(m_dstFrameProperty, m_srcFrameProperty);
}


FrameOperation::FrameOperation(Rect rec, AVPixelFormat format)
{
	m_srcFrameProperty.rect = rec;
	m_srcFrameProperty.format = format;

	m_dstFrameProperty = m_dstFrameProperty;
	m_dstFrameProperty.rect.width = 320;
	m_dstFrameProperty.rect.height = 240;
	create_SwsContext(m_srcFrameProperty,m_dstFrameProperty);
}


FrameOperation::FrameOperation(Rect rec, AVPixelFormat srcFormat, AVPixelFormat dstFormat)
{
	m_dstFrameProperty.rect = rec;
	m_dstFrameProperty.format = srcFormat;

	m_srcFrameProperty = m_dstFrameProperty;

	m_srcFrameProperty.format = dstFormat;
	create_SwsContext(m_dstFrameProperty, m_srcFrameProperty);
}



FrameOperation::FrameOperation(const FrameProperty &frameProperty)
	:m_dstFrameProperty(frameProperty)
{

	create_SwsContext(frameProperty);
}

FrameOperation::operator bool()
{
	return m_createSuccess;
}


bool FrameOperation::create_SwsContext(const FrameProperty &srcFrameProperty, const FrameProperty &dstFrameProperty)
{
	const Rect			&srcRect			= srcFrameProperty.rect;
	const AVPixelFormat &src_pix_fmt		= srcFrameProperty.format;
	const Rect			&dstRect			= dstFrameProperty.rect;
	const AVPixelFormat &dst_pix_fmt		= dstFrameProperty.format;


	m_srcHeight = srcRect.height;

	SwsContext *swsContext = sws_getContext(srcRect.width, srcRect.height,	//源
							src_pix_fmt,						//源帧的格式
							dstRect.width, dstRect.height,	//目
							dst_pix_fmt,				//要转换的成格式
							SWS_BICUBIC, NULL, NULL, NULL);
	if (swsContext)
	{
		m_swsContext.reset(swsContext, [](SwsContext *p) {
			sws_freeContext(p);
		});
	}
	else
	{
		m_createSuccess = false;
		return false;
	}
	return true;
}

bool FrameOperation::create_SwsContext(const FrameProperty &frameProperty)
{
	return create_SwsContext(frameProperty, frameProperty);
}


void FrameOperation::scale(AVFrame *srcFrame, AVFrame *dstFrame)
{
	int i = sws_scale(m_swsContext.get(),
			(const uint8_t* const*)srcFrame->data, srcFrame->linesize, 0, m_srcHeight,
			dstFrame->data, dstFrame->linesize);
}

int FrameOperation::getFrameSize(AVPixelFormat pix_fmt,int width,int height)
{
	return avpicture_get_size(pix_fmt, width, height);
}

std::shared_ptr<AVFrame> FrameOperation::create_AVFrame_buffer()
{

	const Rect &rect		= m_dstFrameProperty.rect;
	AVPixelFormat pix_fmt	= m_dstFrameProperty.format;

	uint8_t *out_buffer = NULL;
	AVFrame	*pFrameYUV = av_frame_alloc();

	size_t size = avpicture_get_size(pix_fmt, rect.width, rect.height);		//求这种格式的要的内存大小
	out_buffer = (uint8_t *)av_malloc(size);	//分配内存
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, pix_fmt, rect.width, rect.height);	//和AVFrame绑定

	return std::shared_ptr<AVFrame>(pFrameYUV, [](AVFrame *p) {
		av_frame_free(&p);
	});
}

