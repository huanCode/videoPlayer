#include "stdafx.h"
#include "DecodecVideoModule.h"


DecodecVideoModule::DecodecVideoModule(UINT16 width, UINT16 height)
	:m_frameOperation(width, height, PIX_FMT_YUV420P)
	,m_decodecVideo(CODEC_ID_H264)
	,m_pSrcYUVFrame()
	,m_pDstYUVFrame()
{
	createYUVFrames();
}


DecodecVideoModule::DecodecVideoModule(Rect rect)
	:m_frameOperation(rect, PIX_FMT_YUV420P)
	, m_decodecVideo(CODEC_ID_H264)
	, m_pSrcYUVFrame()
	, m_pDstYUVFrame()
{
	createYUVFrames();
}

//bool DecodecVideoModule::decode(const uint8_t *pSrcStream, UINT32 streamLength, AVFrame *&p)
uint8_t* DecodecVideoModule::decode(const uint8_t *pSrcStream, UINT32 streamLength)
{
	bool sucess = m_decodecVideo.decode(pSrcStream, m_pSrcYUVFrame.get(), streamLength);
	if (sucess)
	{
		m_frameOperation.scale(m_pSrcYUVFrame.get(), m_pDstYUVFrame.get());
		
		return m_pDstYUVFrame.get()->data[0];
	}
	return NULL;
}

DecodecVideoModule::~DecodecVideoModule()
{
}

int DecodecVideoModule::getFrameSize()
{
	return m_frameOperation.getFrameSize(PIX_FMT_YUV420P, m_rect.width, m_rect.height);
}

void DecodecVideoModule::createYUVFrames()
{
	m_pSrcYUVFrame.reset(av_frame_alloc(), [](AVFrame *p) {av_frame_free(&p); });
	m_pDstYUVFrame = m_frameOperation.create_AVFrame_buffer();
}
