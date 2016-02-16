#ifndef SOURCEFILE_HPP
#define SOURCEFILE_HPP
#include <string>
using namespace std;
extern "C"
{
#include "libavformat/avformat.h"   
};
class SourceFile 
{
public:
	SourceFile(string strFilePath);
	void InitSourceFile();

private:
	int	GetVideoStreamID();
	int GetAudioStreamID();
	int GetStreamID(AVMediaType streamType);
private:
	string				m_strFilePath;
	AVFormatContext		*m_pFormatContext;
};


#endif