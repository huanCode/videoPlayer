#ifndef ISourceVideo_H
#define ISourceVideo_H
#pragma once
#include <string>
using namespace std;
class ISourceVideo
{
public:
	ISourceVideo() {};
	~ISourceVideo() {};

	 virtual void  receiveVideo(string strIP,unsigned int port) = 0;

};



#endif


