#ifndef BUFFERARRAY_H
#define BUFFERARRAY_H
#include <vector>
#include <list>
#include <basetsd.h>
#include <iostream>
//#include <mutex>

using namespace std;
//using namespace boost;


typedef struct _Node
{
	typedef vector<uint8_t> Buffer;
	_Node(UINT32 bufferSize) 
		:bufferArray(bufferSize)
		, prev(this)
		, next(this)
	{}
	Buffer			bufferArray;
	_Node			*prev;
	_Node			*next;

}Node,*PNode;



class BufferArray
{
public:
	BufferArray(UINT32	maxBufferArray, UINT32	minBufferArray, UINT32	alloctSize, UINT32 bufferSize);
	~BufferArray();

	bool pop(vector<uint8_t> &out_buffer);
	bool push(vector<uint8_t> &in_buffer);
	bool empty();
	bool full();
	
	void createList(PNode headNode, PNode tailNode);	//创建链表，单没形成循环
	void createDBList();	//创建双向循环链表
	bool extendDBList();	//扩展m_alloctSize个双向循环链表
	
private:
	void InitBufferArray();
private:
	UINT32		m_maxBufferArray;	//最大的缓存区数量
	UINT32		m_minBufferArray;	//最小的缓存区数量
	UINT32		m_alloctSize;		//每次超出缓存区大小时，自动增加的大小
	UINT32		m_nousedCount;
	UINT32		m_bufferSize;
public:
	PNode		m_pHead = nullptr;
	PNode		m_pTail = nullptr;
	//PNode		m_pTail = nullptr;
	bool		m_success = true;


	
};




#endif
