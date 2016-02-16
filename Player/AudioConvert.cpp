#include "stdafx.h"
#include "AudioConvert.h"

AudioConvert::AudioConvert(AVCodecContext *pCodecCtx)
	:m_pCodecCtx(pCodecCtx)
	,m_buffer(std::vector<uint8_t>(MAX_AUDIO_FRAME_SIZE))
{

}

bool AudioConvert::InitAudio()
{
	//int out_buffer_size = av_samples_get_buffer_size(NULL, 
	//						m_pCodecCtx->channels,	//声道数
	//						m_pCodecCtx->frame_size,	//帧的大小
	//						m_pCodecCtx->sample_fmt, //采样格式
	//						1);	//

	//if (out_buffer_size < 0)
	//{
	//	printf("Error in av_samples_get_buffer_size()!\n");
	//	return false;
	//}

	//m_SwrContext = swr_alloc();

	//m_SwrContext = swr_alloc_set_opts(m_SwrContext, out_channel_layout, out_sample_fmt, out_sample_rate,
	//	in_channel_layout, pCodecCtx->sample_fmt, pCodecCtx->sample_rate, 0, NULL);
	return true;
}
