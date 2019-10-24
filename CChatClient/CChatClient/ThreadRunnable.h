
/*
 * Runnable.h
 * Implementation of non static member inside thread method
 */

#ifndef __THREADRUNNABLE_H__
#define __THREADRUNNABLE_H__

class CThreadRunnable
{
public:
	CThreadRunnable(){}
	virtual ~CThreadRunnable(){};
	static void run_thread(void *args)
	{
		CThreadRunnable *pRunnable = static_cast<CThreadRunnable*>(args);
		int actual_arg = (int)args;
		pRunnable->run(actual_arg);
	}

protected:
	virtual void run(int actual_arg) = 0;
};


#endif // __THREADRUNNABLE_H__