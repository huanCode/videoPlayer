#ifndef FRAMEOPERATION_H
#define FRAMEOPERATION_H
#pragma once
//对原始AVFrame进行格式转换
//如YUV420转RGB24等
//对帧进行拉伸，如1280*720拉伸为480*320等


#include <memory>
#include <basetsd.h>
#include "structure.h"
using namespace std;


extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
};



typedef struct _FrameProperty
{
	Rect			rect;
	AVPixelFormat	format;
}FrameProperty, PFrameProperty;


class FrameOperation 
{
public:
	FrameOperation(UINT32 width,UINT32 height, AVPixelFormat format);
	FrameOperation(UINT32 width, UINT32 height, AVPixelFormat srcFormat, AVPixelFormat dstFormat);
	FrameOperation(Rect rec, AVPixelFormat format);
	FrameOperation(Rect rec, AVPixelFormat srcFormat, AVPixelFormat dstFormat);



	FrameOperation(const FrameProperty &srcFrameProperty);
	std::shared_ptr<AVFrame> create_AVFrame_buffer();
	void scale(AVFrame *srcFrame, AVFrame *dstFrame);

	int getFrameSize(AVPixelFormat pix_fmt, int width, int height);
	operator bool();
private:

	bool create_SwsContext(const FrameProperty &srcFrameProperty,const FrameProperty &dstFrameProperty);
	bool create_SwsContext(const FrameProperty &frameProperty);

private:
	bool m_createSuccess = true;
	int  m_srcHeight = 0;
	std::shared_ptr<SwsContext> m_swsContext;
	FrameProperty		m_dstFrameProperty;
	FrameProperty		m_srcFrameProperty;

};






#endif
