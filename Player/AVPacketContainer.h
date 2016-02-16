#ifndef AVPACKETCONTAINER
#define AVPACKETCONTAINER
extern "C"
{
#include "libavformat/avformat.h"
};
class AVPacketContainer
{
public:
	AVPacketContainer();
	~AVPacketContainer();
	static AVPacket* createAVPacket();
	static void freePacket(AVPacket* packet);
private:
	AVPacket	*m_pPacket;
};

AVPacketContainer::AVPacketContainer()
{
}

AVPacketContainer::~AVPacketContainer()
{
}


AVPacket* AVPacketContainer::createAVPacket()
{
	return (AVPacket *)av_malloc(sizeof(AVPacket));
}


void AVPacketContainer::freePacket(AVPacket* packet)
{
	av_free_packet(packet);
}

#endif
