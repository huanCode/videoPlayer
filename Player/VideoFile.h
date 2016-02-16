#ifndef VIDEOFILE_H
#define VIDEOFILE_H
#include <string>
using namespace std;
extern "C"
{
#include "libavformat/avformat.h"
};


class VideoFile
{
public:
	
	VideoFile(string strFilePath);
	~VideoFile();

	bool Init();


	void sendFrame();

	int	GetVideoStreamID();
	int GetAudioStreamID();

	AVPacket* readFrame();

private:

	int GetStreamID(AVMediaType streamType);

private:
	int					m_videoIndex = 0;
	int					m_audioIndex = 0;
	bool				m_bStopSendFrame = true;
	AVFormatContext		*m_pFormatCtx;
	AVPacket			*m_packet;
	AVFrame				*m_pFrame;	//负责生产，不负责销毁
	string				m_strFilePath;
};




#endif