#include "stdafx.h"
#include "BufferArray.hpp"


BufferArray::BufferArray(UINT32	maxBufferArray, UINT32	minBufferArray, UINT32	alloctSize, UINT32 bufferSize)
	:m_maxBufferArray(maxBufferArray)
	,m_minBufferArray(minBufferArray)
	,m_alloctSize(alloctSize)
	,m_bufferSize(bufferSize)
	,m_nousedCount(minBufferArray)
{
	InitBufferArray();
}

BufferArray::~BufferArray()
{
}




void BufferArray::InitBufferArray()
{
	//验证
	if (!(m_maxBufferArray >= m_minBufferArray))
	{
		m_success = false;
		cout << "BufferArray alloct is error!" << endl;
		return;
	}

	if (m_alloctSize ==0 && m_bufferSize==0)
	{
		m_success = false;
		cout << "BufferArray alloct is error!" << endl;
		return;
	}

	//createDBList(m_pHead, m_pTail);

}

bool BufferArray::pop(vector<uint8_t> &out_buffer)
{
	if (empty())
	{
		return false;
	}


}


bool BufferArray::push(vector<uint8_t> &in_buffer)
{
	if (m_maxBufferArray == m_minBufferArray)
	{
		return false;
	}

	if (full())
	{
		//extendList();
	}
	return false;
}

bool BufferArray::empty()
{

	if (m_nousedCount)
	{
		return false;	//有数据
	}

	return true;	//空
}

bool BufferArray::full()
{
	return !empty();
}

//bool BufferArray::extendList()
//{
//	PNode beginNode = nullptr;
//	PNode currentNode = nullptr;
//	PNode markNode = nullptr;
//	for (int i = 0; i < m_alloctSize; i++)
//	{
//		if (currentNode)
//		{
//			markNode = new Node(m_bufferSize);
//			currentNode->next = markNode;
//			markNode->prev = currentNode;
//
//			currentNode = markNode;
//
//		}
//		else
//		{
//			//第一个节点
//			beginNode = currentNode = new Node(m_bufferSize);
//
//		}
//
//		cout << currentNode << endl;
//	}
//
//
//	//首尾相连
//	beginNode->prev = currentNode;
//	currentNode->next = beginNode;
//
//	//m_pHead = m_pTail = currentNode;
//}

void BufferArray::createList(PNode headNode, PNode tailNode)
{

	PNode newNode = nullptr;
	//PNode markNode = nullptr;
	for (int i = 0; i < m_alloctSize; i++)
	{
		if (headNode)
		{
			newNode = new Node(m_bufferSize);
			headNode->next = newNode;
			newNode->prev  = headNode;

			headNode = newNode;

		}
		else
		{
			//第一个节点
			headNode = tailNode = new Node(m_bufferSize);

		}
	}
}

void BufferArray::createDBList()
{


	createList(m_pHead, m_pTail);

	m_pHead->prev = m_pTail;
	m_pTail->next = m_pHead;

	m_pHead = m_pTail;
}

//bool BufferArray::extendDBList()
//{
//	PNode pTail = nullptr;
//	PNode currentNode = nullptr;
//	//createList(beginNode, currentNode);
//
//	//m_pTail->next = beginNode;
//	//beginNode->prev = m_pTail;
//
//	//m_pHead->prev = currentNode;
//
//	return false;
//}
