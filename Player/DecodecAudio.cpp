#include "stdafx.h"
#include "DecodecAudio.h"

DecodecAudio::DecodecAudio(AVCodecContext  *pCodecCtx)
	:m_pCodecCtx(pCodecCtx)
{

}


bool DecodecAudio::InitAudioDecode()
{
	m_pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);
	if (m_pCodec == NULL) {
		printf("Audio Codec not found.\n");
		return false;
	}


	if (avcodec_open2(m_pCodecCtx, m_pCodec, NULL) < 0) {
		printf("Could not open Audio codec.\n");
		return false;
	}



	return true;
}

DecodecAudio::~DecodecAudio()
{
}




bool DecodecAudio::decodeAudio(AVPacket *in_packet, AVFrame *out_pFrame)
{
//	int	decodeFinish = 0;
//	int result = 0;
//
//	result = avcodec_decode_audio4(m_pCodecCtx, out_pFrame, &decodeFinish, in_packet);
//	if (result < 0) {
//		printf("Error in decoding audio frame!\n");
//		return false;
//	}
//	if (decodeFinish > 0)
//	{
//		return true;	//OK
//	}
	
	return false;	//没有帧给解码
}
