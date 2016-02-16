#ifndef DECODECAUDIO_H
#define DECODECAUDIO_H
#include "Decode.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
};

class DecodecAudio
{
public:
	DecodecAudio(AVCodecContext  *pCodecCtx);
	bool InitAudioDecode();
	~DecodecAudio();
	bool decodeAudio(AVPacket *in_packet, AVFrame *out_pFrame);
private:
	AVCodecContext	*m_pCodecCtx;
	AVCodec			*m_pCodec;

	

};




#endif
