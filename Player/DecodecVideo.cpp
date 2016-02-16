#include "stdafx.h"
#include "DecodeVideo.hpp"

//DecodecVideo::DecodecVideo()
//{
//	Init();
//}


DecodecVideo::DecodecVideo(AVCodecID CODEC_ID)
	:m_CODEC_ID_H264(CODEC_ID)
{
	Init();
}


DecodecVideo::DecodecVideo(AVCodecContext  *pCodecCtx)
{
	m_avCodecContext.reset((pCodecCtx),
		[](AVCodecContext *p)
	{
		avcodec_close(p);
		av_free(p);
	});

	if (!m_avCodecContext)
	{
		m_successfulInit = false;
	}

	m_avCodec.reset(avcodec_find_decoder(pCodecCtx->codec_id),	//创建 CODEC_ID一般为H264
		[](AVCodec *p) {});	//不需要在这里释放

	if (!m_avCodec)
	{
		m_successfulInit = false;
	}


	if (avcodec_open2(m_avCodecContext.get(), m_avCodec.get(), NULL) < 0)
	{
		cout << "Could not open codec" << endl;
		m_successfulInit = false;
	}
}


DecodecVideo::~DecodecVideo()
{
	
}

DecodecVideo::operator bool()
{
	return m_successfulInit;
}

void DecodecVideo::free()
{
	free_Decode();
}


void DecodecVideo::free_Decode()
{
	m_avCodecContext.reset();
	m_avCodecParserContext.reset();

}


void DecodecVideo::Init()
{
	Init_Decode();

	if (!m_successfulInit)
	{
		free();
	}

	av_init_packet(&m_avPacket);
	
}



void DecodecVideo::Init_Decode()
{
	avcodec_register_all();
	

	shared_ptr<AVCodec>			avCodec			= createAVCodec_1(m_CODEC_ID_H264);
	shared_ptr<AVCodecContext>	avCodecContext	= createAVCodecContext_2(avCodec);


	openAvcodec_3(avCodec, avCodecContext);
	createAVCodecParserContext();


}


std::shared_ptr<AVCodec> DecodecVideo::createAVCodec_1(AVCodecID CODEC_ID)
{
	std::shared_ptr<AVCodec> result(avcodec_find_decoder(CODEC_ID),	//创建 CODEC_ID一般为H264
									[](AVCodec *p) {});	//不需要在这里释放
	
	if (result)
	{
		m_avCodec = result;
	}
	else
	{
		cout << "find not decode" << endl;
		m_successfulInit = false;
	}

	return result;
}

shared_ptr<AVCodecContext> DecodecVideo::createAVCodecContext_2(shared_ptr<AVCodec>	 avCodec)
{
	std::shared_ptr<AVCodecContext> result;

	if (m_successfulInit)
	{
		result.reset(avcodec_alloc_context3(avCodec.get()),
												[](AVCodecContext *p)
												{
													avcodec_close(p);
													av_free(p);
												});

		if (result)
		{
			m_avCodecContext = result;
			m_successfulInit = true;
		}
		else
		{
			cout << "Could not allocate video codec context" << endl;
			m_successfulInit = false;
		}
	}

	return result;
}

void DecodecVideo::openAvcodec_3(std::shared_ptr<AVCodec>  avCodec, std::shared_ptr<AVCodecContext> avCodecContext)
{
	if (m_successfulInit)
	{
		//av_dict_set(&opts, "b", "2.5M", 0);
		if (avcodec_open2(avCodecContext.get(), avCodec.get(), NULL) < 0)
		{
			cout << "Could not open codec" << endl;
			m_successfulInit = false;
		}
	}

}

void DecodecVideo::createAVCodecParserContext()
{
	if (m_successfulInit)
	{
		m_avCodecParserContext.reset(av_parser_init(m_CODEC_ID_H264),
									[](AVCodecParserContext *p) 
									{
										av_parser_close(p);
									});

		if (m_avCodecParserContext.get() == nullptr)
		{
			cout << "create AVCodecParserContext is error!" << endl;
			m_successfulInit = false;
		}
	}
}





bool DecodecVideo::setAVPacket(const uint8_t *source_Stream, const UINT32 &stream_length)
{

	if (stream_length > 0)
	{
		int result = 0;
		do 
		{
			
			result = av_parser_parse2(m_avCodecParserContext.get(), m_avCodecContext.get(),
				&m_avPacket.data, &m_avPacket.size,		//source
				source_Stream, stream_length,
				AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);

			if (result == 23)
			{
				break;
			}


		} while (result > 0);



		if (m_avPacket.size)
		{
			cout << "av_parser_parse2 :" << m_avPacket.size << endl;
			//cout << "显示顺序：" << m_avCodecParserContext->pts << endl;
			switch (m_avCodecParserContext->pict_type) 
			{
				case AV_PICTURE_TYPE_I: printf("Type:【I】\n"); break;
				case AV_PICTURE_TYPE_P: printf("Type:P\n"); break;
				case AV_PICTURE_TYPE_B: printf("Type:B\n"); break;
					
				default: printf("Type:Other\n"); break;
			}


			return true;
		}
	}

	return false;
}


bool DecodecVideo::decodeFrame(AVCodecContext *avCodecContext,AVPacket *in_packet,AVFrame *out_pFrame)
{
	int result;
	int decodeFrameResult;

	result = avcodec_decode_video2(m_avCodecContext.get(),
									out_pFrame,
									&decodeFrameResult,	//大与0，就是解码帧成功
									in_packet);
	av_free_packet(in_packet);
	bool successful = true;
	if (result >= 0)
	{
		if (decodeFrameResult >= 1)
		{
			cout << "解码成功，是完整帧！" << endl;
		}
		else
		{
			cout << "解码成功，不是完整帧！" << endl;
			successful = false;
			//cout << "解码后长度：" << result << endl;
		}
		//解码成功
		

	}
	else
	{
		cout << "avcodec_decode_video2 is error" << endl;
		successful = false;
	}

	return successful;

}


bool DecodecVideo::decode(const uint8_t *source_Stream, AVFrame *out_pFrame, UINT32 stream_length)
{
	if (setAVPacket(source_Stream, stream_length))
	{
		return decodeFrame(m_avCodecContext.get(),&m_avPacket,out_pFrame);
	}
	return false;
}


bool DecodecVideo::decode(AVCodecContext *avCodecContext,AVPacket *in_packet, AVFrame *out_pFrame)
{
	return decodeFrame(avCodecContext,in_packet,out_pFrame);
}





