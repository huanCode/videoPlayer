#include "stdafx.h"
#include <iostream>
#include "CameraRemote.hpp"
using namespace std;
CameraRemote::CameraRemote(UINT16 width, UINT16 height)
	:m_rect(width, height)

{

}

CameraRemote::CameraRemote()
	:m_rect(0, 0)

{

}


UINT16 CameraRemote::getWidth()
{
	return m_rect.width;
}
UINT16 CameraRemote::getheight()
{
	return m_rect.height;
}


void CameraRemote::createReadThread(string strIP, unsigned int port, std::function<void(const uint8_t*, UINT32)> display)
{
	TCPClient *pTCPClient = new TCPClient(m_io_service, strIP, port);
	m_tcp_client.reset(pTCPClient);
	if (!m_tcp_client->connect())
	{
		cout << m_tcp_client->GetIP()<<":"<< m_tcp_client->GetPort()<<"连接失败！" << endl;
		return;
	}



	UINT32				bufferSize = 0;
	while (true)
	{
		readFrame(m_packetBuffer, bufferSize);

		if (bufferSize > INFOSTREAMSIZE)
		{
			const uint8_t* pBuffer = m_pDecodecHandle->decode(&m_packetBuffer[0], bufferSize);
			display(pBuffer, m_frameSize);
		}
		else if(bufferSize == INFOSTREAMSIZE)
		{
			//初始化，只执行一次
			
			m_rect = getRectByStream(&m_packetBuffer[0]);
			m_pDecodecHandle.reset(new DecodecVideoModule(m_rect));

			m_frameSize = m_pDecodecHandle->getFrameSize();

			m_pDecodecHandle->decode(&m_packetBuffer[0], bufferSize);
		}

	}


}

Rect CameraRemote::getRectByStream(unsigned char* chs)
{
	Rect rect;
	StreamHandle s;
	s.handle(chs);
	rect.width = s.getWidth();
	rect.height = s.getHeight();

	return rect;
}

void CameraRemote::readFrame(vector<uint8_t> &buffer, UINT32 &bufferSize)
{
	//读头
	m_tcp_client->read(m_packetHeader);
	

	if (m_packetHeader[0].uPacketType != PACKETTYPE)
	{
		cout << "revice packet header is error！" << endl;
		return;
	}

	//读packet
	
	bufferSize = m_packetHeader[0].uSize;
	cout << "uSize:" << bufferSize << endl;
	if (buffer.size() < bufferSize)
	{
		buffer.resize(bufferSize+4);	//扩大,切记
	}

	m_tcp_client->read(buffer, bufferSize+4);
}


