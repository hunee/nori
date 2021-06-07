/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __THREAD_H__
#define __THREAD_H__

#include "function.h"

#if defined (WIN32)
#else
#include <pthread.h>
#include <semaphore.h>

#include <unistd.h>
#endif



/**
 * thread_mutex
 */
class thread_mutex {
#if defined (WIN32)
	HANDLE _mutex;
#else
	pthread_mutex_t _mutex;
#endif
	

public:
	thread_mutex()
	{
#if defined (WIN32)
		_mutex = CreateMutex(
												 NULL,              // default security attributes
												 FALSE,             // initially not owned
												 NULL);             // unnamed mutex
#else
		pthread_mutex_init(&_mutex, NULL);
#endif
	}
	~thread_mutex()
	{
#if defined (WIN32)
		CloseHandle(_mutex);
#else
		pthread_mutex_destroy(&_mutex);
#endif
	}

public:
	void lock()
	{
#if defined (WIN32)
		WaitForSingleObject(_mutex, INFINITE);
#else
		pthread_mutex_lock(&_mutex);
#endif
	}
	void trylock()
	{
#if defined (WIN32)
		WaitForSingleObject(_mutex, INFINITE);
#else
		pthread_mutex_trylock(&_mutex);
#endif
	}
	void unlock()
	{
#if defined (WIN32)
		ReleaseMutex(_mutex);
#else
		pthread_mutex_unlock(&_mutex);
#endif
	}
};


/**
 * thread_cond
 */
class thread_cond {
#if defined (WIN32)
#else
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
#endif
	
public:
	thread_cond(thread_mutex * mutex)
	{
#if defined (WIN32)
#else
		pthread_mutex_init(&_mutex, NULL);
		pthread_cond_init(&_cond, NULL);
#endif
	}
	~thread_cond()
	{
#if defined (WIN32)
#else
		pthread_cond_destroy(&_cond);
#endif
	}
	
public:
	void wait()
	{
#if defined (WIN32)
#else
		pthread_cond_wait(&_cond, &_mutex);
#endif
	}
	void signal()
	{
#if defined (WIN32)
#else
		pthread_cond_signal(&_cond);
#endif
	}
	void broadcast()
	{
#if defined (WIN32)
#else
		pthread_cond_broadcast(&_cond);
#endif
	}
	
	void lock()
	{
#if defined (WIN32)
#else
		pthread_mutex_lock(&_mutex);
#endif
	}
	void unlock()
	{
#if defined (WIN32)
#else
		pthread_mutex_unlock(&_mutex);
#endif
	}
	
	/*
	 thread A()
	 {
	 lock();
	 
	 ...;
	 
	 signal();
	 unlock();
	 }
	 
	 threadB()
	 {
	 lock();
	 wait();
	 
	 ...;
	 
	 unlock();
	 }
	 */
	
};


/**
 * semaphore
 */
class semaphore {
#if defined (WIN32)
#else
	sem_t _semaphore;
#endif
	
public:
	semaphore(int pshared = 0)
	{
#if defined (WIN32)
#else
		sem_init(&_semaphore, (pshared >= SEM_VALUE_MAX) ? SEM_VALUE_MAX : pshared, 0);
#endif
	}
	~semaphore()
	{
#if defined (WIN32)
#else
		sem_destroy(&_semaphore);
#endif
	}
	
public:
	void post()
	{
#if defined (WIN32)
#else
		sem_post(&_semaphore);
#endif
	}
	void wait()
	{
#if defined (WIN32)
#else
		sem_wait(&_semaphore);
#endif
	}
	
	int getvalue()
	{
		int value;
#if defined (WIN32)
#else
		sem_getvalue(&_semaphore, &value);
#endif
		
		return value;
	}
};


/**
 * thread
 */
class thread {
#if defined (WIN32)
	HANDLE _thread;
#else
	pthread_t _thread;
#endif
	
private:
	static void* thread_proc(void * arg)
	{
		thread* self = static_cast<thread*> (arg);
		if (self)
			self->run();
		
		return NULL;
	}
	static void* thread_proc_detached(void* arg)
	{
		function<void>* f = static_cast<function<void>*> (arg);
		if (f)
			(*f)();
		
		return NULL;
	}
	
public:
	thread()
	: _thread(0)
	{
	}
	virtual ~thread()
	{
		//TRACEF();
		
#if defined (WIN32)
		::Sleep(2);

		DWORD exitCode;
    GetExitCodeThread(_thread, &exitCode);
		TerminateThread(_thread, exitCode);
		
		WaitForSingleObject(_thread, INFINITE);
		CloseHandle(_thread);
#else
		pthread_join(_thread, NULL);
#endif
		
		_thread = 0;
	}
	
public:
	int start(function<void>* f = NULL)
	{
		//TRACEC();
		
#if defined (WIN32)
		DWORD threadId;
		
		if (f)
		{
			_thread = CreateThread(
														 NULL,
														 0,
														 (LPTHREAD_START_ROUTINE) thread_proc_detached,
														 (void *) f,
														 0,
														 &threadId);
			
			CloseHandle(_thread);
		}
		else
		{
			_thread = CreateThread(
														 NULL,
														 0,
														 (LPTHREAD_START_ROUTINE) thread_proc,
														 (void *) this,
														 0,
														 &threadId);
		}
#else
		///
		pthread_attr_t attr;
		
		pthread_attr_init(&attr);
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
		
		if (f)
		{
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
			pthread_create(&_thread, &attr, thread::thread_proc_detached, f);
		}
		else
		{
			pthread_create(&_thread, &attr, thread::thread_proc, this);
		}
		
		pthread_attr_destroy(&attr);
#endif
		
		return TRUE;
	}
	void quit()
	{
#if defined (WIN32)
		::Sleep(2);		
#else
		pthread_exit(NULL);
		
		::usleep(10);
#endif
	}
	
	unsigned int sleep(unsigned int seconds)
	{
#if defined (WIN32)
		::Sleep(seconds);
		return 0;
#else
		return ::usleep(seconds*10000);
#endif
		
	}
protected:
	virtual void run() =0;
	/*	{
	 //TRACEF();
	 
	 while (1)
	 {
	 //_mutex.lock();
	 
	 //_mutex.unlock();
	 
	 //			if (_self == NULL)
	 {
	 quit();
	 break;
	 }
	 }
	 }*/
};


/**
 * mutex_lock
 */
class mutex_lock {
	thread_mutex* _mutex;
	
public:
	mutex_lock(thread_mutex* mutex)
	: _mutex(mutex)
	{
		_mutex->lock();
	}
	~mutex_lock()
	{
		_mutex->unlock();
	}
};

#endif //__THREAD_H__
