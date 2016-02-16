// Player.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "GuiVideo.hpp"

#include "DecodecVideoModule.h"
#include "CameraRemote.hpp"
//#include <mutex>
//#include <thread>
using namespace std;
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
#include "SDL.h"
};

#define MAX_AUDIO_FRAME_SIZE 392000 
void  fill_audio(void *udata, Uint8 *stream, int len);

void FileVideo();
int ss();



int _tmain(int argc, _TCHAR* argv[])
{
	//Save2();


	/*CameraRemote ca(1280, 720);
	GuiVideo	 gui(320, 240);
	std::function<void(const uint8_t*, UINT32)> display = std::bind(&GuiVideo::displayVideo1, &gui, std::placeholders::_1, std::placeholders::_2);
	ca.createReadThread(string("192.168.102.70"), 5548, display);
*/


	//ss();
	FileVideo();

    return 1;
}



void CaptureCamera()
{
	//avdevice_register_all();
	////avformat_network_init();
	//AVFormatContext *pFormatCtx = avformat_alloc_context();
	////AVInputFormat *ifmt = av_find_input_format("dshow");
	//if (avformat_open_input(&pFormatCtx, "rtp://192.168.102.31:5548", NULL, NULL) != 0) {
	//	printf("Couldn't open input stream.\n");
	//	return;
	//}

	//if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	//{
	//	printf("Couldn't find stream information.\n");
	//	return;
	//}



	//int videoindex = -1;
	//for (int i = 0; i < pFormatCtx->nb_streams; i++)
	//	if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
	//	{
	//		videoindex = i;
	//		break;
	//	}

	//if (videoindex == -1)
	//{
	//	printf("Couldn't find a video stream.\n");
	//	return;
	//}
	//
	//DecodecVideo d(CODEC_ID_RAWVIDEO);
	////DecodecVideo d(pFormatCtx->streams[videoindex]->codec->codec_id);
	//UINT32 width = pFormatCtx->streams[videoindex]->codec->width;
	//UINT32 height = pFormatCtx->streams[videoindex]->codec->height;
	//Rect rect = { width,height };
	//GuiVideo gui(rect);
	//AVPacket *packet = (AVPacket *)av_malloc(sizeof(AVPacket));

	//AVFrame *pFrame, *pFrameYUV;
	//pFrame = av_frame_alloc();
	//pFrameYUV = av_frame_alloc();
	//FrameProperty frameProperty = { rect ,PIX_FMT_YUV420P };
	//FrameOperation frameOperation(frameProperty);
	//
	//while (true)
	//{
	//	if (av_read_frame(pFormatCtx, packet) >= 0) 
	//	{
	//		//d.decode(packet, pFrame);
	//	/*	frameOperation.scale(pFrame, pFrameYUV);
	//		gui.show(pFrameYUV);*/
	//	}
	//}

}

static  Uint8  *audio_chunk;
static  Uint32  audio_len;
static  Uint8  *audio_pos;

void  fill_audio(void *udata, Uint8 *stream, int len) {
	//SDL 2.0
	SDL_memset(stream, 0, len);
	if (audio_len == 0)		/*  Only  play  if  we  have  data  left  */
		return;
	len = (len > audio_len ? audio_len : len);	/*  Mix  as  much  data  as  possible  */

	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	audio_pos += len;
	audio_len -= len;
}
void FileVideo()
{
	av_register_all();
	avformat_network_init();
	AVFormatContext *pFormatCtx = avformat_alloc_context();

	if (avformat_open_input(&pFormatCtx, "Friends.mkv", NULL, NULL) != 0) {
		printf("Couldn't open input stream.\n");
		return;
	}

	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		printf("Couldn't find stream information.\n");
		return;
	}


	int videoindex = -1;
	for (int i = 0; i < pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoindex = i;
			break;
		}

	if (videoindex == -1) {
		printf("Didn't find a video stream.\n");
		return;
	}


	AVCodecContext	*pCodecCtx;
	pCodecCtx = pFormatCtx->streams[videoindex]->codec;

	AVCodec			*pCodec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) {
		printf("Codec not found.\n");
		return;
	}

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec.\n");
		return;
	}

	av_dump_format(pFormatCtx, 0, "Friends.mkv", 0);

	//DecodecVideo d(pFormatCtx->streams[videoindex]->codec->codec_id);
	DecodecVideo d(pCodecCtx);

	UINT16 width = pFormatCtx->streams[videoindex]->codec->width;
	UINT16 height = pFormatCtx->streams[videoindex]->codec->height;
	Rect rect = { width,height };
	GuiVideo gui(rect);


	AVPacket *packet = (AVPacket *)av_malloc(sizeof(AVPacket));

	AVFrame *pFrame;
	pFrame = av_frame_alloc();


	FrameProperty frameProperty = { rect ,PIX_FMT_YUV420P };
	FrameOperation frameOperation(frameProperty);

	std::shared_ptr<AVFrame> dstFrame = frameOperation.create_AVFrame_buffer();

	int lt = 0;
	int ret, got_picture;

	while (true)
	{
		if (av_read_frame(pFormatCtx, packet) >= 0)
		{

			if (packet->stream_index == videoindex)
			{
				if (d.decode(pFormatCtx->streams[videoindex]->codec, packet, pFrame))
				{
					frameOperation.scale(pFrame, dstFrame.get());
					gui.displayVideo(dstFrame.get());
				}
			}
			else
			{
				cout << "��Ƶ" << endl;
			}
		}
	}




}


