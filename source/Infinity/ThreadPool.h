#pragma once

#include "ThreadConditionVariable.h"
#include "CpuDuration.h"
#include <list>
#include <thread>
#include <bitset>

namespace Infinity
{
	template<class Worker>
	class ThreadPool {
		friend Worker;
		std::list<std::thread> mWorkers;
		ThreadConditionVariable mWorkersCondition;
		ThreadConditionVariable mCondition;
		std::mutex mWaitMutex;
		std::chrono::milliseconds mRunDuration;
		enum STATUS {
			STATUS_STOP,
			STATUS_MAX
		};
		std::bitset<STATUS_MAX> mStatus;
	public:
		ThreadPool(size_t threadnum,typename Worker::TickFunc func,typename Worker::ArgmentType &arg);
		~ThreadPool( );
		void Run();
		void Destroy();
	};

	template<class Worker>
	ThreadPool<Worker>::ThreadPool(size_t threadnum,typename Worker::TickFunc func,typename Worker::ArgmentType &arg) {
		for( size_t i = 0 ; i < threadnum ; ++ i ) {
			mWorkers.push_back(std::thread(Worker(i,*this,func,arg)));
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	template<class Worker>
	ThreadPool<Worker>::~ThreadPool( )
	{ }

	template<class Worker>
	void ThreadPool<Worker>::Run() {
		CpuDuration duration;
		this->mWorkersCondition.NotifyAll();
		while(!this->mWorkersCondition.IsWait()) {
			std::this_thread::yield();
		}
		duration.GetDuration(mRunDuration);
	}

	template<class Worker>
	void ThreadPool<Worker>::Destroy() {
		{
			std::mutex mtx;
			std::lock_guard<std::mutex> lock(mtx);
			mStatus[STATUS_STOP] = 1;
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));

		mWorkersCondition.NotifyAll();
		for( auto &the : mWorkers ) {
			the.join();
		}

	}

}
