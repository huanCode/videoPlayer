#include "stdafx.h"
#include "queue_thread.hpp"

queue_thread::queue_thread()
//:m_maxBufferSize(maxBufferSize)
{
}

queue_thread::~queue_thread()
{
	//clear_thread();
}

//bool queue_thread::push_thread(vector<uint8_t>* buffer)
//{
//	std::lock_guard<std::mutex> lock(m_mutex);
//	if (m_maxBufferSize == m_queue.size())
//	{
//		printf("达到队列最大限制.\n");
//		return false;
//	}
//
//	m_queue.push(buffer);
//}
//
//bool queue_thread::pop_thread(vector<uint8_t>* buffer)
//{
//	std::lock_guard<std::mutex> lock(m_mutex);
//	if (m_queue.empty())
//	{
//		buffer = nullptr;
//		return false;
//	}
//
//	buffer = m_queue.front();
//	m_queue.pop();
//	return true;
//}
//
//void queue_thread::clear_thread()
//{
//	std::lock_guard<std::mutex> lock(m_mutex);
//	vector<uint8_t>* temp = nullptr;
//	while (!m_queue.empty())
//	{
//		temp = m_queue.front();
//		delete temp;
//	}
//}
