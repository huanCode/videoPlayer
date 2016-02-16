
#ifndef STRUCTURE_H
#define STRUCTURE_H
#pragma once
#include "stdafx.h"
#include <basetsd.h>


typedef struct _MEDIA_HEADER_NEW
{
	UINT32 uPacketType; //������
	UINT32 uPacketLen; //������
	UINT32 uHeader;    //ͷ���
	UINT32 uVersion;     //�汾��
	UINT32 uSize;			//���ݳ���
	UINT32 uType;			//���ݰ����ͣ�0: �������1:������
	UINT32 uStreamID;		//������ID��
	UINT32 uTimeStamp;	//ʱ���
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