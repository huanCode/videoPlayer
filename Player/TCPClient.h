#pragma once
#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include "stdafx.h"
#include <string>
#include <vector>
#include "boost/asio.hpp"

using namespace std;
using namespace boost;
using namespace asio;
using namespace ip;

class TCPClient
{
public:
	TCPClient(asio::io_service& io_service,string &strIP,UINT32 port);
	~TCPClient() {};

	bool connect();
	UINT32 GetPort();
	string GetIP();

	template<typename T>
	bool read(const vector<T> &buffers, UINT32 readLength);

	template<typename T>
	bool read(vector<T> &buffers)
	{
		boost::system::error_code error;
		int i = asio::read(m_client, asio::buffer(buffers), error);
		return error ? false : true;
	}

	template<typename T>
	bool read(vector<T> &buffers, UINT32 bufSize)
	{
		boost::system::error_code error;
		int i = asio::read(m_client, asio::buffer(buffers), boost::asio::transfer_exactly(bufSize), error);
		return error ? false : true;
	}
private:
	asio::io_service& m_io_service;
	tcp::socket				m_client;
	tcp::endpoint			m_endpoint;
};



#endif