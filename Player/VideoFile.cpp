#include "stdafx.h"
#include "VideoFile.h"


bool VideoFile::Init()
{
	m_pFormatCtx = avformat_alloc_context();
	if (m_pFormatCtx)
	{
		return false;
	}

	if (avformat_open_input(&m_pFormatCtx, m_strFilePath.data(), NULL, NULL) != 0) {
		printf("Couldn't open input stream.\n");
		return false;
	}

	if (avformat_find_stream_info(m_pFormatCtx, NULL) < 0) {
		printf("Couldn't find stream information.\n");
		return false;
	}

	return true;
}

void VideoFile::sendFrame()
{
	int	videoIndex = GetVideoStreamID();
	int	audioIndex = GetAudioStreamID();

	AVPacket *packet = nullptr;
	while (m_bStopSendFrame)
	{
		if (av_read_frame(m_pFormatCtx, packet) >= 0)
		{

			if (packet->stream_index == videoIndex)
			{
				//if (d.decode(m_pFormatCtx->streams[videoindex]->codec, packet, pFrame))
				//{
				//	frameOperation.scale(pFrame, dstFrame.get());
				//	gui.displayVideo(dstFrame.get());
				//}
			}
			else if (packet->stream_index == audioIndex)
			{
			}
			else
			{
			}
			
		}
	}

}

VideoFile::VideoFile(string strFilePath)
	:m_strFilePath(strFilePath)
{
}

VideoFile::~VideoFile()
{
}

int VideoFile::GetVideoStreamID()
{
	return GetStreamID(AVMEDIA_TYPE_VIDEO);
}

int VideoFile::GetAudioStreamID()
{
	return GetStreamID(AVMEDIA_TYPE_AUDIO);
}

AVPacket* VideoFile::readFrame()
{
	AVPacket *packet = nullptr;

	if (av_read_frame(m_pFormatCtx, packet) >= 0)
	{
		return packet;
	}
	packet = nullptr;
	return packet;
}

int VideoFile::GetStreamID(AVMediaType streamType)
{
	int index = -1;
	for (int i = 0; i < m_pFormatCtx->nb_streams; i++)
	{
		if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			index = i;
			break;
		}

	}

	if (index == -1) {
		printf("Didn't find a stream.\n");
	}
	return index;

}