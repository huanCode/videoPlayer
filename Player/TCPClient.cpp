#include "stdafx.h"
#include "TCPClient.h"

TCPClient::TCPClient(asio::io_service& io_service, string &strIP, UINT32 port)
	:m_endpoint(ip::address::from_string(strIP.c_str()), port)
	, m_io_service(io_service)
	, m_client(m_io_service)
{
	
		

}

bool TCPClient::connect()
{
	boost::system::error_code error;
	m_client.connect(m_endpoint, error);
	return error ? false : true;
}

UINT32 TCPClient::GetPort()
{
	return m_endpoint.port();
}

std::string TCPClient::GetIP()
{
	return m_endpoint.address().to_string();
}

template<typename T>
bool TCPClient::read(const vector<T> &buffers,UINT32 readLength)
{
	boost::system::error_code error;
	asio::read(m_client, asio::buffer(buffers), asio::transfer_exactly(readLength), error);
	return error ? false : true;
}
//
//template<typename T>
//bool TCPClient::read(vector<T> &buffers)
//{
//	boost::system::error_code error;
//	asio::read(m_client, asio::buffer(buffers),error);
//	return error ? false : true;
//}
