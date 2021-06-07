/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __DISPATCH_QUEUE_H__
#define __DISPATCH_QUEUE_H__

#include "thread.h"

#include <deque>

template <typename V> class function;

class dispatch_queue : public thread {
private:
	std::deque<function<void>*> _queue;
	thread_mutex _mutex;
	
public:
	dispatch_queue* _self;
	
private:
	static void * create_detached(void* arg)
	{
		function<void>* f = static_cast<function<void>*> (arg);
		if (f)
		{
			(*f)();
		}
		
		return nullptr;
	}
	
public:
	dispatch_queue()
	{
		_self = this;
		
		/**
		 * start thread
		 */
		start();
	}

	~dispatch_queue()
	{
		//TRACEF();
		
		// stop thread
		_self = nullptr;
		
		
		/**
		 * clear queue
		 */
		_mutex.lock();
		
		while (!_queue.empty())
		{
			function<void>* f = _queue.front();
			_queue.pop_front();
			
			delete f;
		}
		
		_mutex.unlock();
	}
	
	void async(function<void>* f)
	{
#if 0
		// TODO: fix me!!! memory leak
#if defined (_WIN32)
		DWORD threadId;
		
		HANDLE thread = CreateThread(
																 NULL,
																 0,
																 (LPTHREAD_START_ROUTINE) create_detached,
																 (void*) f,
																 0,
																 &threadId);
		
		CloseHandle(thread);
		
#else
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		
		pthread_t thread;
		pthread_create(&thread, &attr, create_detached, (void*) f);
		
		pthread_attr_destroy(&attr);
#endif
#endif
		
		(*f)();
		
		//???
		delete f;
	}
	
	void sync(function<void>* f)
	{
		_mutex.lock();
		
		_queue.push_back(f);
		
		_mutex.unlock();
	}
	
	void flush()
	{
		//TRACEC();
		
		/**
		 * clear queue
		 */
		while (!_queue.empty())
		{
			_mutex.lock();

			function<void>* f = _queue.front();
			_queue.pop_front();
			
			_mutex.unlock();

			
			/**
			 *
			 */
			(*f)();
			
			delete f;
		}
	}
	
protected:
	void run()
	{
		
		// TODO: fixme!!!
		while (1)
		{
			/// ???
			if (!_queue.empty())
			{
				_mutex.lock();
				
				function<void>* f = _queue.front();
				_queue.pop_front();
				
				_mutex.unlock();
				
				/**
				 *
				 */
				(*f)();
				
				delete f;
			}
			else
			{
				sleep(1);
			}
			
			
			/**
			 *
			 */
			if (_self == nullptr)
			{
				quit();
				break;
			}
		}
	}
};

#define DISPATCH_QUEUE_FUNCTION(target, method) function<void>(this, &target::method)

#endif //__DISPATCH_QUEUE_H__