//void FileVideo()
//{
//	av_register_all();
//	avformat_network_init();
//	AVFormatContext *pFormatCtx = avformat_alloc_context();
//
//
//	//char url[] = "WavinFlag.aac";
//	//char url[] = "Friends.mkv";
//	//01.flv
//	if (avformat_open_input(&pFormatCtx, "Friends.mkv", NULL, NULL) != 0) {
//		printf("Couldn't open input stream.\n");
//		return;
//	}
//
//	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
//		printf("Couldn't find stream information.\n");
//		return;
//	}
//
//
//	int audioStream = -1;
//	for (int i = 0; i < pFormatCtx->nb_streams; i++)
//		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
//			audioStream = i;
//			break;
//		}
//
//	if (audioStream == -1) {
//		printf("Didn't find a video stream.\n");
//		return;
//	}
//
//
//	AVCodecContext	*pCodecCtx;
//	pCodecCtx = pFormatCtx->streams[audioStream]->codec;
//	
//	AVCodec			*pCodec;
//	
//	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
//	if (pCodec == NULL) {
//		printf("Codec not found.\n");
//		return;
//	}
//
//	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
//		printf("Could not open codec.\n");
//		return;
//	}
//
//
//
//	if (SDL_Init(SDL_INIT_AUDIO)) {
//		printf("Could not initialize SDL - %s\n", SDL_GetError());
//		return;
//	}
//
//	uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
//	AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
//	int out_sample_rate = 44100;
//	int out_nb_samples = 1536;
//	
//	int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
//	int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);
//	uint8_t	 *out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
//
//
//	//SDL_AudioSpec
//	SDL_AudioSpec wanted_spec;
//	wanted_spec.freq = out_sample_rate;
//	wanted_spec.format = AUDIO_S16SYS;
//	wanted_spec.channels = out_channels;
//	wanted_spec.silence = 0;
//	wanted_spec.samples = out_nb_samples;	//�����ʴ�С
//	wanted_spec.callback = fill_audio;
//	wanted_spec.userdata = pCodecCtx;
//
//	
//
//	if (SDL_OpenAudio(&wanted_spec, NULL) < 0) {
//		printf("can't open audio.\n");
//		return;
//	}
//
//	//FIX:Some Codec's Context Information is missing
//	int64_t in_channel_layout = av_get_default_channel_layout(pCodecCtx->channels);
//	struct SwrContext *au_convert_ctx = swr_alloc();
//	
//	au_convert_ctx = swr_alloc_set_opts(au_convert_ctx,
//
//		out_channel_layout,
//		out_sample_fmt,
//		out_sample_rate,
//
//		in_channel_layout,
//		pCodecCtx->sample_fmt,
//		pCodecCtx->sample_rate, 0, NULL);
//	swr_init(au_convert_ctx);
//
//
//	AVPacket		*packet = (AVPacket *)av_malloc(sizeof(AVPacket));
//	av_init_packet(packet);
//
//	AVFrame			*pFrame = av_frame_alloc();
//
//	int got_picture;
//	int ret;
//
//
//	
//	
//	int index = 0;
//	while (av_read_frame(pFormatCtx, packet) >= 0) 
//	{
//		if (packet->stream_index == audioStream) 
//		{
//			ret = avcodec_decode_audio4(pCodecCtx, pFrame, &got_picture, packet);
//			if (ret < 0) 
//			{
//				printf("Error in decoding audio frame.\n");
//				return;
//			}
//			if (got_picture > 0) 
//			{
//				swr_convert(au_convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pFrame->data, pFrame->nb_samples);
//
//				printf("index:%5d\t pts:%lld\t packet size:%d   nb_samples:%d\n", index, packet->pts, packet->size, pFrame->nb_samples);
//
//				index++;
//			}
//
//
//			while (audio_len > 0)//Wait until finish
//				SDL_Delay(1);
//
//			//Set audio buffer (PCM data)
//			audio_chunk = (Uint8 *)out_buffer;
//			//Audio buffer length
//			audio_len = out_buffer_size;
//			audio_pos = audio_chunk;
//
//			//Play
//			SDL_PauseAudio(0);
//			//while (audio_len > 0)//Wait until finish
//			//	SDL_Delay(1);
//		}
//		av_free_packet(packet);
//	}
//
//	swr_free(&au_convert_ctx);
//
//
//	SDL_CloseAudio();//Close SDL
//	SDL_Quit();
//
//	av_free(out_buffer);
//	// Close the codec
//	avcodec_close(pCodecCtx);
//	// Close the video file
//	avformat_close_input(&pFormatCtx);
//
//
//
//
//
//
//
//
//
//}


