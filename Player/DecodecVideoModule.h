#ifndef DOCODECVIDEOMODULE_H
#define DOCODECVIDEOMODULE_H
#include "FrameOperation.hpp"
#include "DecodeVideo.hpp"
#include "structure.h"

class DecodecVideoModule
{
public:
	DecodecVideoModule(UINT16 width, UINT16 height);
	DecodecVideoModule(Rect rect);
	uint8_t* decode(const uint8_t *pSrcStream, UINT32 streamLength);
	//bool decode(const uint8_t *pSrcStream, UINT32 streamLength, AVFrame *&p);

	~DecodecVideoModule();
	int getFrameSize();
private:
	void createYUVFrames();

private:
	FrameOperation	m_frameOperation;
	DecodecVideo	m_decodecVideo;
	Rect			m_rect;

	std::shared_ptr<AVFrame>	m_pSrcYUVFrame;
	std::shared_ptr<AVFrame>	m_pDstYUVFrame;
};



#endif