#pragma once

#include <bitset>
#include <condition_variable>

namespace Infinity
{
	class ThreadConditionVariable : std::condition_variable
	{
		enum STATUS {
			STATUS_WAIT,
			STATUS_MAX
		};
		std::bitset<STATUS_MAX> mStatus;
		std::mutex mWaitMutex;
	public:
		bool IsWait( );
		void Wait();
		void NotifyAll();
	};

	bool ThreadConditionVariable::IsWait() {
		std::lock_guard<std::mutex> lock(mWaitMutex);
		return mStatus[STATUS_WAIT];
	}

	void ThreadConditionVariable::Wait() {
		std::unique_lock<std::mutex> lock(mWaitMutex);
		mStatus[STATUS_WAIT] = 1;
		wait(lock);
	}

	void ThreadConditionVariable::NotifyAll() {
		mStatus[STATUS_WAIT] = 0;
		notify_all();
	}

}