int ss()
{
	AVFormatContext	*pFormatCtx;
	int				i, audioStream;
	AVCodecContext	*pCodecCtx;
	AVCodec			*pCodec;
	AVPacket		*packet;
	uint8_t			*out_buffer;
	AVFrame			*pFrame;
	SDL_AudioSpec wanted_spec;
	int ret;
	uint32_t len = 0;
	int got_picture;
	int index = 0;
	int64_t in_channel_layout;
	struct SwrContext *au_convert_ctx;

	FILE *pFile = NULL;
	char url[] = "11.rmvb";
	//char url[] = "Friends.mkv";
	//
	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();
	//Open
	if (avformat_open_input(&pFormatCtx, url, NULL, NULL) != 0) {
		printf("Couldn't open input stream.\n");
		return -1;
	}
	// Retrieve stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		printf("Couldn't find stream information.\n");
		return -1;
	}
	// Dump valid information onto standard error
	av_dump_format(pFormatCtx, 0, url, false);

	// Find the first audio stream
	audioStream = -1;
	for (i = 0; i < pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStream = i;
			break;
		}

	if (audioStream == -1) {
		printf("Didn't find a audio stream.\n");
		return -1;
	}

	// Get a pointer to the codec context for the audio stream
	pCodecCtx = pFormatCtx->streams[audioStream]->codec;

	// Find the decoder for the audio stream
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) {
		printf("Codec not found.\n");
		return -1;
	}

	// Open codec
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec.\n");
		return -1;
	}




	packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	av_init_packet(packet);

	//Out Audio Param
	uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
	//nb_samples: AAC-1024 MP3-1152
	int out_nb_samples = pCodecCtx->frame_size;
	AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
	int out_sample_rate = 44100;
	int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
	//Out Buffer Size
	int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);

	out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
	pFrame = av_frame_alloc();
	//SDL------------------

	//Init
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return -1;
	}
	//SDL_AudioSpec
	wanted_spec.freq = out_sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = out_channels;
	wanted_spec.silence = 0;
	wanted_spec.samples = out_nb_samples;
	wanted_spec.callback = fill_audio;
	wanted_spec.userdata = pCodecCtx;

	if (SDL_OpenAudio(&wanted_spec, NULL) < 0) {
		printf("can't open audio.\n");
		return -1;
	}


	//FIX:Some Codec's Context Information is missing
	in_channel_layout = av_get_default_channel_layout(pCodecCtx->channels);
	//Swr

	au_convert_ctx = swr_alloc();
	au_convert_ctx = swr_alloc_set_opts(au_convert_ctx, out_channel_layout, out_sample_fmt, out_sample_rate,
		in_channel_layout, pCodecCtx->sample_fmt, pCodecCtx->sample_rate, 0, NULL);
	swr_init(au_convert_ctx);

	while (av_read_frame(pFormatCtx, packet) >= 0) {
		if (packet->stream_index == audioStream) {
			ret = avcodec_decode_audio4(pCodecCtx, pFrame, &got_picture, packet);
			if (ret < 0) {
				printf("Error in decoding audio frame.\n");
				return -1;
			}
			if (got_picture > 0) {
				swr_convert(au_convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pFrame->data, pFrame->nb_samples);
				printf("index:%5d\t pts:%lld\t packet size:%d   nb_samples:%d\n", index, packet->pts, packet->size, pFrame->nb_samples);




				index++;
			}


			while (audio_len > 0)//Wait until finish
				SDL_Delay(1);

			//Set audio buffer (PCM data)
			audio_chunk = (Uint8 *)out_buffer;
			//Audio buffer length
			audio_len = out_buffer_size;
			audio_pos = audio_chunk;

			//Play
			SDL_PauseAudio(0);

		}
		av_free_packet(packet);
	}

	swr_free(&au_convert_ctx);


	SDL_CloseAudio();//Close SDL
	SDL_Quit();


	av_free(out_buffer);
	// Close the codec
	avcodec_close(pCodecCtx);
	// Close the video file
	avformat_close_input(&pFormatCtx);

}
