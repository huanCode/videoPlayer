#ifndef CAMERAREMOTE_H
#define CAMERAREMOTE_H
#include <memory>
#include <functional>
#include "TCPClient.h"
#include "structure.h"
#include "DecodecVideoModule.h"
#include "StreamHandle.h"
#define PACKETTYPE 0x7FFA0000
#define INFOSTREAMSIZE 23
class CameraRemote
{
public:
	CameraRemote(UINT16 width, UINT16 height);
	CameraRemote();
	void createReadThread(string strIP, unsigned int port, std::function<void(const uint8_t*,UINT32)> display);

	struct StreamPacket
	{
		
		vector<uint8_t>				oneFrameBuffer;
	};

	UINT16 getWidth();
	UINT16 getheight();

private:
	void readFrame(vector<uint8_t> &buffer, UINT32 &bufferSize);

	Rect getRectByStream(unsigned char* chs);
private:

	//const	UINT32				PACKETTYPE = 0x7FFA0000;
	asio::io_service			m_io_service;
	Rect						m_rect;
	//UINT32						m_frameSize = m_rect.width * m_rect.height;
	//StreamPacket				m_streamPacket = { vector<MEDIA_HEADER_NEW>(1),vector<uint8_t>(10240)};
	UINT32						m_headerSize = sizeof(MEDIA_HEADER_NEW);
	std::unique_ptr<TCPClient>	m_tcp_client;
	//DecodecVideoModule			m_decodecHandle;
	std::unique_ptr<DecodecVideoModule>	m_pDecodecHandle;



	vector<MEDIA_HEADER_NEW>	m_packetHeader = vector<MEDIA_HEADER_NEW>(1);
	vector<uint8_t>				m_packetBuffer = vector<uint8_t>(10240);


	int							m_frameSize = 0;
};

#endif

