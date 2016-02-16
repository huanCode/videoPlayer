#include "stdafx.h"
#include "SourceFile.hpp"

SourceFile::SourceFile(string strFilePath)
	:m_strFilePath(strFilePath)
{

}

void SourceFile::InitSourceFile()
{
	av_register_all();

	//
	if (avformat_open_input(&m_pFormatContext, m_strFilePath.c_str(), NULL, NULL) != 0) {
		printf("Couldn't open input stream.\n");
		return;
	}

	if (avformat_find_stream_info(m_pFormatContext, NULL) < 0) {
		printf("Couldn't find stream information.\n");
		return;
	}

}

int SourceFile::GetVideoStreamID()
{
	return GetStreamID(AVMEDIA_TYPE_VIDEO);
}

int SourceFile::GetAudioStreamID()
{
	return GetStreamID(AVMEDIA_TYPE_AUDIO);
}

int SourceFile::GetStreamID(AVMediaType streamType)
{
	int videoindex = -1;
	for (int i = 0; i < m_pFormatContext->nb_streams; i++)
	{
		if (m_pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoindex = i;
			break;
		}

	}

	if (videoindex == -1) {
		printf("Didn't find a stream.\n");
	}
	return videoindex;
		
}

