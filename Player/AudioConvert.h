#ifndef AUDIOCONVERT_H
#define AUDIOCONVERT_H
#include <vector>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/channel_layout.h"
#include "libswresample/swresample.h"
};


#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio

class AudioConvert
{
public:
	AudioConvert(AVCodecContext  *pCodecCtx);
	bool InitAudio();

private:
	AVCodecContext  *m_pCodecCtx;
	std::vector<uint8_t>		m_buffer;
	SwrContext			*m_SwrContext;
	
};

#endif