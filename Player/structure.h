
#ifndef STRUCTURE_H
#define STRUCTURE_H
#pragma once
#include "stdafx.h"
#include <basetsd.h>


typedef struct _MEDIA_HEADER_NEW
{
	UINT32 uPacketType; //包类型
	UINT32 uPacketLen; //包长度
	UINT32 uHeader;    //头标记
	UINT32 uVersion;     //版本号
	UINT32 uSize;			//数据长度
	UINT32 uType;			//数据包类型，0: 控制命令，1:数据流
	UINT32 uStreamID;		//数据流ID，
	UINT32 uTimeStamp;	//时间戳
} MEDIA_HEADER_NEW, *PMEDIA_HEADER_NEW;

typedef struct _Rect
{
	_Rect(UINT16 w,UINT16	h)
		:width(w)
		,height(h)
	{}
	_Rect() {}

	UINT16	width;
	UINT16	height;
}Rect, *PRect;

#endif