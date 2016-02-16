#ifndef DECODECVIDEL_H
#define DECODECVIDEL_H
#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <basetsd.h>
#include "structure.h"
using namespace std;
//Windows

#define __STDC_CONSTANT_MACROS

#ifdef _WIN32
//Windows
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#ifdef __cplusplus
};
#endif
#endif


class DecodecVideo 
{
public:
	//DecodecVideo();	//默认H264
	DecodecVideo(AVCodecID CODEC_ID);
	DecodecVideo(AVCodecContext  *pCodecCtx);
	~DecodecVideo();

	bool decode(const uint8_t *source_Stream, AVFrame *out_pFrame,UINT32 stream_length);
	bool decode(AVCodecContext *avCodecContext,AVPacket *in_packet, AVFrame *out_pFrame);

private:
	bool setAVPacket(const uint8_t *source_Stream,const UINT32 &stream_length);
	bool decodeFrame(AVCodecContext *avCodecContext, AVPacket *in_packet,AVFrame *out_pFrame);
	
	operator bool();

	

private:
	void Init();
	void Init_Decode();

	std::shared_ptr<AVCodec>		createAVCodec_1(AVCodecID CODEC_ID);
	std::shared_ptr<AVCodecContext> createAVCodecContext_2(std::shared_ptr<AVCodec>	avCodec);
	void							openAvcodec_3(std::shared_ptr<AVCodec>  avCodec, std::shared_ptr<AVCodecContext> avCodecContext);
	void							createAVCodecParserContext();

	void free();
	void free_Decode();

	

private:

	AVCodecID								m_CODEC_ID_H264 = CODEC_ID_H264;
	std::shared_ptr<AVCodec>				m_avCodec;	//不用释放
	std::shared_ptr<AVCodecContext>			m_avCodecContext;
	std::shared_ptr<AVCodecParserContext>	m_avCodecParserContext;
	bool									m_successfulInit = true;	//初始化是否成功

	AVPacket								m_avPacket;	//是指针要用av_free_packet释放

};

















#endif

